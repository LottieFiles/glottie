enum Phase {
		_maxX,
		_minX,
		_maxY,
		_minY,
		_passedMaxX,
		_passedMinX,
		_passedMaxY,
		_passedMinY
	};

struct XY {
	int x;
	int y;
};

struct alignas(ALIGNSIZE) BezierCurve {
	float* x = 0;
	float* y = 0;
	float* z = 0;
};

//struct alignas(alignof(struct Vertex*)) Vertex {
struct alignas(ALIGNSIZE) Vertex {
//struct Vertex {
	//GLfloat position[4];
	GLfloat x,y,z,a;
};

//struct alignas(alignof(struct ArrayOfVertex*)) ArrayOfVertex {
struct alignas(ALIGNSIZE) ArrayOfVertex {
//struct ArrayOfVertex {
	struct ArrayOfVertex* start = NULL;
	struct ArrayOfVertex* next = NULL;
	struct ArrayOfVertex* prev = NULL;

	struct ArrayOfVertex* bindNext = NULL;
	struct ArrayOfVertex* bindPrev = NULL;

	struct ArrayOfVertex* reserveNext = NULL;

	struct Vertex* vertex = NULL;
	int order;
	int idxOrder;
	bool reserved = false;
	bool bezier = false;
};

struct alignas(ALIGNSIZE) ArrayOfArrayOfVertex {
	struct ArrayOfArrayOfVertex* start = NULL;
	struct ArrayOfArrayOfVertex* next = NULL;
	struct ArrayOfArrayOfVertex* prev = NULL;

	struct ArrayOfVertex* arrayItem;
};

struct alignas(ALIGNSIZE) Dimensions {
	struct ArrayOfVertex* topVertex = NULL;

	GLfloat maxXval = 0;
	GLfloat minXval = 0;
	GLfloat maxYval = 0;
	GLfloat minYval = 0;

	unsigned int maxXord;
	unsigned int minXord;
	unsigned int maxYord;
	unsigned int minYord;
};

/*
struct ArrayOfFloat {
	struct ArrayOfFloat* parent = NULL; // only one
	struct ArrayOfFloat* child = NULL; // only one
	float isSubArray = false;
	vector<float> value;
} *currentArrayOfFloat;
*/

//struct alignas(alignof(struct ValuesVector*)) ValuesVector {
struct alignas(ALIGNSIZE) ValuesVector {
//struct ValuesVector {
	char value[KVLEN];
	struct ValuesVector* start = NULL;
	struct ValuesVector* prev = NULL;
	struct ValuesVector* next = NULL;

	//struct ArrayOfString* rootKey = NULL;
	struct ArrayOfString* root = NULL;
	struct ArrayOfString* parent = NULL; // only one
	struct ArrayOfString* child = NULL; // only one

	//string value;
};

//struct alignas(alignof(struct ArrayOfString*)) ArrayOfString {
struct alignas(ALIGNSIZE) ArrayOfString {
//struct ArrayOfString {
	struct ArrayOfString* root = NULL;

	//float isSubArray = false;
	struct ValuesVector* parent = NULL;

	struct ValuesVector* vector = NULL;

	bool closed = false;
} *currentArrayOfString;

//struct alignas(alignof(struct KeyValue*)) KeyValue {
struct alignas(ALIGNSIZE) KeyValue {
//struct KeyValue {
	//string key;
	char key[KVLEN];
	//string value = NULL;
	char value[KVLEN];
	struct KeyValue* start = NULL;
	struct KeyValue* next = NULL;
	struct KeyValue* prev = NULL;

	struct ArrayOfString* arrayValue = NULL;
} *currentKeyValue;

//struct alignas(alignof(struct KeyValueTrail*)) KeyValueTrail {
//struct alignas(16777216) KeyValueTrail {
struct alignas(ALIGNSIZE) KeyValueTrail {
//struct KeyValueTrail {
	struct KeyValueTrail* start = NULL;
	struct KeyValueTrail* next = NULL;
	struct KeyValueTrail* prev = NULL;

	struct KeyValue* keyValue = NULL;
} *currentKeyValueTrail;

struct alignas(ALIGNSIZE) textBlock {
	struct textBlock* start = NULL;
	struct textBlock* next = NULL;
	struct textBlock* prev = NULL;

	char text[TEXTBLOCK];
};

struct alignas(ALIGNSIZE) TriangulateReturn {
	//GLfloat* vbo;
	//struct Vertex* vbo;
	//struct Vertex* cbo;
	//struct IndexArray* index;
	std::vector<GLfloat> vbo;
	std::vector<GLfloat> cbo;
	std::vector<unsigned int> index;
	int idxCount;
};

struct alignas(ALIGNSIZE) ColorsReturn {
	GLfloat* cbo;
	int cboLength;
};

struct alignas(ALIGNSIZE) FloatArrayReturn {
	float* floatArray;
	int count;
};

struct alignas(ALIGNSIZE) IntArrayReturn {
	int* intArray;
	int count;
};

struct alignas(ALIGNSIZE) IndexArray {
	//unsigned int position[3];
	int x;
	int y;
	int z;
};

struct alignas(ALIGNSIZE) BoundingBox {
	float w;
	float h;
	float initX;
	float initY;
	float anchorX;
	float anchorY;
};

struct alignas(ALIGNSIZE) Transform {
	struct TransformAOV* p = NULL;
};
