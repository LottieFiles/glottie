struct alignas(ALIGNSIZE) TransformMatrix {
	struct TransformMatrix* start = NULL;
	struct TransformMatrix* prev = NULL;
	struct TransformMatrix* next = NULL; 
	
	glm::mat4 transform = glm::mat4(1.0f);

	float angle;
	glm::vec3 vector;
	glm::vec3 inverseVector;
	float opacity = -1;

	glm::vec3 translate;
	glm::vec3 scale;
	bool isRotate = false;
	bool isScale = false;
	bool isTranslate = false;
	int startTime = -1;
	int endTime = -1;
} *defaultTransformMatrix = NULL;

struct alignas(ALIGNSIZE) VAOList {
	struct VAOList* start = NULL;
	struct VAOList* prev = NULL;
	struct VAOList* next = NULL;

	GLuint *vao;
	int idxSize;

	int frame;
} *boundVAO = NULL;

struct alignas(ALIGNSIZE) BuffersList {
	struct BuffersList* start = NULL;
	struct BuffersList* prev = NULL;
	struct BuffersList* next = NULL;

	/*
	GLuint *vbo;	
	GLuint *cbo;	
	GLuint *ibo;
	*/

	struct Buffers* buffers_v;
};

struct alignas(ALIGNSIZE) CompositionList {
	struct CompositionList* start = NULL;
	struct CompositionList* prev = NULL;
	struct CompositionList* next = NULL;

	struct CompositeArray* composite = NULL;
};

struct alignas(ALIGNSIZE) FrameCompositionRef {
	struct FrameCompositionRef* start = NULL;
	struct FrameCompositionRef* prev = NULL;
	struct FrameCompositionRef* next = NULL;

	struct CompositionList* compositionList = NULL;

	int frame;
} *layersAnimationSequence = NULL, *shapesAnimationSequence = NULL;

struct alignas(ALIGNSIZE) CompositeArray {
	struct CompositeArray* start = NULL;
	struct CompositeArray* prev = NULL;
	struct CompositeArray* next = NULL;

	struct BuffersList* buffers = NULL;

	struct VAOList* vaol = NULL;

	//struct TransformMatrix* position = NULL;
	//struct TransformMatrix* scale = NULL;
	/*
	glm::mat4 position = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	*/

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);

	float opacity = -1;

	float rotateAngle = -1;

	int frame = -1;

	bool positionSet = false;
	bool scaleSet = false;
	bool rotateSet = false;
	bool opacitySet = false;

	bool transformSet = false;
};

struct alignas(ALIGNSIZE) Transform {
	struct TransformAOV* p = NULL;
	struct TransformAOV* r = NULL;
	struct TransformAOV* s = NULL;
	struct TransformAOV* o = NULL;

	struct CompositeArray* composite = NULL;

	int startTime = -1;
	int endTime = -1;
};

struct alignas(ALIGNSIZE) TransformAOV {
	struct ArrayOfVertex* v = NULL;
	struct ArrayOfVertex* i = NULL;
	struct ArrayOfVertex* o = NULL;

	struct TransformMatrix* transformMatrix = NULL;

	int startTime = -1;
	int endTime = -1;
	float* frames;
	float* segSize;
	int v_count = 0;
	int bezier_count = 0;
	int s_count;

};

struct Vertex* lastPosition;

