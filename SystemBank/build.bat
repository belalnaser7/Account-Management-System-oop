@echo off
REM ------------------------------
REM Build Script for SystemBank
REM ------------------------------


REM Compile main program
g++ ConsoleApllication1.cpp ^
-ICORE ^
-IClients ^
-IScreens ^
-IUser ^
-ICurrencies ^
-o ConsoleApllication1

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ Build Failed!
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ✅ Build Succeeded! Running program...
.\ConsoleApllication1
pause