
@echo OFF
setlocal enabledelayedexpansion

:parse-arg
if "%~1"=="" goto :end
for /f "tokens=1,* delims==" %%A in ("%~1") do (
    set "%%A=%%B"
    echo "%%A=%%B"
)

shift
goto parse-arg
:end

cd %PROJECT_DIR%

cmake -G "Visual Studio 18 2026"            ^
    -T host=x64             ^
    -S .            ^
    -B Library/Engine-Build             ^
    -DPROJECT_DIR="%PROJECT_DIR%"          ^
    -DENGINE_PATH="%ENGINE_PATH%"          ^
    -DECLIPSED_EDITOR=ON ^
    -DCONFIG="%CONFIG%" ^
    -DENABLE_NETWORKING="%ENABLE_NETWORKING%" ^
    -DENABLE_STEAM_SDK="%ENABLE_STEAM_SDK%" ^
    -DENABLE_DISCORD_SDK="%ENABLE_DISCORD_SDK%" ^