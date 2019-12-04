#define KVLEN 21

struct XY {
	int x;
	int y;
};

//struct alignas(alignof(struct Vertex*)) Vertex {
struct alignas(128) Vertex {
//struct Vertex {
	GLfloat position[4];
};

//struct alignas(alignof(struct ArrayOfVertex*)) ArrayOfVertex {
struct alignas(128) ArrayOfVertex {
//struct ArrayOfVertex {
	struct ArrayOfVertex* start = NULL;
	struct ArrayOfVertex* next = NULL;
	struct ArrayOfVertex* prev = NULL;

	struct Vertex* vertex = NULL;
};

struct ArrayOfFloat {
	struct ArrayOfFloat* parent = NULL; // only one
	struct ArrayOfFloat* child = NULL; // only one
	float isSubArray = false;
	vector<float> value;
} *currentArrayOfFloat;

//struct alignas(alignof(struct ValuesVector*)) ValuesVector {
struct alignas(128) ValuesVector {
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
struct alignas(128) ArrayOfString {
//struct ArrayOfString {
	struct ArrayOfString* root = NULL;

	//float isSubArray = false;
	struct ValuesVector* parent = NULL;

	struct ValuesVector* vector = NULL;

	bool closed = false;
} *currentArrayOfString;

//struct alignas(alignof(struct KeyValue*)) KeyValue {
struct alignas(128) KeyValue {
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
struct alignas(128) KeyValueTrail {
//struct KeyValueTrail {
	struct KeyValueTrail* start = NULL;
	struct KeyValueTrail* next = NULL;
	struct KeyValueTrail* prev = NULL;

	struct KeyValue* keyValue = NULL;
} *currentKeyValueTrail;


