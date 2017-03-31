// moflexconv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <regex>
#include "windows.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

// replace '\' with "\\"
void ReplaceChar(const char * pSrc, char * pDest)
{
	size_t j = 0;
	for (size_t i = 0; i < strlen(pSrc); ++i)
	{
		pDest[j] = pSrc[i];
		if (pSrc[i] == '\\')
		{
			++j;
			if (j < 255) pDest[j] = '\\';
		}
		++j;
	}
	if (j < 255) pDest[j] = 0;
}

void RegexReplaceText(const char * lpszRegexText, const char * szRegexBuf, string & strQueueFile)
{
	regex inputfile(lpszRegexText);
	char szTmpBuf[255];
	strcpy_s(szTmpBuf, szRegexBuf);
	ReplaceChar(szRegexBuf, szTmpBuf);
	strQueueFile = regex_replace(strQueueFile, inputfile, szTmpBuf);
}

int wmain(int argc, wchar_t * argv[])
{
	// remove cache file
	wstring strAppPath = _wgetenv(L"APPDATA");
	wstring strMMEPath = _wgetenv(L"MOBICLIP_MULTICORE_ENCODER_PATH");
	if (strMMEPath.empty())
	{
		wcout << L"MME not installed or need repair" << endl;
		return 0xff;
	}
	strAppPath += LR"(Roaming\Mobiclip\Mobiclip Encoding Tool\MobiclipEncodingTool.options)";
	DeleteFile(strAppPath.c_str());

	wstring strQueue;
	wstring strInputFile;
	string strQueueFile;
	if (argc < 2)
	{
		wcout << L"Invalid parameters" << endl;
		return 1;
	}
	if (wcscmp(argv[1], L"-q") == 0)
	{
		if (argc < 4)
		{
			wcout << L"Invalid parameters" << endl;
			return 1;
		}
		
		strQueue = argv[2];
		strInputFile = argv[3];
	}
	else
	{
		strInputFile = argv[1];
	}

	if (strQueue.empty())
	{
		strQueueFile = str2DTemplate;
	}
	else
	{
		ifstream queueFile(strQueue);
		if (queueFile.fail())
		{
			wcout << L"Invalid queue file" << endl;
			return 3;
		}

		// read file content to string
		stringstream strStream;
		strStream << queueFile.rdbuf();

		strQueueFile = strStream.str();
	}


	if (strQueueFile.empty())
	{
		wcout << L"Invalid queue file" << endl;
		return 3;
	}
	if (strQueueFile.find(R"("MobiclipEncoder")") == strQueueFile.npos)
	{
		wcout << L"Not supported, only used to convert to moflex format" << endl;
		return 4;
	}

	// regex replace to replace input file with old ones
	wchar_t szInputFileNameFull[MAX_PATH];
	wchar_t * szInputFileName;
	wchar_t szInputFileNameFolder[MAX_PATH];

	GetFullPathName(strInputFile.c_str(), MAX_PATH, szInputFileNameFull, &szInputFileName);
	wcscpy_s(szInputFileNameFolder, szInputFileNameFull);
	szInputFileNameFolder[szInputFileName - szInputFileNameFull] = 0;

	char szRegexBuf[255];
	
	// input file name
	sprintf_s(szRegexBuf, R"(InputFilename" : "%S",)", szInputFileNameFull);
	RegexReplaceText(R"(InputFilename(.*),)", szRegexBuf, strQueueFile);
	// file names
	sprintf_s(szRegexBuf, R"(Filenames" : [ "%S"],)", szInputFileName);
	RegexReplaceText(R"(Filenames(.*),)", szRegexBuf, strQueueFile);
	
	// folder
	sprintf_s(szRegexBuf, R"(Directory" : "%S",)", szInputFileNameFolder);
	RegexReplaceText(R"(Directory(.*),)", szRegexBuf, strQueueFile);

	// removesome values
	RegexReplaceText(R"(Duration(.*),)", R"(Duration" : "",)", strQueueFile);
	RegexReplaceText(R"(Status(.*),)", R"(Status" : 0,)", strQueueFile);
	RegexReplaceText(R"(TimeEnded(.*),)", R"(TimeEnded" : "",)", strQueueFile);
	RegexReplaceText(R"(TimeStarted(.*),)", R"(TimeStarted" : "",)", strQueueFile);

	// change some settings
	RegexReplaceText(R"("FilenameBitrate" : true,)", R"("FilenameBitrate" : false,)", strQueueFile);
	RegexReplaceText(R"("FilenameDraft" : true,)", R"("FilenameDraft" : false,)", strQueueFile);
	RegexReplaceText(R"("FilenameFps" : true,)", R"("FilenameFps" : false,)", strQueueFile);
	RegexReplaceText(R"("FilenamePass" : true,)", R"("FilenamePass" : false,)", strQueueFile);
	RegexReplaceText(R"("FilenameResolution" : true,)", R"("FilenameResolution" : false,)", strQueueFile);

	string strTmpQueue;
	strTmpQueue = "Tmp.queue";
	ofstream queueTmp(strTmpQueue.c_str());
	queueTmp.write(strQueueFile.c_str(), strQueueFile.size());
	queueTmp.flush();
	queueTmp.close();

	strMMEPath += L"\\MobiclipMulticoreEncoder.exe";
	wchar_t cmdline[255];
	swprintf_s(cmdline, L" -q %S", strTmpQueue.c_str());
	STARTUPINFO oStartupInfo;
	PROCESS_INFORMATION oProcessInfo;
	ZeroMemory(&oStartupInfo, sizeof(oStartupInfo));
	oStartupInfo.cb = sizeof(oStartupInfo);
	oStartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	oStartupInfo.wShowWindow = SW_SHOWNORMAL;
	ZeroMemory(&oProcessInfo, sizeof(oProcessInfo));
	strMMEPath = strMMEPath;
	BOOL bRes = CreateProcess(strMMEPath.c_str(), cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &oStartupInfo, &oProcessInfo);

	if (bRes)
	{
		WaitForSingleObject(oProcessInfo.hProcess, INFINITE);

		//关闭进程和线程的句柄
		CloseHandle(oProcessInfo.hProcess);
		CloseHandle(oProcessInfo.hThread);
	}
	else
	{
		wchar_t buf[255];
		DWORD dwErr = GetLastError();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, buf, 255, 0);
		wcout << buf << endl;
		return 5;
	}
	strMMEPath += L" ";
	strMMEPath += cmdline;
	wcout << strMMEPath.c_str() << endl;
	_wsystem(strMMEPath.c_str());

	DeleteFileA(strTmpQueue.c_str());

    return 0;
}

