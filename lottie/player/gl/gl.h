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

int preSwitch[20]; // to determine the switch of assets to layers (and vice versa)
int currentUniversalCount;
SDL_Window* wnd = NULL;
SDL_Renderer* rdr = NULL;
SDL_GLContext glc;
int lastRefIndex = 0;
GLuint mainShader;

bool redrawRequired = false;
//GLuint* shaderProgram;

struct Transform* currentShapesTransform = NULL;
struct Transform* currentLayersTransform = NULL;

#ifdef EMT
struct alignas(ALIGNSIZE) RedrawBuffers {
#else
struct RedrawBuffers {
#endif
	struct RedrawBuffers* start;
	struct RedrawBuffers* next;
	struct RedrawBuffers* prev;

	struct Buffers* buffers;
} *redrawList = NULL;

#ifdef EMT
struct alignas(ALIGNSIZE) ShaderProgram {
#else
struct ShaderProgram {
#endif
	struct ShaderProgram* start = NULL;
	struct ShaderProgram* next = NULL;
	struct ShaderProgram* prev = NULL;

	GLuint* shader;
} *lastShaderProgramCreated;

#ifdef EMT
struct alignas(ALIGNSIZE) Buffers {
#else
struct Buffers {
#endif
	struct Buffers* start = NULL;
	struct Buffers* next = NULL;
	struct Buffers* prev = NULL;

	struct Dimensions* dimensions = NULL;

	struct Transform* shapesTransform = NULL;
	struct Transform* layersTransform = NULL;

	/*
	glm::mat4 lastTrans = glm::mat4(1.0f);
	glm::mat4 lastTransShapesS = glm::mat4(1.0f);
	glm::mat4 lastTransShapesP = glm::mat4(1.0f);
	glm::mat4 lastTransLayersS = glm::mat4(1.0f);
	glm::mat4 lastTransLayersP = glm::mat4(1.0f);
	*/

	//struct CompositeArray* lastShapesComposite;
	//struct CompositeArray* lastLayersComposite;

	glm::mat4 lastLayersTransform;
	glm::mat4 lastShapesTransform;

	bool layersTransformSet = false;
	bool shapesTransformSet = false;

	glm::mat4 lastLayersRotate;
	glm::mat4 lastShapesRotate;

	bool layersRotateSet = false;
	bool shapesRotateSet = false;

	glm::mat4 lastLayersScale;
	glm::mat4 lastShapesScale;

	bool layersScaleSet = false;
	bool shapesScaleSet = false;

	float lastLayersOpacity = 1.0f;
	float lastShapesOpacity = 1.0f;

	bool layersOpacitySet = false;
	bool shapesOpacitySet = false;

	GLint* posAttrib = NULL;
	GLint* colAttrib = NULL;

#ifdef WINDOWS
	struct CVAO* vao = NULL;
#else
	GLuint* vao = NULL;
#endif
	GLuint* vbo = NULL;
	GLuint* cbo = NULL;
	GLuint* ibo = NULL;
	std::vector<unsigned int> idx; // array of triangulation data
	int idxCount;
	bool preppedFrame = false;

	bool firstFrameRendered = false;

	bool lastTransSet = false;

	bool changed = false;
	bool clockwise;

	bool filled = false;

	bool addedToComposition = false;
} *lastBuffersCreated = NULL;

struct CVAO {
	GLint* posAttrib = NULL;
	GLint* colAttrib = NULL;

	GLuint* vao = NULL;
	GLuint* vbo = NULL;
	GLuint* cbo = NULL;
	GLuint* ibo = NULL;
};