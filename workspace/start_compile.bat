@echo off
chcp 65001 > null
cd /D E:/source/ARM_QT/workspace
g++ main_code.cpp -o main_code.exe
main_code.exe < input.txt
del main_code.exe
exit