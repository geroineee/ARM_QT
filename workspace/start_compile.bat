@echo off
chcp 65001
cd /D C:/Users/sasha/Documents/repositories/ARM_QT/workspace
g++ main_code.cpp -o main_code.exe
main_code.exe <input.txt> output.txt
del main_code.exe
exit