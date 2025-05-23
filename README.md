# 3D Tank Prototype – OpenGL

This project is a complete prototype of a 3D tank built using C++ and OpenGL. It was designed as a foundational example of a simple 3D game element that could be integrated into larger gameplay systems or serve as a base for prototyping mechanics such as movement, rotation, shooting, and animation.

## 🎮 Features

- Fully rendered 3D tank composed of:
  - Central body
  - Left and right treads (tracks)
  - Rotating cannon and turret base
- Simple texture mapping
- Modular structure for easy code updates and extensions
- Real-time rendering using GLUT and OpenGL
- Swappable assets (textures, scale, etc.)

## 🧰 Technologies Used

- C++
- OpenGL (Fixed-function pipeline)
- GLUT (for windowing and input)
- SOIL (for texture loading)

## 🚀 How to Run

Just run the executable:

```bash
./bin/tank.exe
   ```
Or, for compile:

### Prerequisites

Ensure you have the following installed:

- C++ Compiler (g++, MinGW)
- OpenGL development libraries
- FreeGLUT
- GLEW
- SOIL (Simple OpenGL Image Library)

### Install the dependencies (Windows with MSYS2 MinGW)

1. Update the app:
   ```bash
   pacman -Syu
   ```
5. Then install:

   ```bash
   pacman -S mingw-w64-x86_64-freeglut mingw-w64-x86_64-glew mingw-w64-x86_64-soil
   ```

6. Compile in a terminal:

   ```bash
   g++ main.cpp core/*.cpp render/*.cpp -o bin/tank.exe -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lfreeglut -lglew32 -lSOIL -lopengl32 -lglu32 ./bin/tank.exe
   ```

### Linux

1. Make sure the following packages are installed:

   ```bash
   sudo apt-get install freeglut3-dev libsoil-dev g++
   ```

2. Compile and run as above.

## 🧭 Controls

- `Arrow keys` — Moves the camera and the turret
- `W / A / S / D` — Moves the tank
- `V` — Changes the perspective to 1st ou 3rd person

## 📄 License & Rights

This project was created for portfolio and prototype purposes. All textures and assets included are either public domain or originally authored. You are free to study and expand the code.
