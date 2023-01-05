/////////////////////////////////////////////////////////
/////////                                       /////////
/////////  ******            *****************  /////////
/////////   ****              ***************   /////////
/////////    ***               ***         **   /////////
/////////    ***               ***              /////////
/////////    ***               ***     **       /////////
/////////    ***               **********       /////////
/////////    ***               **********       /////////
/////////    ***               ***     **       /////////
/////////    ***               ***              /////////
/////////    ***       **      ***              /////////
/////////   **************    *****             /////////
/////////  ****************  *******            /////////
/////////                                       /////////
/////////////////////////////////////////////////////////
///////  Created by: https://github.com/shaafiee  ///////
///////      Copyright 2020, lottiefiles.com      ///////
/////////////////////////////////////////////////////////

#ifdef __EMSCRIPTEN__
#define EMT 1

#else


#endif

#ifdef FOR_WINDOWS
	#include "configure.h"
#endif


//#define ISDLL 1

#define KVLEN 128

#pragma once
#ifdef WINRT
#include <unknwn.h>
#include <winrt/Windows.Foundation.h>
#endif

#ifdef EMT
#define ALIGNSIZE 256
#endif

#define TEXTBLOCK 220

//#include <functional>


#ifdef ISDLL
	#include "dllrelated.h"
#endif

#ifdef EMT
#include <emscripten.h> // emscripten
#include <emscripten/html5.h> // emscripten
#endif




#ifdef EMT
#else
	#ifdef APPLE
		#include <OpenGL/gl.h>
	#else

		#ifdef WINDOWS

#ifdef GLES2
	#include <GLES2/gl2.h>
	#include <angle_gl.h>
	#ifdef EGLWINDOWS
	#include "EGL/egl.h"
	#include "SDL_egl.h"
	#else
	#include <GLES2/gl2ext.h>
	#endif
#else
//#include <GLES3/gl3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>
//#include <SDL_opengles2.h>
#include <sdl/SDL_opengl.h>
#endif


		#endif

	#endif
#endif


#ifdef EMT
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h> // emscripten
#include <SDL_opengles2.h> // empscripten
#else
#ifdef WINDOWS
#include <Windows.h>
#include <sdl/SDL.h>
#include <sdl/SDL_syswm.h>
//#include <SDL_opengles2.h> // empscripten
#endif

#ifdef LINUX
#include <GL/glew.h>
#include <SDL2/SDL.h> // emscripten
#include <SDL2/SDL_opengl.h>
#endif
#endif

#ifdef EMT
//#include <SDL2/SDL.h>
//#define GL_GLEXT_PROTOTYPES
//#include <GLES2/gl2ext.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#endif

#include "glm/glm.hpp" // glm::vec3
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::mat4
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#ifdef WINDOWS
//#pragma comment(lib,"user32.lib") 
//#pragma comment(lib,"opengl32.lib") 
#endif

#ifdef WINRT
struct __declspec(uuid("ddc36e02-18ac-47c4-ae17-d420eece2281")) IMyComInterface : ::IUnknown
{
	virtual HRESULT __stdcall Call() = 0;
};
#endif


using namespace std;

#ifdef WINRT
using namespace winrt;
using namespace Windows::Foundation;
#endif


#ifdef EMT
/*
std::function<void()> loop;
void mainloop() { loop(); }
void _doMain() { loop(); }
*/
#else
#endif

/*
alignas(256) GLuint* vao[1024];
alignas(256) GLuint* vbo[1024];
alignas(256) GLuint* ibo[1024];
alignas(256) GLuint* shaderProgram[1024];
alignas(256) GLint* posAttrib[1024];
*/

glm::mat4 identityMatrix;

#ifdef EMT
struct alignas(ALIGNSIZE) BackgroundColor {
#else
struct BackgroundColor {
#endif
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float alpha = 0.0f;
} globalBackground;


#ifdef EGLWINDOWS
struct EGLVariables {
	EGLDisplay display;
	EGLSurface surface;
} *eglVars;
#endif


#include "main.h"
#include "gl/gl.h"
#include "misc.h"
#include "deserializer/properties.h"
#include "deserializer/layers.h"
#include "deserializer/shapes.h"
#include "deserializer/helpers.h"
#include "animate/animate.h"
//#include "emscripten/emscripten.cpp"
#include "debugtools.cpp"
#include "misc.cpp"
#include "animate/transform.cpp"
#include "deserializer/deserializer.cpp"
#include "animate/prep_anim.cpp"
#include "gl/gl.cpp"
#include "gl/parentage.cpp"
#include "gl/prep.cpp"
#include "gl/prep_transform.cpp"
//#include "gl/it_adjust.cpp"
//#include "animate/prep_parent.cpp"


#ifdef EMT
extern "C" {
EMSCRIPTEN_KEEPALIVE

#ifdef TEST_SDL_LOCK_OPTS
EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif
#endif

int currentFrame = 0;
//struct timeval tempTime;
long lastTime;
bool quitProgram = false;

void mainloop() {
	if (currentFrame >= theAnimation->op) {
		currentFrame = 0;
	}
	glDraw(NULL, NULL, currentFrame);
	//EM_ASM({console.log("////> init done");});
	currentFrame++;
}

void standaloneLoop() {
/*	const int WIDTH = 20;
	const int HEIGHT = 20;
	const int SQUARE_SIZE = 20;
    SDL_Rect rect = {
        (WIDTH - SQUARE_SIZE) / 2,
        (HEIGHT - SQUARE_SIZE) / 2,
        SQUARE_SIZE,
        SQUARE_SIZE
    };*/

	long currentTime;
	SDL_Event e;
	//cout << theAnimation->frameTime << " is frame time \n";
	while (! quitProgram) {
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quitProgram = true;
			}
			if (e.type == SDL_KEYDOWN){
				quitProgram = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){
				quitProgram = true;
			}

		}
			if (currentFrame >= theAnimation->op) {
				currentFrame = 0;
			}
			//SDL_RenderClear(rdr);
			#ifdef WINDOWS
				//glClear(GL_COLOR_BUFFER_BIT);
			#endif
			glDraw(NULL, NULL, currentFrame);
       			//SDL_RenderPresent(rdr);
			#ifdef EGLWINDOWS
				eglSwapBuffers(eglVars->display, eglVars->surface);
			#else
				SDL_GL_SwapWindow(wnd);
			#endif
			currentFrame++;
			//lastTime = currentTime;
			SDL_Delay(theAnimation->frameTimeMS);
	}
}

