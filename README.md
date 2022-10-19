# Three-dimensional Game of life simulation

This is a proof of concept for a three-dimensional game of life simulation. It is written in C++ and uses OpenGL for rendering.

## Installation

Setup the dependencies mentionned below, *ie* `OpenGL`, `GLFW`, `Glm`, `GLEW`, and `GLUT`. A bash script is available for debian/ubuntu-based systems at `scripts/deps_setup_debian.sh`.

Build the project with `cmake` and `make`:

```bash
cd voxelife
mkdir build
cd build
cmake ..
make
```

Run the program:

```bash
./src/main
```
