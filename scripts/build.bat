@echo off

IF "%~1" == "" GOTO CleanBuild
IF "%~1" == "clean" GOTO Clean
IF "%~1" == "build" GOTO Build

:CleanBuild
call vendor\premake\premake5.exe clean
GOTO Build

:Clean
call vendor\premake\premake5.exe clean
GOTO Done

:Build
call vendor\premake\premake5.exe vs2022
GOTO Done

:Done
PAUSE