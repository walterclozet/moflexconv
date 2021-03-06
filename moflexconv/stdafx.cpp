// stdafx.cpp : 只包括标准包含文件的源文件
// moflexconv.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

string str2DTemplate = R"([
   {
      "Child" : [
         {
            "Child" : [
               {
                  "Child" : [
                     {
                        "Duration" : "",
                        "Fps" : -1,
                        "Progress" : -1,
                        "Status" : 0,
                        "TimeEnded" : "",
                        "TimeStarted" : ""
                     },
                     {
                        "Duration" : "",
                        "Fps" : -1,
                        "Progress" : -1,
                        "Status" : 0,
                        "TimeEnded" : "",
                        "TimeStarted" : ""
                     }
                  ],
                  "Duration" : "",
                  "Fps" : -1,
                  "InputFilename" : "Y:\\a.avi",
                  "Progress" : -1,
                  "Status" : 0,
                  "TimeEnded" : "",
                  "TimeStarted" : ""
               }
            ],
            "Duration" : "",
            "Fps" : -1,
            "GraphFlow" : [ "VideoFiles", "CropResize", "ConvertAudio", "MobiclipEncoder" ],
            "Progress" : -1,
            "Status" : 0,
            "TimeEnded" : "",
            "TimeStarted" : ""
         }
      ],
      "Duration" : "",
      "Fps" : -1,
      "Name" : "Job 1",
      "Progress" : -1,
      "Project" : [
         {
            "Data" : {
               "AspectRatio" : 0.0,
               "ResizeMode" : 0,
               "ResizeType" : 2,
               "UserCrop" : {
                  "Down" : 0,
                  "Left" : 0,
                  "Right" : 0,
                  "Up" : 0
               },
               "UserCropEnabled" : false,
               "UserResize" : {
                  "Height" : 240,
                  "Width" : 400
               },
               "UserResizeEnabled" : true,
               "WinX" : 339,
               "WinY" : -98
            },
            "Filter" : "CropResize",
            "Next" : [
               {
                  "Pin" : 0,
                  "Uid" : 1291034932016
               }
            ],
            "Uid" : 1291001817680,
            "x" : 197,
            "y" : 59
         },
         {
            "Data" : {
               "ChannelCount" : 0,
               "SampleRate" : 0,
               "SampleRateCustom" : 44100,
               "WinX" : -1,
               "WinY" : -1
            },
            "Filter" : "ConvertAudio",
            "Next" : [
               {
                  "Pin" : 0,
                  "Uid" : 1291034977712
               }
            ],
            "Uid" : 1291034932016,
            "x" : 404,
            "y" : 103
         },
         {
            "Data" : {
               "DisplayWarningMessage" : false,
               "Draft" : false,
               "EnableAviSave" : false,
               "EstimatedSizeMode" : 0,
               "FilenameBitrate" : true,
               "FilenameDraft" : true,
               "FilenameFps" : true,
               "FilenameOverwrite" : true,
               "FilenamePass" : true,
               "FilenameResolution" : true,
               "Input" : [
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "01ecac57-1e09-4848-9695-7b24ff0c3500.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  },
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "00b6993b-8aae-4cfb-8846-6a5cf3aceefc.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  },
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "9523fec1-254e-44ec-9d3b-8be2b1bd0eec.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  },
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "c4b0b90e-5ad2-4c7d-be54-acf1e3f58585.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  },
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "0ec8ec05-6349-495a-9f92-2770c07fd912.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  },
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "ac252646-f5bd-402a-a455-71a7399aa066.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  },
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "ca5c09e2-61f0-47f1-a492-d57eee5c3748.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  },
                  {
                     "AudioCompression" : 1,
                     "Bitrate" : 0,
                     "PassFilename" : "e534114a-013a-4365-a0fc-e40bb0eada97.pass",
                     "StreamType" : 0,
                     "Timeline" : false
                  }
               ],
               "KeyframeInterval" : 30.0,
               "MaxFileSize" : 128.0,
               "OutputDecoded" : true,
               "OutputDirectory" : "F:\\tools\\Moflex Helper\\tools",
               "OutputFilename" : "",
               "OutputFormat" : 0,
               "OutputLogInfo" : false,
               "PreloadTime" : 0.0,
               "Qmax" : 48,
               "Qmin" : 12,
               "SynchronizeTimelines" : true,
               "TargetPlatform" : 0,
               "TwoPass" : true,
               "Uid" : "8fe3e4d1-a24e-4cac-9f32-13239074607c",
               "WinX" : -1,
               "WinY" : -1
            },
            "Filter" : "MobiclipEncoder",
            "Uid" : 1291034977712,
            "x" : 570,
            "y" : 188
         },
         {
            "Data" : {
               "Directory" : "Y:",
               "Filenames" : [ "a.avi" ],
               "Index" : 0,
               "WinX" : -1,
               "WinY" : -1
            },
            "Filter" : "VideoFiles",
            "Next" : [
               {
                  "Pin" : 0,
                  "Uid" : 1291001817680
               }
            ],
            "Uid" : 1291032332368,
            "x" : 0,
            "y" : 0
         }
      ],
      "Status" : 0,
      "TimeEnded" : "",
      "TimeStarted" : ""
   }
]
)";