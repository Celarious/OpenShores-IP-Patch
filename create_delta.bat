```bat
@echo off
if "%~2"=="" (
    echo Please drag two files onto this batch file.
    pause
    exit /b
)

echo.
echo File 1: "%~1"
echo File 2: "%~2"
echo.

set /p "choice=Is File 1 the OLD file? (Y/N): "

if /I "%choice%"=="Y" (
    set "old=%~1"
    set "new=%~2"
) else (
    set "old=%~2"
    set "new=%~1"
)

echo.
echo Old file: "%old%"
echo New file: "%new%"
echo.

xdelta3 -f -e -s "%old%" "%new%" "delta_file"

if errorlevel 1 (
    echo.
    echo ERROR: xdelta failed.
) else (
    echo.
    echo xdelta created successfully.
)

pause
```
