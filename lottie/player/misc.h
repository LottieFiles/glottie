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

#ifdef EMT
struct alignas(ALIGNSIZE) XY {
#else
struct XY {
#endif
	int x;
	int y;
};

#ifdef EMT
struct alignas(ALIGNSIZE) BezierCurve {
#else
struct BezierCurve {
#endif
	float* x = 0;
	float* y = 0;
	float* z = 0;
};

#ifdef EMT
struct alignas(ALIGNSIZE) Vertex {
#else
struct Vertex {
#endif
	//GLfloat position[4];
	GLfloat x,y,z,a;
};

#ifdef EMT
struct alignas(ALIGNSIZE) ReturnPosition {
#else
struct ReturnPosition {
#endif
	struct Vertex* layers = NULL;
	struct Vertex* shapes = NULL;
	//struct Vertex* layersTranslated = NULL;
	//struct Vertex* shapesTranslated = NULL;
};

#ifdef EMT
struct alignas(ALIGNSIZE) ArrayOfVertex {
#else
struct ArrayOfVertex {
#endif
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

#ifdef EMT
struct alignas(ALIGNSIZE) ArrayOfArrayOfVertex {
#else
struct ArrayOfArrayOfVertex {
#endif
	struct ArrayOfArrayOfVertex* start = NULL;
	struct ArrayOfArrayOfVertex* next = NULL;
	struct ArrayOfArrayOfVertex* prev = NULL;

	struct ArrayOfVertex* arrayItem;

	bool traversed = false;
	bool translated = false;
};

#ifdef EMT
struct alignas(ALIGNSIZE) Dimensions {
#else
struct Dimensions {
#endif
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

#ifdef EMT
struct alignas(ALIGNSIZE) ValuesVector {
#else
struct ValuesVector {
#endif
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

#ifdef EMT
struct alignas(ALIGNSIZE) ArrayOfString {
#else
struct ArrayOfString {
#endif
	struct ArrayOfString* root = NULL;

	//float isSubArray = false;
	struct ValuesVector* parent = NULL;

	struct ValuesVector* vector = NULL;

	bool closed = false;
} *currentArrayOfString;

#ifdef EMT
struct alignas(ALIGNSIZE) KeyValue {
#else
struct KeyValue {
#endif
	//string key;
	char key[KVLEN];
	//string value = NULL;
	char value[KVLEN];
	struct KeyValue* start = NULL;
	struct KeyValue* next = NULL;
	struct KeyValue* prev = NULL;

	struct ArrayOfString* arrayValue = NULL;
} *currentKeyValue;

#ifdef EMT
struct alignas(ALIGNSIZE) KeyValueTrail {
#else
struct KeyValueTrail {
#endif
	struct KeyValueTrail* start = NULL;
	struct KeyValueTrail* next = NULL;
	struct KeyValueTrail* prev = NULL;

	struct KeyValue* keyValue = NULL;
} *currentKeyValueTrail;

#ifdef EMT
struct alignas(ALIGNSIZE) textBlock {
#else
struct textBlock {
#endif
	struct textBlock* start = NULL;
	struct textBlock* next = NULL;
	struct textBlock* prev = NULL;

	char text[TEXTBLOCK];
};

#ifdef EMT
struct alignas(ALIGNSIZE) TriangulateReturn {
#else
struct TriangulateReturn {
#endif
	//GLfloat* vbo;
	//struct Vertex* vbo;
	//struct Vertex* cbo;
	//struct IndexArray* index;
	std::vector<GLfloat> vbo;
	std::vector<GLfloat> cbo;
	std::vector<unsigned int> index;
	int idxCount;
};

#ifdef EMT
struct alignas(ALIGNSIZE) ColorsReturn {
#else
struct ColorsReturn {
#endif
	GLfloat* cbo;
	int cboLength;
};

#ifdef EMT
struct alignas(ALIGNSIZE) FloatArrayReturn {
#else
struct FloatArrayReturn {
#endif
	float* floatArray;
	int count;
};

#ifdef EMT
struct alignas(ALIGNSIZE) IntArrayReturn {
#else
struct IntArrayReturn {
#endif
	int* intArray;
	int count;
};

#ifdef EMT
struct alignas(ALIGNSIZE) IndexArray {
#else
struct IndexArray {
#endif
	//unsigned int position[3];
	int x;
	int y;
	int z;
};

#ifdef EMT
struct alignas(ALIGNSIZE) BoundingBox {
#else
struct BoundingBox {
#endif
	float w = 0; // width
	float h = 0; // height
	// without layer offset
	float baseX = 0; // only the x-axis value
	float baseY = 0; // only the y-axis value
	float baseZ = 0; // only the z-axis value

	float offsetX = 0; // the offset to apply (due to parents)
	float offsetY = 0; // 
	float offsetZ = 0; // 

	// with layer offset
	float initX = 0; // top of bounding box
	float initY = 0; // left  of bounding box
	float initXc = 0; // center of bounding box
	float initYc = 0; // center of bounding box

	float initXf = 0; // center of bounding box
	float initYf = 0; // center of bounding box

	float initXfc = 0; // center of bounding box
	float initYfc = 0; // center of bounding box

	float anchorX = 0;
	float anchorY = 0;

	float translatedX = 0;
	float translatedY = 0;

	float anchorZ = 0;

	bool anchorSet = false;
	bool offsetSet = false;
};

