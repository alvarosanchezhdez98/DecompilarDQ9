@echo off
title Dragon Quest IX Decomp Studio
cd /d "%~dp0"

echo =======================================================
echo   DRAGON QUEST IX DECOMPILATION STUDIO
echo =======================================================
echo Starting local application server...

where py >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    py tools\gui.py
    goto end
)

where python >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    python tools\gui.py
    goto end
)

echo [ERROR] Python was not found!
echo Please ensure Python is installed and added to PATH.
pause

:end
