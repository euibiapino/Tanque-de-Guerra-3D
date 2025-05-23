@echo off
g++ main.cpp core/*.cpp render/*.cpp -o bin\tank.exe -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -lfreeglut -lglew32 -lSOIL -lopengl32 -lglu32
if %errorlevel% equ 0 (
    bin\tank.exe
)