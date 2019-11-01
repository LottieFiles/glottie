
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

struct ValuesVector {
	struct ValuesVector* start = NULL;
	struct ValuesVector* prev = NULL;
	struct ValuesVector* next = NULL;
	//string value;
	char value[30];
};

struct ArrayOfString {
	struct ArrayOfString* root = NULL;
	struct ArrayOfString* parent = NULL; // only one
	struct ArrayOfString* child = NULL; // only one
	//float isSubArray = false;
	struct ValuesVector* vector = NULL;
} *currentArrayOfString;

struct KeyValue {
	struct KeyValue* start = NULL;
	struct KeyValue* next = NULL;
	struct KeyValue* prev = NULL;

	//string key;
	char key[30];
	//string value = NULL;
	char value[30];
	struct ArrayOfString* arrayValue = NULL;
} *currentKeyValue;

struct KeyValueTrail {
	struct KeyValueTrail* start = NULL;
	struct KeyValueTrail* next = NULL;
	struct KeyValueTrail* prev = NULL;

	struct KeyValue* keyValue = NULL;
} *currentKeyValueTrail;


