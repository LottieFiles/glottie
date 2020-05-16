#define KVLEN 128
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
#include <sys/time.h>

using namespace std;

std::function<void()> loop;
void main_loop() { loop(); }
void _doMain() { loop(); }

/*
alignas(256) GLuint* vao[1024];
alignas(256) GLuint* vbo[1024];
alignas(256) GLuint* ibo[1024];
alignas(256) GLuint* shaderProgram[1024];
alignas(256) GLint* posAttrib[1024];
*/

#include "main.h"
#include "gl/gl.h"
#include "misc.h"
#include "deserializer/properties.h"
#include "deserializer/layers.h"
#include "deserializer/shapes.h"
#include "deserializer/helpers.h"
//#include "emscripten/emscripten.cpp"
#include "misc.cpp"
#include "animate/transform.cpp"
#include "deserializer/deserializer.cpp"
#include "animate/prep_anim.cpp"
#include "gl/gl.cpp"
#include "gl/prep.cpp"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void loadJson(char* buffer, int theLength) {
	deserializeChar(buffer, theLength);
	EM_ASM({console.log("////> init done");});
	glInit();
	EM_ASM({console.log("////> gl init done");});

	glInitShaders(0);
	EM_ASM({console.log("////> start of prepping shapes");});
	prepShapes();
	EM_ASM({console.log("////> done prepping shapes");});
	redrawRequired = true;

	//gettimeofday(&timeRef, NULL);
	//double currentTime = (double)timeRef.tv_sec + ((double)timeRef.tv_usec / 1000000);
	//EM_ASM({console.log("////> TIME " + $0 + " ");}, currentTime);

	struct Buffers* buffersToRender;
/*	if (lastBuffersCreated != NULL) {
		buffersToRender = lastBuffersCreated->start->next->next;
		buffersToRender->start = buffersToRender;
		buffersToRender->next = NULL;
		//glDraw(NULL, NULL);
	}*/

	double lastTime = seconds();
	double currentTime = 0;
	int currentFrame = 0;
	while (1) {
		if (currentTime == 0) {
			glDraw(NULL, NULL, currentFrame);
		} else if (currentTime - lastTime > theAnimation->frameTime) {
			glDraw(NULL, NULL, currentFrame);
			currentFrame++;
			lastTime = currentTime;
		}
		if (currentFrame > theAnimation->op) {
			currentFrame = 0;
		}
		currentTime = seconds();
	}


	EM_ASM({console.log("////> done drawing " + $0 + " " + $1);}, theAnimation->w, theAnimation->h);

}



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
/*	if (lastBuffersCreated != NULL) {
		buffersToRender = lastBuffersCreated->start->next->next;
		buffersToRender->start = buffersToRender;
		buffersToRender->next = NULL;
		//glDraw(NULL, NULL);
	}*/



	EM_ASM({console.log("////> done drawing " + $0 + " " + $1);}, theAnimation->w, theAnimation->h);

	return 1;
}

}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	//doMain(NULL);
}

