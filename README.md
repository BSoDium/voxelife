# 🧬 Three-dimensional Game of life simulation

This is a proof of concept for a three-dimensional game of life simulation. It is written in C++ and uses OpenGL for rendering.

## Installation

### Generic setup

This repository uses vcpkg for dependency management. You may use third party package managers, such as apt, to install the dependencies, but the following instructions assume you do not. All dependencies are listed in the `vcpkg.json` file.

Start by installing vcpkg globally on your system. You can find instructions for this on the vcpkg [getting started](https://vcpkg.io/en/getting-started.html) manual. Once vcpkg is installed and added to your path, clone this repository and run the following commands:

```bash
cd voxelife
vcpkg install
```

If you encounter any errors while running the install command, please refer to the [vcpkg issues](https://github.com/microsoft/vcpkg/issues), as it is highly likely that someone else has encountered it before.

:fire: Top related issues:  
> https://github.com/microsoft/vcpkg/issues/26848

Once the dependencies are installed, you can build the project using cmake. The following commands will build the project and place the executable in the `build` directory.

```bash
mkdir build
cmake -DCMAKE_TOOLCHAIN_FILE:STRING={vcpkg root}/scripts/buildsystems/vcpkg.cmake .
cd build
make
```
with `{vcpkg root}` being the path to the vcpkg root directory (e.g. `~/vcpkg`).

Run the program:

```bash
./voxelife
```

### Visual Studio Code

Open the VS Code workspace, which can be found at the root of the repository. Proceed then to install the recommended extensions, and configure the cmake tools extension to use the vcpkg toolchain file, by adding the following to your `settings.json` file:

```json
{
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "{vcpkg root}/scripts/buildsystems/vcpkg.cmake"
    }
}
```
You should now be able to build and run the project from within VS Code, by opening the <kbd>Run and Debug</kbd> panel and selecting the `(gdb) Launch` configuration.
