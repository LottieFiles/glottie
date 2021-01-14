



# Glottie

**Glottie** is an OpenGL player for lottie animations. It is a C++ software that has been designed from ground-up for lightness and portability. Its scene graph builder, geometry generator and animation sequencer have been designed strictly for the scope of lottie, making it the leanest lottie player.

## Current state of project

Glottie is currently still under development and does not support all the features of the lottie format, as has been documented in at https://github.com/airbnb/lottie-web/tree/master/docs/json.

This player can play lotties, but with the following limitations:
- Borders are currently not supported.
- Tweening of basic shapes is not supported.
- Transformations of a parent layer or group (it) are not inherited.
- Shape items currently unsupported are gFill, gStroke, merge, repeater, stroke and trim.
- The only effects currently supported are color and fill.
- No external sources are currently supported.

### Contributing

Learn how you can [contribute to this project](doc/contributing.md).

## Compiling Glottie

From a single codebase, Glottie can be compiled to:
* WASM (using Emscripten)
* Windows
* Linux
* MacOS

#### WASM

Currently Glottie has a configuration to compile only with Emscripten. The script to compile for WASM is [wasm_build](wasm_build).

The only prerequisite for running the *wasm_build* script is a working [Emscripten installation](https://emscripten.org/docs/getting_started/downloads.html).

#### Windows

Compilation to Windows has been set up to use *CMake*. A preconfigured [CMakeLists.txt](CMakeLists.txt) is included in the Glottie codebase, which has been configured by default to compile for Windows 10.

The *CMake* configuration uses [winclude](winclude) as the include directory.

Glottie is compiled to Windows using [Google ANGLE](https://github.com/google/angle), and therefore uses ANGLE's EGL and GLES - with the compiler yielding a native DirectX player. The only other prerequisite library is SDL2.

#### Linux

Compilation to Linux is facilitated by the *Bash* script [linux_build](linux_build). The *linux_build* script uses [include](include) as the include directory.

#### MacOS

Compilation to MacOS is accomplished by running the script [macos_build](macos_build). The *macos_build* script uses [include](include) as the include directory.

## Testing Glottie

For all platforms other than WASM, Glottie presently reads a JSON file from stdin. Hence, to run Glottie, simply pipe in a JSON file.

#### Linux and MacOS

cat <JSONfile> | glottie

#### Windows

type <JSONfile> | <CMAKE_INSTALL_PREFIX>/glottie.exe

#### WASM

The **index.html** file in *examples/wasm* is a base template for loading the WASM player.