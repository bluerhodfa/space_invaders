::@echo off
:: > Setup required Environment
:: -------------------------------------
set COMPILER_DIR=/usr/bin/cc
set PATH=%PATH%;%COMPILER_DIR%
cd %~dp0
:: .
:: > Compile simple .rc file
:: ----------------------------
cmd /c windres ..\..\src\space_invaders.rc -o ..\..\src\space_invaders.rc.data
:: .
:: > Generating project
:: --------------------------
cmd /c mingw32-make -f ..\..\src\Makefile ^
PROJECT_NAME=space_invaders ^
PROJECT_VERSION=1.0 ^
PROJECT_DESCRIPTION="my cool new space invadersclone in C and Raylib" ^
PROJECT_INTERNAL_NAME=space_invaders ^
PROJECT_PLATFORM=PLATFORM_DESKTOP ^
PROJECT_SOURCE_FILES="space_invaders.c" ^
BUILD_MODE="RELEASE" ^
BUILD_WEB_ASYNCIFY=FALSE ^
BUILD_WEB_MIN_SHELL=TRUE ^
BUILD_WEB_HEAP_SIZE=268435456 ^
RAYLIB_MODULE_AUDIO=TRUE ^
RAYLIB_MODULE_MODELS=TRUE
