

#define KVLEN 128

#ifdef EMT
#define ALIGNSIZE 256
#endif

#define TEXTBLOCK 220

//#include <functional>

#include "configure.h"

#ifdef EMT
#include <emscripten.h> // emscripten
#include <emscripten/html5.h> // emscripten
#endif



#ifdef EMT
#else
	#ifdef APPLE
		#include <OpenGL/gl.h>
		//#include <OpenGL/glu.h>
		//#include <OpenGL/glext.h>
		//#include <GLUT/glut.h>
	#else
		#include <GL/glew.h>
		//#include <GL/glfw3.h>
		#include <GLFW/glfw3.h>
		//#include <GL/glu.h>
		//#include <GL/glext.h>
		//#include <GL/glx.h>
		//#include <GL/gl.h>
		//#include <GL/glut.h>
		//#include <GL/freeglut.h>
	#endif
#endif

#ifdef EMT
	#define GL_GLEXT_PROTOTYPES
	#include <SDL2/SDL.h> // emscripten
	#include <SDL_opengles2.h> // empscripten
#else
	#include <SDL2/SDL.h> // emscripten
	#include <SDL2/SDL_opengl.h>
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
#include <sys/time.h>


using namespace std;

#ifdef EMT
/*
std::function<void()> loop;
void mainloop() { loop(); }
void _doMain() { loop(); }
*/
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
struct timeval tempTime;
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
	cout << theAnimation->frameTime << " is frame time \n";
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
				glDraw(NULL, NULL, currentFrame);
       				//SDL_RenderPresent(rdr);
				SDL_GL_SwapWindow(wnd);
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
	cout << "Deserializing... \n";
	#endif
	deserializeChar(buffer, theLength);
	//EM_ASM({console.log("////> init done");});

	#ifdef EMT
	#else
	cout << "GL init... \n";
	#endif
	glInit();
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

	//gettimeofday(&timeRef, NULL);
	//double currentTime = (double)timeRef.tv_sec + ((double)timeRef.tv_usec / 1000000);
	//EM_ASM({console.log("////> TIME " + $0 + " ");}, currentTime);

	/*
	if (! lastBuffersCreated->filled) {
		lastBuffersCreated = lastBuffersCreated->prev;
	}
	lastBuffersCreated->next = lastBuffersCreated->start;
	//EM_ASM({console.log("////> pre-starting");});
	lastBuffersCreated->start->prev = lastBuffersCreated;
	*/

	//EM_ASM({console.log("////> starting");});
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
	//layersAnimationSequence = layersAnimationSequence->start;
	//shapesAnimationSequence = shapesAnimationSequence->start;
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
	gettimeofday(&tempTime, NULL);
	lastTime = (tempTime.tv_sec * 1000) + (tempTime.tv_usec / 1000);
	standaloneLoop();
	#endif
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

	identityMatrix = glm::mat4(1.0f);

	deserialize();
	//EM_ASM({console.log("////> init done");});
	glInit();
	//EM_ASM({console.log("////> gl init done");});

	glInitShaders(0);
	//EM_ASM({console.log("////> start of prepping shapes");});
	prepShapes();
	//EM_ASM({console.log("////> done prepping shapes");});

	redrawRequired = true;

	struct Buffers* buffersToRender;
/*	if (lastBuffersCreated != NULL) {
		buffersToRender = lastBuffersCreated->start->next->next;
		buffersToRender->start = buffersToRender;
		buffersToRender->next = NULL;
		//glDraw(NULL, NULL);
	}*/



	//EM_ASM({console.log("////> done drawing " + $0 + " " + $1);}, theAnimation->w, theAnimation->h);

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
		loadJson(strdup(jsonString.c_str()), jsonString.size(), bgRed, bgGreen, bgBlue, bgAlpha);
	} else {
		cout << "Nothing \n";
	}
	cout << "Done \n";
}

int main(int argc, char *argv[]) {
	//SDL_Init(SDL_INIT_EVERYTHING);

	#ifdef EMT
	#else
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
			cout << "Pass 3 colours and alpha value please \n";
		}
	#endif

	//doMain(NULL);
}

