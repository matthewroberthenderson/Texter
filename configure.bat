@echo off
SETLOCAL EnableDelayedExpansion

::if you change this, don't foget to git ignore the folder.
set folder_name="_project" 

if not exist "%folder_name%" (
  mkdir "%folder_name%"
  echo Created folder "%folder_name%".
) else (
  echo Folder "%folder_name%" already exists. Moving onto the CMake config step.
  goto cmake_configure
)



:cmake_configure
echo Checking for CMake...

where cmake.exe >nul 2>nul
if errorlevel 1 (
    echo CMake is not installed or not in the system PATH.
    echo I use CMake to configure this project, you will need that to build.

    rem Give them a bit more info.
    set TEXT_FILE="CMakeLists.txt"
    set SEARCH_STRING="VERSION"

    rem Search for the string in the file and extract the version number
    for /f "tokens=2 delims=()" %%a in ('findstr /C:"!SEARCH_STRING!" "!TEXT_FILE!"') do set VERSION=%%a

    rem Check if the version number was found and echo it to the console
    if defined VERSION (
        echo Download CMake - !VERSION! - From https://cmake.org/. After that try to re-run this script.
    ) else (
        echo Strange, i could not find the version number when i searched for: "!SEARCH_STRING!" in the CMakeLists.txt.
        echo Something is either wrong/changed in CMakeLists.txt or this build script... 
    )


) else (
    echo CMake is installed and in the system PATH.
    cd _project
    echo moved to _project directory
    echo current directory looks like this:
    dir
    echo Configuring now.
    cmake ../

)


pause
exit /b 0
