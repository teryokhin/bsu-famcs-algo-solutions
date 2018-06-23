@echo off
:loop
12test.exe
1317.exe
copy tst.out tst.ans
12ch.exe
fc tst.out tst.ans
if ERRORLEVEL 1 goto fuck
goto loop
:fuck