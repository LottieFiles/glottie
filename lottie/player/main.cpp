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

// forward declarations
struct ScopeTrail* lastScopeBeforeThis(struct ScopeTrail*);
struct ScopeBefore lastScopeBeforeObject();
struct Layers* newLayers(struct Layers*);
struct ShapesItem* newShapesItem(struct ShapesItem*);
struct PropertiesShape* newPropertiesShape();

int currentUniversalCount;
SDL_Window* wnd;
SDL_Renderer* rdr;
SDL_GLContext glc;
GLuint* vao[1024];
GLuint* vbo[1024];
GLuint* ibo[1024];
GLuint* shaderProgram[1024];
GLuint mainShader;
GLint* posAttrib[1024];
int lastRefIndex = 0;

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
#include "gl/prep.cpp"

int main() {
	deserialize();
	glInit();
	//glDraw();
	prepShapes();
	glInitShaders(0);
	glDraw(0,0);
	return 1;
}
