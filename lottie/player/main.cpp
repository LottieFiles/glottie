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
#include <cmath>

using namespace std;

std::function<void()> loop;
void main_loop() { loop(); }



// forward declarations
struct ScopeTrail* lastScopeBeforeThis(struct ScopeTrail*);
struct ScopeBefore lastScopeBeforeObject();
struct Layers* newLayers(struct Layers*);
struct ShapesItem* newShapesItem(struct ShapesItem*);
struct PropertiesShape* newPropertiesShape();
struct ShaderProgram* newShaderProgram();

/*
alignas(256) int currentUniversalCount;
alignas(256) SDL_Window* wnd;
alignas(256) SDL_Renderer* rdr;
alignas(256) SDL_GLContext glc;
alignas(256) int lastRefIndex = 0;
alignas(256) GLuint mainShader;
*/

int preSwitch[20]; // to determine the switch of assets to layers (and vice versa)
int currentUniversalCount;
SDL_Window* wnd = NULL;
SDL_Renderer* rdr = NULL;
SDL_GLContext glc;
int lastRefIndex = 0;
GLuint mainShader;

bool redrawRequired = false;
//GLuint* shaderProgram;

struct alignas(ALIGNSIZE) RedrawBuffers {
	struct RedrawBuffers* start;
	struct RedrawBuffers* next;
	struct RedrawBuffers* prev;

	struct Buffers* buffers;
} *redrawList = NULL;

struct alignas(ALIGNSIZE) ShaderProgram {
	struct ShaderProgram* start = NULL;
	struct ShaderProgram* next = NULL;
	struct ShaderProgram* prev = NULL;

	GLuint* shader;
} *lastShaderProgramCreated;

struct alignas(ALIGNSIZE) Buffers {
	struct Buffers* start = NULL;
	struct Buffers* next = NULL;
	struct Buffers* prev = NULL;

	struct Dimensions* dimensions = NULL;

	GLuint* vao = NULL;
	GLuint* vbo = NULL;
	GLuint* ibo = NULL;
	unsigned int* idx; // array of triangulation data
	int idxCount;

	GLint* posAttrib = NULL;
	bool changed = false;
	bool clockwise;
} *lastBuffersCreated;

/*
alignas(256) GLuint* vao[1024];
alignas(256) GLuint* vbo[1024];
alignas(256) GLuint* ibo[1024];
alignas(256) GLuint* shaderProgram[1024];
alignas(256) GLint* posAttrib[1024];
*/

#include "main.h"
#include "misc.h"
#include "deserializer/properties.h"
#include "deserializer/layers.h"
#include "deserializer/shapes.h"
#include "deserializer/helpers.h"
//#include "emscripten/emscripten.cpp"
#include "misc.cpp"
#include "deserializer/deserializer.cpp"
#include "gl/gl.cpp"
#include "gl/prep.cpp"


extern "C" {

int simpleFunction(int someInt) {
	return someInt + someInt;
}

int doMain(char someChar[]) {
	/*
	if (someChar == NULL || strlen(someChar) <= 0) {
	} else {
		jsonString.assign(someChar);
	}
	*/
	//if (someChar.length() > 0) {
	//	return someChar.length();
	//}
	//if (strlen(someChar) > 0) {
	//	return strlen(someChar);
	//}

	deserialize();
	EM_ASM({console.log("////> init done");});
	glInit();
	EM_ASM({console.log("////> gl init done");});

	glInitShaders(0);
	EM_ASM({console.log("////> start of prepping shapes");});
	prepShapes();
	EM_ASM({console.log("////> done prepping shapes");});
	redrawRequired = true;

	struct Buffers* buffersToRender;
	buffersToRender = lastBuffersCreated->start->next->next;
	buffersToRender->start = buffersToRender;
	buffersToRender->next = NULL;

	//glDraw(NULL, buffersToRender);
	glDraw(NULL, NULL);

	EM_ASM({console.log("////> done drawing");});

	return 1;
}

}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	doMain(NULL);
}

