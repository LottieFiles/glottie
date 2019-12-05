#define KVLEN 21
#define ALIGNSIZE 256
#define TEXTBLOCK 220

#include <functional>

#include <emscripten.h> // emscripten
#include <SDL2/SDL.h> // emscripten
//#include <SDL2/SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h> // empscripten
//#include <GLES2/gl2.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

std::function<void()> loop;
void main_loop() { loop(); }

#include "main.h"
#include "misc.h"
#include "misc.cpp"
#include "deserializer/properties.h"
#include "deserializer/layers.h"
#include "deserializer/shapes.h"
#include "deserializer/helpers.h"
//#include "emscripten/emscripten.cpp"
#include "deserializer/deserializer.cpp"
#include "gl/gl.cpp"

int main()
{
	deserialize();
	//glInit();

	return 1;
}
