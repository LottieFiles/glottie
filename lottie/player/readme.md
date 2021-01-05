# Glottie

**Glottie** is an OpenGL player for lottie animations. It is a C++ software that has been designed from ground-up for lightness and portability. Its scene graph builder, geometry generator and animation sequencer have been designed strictly for the scope of lottie, making it the leanest lottie player.

## Current state of project

Glottie is currently still under development and does not support all the features of the lottie format, as has been documented in at https://github.com/airbnb/lottie-web/tree/master/docs/json.

This player can play lotties, but with the following limitations:
- [Borders](docs/borders.md) are currently not supported.
- [Tweening](docs/tweening.md) of basic shapes is not supported.
- [Transformations](docs/transformations.md) of a parent layer or group (it) are not inherited.
- [Shape items](docs/shapes.md) currently unsupported are gFill, gStroke, merge, repeater, stroke and trim.
- The only [effects](docs/effects.md) currently supported are color and fill.
- No external sources are currently supported.

## Testing Glottie

From a single codebase, Glottie can be compiled to:
* WASM (using Emscripten)
* Windows
* Linux
* MacOS

#### WASM

Currently Glottie has a configuration to compile only for Emscripten. The script to compile for WASM is [wasm_build](wasm_build).

The only prerequisite for running the *wasm_build* script is a working [Emscripten installation](https://emscripten.org/docs/getting_started/downloads.html).

#### Windows

Compilation to Windows has been set up to use *CMake*. A preconfigured [CMakeLists.text](CMakeLists.txt) is included in the Glottie codebase, which has been configured by default to compile for Windows 10.

The *CMake* configuration uses [winclude](winclude) and [winlib](winlib) as the include and library directories, respectively.

Glottie is compiled to Windows using [Google ANGLE](https://github.com/google/angle), and therefore uses ANGLE's EGL and GLES - with the compiler yielding a native DirectX player. The only other prerequisite library is SDL2, which has also been included in [winclude](winclude).

#### Linux

Compilation to Linux is facilitated by the *Bash* script [linux_build](linux_build). The *linux_build* script uses [include](include) and [lib](lib) as the include and library directories, respectively.

#### MacOS

Compilation to MacOS is accomplished by running the script [macos_build](macos_build). The *macos_build* script uses [include](include) and [lib](lib) as the include and library directories, respectively.

## Execution sequence

File|Purpose
----|-------
[main.cpp](main.cpp)|Program entry point: main()&rightarrow;readFromStdin()&rightarrow;loadJson()
[deserializer/deserializer.cpp](deserializer/deserializer.cpp)|State machine that deserializes the JSON file into a scene graph: deserializeChar()&rightarrow;checkCharacter()&rightarrow;...
[gl/gl.init](gl/gl.init)|Initialize OpenGL system: glInit(), glInitShaders()
[gl/parentage.cpp](gl/parentage.cpp)|Resolve parenting and order scene graph accordingly: parentShapes()&rightarrow;...
[gl/prep.cpp](gl/prep.cpp)|Discover geometric elements, generate their vertex buffers and compute transformations: prepShapes()&rightarrow;prepAssets()&rightarrow;prepLayers()&rightarrow;(findLayersTransform()&rightarrow;[animate/transform.cpp](animate/transform.cpp):fillTransformLayers())&rightarrow;prepShapesItem()&rightarrow;(findShapesTransform()&rightarrow;[animate/transform.cpp](animate/transform.cpp):fillTransformShapes())&rightarrow;prepPropertiesShape()&rightarrow;prepPropertiesShapeProp()&rightarrow;prepTriangulate()&rightarrow;prepVAO()
[animate/prep_transform.cpp](animate/prep_transform.cpp)|Presequence all transformations and add them to the scene graph: prepTransformShapes()&rightarrow;<prepTransformAssets()>&rightarrow;prepTransformLayers()&rightarrow;[animate/transform.cpp](animate/transform.cpp):composeTransformLayers()&rightarrow;[animate/transform.cpp](animate/transform.cpp):fillCompositeAnimation()
[main.cpp](main.cpp)|Setup animation looping: either mainloop() or standaloneLoop()
[gl/gl.cpp](gl/gl.cpp)|Draw loop: glDraw()
