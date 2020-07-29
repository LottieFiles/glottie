
//#include "assignAttributeNames.cpp"

#include "vertexShader.cpp"

// Shader sources
/*
const GLchar* vertexSource =
    "attribute vec4 position; \n"
    "attribute vec4 color; \n"
    "varying vec4 vcolors; \n"
    "uniform int transformationsCount; \n"
    "uniform int preAnimation; \n"
    "uniform int layersPositionSet[16]; \n"
    "uniform int shapesPositionSet[16]; \n"
    "uniform mat4 layersRotate[16]; \n"
    "uniform mat4 shapesRotate[16]; \n"
    "uniform mat4 layersScale[16]; \n"
    "uniform mat4 shapesScale[16]; \n"
    "uniform mat4 layersTransform[16]; \n"
    "uniform mat4 shapesTransform[16]; \n"
    "uniform float objectOpacity[16]; \n"
    "uniform float rotateLayersAngle[16]; \n"
    "uniform vec3 rotateLayersAxisOffset[16]; \n"
    "uniform int rotateLayersAngleSet[16]; \n"
    "uniform float rotateShapesAngle[16]; \n"
    "uniform vec3 rotateShapesAxisOffset[16]; \n"
    "uniform int rotateShapesAngleSet[16]; \n"
    "vec4 quat_from_axis_angle(vec3 axis, float angle) \n"
    "{ \n"
    "  vec4 qr; \n"
    "  float half_angle = (angle * 0.5) * 3.14159 / 180.0; \n"
    "  qr.x = axis.x * sin(half_angle); \n"
    "  qr.y = axis.y * sin(half_angle); \n"
    "  qr.z = axis.z * sin(half_angle); \n"
    "  qr.w = cos(half_angle); \n"
    "  return qr; \n"
    "} \n"
    "vec3 rotate_vertex_position(vec3 passedPosition, vec3 axis, float angle) \n"
    "{ \n"
    "  vec4 q = quat_from_axis_angle(axis, angle); \n"
    "  vec3 v = passedPosition.xyz; \n"
    "  return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v); \n"
    "} \n"
    "void main() \n"
    "{ \n"
    "  vec4 glpre; \n"
    "  vec4 gltemp; \n"
    "  if (preAnimation == 1) { \n"
    "    gl_Position = position; \n"
    "  } else { \n"
    "    glpre = position; \n"
    "    for (int i = 0; i < int(transformationsCount); i++) { \n"
    "      int counter = i; \n"
    "      if (shapesPositionSet[counter] == 1 && layersPositionSet[counter] == 1) { \n"
    "        gltemp = ((layersRotate[counter] * shapesRotate[counter]) * (layersScale[counter] * shapesScale[counter]) * (layersTransform[counter] * shapesTransform[counter])) * glpre; \n"
    "      } else if (layersPositionSet[counter] == 1) {\n"
    "        gltemp = layersRotate[counter] * ((layersScale[counter] * layersTransform[counter]) * glpre); \n"
    "      } else if (shapesPositionSet[counter] == 1) {\n"
    "        gltemp = (shapesRotate[counter] * shapesScale[counter] * shapesTransform[counter]) * glpre; \n"
    "      } \n"
    "    } \n"
    "    gl_Position = gltemp; \n"
    "  } \n"
    "  vcolors = vec4(color.xyz, objectOpacity[0]); \n"
    "} \n";
*/

const GLchar* fragmentSource =
    "precision mediump float; \n"
    "varying vec4 vcolors; \n"
    "void main() \n"
    "{ \n"
    "  gl_FragColor = vcolors; \n"
    "} \n";

/*


    "  if (preAnimation == 1) { \n"
    "    if (shapesPositionSet[0] == 1 && layersPositionSet[0] == 1) { \n"
    "      glpre = ((layersRotate[0] * shapesRotate[0]) * (layersScale[0] * shapesScale[0]) * (layersTransform[0] * shapesTransform[0])) * position; \n"
    "    } else if (layersPositionSet[0] == 1) {\n"
    "      glpre = layersRotate[0] * ((layersScale[0] * layersTransform[0]) * position); \n"
    "    } else if (shapesPositionSet[0] == 1) {\n"
    "      glpre = (shapesRotate[0] * shapesScale[0] * shapesTransform[0]) * position; \n"
    "    } else {\n"
    "      glpre = position; \n"
    "    } \n"
    "  } \n"
*/

