@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

set "exe=DotTreeChecker.exe"
set "input_dir=input"
set "output_dir=output"
set "expected_dir=expected"
set "result_file=result.txt"

if not exist "%output_dir%" mkdir "%output_dir%"
if exist "%result_file%" del "%result_file%"

set total=0

echo [TESTING STARTED] > "%result_file%"
echo Start time: %date% %time% >> "%result_file%"
echo ======================================== >> "%result_file%"

for /l %%i in (1,1,14) do (
    set /a total+=1
    set "input_file=%input_dir%\i_%%i.dot"
    set "output_file=%output_dir%\o_%%i.dot"
    set "expected_file=%expected_dir%\exp_%%i.dot"
    
    echo.
    echo TEST %%i of 14:
    echo Running: %exe% "!input_file!" "!output_file!"
    echo [Test %%i] Input: !input_file! >> "%result_file%"
    echo [Test %%i] Running program... >> "%result_file%"
    
    call "%exe%" "!input_file!" "!output_file!" 2>&1 >> "%result_file%"
    set "error_code=!errorlevel!"
    
    if not exist "!output_file!" (
        echo [Test %%i] ERROR: Output file not created >> "%result_file%"
        echo [TEST %%i] ERROR: Output file not created
    ) else (
        if exist "!expected_file!" (
            echo [Test %%i] Expected output content: >> "%result_file%"
            type "!expected_file!" >> "%result_file%"
            echo ---------------------------------------- >> "%result_file%"
        ) else (
            echo [Test %%i] WARNING: Expected file not found: !expected_file! >> "%result_file%"
            echo ---------------------------------------- >> "%result_file%"
        )
        
        echo [Test %%i] Actual output content: >> "%result_file%"
        type "!output_file!" >> "%result_file%"
        echo ======================================== >> "%result_file%"
        echo [TEST %%i] Output displayed above.
    )
)

echo. >> "%result_file%"
echo [TESTING COMPLETE] >> "%result_file%"
echo End time: %date% %time% >> "%result_file%"
echo.

echo ===== TESTING COMPLETE =====
echo Results saved to %result_file%
echo.

start notepad.exe "%result_file%"

