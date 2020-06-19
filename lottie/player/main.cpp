#define KVLEN 128
#define ALIGNSIZE 512
#define TEXTBLOCK 220

#include <functional>

#include <emscripten.h> // emscripten
#include <emscripten/html5.h> // emscripten
#include <SDL2/SDL.h> // emscripten
//#include <SDL2/SDL.h>

#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h> // empscripten
//#include <glm/glm.hpp>
#include "glm/glm.hpp" // glm::vec3
//#include </usr/include/glm/vec3.hpp> // glm::vec3
//#include </usr/include/glm/vec4.hpp> // glm::vec4
//#include </usr/include/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
//#include </usr/include/glm/gtc/type_ptr.hpp> // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::mat4
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
//#include <GLES2/gl2.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
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

/*
EM_BOOL mainloop(double time, void* userData) {

	glDraw(NULL, NULL, (int)userData);
	return 1;
}
*/
int currentFrame = 0;
void mainloop() {
	if (currentFrame >= theAnimation->op) {
		currentFrame = 0;
	}
	glDraw(NULL, NULL, currentFrame);
	//EM_ASM({console.log("////> init done");});
	currentFrame++;
}

void loadJson(char* buffer, int theLength) {
	deserializeChar(buffer, theLength);
	EM_ASM({console.log("////> init done");});
	glInit();
	EM_ASM({console.log("////> gl init done");});

	glInitShaders(0);
	EM_ASM({console.log("////> start of prepping shapes");});
	prepShapes();
	EM_ASM({console.log("////> done prepping shapes " + $0);}, theAnimation->frameTimeMS);
	redrawRequired = true;

	//gettimeofday(&timeRef, NULL);
	//double currentTime = (double)timeRef.tv_sec + ((double)timeRef.tv_usec / 1000000);
	//EM_ASM({console.log("////> TIME " + $0 + " ");}, currentTime);

	/*
	if (! lastBuffersCreated->filled) {
		lastBuffersCreated = lastBuffersCreated->prev;
	}
	lastBuffersCreated->next = lastBuffersCreated->start;
	EM_ASM({console.log("////> pre-starting");});
	lastBuffersCreated->start->prev = lastBuffersCreated;
	*/

	EM_ASM({console.log("////> starting");});
	struct Buffers* buffersToRender;
/*	if (lastBuffersCreated != NULL) {
		buffersToRender = lastBuffersCreated->start->next->next;
		buffersToRender->start = buffersToRender;
		buffersToRender->next = NULL;
		//glDraw(NULL, NULL);
	}*/
	//emscripten_set_main_loop(mainloop, 0, 1);

	//emscripten_request_animation_frame_loop(mainloop, 0);
	//double currentTime = 0;
	/*
	int currentFrame = 0;
	while (1) {
		if (currentFrame >= theAnimation->op) {
			currentFrame = 0;
		}
		double lastTime = seconds();
		mainloop(lastTime, (void *)currentFrame);
		//SDL_Delay(theAnimation->frameTimeMS);
		SDL_Delay(1000);
		currentFrame++;
	}
	*/
	emscripten_set_main_loop(mainloop, theAnimation->fr, 0);
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

