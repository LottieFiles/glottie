// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position; \n"
    "attribute vec4 color; \n"
    "varying vec4 vcolors; \n"
    "uniform int layersPosition; \n"
    "uniform int shapesPosition; \n"
    "uniform mat4 layersRotate; \n"
    "uniform mat4 shapesRotate; \n"
    "uniform mat4 layersScale; \n"
    "uniform mat4 shapesScale; \n"
    "uniform mat4 layersTransform; \n"
    "uniform mat4 shapesTransform; \n"
    "uniform float objectOpacity; \n"
    "uniform mat4 layersPrecomputed; \n"
    "uniform int isLayersPrecomputed; \n"
    "uniform mat4 shapesPrecomputed; \n"
    "uniform int isShapesPrecomputed; \n"
    "void main() \n"
    "{ \n"
    "    if (shapesPosition == 1 && layersPosition == 1) {\n"
    "      gl_Position = ((layersRotate * shapesRotate) * (layersScale * shapesScale) * (layersTransform * shapesTransform)) * position; \n"
    "    } else if (layersPosition == 1) {\n"
    "      gl_Position = (layersTransform * (layersScale * (layersRotate * position))); \n"
    "    } else if (shapesPosition == 1) {\n"
    "      gl_Position = (shapesRotate * shapesScale * shapesTransform) * position; \n"
    "    } else {\n"
    "      gl_Position = position; \n"
    "    }\n"
    "  vcolors = vec4(color.xyz, objectOpacity); \n"
    "} \n";

const GLchar* fragmentSource =
    "precision mediump float; \n"
    "varying vec4 vcolors; \n"
    "void main() \n"
    "{ \n"
    "  gl_FragColor = vcolors; \n"
    "} \n";



//    "  if (isLayersPrecomputed == 1) {\n"
//    "      gl_Position = layersPrecomputed * position; \n"
//    "  } else if (isShapesPrecomputed == 1) {\n"
//    "      gl_Position = shapesPrecomputed * position; \n"
//    "  } else if (isShapesPrecomputed == 1 && isLayersPrecomputed == 1) {\n"
//    "      gl_Position = layersPrecomputed * (shapesPrecomputed * position); \n"
//    "  } else {\n"
//    "      gl_Position = position; \n"
//    "  }\n"

//    "  vcolors = color; \n"
//    "  gl_Position = (layersTransform * shapesTransform) * position; \n"
//    "uniform mat4 shapesTranslate; \n"
//    "uniform mat4 shapesScale; \n"
//    "uniform mat4 shapesRotate; \n"
//    "uniform mat4 layersTranslate; \n"
//    "uniform mat4 layersScale; \n"
//    "uniform mat4 layersRotate; \n"
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

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); 

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
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

		glm::mat4 lastShapesP = glm::mat4(1.0f);
		glm::mat4 lastShapesS = glm::mat4(1.0f);
		glm::mat4 lastShapesR = glm::mat4(1.0f);
		glm::mat4 lastLayersP = glm::mat4(1.0f);
		glm::mat4 lastLayersS = glm::mat4(1.0f);
		glm::mat4 lastLayersR = glm::mat4(1.0f);
	
		float lastShapesO;
		float lastLayersO;

		glm::mat4 lastLayersPrecomputed = glm::mat4(1.0f);
		int isLayersPrecomputed;
		glm::mat4 lastShapesPrecomputed = glm::mat4(1.0f);
		int isShapesPrecomputed;



		unsigned int layersTransformLoc;
		unsigned int shapesTransformLoc;
		unsigned int layersRotateLoc;
		unsigned int shapesRotateLoc;
		unsigned int layersScaleLoc;
		unsigned int shapesScaleLoc;

		unsigned int layersPositionLoc;
		unsigned int shapesPositionLoc;

		unsigned int layersPrecomputedLoc;
		unsigned int isLayersPrecomputedLoc;
		unsigned int shapesPrecomputedLoc;
		unsigned int isShapesPrecomputedLoc;

		unsigned int opacityValue;


