// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position; \n"
    "attribute vec4 color; \n"
    "varying vec4 vcolors; \n"
    "uniform mat4 shapesTranslate; \n"
    "uniform mat4 shapesScale; \n"
    "uniform mat4 shapesRotate; \n"
    "uniform mat4 layersTranslate; \n"
    "uniform mat4 layersScale; \n"
    "uniform mat4 layersRotate; \n"
    "void main() \n"
    "{ \n"
    "  gl_Position = (layersScale * layersTranslate * layersRotate) * ((shapesScale * shapesTranslate * shapesRotate) * position); \n"
    "  vcolors = color; \n"
    "} \n";

const GLchar* fragmentSource =
    "precision mediump float; \n"
    "varying vec4 vcolors; \n"
    "void main() \n"
    "{ \n"
    "  gl_FragColor = vcolors; \n"
    "} \n";

//    "  gl_Position = (layersScale * layersTranslate * layersRotate) * ((shapesScale * shapesTranslate * shapesRotate) * position); \n"
//    "  gl_Position = ( (shapesScale * layersTranslate) * ((layersScale * layersTranslate) * position) ); \n"
//    "  gl_Position = ((shapesScale * layersScale) * (shapesTranslate * layersTranslate)) * position; \n"
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
	SDL_SetWindowSize(wnd, theAnimation->w, theAnimation->h);
	SDL_RenderSetLogicalSize(rdr, theAnimation->w, theAnimation->h);
	//SDL_RenderSetScale(rdr, theAnimation->scaleFactorX, theAnimation->scaleFactorY);
	//EM_ASM({console.log("glinit 1.8");});
}

float _xPos = 0;
float _yPos = 0;
float _zPos = 0;
float _translation = false;
float _rotation = false;
int deltaFrame = 0;
/*glm::mat4 trans;
glm::mat4 transShapesP;
glm::mat4 transShapesS;
glm::mat4 transLayersP;
glm::mat4 transLayersS;
glm::mat4 transL;
*/

glm::mat4 lastLayersPosition;
glm::mat4 lastLayersScale;
glm::mat4 lastLayersRotate;
glm::mat4 lastShapesPosition;
glm::mat4 lastShapesScale;
glm::mat4 lastShapesRotate;

bool lastLayersPositionSet = false;
bool lastLayersScaleSet = false;
bool lastLayersRotateSet = false;
bool lastShapesPositionSet = false;
bool lastShapesScaleSet = false;
bool lastShapesRotateSet = false;

bool firstPass = false;
bool secondPass = false;

glm::mat4 identityMatrix = glm::mat4(1.0f);

