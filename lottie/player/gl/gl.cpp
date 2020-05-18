// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position; \n"
    "attribute vec4 color; \n"
    "varying vec4 vcolors; \n"
    "uniform mat4 transform; \n"
    "void main() \n"
    "{ \n"
    "  vcolors = color; \n"
    "  gl_Position = position * transform; \n"
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
		//EM_ASM({console.log("..................> vertex shader failed")});
	}
	if (fragmentSuccess == GL_FALSE) {
		//EM_ASM({console.log("..................> fragment shader failed")});
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
	//EM_ASM_({console.log("glinit 1.0 " + $0 + " " + $1 + " " + $2);}, theAnimation->w, theAnimation->h, theAnimation->scaleFactor);
	//SDL_Init(SDL_INIT_VIDEO);

	//EM_ASM_({console.log("glinit 9 " + $0 + " " + $1 + " " + $2);}, theAnimation->w, theAnimation->h, theAnimation->scaleFactor);

	//int* someInt = new int[5000000]();
	//delete[] someInt;
	//wnd = new SDL_Window;
	SDL_Init(SDL_INIT_EVERYTHING);

	int scaledWidth = theAnimation->w;
	int scaledHeight = theAnimation->h;
    
	//EM_ASM_({console.log("glinit 1.0 " + $0 + " " + $1);}, scaledWidth, scaledHeight);

	//wnd = SDL_CreateWindow("lottie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scaledWidth, scaledHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	//wnd = SDL_CreateWindow("lottie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scaledWidth, scaledHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	//wnd = new SDL_Window();
	wnd = SDL_CreateWindow("lottie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scaledWidth, scaledHeight, 0);


	/*SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);*/

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); 

	//EM_ASM({console.log("glinit 1.1");});
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	//EM_ASM({console.log("glinit 1.2");});
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	//EM_ASM({console.log("glinit 1.3");});
	SDL_GL_SetSwapInterval(0);
	//EM_ASM({console.log("glinit 1.4");});
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//EM_ASM({console.log("glinit 1.5");});

	//glEnable(GL_MULTISAMPLE);
	//EM_ASM({console.log("glinit 1.6 " + $0);}, wnd);
	glc = SDL_GL_CreateContext(wnd);

	//EM_ASM({console.log("glinit 1.7");});
	//rdr = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	rdr = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetWindowSize(wnd, theAnimation->w * theAnimation->scaleFactorX, theAnimation->h * theAnimation->scaleFactorY);
	SDL_RenderSetLogicalSize(rdr, theAnimation->w * theAnimation->scaleFactorX, theAnimation->h * theAnimation->scaleFactorY);
	SDL_RenderSetScale(rdr, theAnimation->scaleFactorX, theAnimation->scaleFactorY);
	//EM_ASM({console.log("glinit 1.8");});
}