//    "  if (shapesPositionSet == 1 && layersPositionSet == 1) {\n"
//    "    gl_Position = ((layersRotate * shapesRotate) * (layersScale * shapesScale) * (layersTransform * shapesTransform)) * position; \n"
//    "  } else if (layersPositionSet == 1) {\n"
//    "    gl_Position = layersRotate * ((layersScale * layersTransform) * position); \n"
//    "  } else if (shapesPositionSet == 1) {\n"
//    "    gl_Position = (shapesRotate * shapesScale * shapesTransform) * position; \n"
//    "  } else {\n"
//    "    gl_Position = position; \n"
//    "  }\n"


//    "  if (rotateShapesAngleSet == 1) { \n"
//    "    glpre = vec4(rotate_vertex_position(vec3(glpre.xyz), vec3(0, 0, 1), rotateShapesAngle), 1.0); \n"
//    "  } \n"
//    "  if (rotateLayersAngleSet == 1) { \n"
//    "    glpre = vec4(rotate_vertex_position(vec3(glpre.xyz), vec3(0, 0, 1), rotateLayersAngle), 1.0); \n"
//    "  } \n"
//    "  gl_Position = glpre;\n"


/* in precomputed transformations are needed
    "uniform mat4 layersPrecomputed[16]; \n"
    "uniform int isLayersPrecomputed[16]; \n"
    "uniform mat4 shapesPrecomputed[16]; \n"
    "uniform int isShapesPrecomputed[16]; \n"
*/


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

		/*
		glm::mat4 lastLayersPrecomputed = glm::mat4(1.0f);
		int isLayersPrecomputed;
		glm::mat4 lastShapesPrecomputed = glm::mat4(1.0f);
		int isShapesPrecomputed;
		*/


		unsigned int layersTransformLoc;
		unsigned int shapesTransformLoc;
		unsigned int layersRotateLoc;
		unsigned int shapesRotateLoc;
		unsigned int layersScaleLoc;
		unsigned int shapesScaleLoc;

		unsigned int layersPositionSetLoc;
		unsigned int shapesPositionSetLoc;

		unsigned int preAnimationLoc;

		/*
		unsigned int layersPrecomputedLoc;
		unsigned int isLayersPrecomputedLoc;
		unsigned int shapesPrecomputedLoc;
		unsigned int isShapesPrecomputedLoc;
		*/

		glm::vec3 lastRotateLayersAxisOffset;
		float lastRotateLayersAngle;
		unsigned int lastRotateLayersAngleSet;

		glm::vec3 lastRotateShapesAxisOffset;
		float lastRotateShapesAngle;
		unsigned int lastRotateShapesAngleSet;

		unsigned int rotateShapesAngleLoc;
		unsigned int rotateShapesAngleSetLoc;
		unsigned int rotateShapesAxisOffsetLoc;

		unsigned int rotateLayersAngleLoc;
		unsigned int rotateLayersAngleSetLoc;
		unsigned int rotateLayersAxisOffsetLoc;

		unsigned int opacityValueLoc;
		unsigned int transformationsCountLoc;

		bool VAOLExhausted = false;
		bool parentExhausted = false;

		struct Buffers* tempBuffers;

		bool _firstCycleDone = false;
		int layersPositionSet = 0;
		int shapesPositionSet = 0;

		struct CompositeArray* currentCA = NULL;
		struct VAOList* currentVAOL = NULL;
		struct VAOList* startVAOL = NULL;

		struct CompositionList* shapesCL = NULL;
		struct CompositionList* layersCL = NULL;

		int currentTransformationsCount;


#include "associateShaderAttributes.cpp"

		/*
void associateShaderAttributes(int passedIndex) {

		assignAttributeNames(passedIndex);
		//transformationsCountLoc = glGetUniformLocation(mainShader, "transformationsCount");
		//preAnimationLoc = glGetUniformLocation(mainShader, "preAnimation");

		layersTransformLoc = glGetUniformLocation(mainShader, __layersTransform);
		shapesTransformLoc = glGetUniformLocation(mainShader, __shapesTransform);
		layersRotateLoc = glGetUniformLocation(mainShader, __layersRotate);
		shapesRotateLoc = glGetUniformLocation(mainShader, __shapesRotate);
		layersScaleLoc = glGetUniformLocation(mainShader, __layersScale);
		shapesScaleLoc = glGetUniformLocation(mainShader, __shapesScale);

		layersPositionSetLoc = glGetUniformLocation(mainShader, __layersPositionSet);
		shapesPositionSetLoc = glGetUniformLocation(mainShader, __shapesPositionSet);


		rotateLayersAngleLoc = glGetUniformLocation(mainShader, __rotateLayersAngle);
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, __rotateLayersAngleSet);
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, __rotateLayersAxisOffset);

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, __rotateShapesAngle);
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, __rotateShapesAngleSet);
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, __rotateShapesAxisOffset);

		opacityValueLoc = glGetUniformLocation(mainShader, __opacityValue);


}
*/

