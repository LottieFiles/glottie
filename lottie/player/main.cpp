
#define WINDOWS 1

//#define DEBUG 1
//#define DEBUG2 1
#define DEBUG3 1
#define DEBUGPOPULATEVERTICES 1
//#define DEBUGREADARRAY 1

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

#include "configure.h"

#ifdef ISDLL
	#include "dllrelated.h"
#endif

#ifdef EMT
#include <emscripten.h> // emscripten
#include <emscripten/html5.h> // emscripten
#endif


#ifdef EMT
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h> // emscripten
#include <SDL_opengles2.h> // empscripten
#else
#ifdef WINDOWS
#include <Windows.h>
//#include <Wia.h>
	//#include <sdl/SDL_egl.h> // emscripten
	//#include <sdl/SDL_opengl.h>
//#include <sdl/SDL_egl.h>
//#include <sdl/SDL_opengles2.h>
#include <sdl/SDL.h>
#include <sdl/SDL_syswm.h>
		//#include <sdl/SDL_syswm.h>
#endif

#ifdef LINUX
#include <SDL2/SDL.h> // emscripten
#include <SDL2/SDL_opengl.h>
#endif
#endif


#ifdef EMT
#else
	#ifdef APPLE
		#include <OpenGL/gl.h>
		//#include <OpenGL/glu.h>
		//#include <OpenGL/glext.h>
		//#include <GLUT/glut.h>
	#else
		//#include <GL/glu.h>
		//#include <GL/glext.h>
		//#include <GL/glx.h>
		//#include <GL/glxext.h>
		//#include <GL/gl.h>
		//#define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)

		//#include <GL/glew.h>
		//#include <GLFW/glfw3.h>

		//#include <GL/glu.h>
		//#include <GL/glext.h>
		//#include <GL/glx.h>
		//#include <GL/glxext.h>

		//#include <GL/glfw3.h>
		//#include <GLFW/glfw3.h>
		//#include <GL/glu.h>
		//#include <GL/glext.h>
		//#include <GL/glx.h>
		//#include <GL/gl.h>

		//#include <GL/glew.h>jjj
		//#include <GL/glut.h>
		//#include <GL/freeglut.h>
		//#include <GL/gl.h>
		//#include <GL/glu.h>

		#ifdef WINDOWS
			//#include <EGL/egl.h>

		#include <GLES2/gl2.h>
		#include <GLES2/gl2ext.h>

		#endif

	#endif
#endif


#ifdef EMT
//#include <SDL2/SDL.h>
//#define GL_GLEXT_PROTOTYPES
//#include <GLES2/gl2ext.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#endif

//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/glm.hpp>
#include "glm/glm.hpp" // glm::vec3
//#include </usr/include/glm/vec3.hpp> // glm::vec3
//#include </usr/include/glm/vec4.hpp> // glm::vec4
//#include </usr/include/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
//#include </usr/include/glm/gtc/type_ptr.hpp> // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::mat4
//#include "glm/gtc/quaternion.hpp"
//#include "glm/gtx/quaternion.hpp"
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
//#include <sys/time.h>

#ifdef WINDOWS
#pragma comment(lib,"user32.lib") 
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
#endif

/*
EM_BOOL mainloop(double time, void* userData) {

	glDraw(NULL, NULL, (int)userData);
	return 1;
}
*/

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
			//gettimeofday(&tempTime, NULL);
			//currentTime = (tempTime.tv_sec * 1000) + (tempTime.tv_usec / 1000);

			//if (currentTime - lastTime > theAnimation->frameTimeMS) {
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
				/*SDL_SetRenderDrawColor(rdr, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(rdr);
				SDL_SetRenderDrawColor(rdr, 0, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(rdr, &rect);
       				SDL_RenderPresent(rdr);
				*/
				//SDL_GL_SwapWindow(wnd);
				//SDL_UpdateWindowSurface(wnd);
				//EM_ASM({console.log("////> init done");});
				currentFrame++;
				//lastTime = currentTime;
			//}
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
	//EM_ASM({console.log("////> init done");});

	#ifdef EMT
	#else
	cout << "GL init... \n";
	#endif
	glInit(NULL);
	//EM_ASM({console.log("////> gl init done");});

	#ifdef EMT
	#else
	cout << "Initializing shaders... \n";
	#endif
	glInitShaders(0);

	//EM_ASM({console.log("////> start of parenting shapes");});
	#ifdef EMT
	#else
	cout << "Associating parents... \n";
	#endif
	parentShapes();

	//EM_ASM({console.log("////> start of prepping shapes");});
	//itAdjust();

	//EM_ASM({console.log("////> start of prepping shapes");});
	#ifdef EMT
	#else
	cout << "Prepping shapes... \n";
	#endif
	prepShapes();

	//EM_ASM({console.log("////> start of offsetting parented shapes");});
	parentOffsetShapes();

//	//EM_ASM({console.log("////> start of prepping transforms for shapes");});
//	prepParentShapes();

	//EM_ASM({console.log("////> start of prepping transforms for shapes");});
	#ifdef EMT
	#else
	cout << "Prepping transform shapes... \n";
	#endif
	prepTransformShapes();
	//EM_ASM({console.log("////> matching VAOs");});
	#ifdef EMT
	#else
	cout << "Match parent VAOs... \n";
	#endif
	if (animationSequence != NULL) {
		matchParentVAO();
	}

	//EM_ASM({console.log("////> done prepping shapes " + $0);}, theAnimation->frameTimeMS);
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
	//gettimeofday(&tempTime, NULL);
	//lastTime = (tempTime.tv_sec * 1000) + (tempTime.tv_usec / 1000);
	standaloneLoop();
	#endif
}


int doMain(char someChar[]) {

	identityMatrix = glm::mat4(1.0f);

	deserialize();
	//EM_ASM({console.log("////> init done");});
	glInit(NULL);
	//EM_ASM({console.log("////> gl init done");});

	glInitShaders(0);
	//EM_ASM({console.log("////> start of prepping shapes");});
	prepShapes();
	//EM_ASM({console.log("////> done prepping shapes");});

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
		//std::cout << line << std::endl;
	}
	if (jsonString.size() > 0) {
		cout << "Loading animation \n";
		int theLength = jsonString.length();
		char* jString = new char[theLength];
		std::strcpy(jString, jsonString.c_str());
		//char* jsonCharString = strdup(jsonString.c_str());
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
		//glewExperimental = GL_TRUE;
		cout << SDL_GetError() << "\n";
		cout << "Attempting standalone \n";
		//glutInit(&argc, argv);
		//glutCreateWindow("test");
		/*glutInitDisplayMode(GLUT_RGB);
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			cout << "GLEW not ok: " << glewGetErrorString(err) << "\n";
			exit(1);
		}
		if (!GLEW_VERSION_2_1) {
			cout << "GLEW version mismatch \n";
			exit(1);
		}*/

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
			//cout << "Pass 3 colours and alpha value please \n";
		}
	#endif

	//doMain(NULL);
	return 1;
}

