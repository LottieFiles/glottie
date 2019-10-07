
struct XY {
	int x;
	int y;
};

struct ArrayOfFloat {
	struct ArrayOfFloat* root;
	struct ArrayOfFloat* subArray;
	vector<float> value;
} *currentArrayOfFloat;

struct ArrayOfString {
	struct ArrayOfString* root;
	struct ArrayOfString* subArray;
	vector<string> value;
} *currentArrayOfString;

struct KeyValue {
	struct KeyValue* start;
	struct KeyValue* end;
	struct KeyValue* next;
	struct KeyValue* prev;

	string key;
	string value = NULL;
	struct ArrayOfString* arrayValue;
} *currentKeyValue;




// functions

int stringToInt(string inputString) {
	stringstream streamer(inputString);
	int outputInt;
	streamer >> outputInt;
	return outputInt;
}

float stringToFloat(string inputString) {
	stringstream streamer(inputString);
	float outputFloat;
	streamer >> outputFloat;
	return outputFloat;
}