void pushShaderAttributes(struct VAOList* passedVAOL, int passedIndex) {

		lastShapesO = 1.0;
		lastLayersO = 1.0;

					if (passedVAOL->layersComposite != NULL) {
						lastLayersP = passedVAOL->layersComposite->transform;
						lastLayersS = passedVAOL->layersComposite->scale;
						lastLayersR = passedVAOL->layersComposite->rotate;
						lastLayersO = passedVAOL->layersComposite->opacity;
						//EM_ASM({console.log("vaol" + $0);}, lastLayersO);
						//lastLayersPrecomputed = passedVAOL->layersComposite->precomputed;
	
						glUniformMatrix4fv(layersTransformLoc, 1, GL_FALSE, glm::value_ptr(lastLayersP));
						glUniformMatrix4fv(layersRotateLoc, 1, GL_FALSE, glm::value_ptr(lastLayersR));
						glUniformMatrix4fv(layersScaleLoc, 1, GL_FALSE, glm::value_ptr(lastLayersS));
						//glUniformMatrix4fv(layersPrecomputedLoc, 1, GL_FALSE, glm::value_ptr(lastLayersPrecomputed));

						if (passedVAOL->layersComposite->rotateSet) {
							lastRotateLayersAngleSet = 1;
							lastRotateLayersAngle = passedVAOL->layersComposite->rotateAngle;
							lastRotateLayersAxisOffset = passedVAOL->layersComposite->rotateAxisOffset;
						}
						glUniform1i(rotateLayersAngleSetLoc, lastRotateLayersAngleSet);
						glUniform1f(rotateLayersAngleLoc, lastRotateLayersAngle);
						glUniform3fv(rotateLayersAxisOffsetLoc, 1, glm::value_ptr(lastRotateLayersAxisOffset));

						glUniform1i(layersPositionSetLoc, 1);
						//glUniform1i(isLayersPrecomputedLoc, 1);
	
					} else {
						glUniform1i(layersPositionSetLoc, 0);
						//glUniform1i(isLayersPrecomputedLoc, 0);
					}
	
					if (passedVAOL->shapesComposite != NULL) {
						lastShapesP = passedVAOL->shapesComposite->transform;
						lastShapesS = passedVAOL->shapesComposite->scale;
						lastShapesR = passedVAOL->shapesComposite->rotate;
						lastShapesO = passedVAOL->shapesComposite->opacity;
						//lastShapesPrecomputed = passedVAOL->shapesComposite->precomputed;
	
						glUniformMatrix4fv(shapesTransformLoc, 1, GL_FALSE, glm::value_ptr(lastShapesP));
						glUniformMatrix4fv(shapesRotateLoc, 1, GL_FALSE, glm::value_ptr(lastShapesR));
						glUniformMatrix4fv(shapesScaleLoc, 1, GL_FALSE, glm::value_ptr(lastShapesS));
						//glUniformMatrix4fv(shapesPrecomputedLoc, 1, GL_FALSE, glm::value_ptr(lastShapesPrecomputed));
			
						if (passedVAOL->shapesComposite->rotateSet) {
							lastRotateShapesAngleSet = 1;
							lastRotateShapesAngle = passedVAOL->shapesComposite->rotateAngle;
							lastRotateShapesAxisOffset = passedVAOL->shapesComposite->rotateAxisOffset;
						}
						glUniform1i(rotateShapesAngleSetLoc, lastRotateShapesAngleSet);
						glUniform1f(rotateShapesAngleLoc, lastRotateShapesAngle);
						glUniform3fv(rotateShapesAxisOffsetLoc, 1, glm::value_ptr(lastRotateShapesAxisOffset));
	
						glUniform1i(shapesPositionSetLoc, 1);
						//glUniform1i(isShapesPrecomputedLoc, 1);
	
					} else {
						glUniform1i(shapesPositionSetLoc, 0);
						//glUniform1i(isShapesPrecomputedLoc, 0);
					}
	
					if (passedVAOL->layersComposite != NULL && passedVAOL->shapesComposite != NULL) {
						if (lastLayersO < lastShapesO) {
							glUniform1f(opacityValueLoc, lastLayersO);
						} else {
							glUniform1f(opacityValueLoc, lastShapesO);	
						}
					} else if (passedVAOL->layersComposite != NULL) {
						glUniform1f(opacityValueLoc, lastLayersO);
					} else if (passedVAOL->shapesComposite != NULL) {
						glUniform1f(opacityValueLoc, lastShapesO);	
					}
	

}



