
struct XY {
	int x;
	int y;
};

struct Vertex {
	GLfloat position[4];
};

struct ArrayOfVertex {
	struct ArrayOfVertex* start;
	struct ArrayOfVertex* next;
	struct ArrayOfVertex* prev;

	struct Vertex* vertex;
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
	struct ValuesVector* start = NULL;
	struct ValuesVector* prev = NULL;
	struct ValuesVector* next = NULL;
	//string value;
	char value[21];
};

//struct alignas(alignof(struct ArrayOfString*)) ArrayOfString {
struct alignas(256) ArrayOfString {
//struct ArrayOfString {
	struct ArrayOfString* root = NULL;
	struct ArrayOfString* parent = NULL; // only one
	struct ArrayOfString* child = NULL; // only one
	//float isSubArray = false;
	struct ValuesVector* vector = NULL;
} *currentArrayOfString;

//struct alignas(alignof(struct KeyValue*)) KeyValue {
struct alignas(512) KeyValue {
//struct KeyValue {
	struct KeyValue* start = NULL;
	struct KeyValue* next = NULL;
	struct KeyValue* prev = NULL;

	//string key;
	char key[21];
	//string value = NULL;
	char value[21];
	struct ArrayOfString* arrayValue = NULL;
} *currentKeyValue;

//struct alignas(alignof(struct KeyValueTrail*)) KeyValueTrail {
//struct alignas(16777216) KeyValueTrail {
struct alignas(1024) KeyValueTrail {
//struct KeyValueTrail {
	struct KeyValueTrail* start = NULL;
	struct KeyValueTrail* next = NULL;
	struct KeyValueTrail* prev = NULL;

	struct KeyValue* keyValue = NULL;
} *currentKeyValueTrail;