void glDraw(struct ShaderProgram* passedShaderProgram, struct Buffers* buffersToRender, int frame) {


	if (frame == 0 && firstPass) {
		secondPass = true;
	}

	if (frame == 0 && ! firstPass) {
		firstPass = true;
	}
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
					if (frame == 0) {
						tempBuffers->lastLayersPositionSet = false;
						tempBuffers->lastLayersScaleSet = false;
						tempBuffers->lastLayersRotateSet = false;
						tempBuffers->lastShapesPositionSet = false;
						tempBuffers->lastShapesScaleSet = false;
						tempBuffers->lastShapesRotateSet = false;
					}

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



						//shapesComposite = NULL;
						//layersComposite = NULL;
						if (	(tempBuffers->shapesTransform != NULL && tempBuffers->shapesTransform->startTime > frame) || 
							(tempBuffers->layersTransform != NULL && tempBuffers->layersTransform->startTime > frame)) {
								if (tempBuffers->prev == tempBuffers->start->prev && firstCycleDone) {
									exhausted = true;
								} else {
									tempBuffers = tempBuffers->prev;
								}
								firstCycleDone = true;
								continue;
						}

						unsigned int shapesTranslateLoc = glGetUniformLocation(mainShader, "shapesTranslate");
						unsigned int shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale");
						unsigned int shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate");
						unsigned int layersTranslateLoc = glGetUniformLocation(mainShader, "layersTranslate");
						unsigned int layersScaleLoc = glGetUniformLocation(mainShader, "layersScale");
						unsigned int layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate");

						//if (! secondPass) {					
						_translation = true;
						if (tempBuffers->shapesTransform != NULL && tempBuffers->shapesTransform->startTime <= frame) {
							if (tempBuffers->shapesTransform->startTime == frame) {
								tempBuffers->shapesTransform->composite = tempBuffers->shapesTransform->composite->start;
							} else {
								if (tempBuffers->shapesTransform->composite != NULL && tempBuffers->shapesTransform->composite->next != NULL) {
									tempBuffers->shapesTransform->composite = tempBuffers->shapesTransform->composite->next;
								}
							}
							if (tempBuffers->shapesTransform->composite != NULL) {
								//transShapesP = tempBuffers->shapesTransform->composite->position;
								//transShapesS = tempBuffers->shapesTransform->composite->scale;
								if (tempBuffers->shapesTransform->composite->positionSet) {
									//glUniformMatrix4fv(shapesTranslateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->shapesTransform->composite->position));
									tempBuffers->lastShapesPosition = tempBuffers->shapesTransform->composite->position;
									tempBuffers->lastShapesPositionSet = true;
								} else {
									_translation = false;

								}
								if (tempBuffers->shapesTransform->composite->scaleSet) {
									//glUniformMatrix4fv(shapesScaleLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->shapesTransform->composite->scale));
									tempBuffers->lastShapesScale = tempBuffers->shapesTransform->composite->scale;
									tempBuffers->lastShapesScaleSet = true;
								} else {
									_translation = false;

								}
								if (tempBuffers->shapesTransform->composite->rotateSet) {
									//glUniformMatrix4fv(shapesRotateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->shapesTransform->composite->rotate));
									tempBuffers->lastShapesRotate = tempBuffers->shapesTransform->composite->rotate;
									tempBuffers->lastShapesRotateSet = true;
								} else {
									_translation = false;
								}
							} else {

								_translation = false;
							}
						} else {

							_translation = false;
							/*
							glUniformMatrix4fv(shapesTranslateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
							glUniformMatrix4fv(shapesScaleLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
							glUniformMatrix4fv(shapesRotateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
							*/
						}
									if (tempBuffers->lastShapesPositionSet) {
										glUniformMatrix4fv(shapesTranslateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->lastShapesPosition));
									} else {
										glUniformMatrix4fv(shapesTranslateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
									}
									if (tempBuffers->lastShapesScaleSet) {
										glUniformMatrix4fv(shapesScaleLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->lastShapesScale));
									} else {
										glUniformMatrix4fv(shapesScaleLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
									}
									if (tempBuffers->lastShapesRotateSet) {
										glUniformMatrix4fv(shapesRotateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->lastShapesRotate));
									} else {
										glUniformMatrix4fv(shapesRotateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
									}


						_translation = true;
						if (tempBuffers->layersTransform != NULL && tempBuffers->layersTransform->startTime <= frame) {
							if (tempBuffers->layersTransform->startTime == frame) {
								tempBuffers->layersTransform->composite = tempBuffers->layersTransform->composite->start;
							} else {
								if (tempBuffers->layersTransform->composite != NULL && tempBuffers->layersTransform->composite->next != NULL) {
									tempBuffers->layersTransform->composite = tempBuffers->layersTransform->composite->next;
								}
							}
							if (tempBuffers->layersTransform->composite != NULL && tempBuffers->layersTransform->composite->frame > -1) {
								//transLayersP = tempBuffers->layersTransform->composite->position;
								//transLayersS = tempBuffers->layersTransform->composite->scale;
								if (tempBuffers->layersTransform->composite->positionSet) {
									//glUniformMatrix4fv(layersTranslateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->layersTransform->composite->position));
									tempBuffers->lastLayersPosition = tempBuffers->layersTransform->composite->position;
									tempBuffers->lastLayersPositionSet = true;
								} else {
									_translation = false;

								}
								if (tempBuffers->layersTransform->composite->scaleSet) {
									//glUniformMatrix4fv(layersScaleLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->layersTransform->composite->scale));
									tempBuffers->lastLayersScale = tempBuffers->layersTransform->composite->scale;
									tempBuffers->lastLayersScaleSet = true;
								} else {
									_translation = false;

								}
								if (tempBuffers->layersTransform->composite->rotateSet) {
									//glUniformMatrix4fv(layersRotateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->layersTransform->composite->rotate));
									tempBuffers->lastLayersRotate = tempBuffers->layersTransform->composite->rotate;
									tempBuffers->lastLayersRotateSet = true;
								} else {
									_translation = false;

								}
							} else {
								_translation = false;

							}
						} else {

							_translation = false;
							/*
							glUniformMatrix4fv(layersTranslateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
							glUniformMatrix4fv(layersScaleLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
							glUniformMatrix4fv(layersRotateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
							*/
						}

									if (tempBuffers->lastLayersPositionSet) {
										glUniformMatrix4fv(layersTranslateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->lastLayersPosition));
									} else {
										glUniformMatrix4fv(layersTranslateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
									}
									if (tempBuffers->lastLayersScaleSet) {
										glUniformMatrix4fv(layersScaleLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->lastLayersScale));
									} else {
										glUniformMatrix4fv(layersScaleLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
									}
									if (tempBuffers->lastLayersRotateSet) {
										glUniformMatrix4fv(layersRotateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->lastLayersRotate));
									} else {
										glUniformMatrix4fv(layersRotateLoc, 1, GL_FALSE, glm::value_ptr(identityMatrix));
									}



/*
						glUniformMatrix4fv(shapesTranslateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->shapesPosition));
						glUniformMatrix4fv(shapesScaleLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->shapesScale));
						glUniformMatrix4fv(shapesRotateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->shapesRotate));

						glUniformMatrix4fv(layersTranslateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->layersPosition));
						glUniformMatrix4fv(layersScaleLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->layersScale));
						glUniformMatrix4fv(layersRotateLoc, 1, GL_FALSE, glm::value_ptr(tempBuffers->layersRotate));

*/


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