void glDraw(struct ShaderProgram* passedShaderProgram, struct Buffers* buffersToRender, int frame) {


	if (frame == 0 && firstPass) {
		secondPass = true;
	}

	if (frame == 0 && ! firstPass) {
		firstPass = true;
	}

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);




		//struct Buffers* tempBuffers = lastBuffersCreated->start;
		if (lastBuffersCreated == NULL) {
			//EM_ASM({console.log("no buffers!");});
			return;
		}
		struct Buffers* tempBuffers = lastBuffersCreated->start->prev;
		struct VAOList* tempVAOL;

		bool buffersExhausted;
		bool firstCycleDone = false;
		bool bogusDone = false;
		int layersPosition = 0;
		int shapesPosition = 0;

		if (passedShaderProgram == NULL) {
			glUseProgram(mainShader);
		} else {
			glUseProgram(*(passedShaderProgram->shader));
		}

		/*
		if (frame == 0) {
			tempBuffers->layersTransformSet = false;
			tempBuffers->shapesTransformSet = false;
			tempBuffers->layersScaleSet = false;
			tempBuffers->shapesScaleSet = false;
			tempBuffers->layersRotateSet = false;
			tempBuffers->shapesRotateSet = false;
		}
		*/

		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale");

		layersPositionLoc = glGetUniformLocation(mainShader, "layersPosition");
		shapesPositionLoc = glGetUniformLocation(mainShader, "shapesPosition");


		layersPrecomputedLoc = glGetUniformLocation(mainShader, "layersPrecomputed");
		isLayersPrecomputedLoc = glGetUniformLocation(mainShader, "isLayersPrecomputed");

		shapesPrecomputedLoc = glGetUniformLocation(mainShader, "shapesPrecomputed");
		isShapesPrecomputedLoc = glGetUniformLocation(mainShader, "isShapesPrecomputed");


		opacityValue = glGetUniformLocation(mainShader, "objectOpacity");


		lastLayersP = identityMatrix;
		lastLayersS = identityMatrix;
		lastLayersR = identityMatrix;
		lastShapesP = identityMatrix;
		lastShapesS = identityMatrix;
		lastShapesR = identityMatrix;

		lastLayersPrecomputed = identityMatrix;
		lastShapesPrecomputed = identityMatrix;
		isLayersPrecomputed = 1;

		lastShapesO = 1.0f;
		lastLayersO = 1.0f;

		bool exhausted = false;

		glUniform1f(opacityValue, 1.0f);
		glUniform1i(shapesPositionLoc, 0);
		glUniform1i(layersPositionLoc, 0);
		while (! exhausted) {
			glUniform1i(isLayersPrecomputedLoc, 0);
			glUniform1i(isShapesPrecomputedLoc, 0);
			if (! tempBuffers->addedToComposition) {
				glBindVertexArrayOES(*(tempBuffers->vao));
				glDrawElements(GL_TRIANGLES, tempBuffers->idx.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArrayOES(0);
			}

			if (tempBuffers->prev == tempBuffers->start->prev && firstCycleDone) {
				exhausted = true;
			} else {
				tempBuffers = tempBuffers->prev;
			}
			firstCycleDone = true;
		}


		if (frame == 0) {
			if (animationSequence != NULL && animationSequence->start != NULL) {
				animationSequence = animationSequence->start;
			}
		}

		struct CompositeArray* currentCA = NULL;
		struct VAOList* currentVAOL = NULL;

		struct CompositionList* shapesCL = NULL;
		struct CompositionList* layersCL = NULL;

		//if (animationSequence != NULL && animationSequence->vaol != NULL) {
		//}




		exhausted = false;
		bool exhaustedCL = false;

		bool firstSubCycleDone = false;
		firstCycleDone = false;

		if (animationSequence != NULL && animationSequence->vaol != NULL) {

			currentVAOL = animationSequence->vaol->start->prev;

			while (! exhausted) {

				if (currentVAOL->vao != NULL) {
					lastShapesO = 1.0f;
					lastLayersO = 1.0f;
	
					if (currentVAOL->layersComposite != NULL) {
						lastLayersP = currentVAOL->layersComposite->transform;
						lastLayersS = currentVAOL->layersComposite->scale;
						lastLayersR = currentVAOL->layersComposite->rotate;
						lastLayersO = currentVAOL->layersComposite->opacity;
						lastLayersPrecomputed = currentVAOL->layersComposite->precomputed;
	
						glUniformMatrix4fv(layersTransformLoc, 1, GL_FALSE, glm::value_ptr(lastLayersP));
						glUniformMatrix4fv(layersRotateLoc, 1, GL_FALSE, glm::value_ptr(lastLayersR));
						glUniformMatrix4fv(layersScaleLoc, 1, GL_FALSE, glm::value_ptr(lastLayersS));
						glUniformMatrix4fv(layersPrecomputedLoc, 1, GL_FALSE, glm::value_ptr(lastLayersPrecomputed));
	
						glUniform1i(layersPositionLoc, 1);
						glUniform1i(isLayersPrecomputedLoc, 1);
	
					} else {
						glUniform1i(layersPositionLoc, 0);
						glUniform1i(isLayersPrecomputedLoc, 0);
					}
	
					if (currentVAOL->shapesComposite != NULL) {
						lastShapesP = currentVAOL->shapesComposite->transform;
						lastShapesS = currentVAOL->shapesComposite->scale;
						lastShapesR = currentVAOL->shapesComposite->rotate;
						lastShapesO = currentVAOL->shapesComposite->opacity;
						lastShapesPrecomputed = currentVAOL->shapesComposite->precomputed;
	
						glUniformMatrix4fv(shapesTransformLoc, 1, GL_FALSE, glm::value_ptr(lastShapesP));
						glUniformMatrix4fv(shapesRotateLoc, 1, GL_FALSE, glm::value_ptr(lastShapesR));
						glUniformMatrix4fv(shapesScaleLoc, 1, GL_FALSE, glm::value_ptr(lastShapesS));
						glUniformMatrix4fv(shapesPrecomputedLoc, 1, GL_FALSE, glm::value_ptr(lastShapesPrecomputed));
	
						glUniform1i(shapesPositionLoc, 1);
						glUniform1i(isShapesPrecomputedLoc, 1);
	
					} else {
						glUniform1i(shapesPositionLoc, 0);
						glUniform1i(isShapesPrecomputedLoc, 0);
					}
	
					if (lastLayersO < lastShapesO) {
						glUniform1f(opacityValue, lastLayersO);
					} else {
						glUniform1f(opacityValue, lastShapesO);	
					}
	
					glBindVertexArrayOES(*(currentVAOL->vao));
					glDrawElements(GL_TRIANGLES, currentVAOL->idxSize, GL_UNSIGNED_INT, 0);
					glBindVertexArrayOES(0);
				}

				if (currentVAOL == currentVAOL->start) {
					exhausted = true;
				} else {
					currentVAOL = currentVAOL->prev;
				}

			}

		}

		glUseProgram(0);

		if (animationSequence != NULL && animationSequence->next != NULL) {
			animationSequence = animationSequence->next;
		}

		return;

}

