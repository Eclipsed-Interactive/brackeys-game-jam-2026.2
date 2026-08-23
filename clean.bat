@echo off

if exist "Build" (
    echo Deleting "Build" directory
    rd /s /q "Build"
)

if exist "Temp" (
    echo Deleting "Temp" directory
    rd /s /q "Temp"
)

if exist "Library" (
    echo Deleting "Library" directory
    rd /s /q "Library"
)

cd Project

if exist "Local" (
    echo Deleting "Local" directory
    rd /s /q "Local"
)