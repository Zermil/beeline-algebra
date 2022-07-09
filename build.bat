@echo off

REM Change this to your visual studio's 'vcvars64.bat' script path
set MSVC_PATH="YOUR_PATH"
set CXXFLAGS=/std:c++17 /EHsc /W4 /WX /wd4996 /nologo %*

call %MSVC_PATH%\vcvars64.bat

pushd %~dp0
if not exist .\build mkdir build
cl %CXXFLAGS% src\main.cpp /Fo:build\ /Fe:build\bline.exe
popd