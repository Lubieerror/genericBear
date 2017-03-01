@echo off
:start
echo Deleting old files!
pause
RMDIR /S out 
echo Compile!
g++ gen-own.cc -O3 -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe
pause
bearit.exe
pause
goto start