void loadJson(char* buffer, int theLength, float bgRed, float bgGreen, float bgBlue, float bgAlpha) {

	if (bgRed > 0.0) {
		globalBackground.red = bgRed;
	}
	if (bgGreen > 0.0) {
		globalBackground.green = bgGreen;
	}
	if (bgBlue > 0.0) {
		globalBackground.blue = bgBlue;
	}
	if (bgAlpha > 0.0) {
		globalBackground.alpha = bgAlpha;
	}

	identityMatrix = glm::mat4(1.0f);

	#ifdef EMT
	#else
	cout << buffer[0] << "\n";
	cout << "Deserializing... \n";
	#endif
	deserializeChar(buffer, theLength);

	#ifdef EMT
	#else
	cout << "GL init... \n";
	#endif

#ifdef WINDOWS
	glInit(NULL);
#else
	glInit();
#endif

	#ifdef EMT
	#else
	cout << "Initializing shaders... \n";
	#endif
	glInitShaders(0);

	#ifdef EMT
	#else
	cout << "Associating parents... \n";
	#endif
	parentShapes();

	#ifdef EMT
	#else
	cout << "Prepping shapes... \n";
	#endif
	prepShapes();

	parentOffsetShapes(); // account all position offsets from parentage

	#ifdef EMT
	#else
	cout << "Prepping transform shapes... \n";
	#endif
	prepTransformShapes();
	#ifdef EMT
	#else
	cout << "Match parent VAOs... \n";
	#endif
	if (animationSequence != NULL) {
		matchParentVAO();
	}

	redrawRequired = true;


	struct Buffers* buffersToRender;

	#ifdef EMT
	#else
	cout << "Start animating... \n";
	#endif
	if (animationSequence != NULL) {
		animationSequence = animationSequence->start;
	} else {
		#ifdef EMT
		#else
			cout << "No animations found... \n";
		#endif
		exit(1);
	}

	#ifdef EMT
	EM_ASM_({console.log("Starting display");});
	emscripten_set_main_loop(mainloop, theAnimation->fr, 0);
	#else
	cout << "Starting main loop... \n";
	standaloneLoop();
	#endif
}


int doMain(char someChar[]) {

	identityMatrix = glm::mat4(1.0f);

	deserialize();
#ifdef WINDOWS
	glInit(NULL);
#else
	glInit();
#endif

	glInitShaders(0);
	prepShapes();

	redrawRequired = true;

	struct Buffers* buffersToRender;

	return 1;
}

#ifdef EMT
}
#endif

void readFromStdin(float bgRed, float bgGreen, float bgBlue, float bgAlpha) {
	for (std::string line; std::getline(std::cin, line);) {
		cout << "Reading JSON \n";
		jsonString = jsonString + line;
	}
	if (jsonString.size() > 0) {
		cout << "Loading animation \n";
		int theLength = jsonString.length();
		char* jString = new char[theLength];
		std::strcpy(jString, jsonString.c_str());
		jsonString.clear();

		loadJson(jString, theLength, bgRed, bgGreen, bgBlue, bgAlpha);
	} else {
		cout << "Nothing \n";
	}
	cout << "Done \n";
}

#ifdef ISDLL
extern "C"
{
	__declspec(dllexport) void jsonAndColor(char* buffer, float bgRed, float bgGreen, float bgBlue, float bgAlpha) {
		
	}

	__declspec(dllexport) void json(char* buffer) {
	}

}
#endif

int main(int argc, char *argv[]) {
	#ifdef WINRT
		winrt::init_apartment();
	#endif

	//SDL_Init(SDL_INIT_EVERYTHING);
	#ifdef EGLWINDOWS
		eglVars = new struct EGLVariables;
	#endif

	#ifdef EMT
	#else
		cout << SDL_GetError() << "\n";
		cout << "Attempting standalone \n";

		if (argc == 5) {
			readFromStdin(
					atof(argv[1]),
					atof(argv[2]),
					atof(argv[3]),
					atof(argv[4])
				);
		} else {
			readFromStdin(
					1,
					1,
					1,
					1
				);
		}
	#endif

	return 1;
}

