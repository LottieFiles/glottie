// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position; \n"
    "attribute vec4 color; \n"
    "varying vec4 vcolors; \n"
    "void main() \n"
    "{ \n"
    "  vcolors = color; \n"
    "  gl_Position = position; \n"
    "} \n";

const GLchar* fragmentSource =
    "precision mediump float; \n"
    "varying vec4 vcolors; \n"
    "void main() \n"
    "{ \n"
    "  gl_FragColor = vcolors; \n"
    "} \n";

//    "  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); \n"
//    "  gl_FragColor = vcolors; \n"
//    "out vec4 FragColor; \n"
//    "precision mediump float; \n"
//    "precision mediump float; \n"

void glInitShaders(int refIndex) {
	GLuint tempShaderProgram;
	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint vertexSuccess = 0;
	GLint fragmentSuccess = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
	if (vertexSuccess == GL_FALSE) {
		EM_ASM({console.log("..................> vertex shader failed")});
	}
	if (fragmentSuccess == GL_FALSE) {
		EM_ASM({console.log("..................> fragment shader failed")});
	}

	// Link the vertex and fragment shader into a shader program
	tempShaderProgram = glCreateProgram();

	glAttachShader(tempShaderProgram, vertexShader);
	glAttachShader(tempShaderProgram, fragmentShader);
	// glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(tempShaderProgram);
	glUseProgram(tempShaderProgram);

	if (refIndex == 0) {
		mainShader = tempShaderProgram;
	} else {
		struct ShaderProgram* passedShaderProgram;
		passedShaderProgram = newShaderProgram();
		passedShaderProgram->shader = &tempShaderProgram;
	}
}

void glInit() {   
	EM_ASM_({console.log("glinit 1.0 " + $0 + " " + $1 + " " + $2);}, theAnimation->w, theAnimation->h, theAnimation->scaleFactor);
	//SDL_Init(SDL_INIT_VIDEO);

	EM_ASM_({console.log("glinit 9 " + $0 + " " + $1 + " " + $2);}, theAnimation->w, theAnimation->h, theAnimation->scaleFactor);

	//int* someInt = new int[5000000]();
	//delete[] someInt;
	//wnd = new SDL_Window;

	int scaledWidth = theAnimation->w * theAnimation->scaleFactor;
	int scaledHeight = theAnimation->h * theAnimation->scaleFactor;
    
	EM_ASM_({console.log("glinit 1.0 " + $0 + " " + $1);}, scaledWidth, scaledHeight);

	//wnd = SDL_CreateWindow("lottie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scaledWidth, scaledHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	//wnd = SDL_CreateWindow("lottie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scaledWidth, scaledHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	//wnd = new SDL_Window();
	wnd = SDL_CreateWindow("lottie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scaledWidth, scaledHeight, 0);

	EM_ASM({console.log("glinit 1.1");});
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	EM_ASM({console.log("glinit 1.2");});
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	EM_ASM({console.log("glinit 1.3");});
	SDL_GL_SetSwapInterval(0);
	EM_ASM({console.log("glinit 1.4");});
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	EM_ASM({console.log("glinit 1.5");});
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	EM_ASM({console.log("glinit 1.6 " + $0);}, wnd);
	glc = SDL_GL_CreateContext(wnd);

	EM_ASM({console.log("glinit 1.7");});
	//rdr = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	rdr = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
	EM_ASM({console.log("glinit 1.8");});
}

void glDraw(struct ShaderProgram* passedShaderProgram, struct Buffers* buffersToRender) {
	loop = [&]
	{
		/*
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT) std::terminate();
		}
		*/

		// Clear the screen to black
		if (redrawRequired) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			//glColor3f(0, 0, 0);
			//glPolygonMode(GL_LINES);
			EM_ASM({console.log("glDraw 1.0");});
	
			// Draw a triangle from the 3 vertices
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			if (redrawList == NULL) {
				EM_ASM({console.log("glDraw 1.1");});
				bool exhausted = false;
				struct Buffers* tempBuffers = lastBuffersCreated->start;

				while (!exhausted) {
					EM_ASM({console.log("glDraw 1.2");});
					if (tempBuffers->vao != NULL) {
						EM_ASM({console.log("glDraw 1.2.1");});
						if (passedShaderProgram == NULL) {
							glUseProgram(mainShader);
						} else {
							glUseProgram(*(passedShaderProgram->shader));
						}
						EM_ASM({console.log("glDraw 1.3");});
						//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						glBindVertexArrayOES(*(tempBuffers->vao));
						//glBindBuffer(GL_ARRAY_BUFFER, *(tempBuffers->vbo));
						//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(tempBuffers->ibo));
						EM_ASM({console.log("glDraw 1.5 " + $0);}, tempBuffers->idx.size());
						glDrawElements(GL_TRIANGLES, tempBuffers->idx.size(), GL_UNSIGNED_INT, 0);
						glBindVertexArrayOES(0);
						glUseProgram(0);
						//SDL_GL_SwapWindow(wnd);
						EM_ASM({console.log("glDraw 1.6");});
					}
					EM_ASM({console.log("glDraw 1.7");});
					if (tempBuffers->next == NULL) {
						exhausted = true;
					} else {
						tempBuffers = tempBuffers->next;
					}
					//break;
				}
			} else {
				bool exhausted = false;
				struct RedrawBuffers* tempRedrawList;
				tempRedrawList = redrawList->start;
				struct Buffers* tempBuffers;

				while (!exhausted) {
					if (passedShaderProgram == NULL) {
						glUseProgram(mainShader);
					} else {
						glUseProgram(*(passedShaderProgram->shader));
					}
					tempBuffers = tempRedrawList->buffers;
					glBindVertexArrayOES(*(tempBuffers->vao));
					glDrawElements(GL_TRIANGLES, tempBuffers->idxCount, GL_UNSIGNED_INT, 0);
					glBindVertexArrayOES(0);
					if (tempRedrawList->next == NULL) {
						exhausted = true;
					} else {
						tempRedrawList = tempRedrawList->next;
						delete tempRedrawList->prev;
					}
				}
				redrawList = NULL;
				//SDL_GL_SwapWindow(wnd);
			}
			redrawRequired = false;
			//SDL_GL_SwapWindow(wnd);
			EM_ASM({console.log("glDraw DONE");});
		}
	};

        #ifdef __EMSCRIPTEN__
                //emscripten_set_main_loop(main_loop, 0, true);
                emscripten_set_main_loop(_doMain, 0, true);
        #else
                //while(true) main_loop();
                while(true) _doMain();
        #endif
}

