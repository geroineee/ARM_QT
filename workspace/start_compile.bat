@echo off
chcp 65001
cd /D E:/source/ARM_QT/workspace
g++ main_code.cpp -o main_code.exe
main_code.exe <input.txt> output.txt
exit