CXX      = g++
TARGET   = bin/tank
SRCS     = main.cpp core/camera.cpp core/input.cpp core/tank.cpp core/terrain.cpp \
           core/projectile.cpp core/enemy.cpp core/obstacles.cpp \
           render/textures.cpp render/lighting.cpp render/hud.cpp
CXXFLAGS = -std=c++17 -O2 -Wall
LIBS     = -lGL -lGLU -lglut -lSOIL -lGLEW

$(TARGET): $(SRCS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
