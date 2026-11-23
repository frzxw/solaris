# Solaris

An interactive solar system in C++ and OpenGL. Fly a free camera between the eight planets, watch them orbit at
adjustable speed, switch between readable and realistic scale, and add moons on the fly.

## Features

- Planets and moons on orbits derived from real astronomical data, textured from TGA images
- A spacecraft-style camera with six degrees of freedom
- Time and movement speed controls
- Readable or realistic planet scale
- Orbit paths on demand
- Background music and sound cues (Windows)
- An in-app help overlay

## Controls

| Key | Action |
| --- | --- |
| `W` `A` `S` `D` | Move forward, left, back, right |
| `I` `K` | Pitch up and down |
| `J` `L` | Roll left and right |
| `Q` `E` | Yaw left and right |
| `,` `.` | Slower or faster movement |
| `-` `=` | Slower or faster time |
| `1`–`9` | Focus a planet |
| `[` `]` | Shrink or grow the planets; `R` resets to realistic scale |
| `O` | Toggle orbit paths |
| `M` | Add a moon to the focused planet |
| `H` | Help |

## Build

Windows with MinGW and freeglut (the DLL is included):

```sh
g++ main.cpp solarsystem.cpp planet.cpp moon.cpp tga.cpp camera.cpp -o solaris.exe -lopengl32 -lglu32 -lfreeglut -lwinmm
./solaris.exe
```

A prebuilt Windows binary with its assets is in `solaris.zip`.

## Code

| File | Contents |
| --- | --- |
| `main.cpp` | Window, render loop and input |
| `solarsystem.cpp` | The system: planets, their positions and time |
| `planet.cpp`, `moon.cpp` | Bodies and how they are drawn |
| `camera.cpp` | The free-flight camera |
| `tga.cpp` | TGA texture loader |
