#define KVLEN 21

struct XY {
	int x;
	int y;
};

//struct alignas(alignof(struct Vertex*)) Vertex {
struct alignas(32) Vertex {
//struct Vertex {
	GLfloat position[4];
};

//struct alignas(alignof(struct ArrayOfVertex*)) ArrayOfVertex {
struct alignas(32) ArrayOfVertex {
//struct ArrayOfVertex {
	struct ArrayOfVertex* start = NULL;
	struct ArrayOfVertex* next = NULL;
	struct ArrayOfVertex* prev = NULL;
	struct ArrayOfVertex* end = NULL;

	struct Vertex* vertex = NULL;
};

struct ArrayOfFloat {
	struct ArrayOfFloat* parent = NULL; // only one
	struct ArrayOfFloat* child = NULL; // only one
	float isSubArray = false;
	vector<float> value;
} *currentArrayOfFloat;

//struct alignas(alignof(struct ValuesVector*)) ValuesVector {
struct alignas(256) ValuesVector {
//struct ValuesVector {
	struct ValuesVector* start = NULL;
	struct ValuesVector* prev = NULL;
	struct ValuesVector* next = NULL;

	//struct ArrayOfString* rootKey = NULL;
	struct ArrayOfString* root = NULL;
	struct ArrayOfString* parent = NULL; // only one
	struct ArrayOfString* child = NULL; // only one


	//string value;
	char value[KVLEN];
};

//struct alignas(alignof(struct ArrayOfString*)) ArrayOfString {
struct alignas(32) ArrayOfString {
//struct ArrayOfString {
	struct ArrayOfString* root = NULL;

	//float isSubArray = false;
	struct ValuesVector* parent = NULL;

	struct ValuesVector* vector = NULL;

	bool closed = false;
} *currentArrayOfString;

//struct alignas(alignof(struct KeyValue*)) KeyValue {
struct alignas(512) KeyValue {
//struct KeyValue {
	struct KeyValue* start = NULL;
	struct KeyValue* next = NULL;
	struct KeyValue* prev = NULL;

	//string key;
	char key[KVLEN];
	//string value = NULL;
	char value[KVLEN];
	struct ArrayOfString* arrayValue = NULL;
} *currentKeyValue;

//struct alignas(alignof(struct KeyValueTrail*)) KeyValueTrail {
//struct alignas(16777216) KeyValueTrail {
struct alignas(32) KeyValueTrail {
//struct KeyValueTrail {
	struct KeyValueTrail* start = NULL;
	struct KeyValueTrail* next = NULL;
	struct KeyValueTrail* prev = NULL;

	struct KeyValue* keyValue = NULL;
} *currentKeyValueTrail;