float _xPos = 0;
float _yPos = 0;
float _zPos = 0;
float _translation = false;
float _rotation = false;
void glDraw(struct ShaderProgram* passedShaderProgram, struct Buffers* buffersToRender, int frame) {

	//loop = [&]
	//{
		/*
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT) std::terminate();
		}
		*/

		// Clear the screen to black
		//if (redrawRequired) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			//glColor3f(0, 0, 0);
			//glPolygonMode(GL_LINES);
			//EM_ASM({console.log("glDraw 1.0");});
	
			// Draw a triangle from the 3 vertices
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			if (redrawList == NULL) {
				//EM_ASM({console.log("glDraw 1.0 " + $0);}, frame);
				//EM_ASM({console.log("glDraw 1.1");});
				bool exhausted = false;
				//struct Buffers* tempBuffers = lastBuffersCreated->start;
				if (lastBuffersCreated == NULL) {
					//EM_ASM({console.log("no buffers!");});
					return;
				}
				struct Buffers* tempBuffers = lastBuffersCreated->start->prev;

				bool firstCycleDone = false;

				while (!exhausted) {
					_xPos = 0;
					_yPos = 0;
					_zPos = 0;
					//EM_ASM({console.log("glDraw 1.2");});
					if (tempBuffers->vao != NULL) {
						//EM_ASM({console.log("glDraw 1.2.1");});
						if (passedShaderProgram == NULL) {
							glUseProgram(mainShader);
						} else {
							glUseProgram(*(passedShaderProgram->shader));
						}
						if (tempBuffers->shapesTransform != NULL && tempBuffers->shapesTransform->p != NULL && tempBuffers->shapesTransform->p->startTime <= frame && tempBuffers->shapesTransform->p->endTime >= frame) {
							if (tempBuffers->shapesTransform->p != NULL) {
								_xPos = (tempBuffers->shapesTransform->p->vertex.at(tempBuffers->shapesTransform->p->startTime - frame))->x;
								_yPos = (tempBuffers->shapesTransform->p->vertex.at(tempBuffers->shapesTransform->p->startTime - frame))->y;
								_zPos = (tempBuffers->shapesTransform->p->vertex.at(tempBuffers->shapesTransform->p->startTime - frame))->z;
								_translation = true;
							}
						}
						//EM_ASM({console.log("glDraw 1.2.2");});
						if (tempBuffers->layersTransform != NULL) {
							//EM_ASM({console.log("glDraw 1.2.2.1 ");});
							if (tempBuffers->layersTransform->p != NULL && tempBuffers->layersTransform->p->startTime <= frame && tempBuffers->layersTransform->p->endTime >= frame) {
									//EM_ASM({console.log("glDraw 1.3.1");});
									_xPos = _xPos + (tempBuffers->layersTransform->p->vertex.at(tempBuffers->layersTransform->p->startTime - frame))->x;
									//EM_ASM({console.log("glDraw 1.3.2");});
									_yPos = _yPos + (tempBuffers->layersTransform->p->vertex.at(tempBuffers->layersTransform->p->startTime - frame))->y;
									//EM_ASM({console.log("glDraw 1.3.3");});
									_zPos = _zPos + (tempBuffers->layersTransform->p->vertex.at(tempBuffers->layersTransform->p->startTime - frame))->z;
									_translation = true;
							}
						}
						//EM_ASM({console.log("glDraw 1.3");});
						//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						glm::mat4 trans = glm::mat4(1.0f);
						if (_translation) {
							//glTranslatef((GLfloat)_xPos, (GLfloat)_yPos, (GLfloat)_zPos);
							//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(_xPos, _yPos, _zPos));
							trans = glm::translate(trans, glm::vec3(_xPos, _yPos, _zPos));
						}
						unsigned int transformLoc = glGetUniformLocation(mainShader, "transform");
						glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

						glBindVertexArrayOES(*(tempBuffers->vao));
						//glBindBuffer(GL_ARRAY_BUFFER, *(tempBuffers->vbo));
						//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(tempBuffers->ibo));
						//EM_ASM({console.log("glDraw 1.5 " + $0);}, tempBuffers->idx.size());
						glDrawElements(GL_TRIANGLES, tempBuffers->idx.size(), GL_UNSIGNED_INT, 0);
						glBindVertexArrayOES(0);
						glUseProgram(0);
						//SDL_GL_SwapWindow(wnd);
						//EM_ASM({console.log("glDraw 1.6");});
					}
					//EM_ASM({console.log("glDraw 1.7");});

					if (tempBuffers->prev == tempBuffers->start->prev && firstCycleDone) {
						exhausted = true;
					} else {
						tempBuffers = tempBuffers->prev;
					}
					firstCycleDone = true;
					/*
					if (tempBuffers->next == NULL) {
						exhausted = true;
					} else {
						tempBuffers = tempBuffers->next;
					}
					*/
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
			//EM_ASM({console.log("glDraw DONE");});
		//}
	//};

}

