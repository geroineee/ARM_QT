@echo off
chcp 65001 > null.txt
cd /D C:/Users/sasha/Documents/repositories/ARM_QT/workspace/
g++ main_code.cpp -o main_code.exe
main_code.exe < input.txt
del main_code.exe
del null.txt
exit