void glDraw(struct ShaderProgram* passedShaderProgram, struct Buffers* buffersToRender, int frame) {


	if (frame == 0 && firstPass) {
		secondPass = true;
	}

	if (frame == 0 && ! firstPass) {
		firstPass = true;
	}

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);


		tempBuffers = lastBuffersCreated->start->prev;


		//struct Buffers* tempBuffers = lastBuffersCreated->start;
		if (lastBuffersCreated == NULL) {
			//EM_ASM({console.log("no buffers!");});
			return;
		}


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



		//associateShaderAttributes(0);

		lastLayersP = identityMatrix;
		lastLayersS = identityMatrix;
		lastLayersR = identityMatrix;
		lastShapesP = identityMatrix;
		lastShapesS = identityMatrix;
		lastShapesR = identityMatrix;

		//lastLayersPrecomputed = identityMatrix;
		//lastShapesPrecomputed = identityMatrix;
		//isLayersPrecomputed = 1;

		lastShapesO = 1.0f;
		lastLayersO = 1.0f;


		lastRotateLayersAngleSet = 0;
		lastRotateShapesAngleSet = 0;

		associateShaderAttributes(0);

		glUniform1i(preAnimationLoc, 1);
		glUniform1i(transformationsCountLoc, -1);
		glUniform1f(opacityValueLoc, 1.0);
		/*
		glUniform1i(rotateLayersAngleSetLoc, lastRotateLayersAngleSet);
		glUniform1i(rotateShapesAngleSetLoc, lastRotateShapesAngleSet);

		glUniform1f(opacityValue, 1.0f);
		glUniform1i(shapesPositionSetLoc, 0);
		glUniform1i(layersPositionSetLoc, 0);
		*/

		VAOLExhausted = false;

		//glUniform1i(shapesPositionSetLoc, 0);
		//glUniform1i(layersPositionSetLoc, 0);


		while (! VAOLExhausted) {
			//glUniform1i(isLayersPrecomputedLoc, 0);
			//glUniform1i(isShapesPrecomputedLoc, 0);
			if (! tempBuffers->addedToComposition) {


				glBindVertexArrayOES(*(tempBuffers->vao));
				glDrawElements(GL_TRIANGLES, tempBuffers->idx.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArrayOES(0);
			}

			if (tempBuffers->prev == tempBuffers->start->prev && _firstCycleDone) {
				VAOLExhausted = true;
			} else {
				tempBuffers = tempBuffers->prev;
			}
			_firstCycleDone = true;
		}


		if (frame == 0) {
			if (animationSequence != NULL && animationSequence->start != NULL) {
				animationSequence = animationSequence->start;
			}
		}

		currentCA = NULL;
		currentVAOL = NULL;

		shapesCL = NULL;
		layersCL = NULL;

		layersPositionSet = 0;
		shapesPositionSet = 0;
		//if (animationSequence != NULL && animationSequence->vaol != NULL) {
		//}




		VAOLExhausted = false;
		parentExhausted = false;

		_firstCycleDone = false;

		if (animationSequence != NULL && animationSequence->vaol != NULL) {

			currentVAOL = animationSequence->vaol->start->prev;

			while (! VAOLExhausted) {

				currentTransformationsCount = 0;

				if (currentVAOL->vao != NULL) {

					lastShapesO = 1.0f;
					lastLayersO = 1.0f;


					associateShaderAttributes(0);
					glUniform1i(preAnimationLoc, 0);
					pushShaderAttributes(currentVAOL, 0);
					currentTransformationsCount++;

					if (currentVAOL->parentVAOL != NULL) {
						startVAOL = currentVAOL;
						
						while (currentVAOL->parentVAOL != NULL) {
							currentVAOL = currentVAOL->parentVAOL;
							associateShaderAttributes(currentTransformationsCount);
							pushShaderAttributes(currentVAOL, currentTransformationsCount);
							currentTransformationsCount++;
						}

						currentVAOL = startVAOL;
					}

					glUniform1i(transformationsCountLoc, currentTransformationsCount);

					glBindVertexArrayOES(*(currentVAOL->vao));
					glDrawElements(GL_TRIANGLES, currentVAOL->idxSize, GL_UNSIGNED_INT, 0);
					glBindVertexArrayOES(0);

				}

				if (currentVAOL == currentVAOL->start) {
					VAOLExhausted = true;
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

