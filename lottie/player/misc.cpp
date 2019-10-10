
struct XY {
	int x;
	int y;
};

struct ArrayOfFloat {
	struct ArrayOfFloat* parent; // only one
	struct ArrayOfFloat* child; // only one
	float isSubArray = false;
	vector<float> value;
} *currentArrayOfFloat;

struct ArrayOfString {
	struct ArrayOfString* parent; // only one
	struct ArrayOfString* child; // only one
	float isSubArray = false;
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

bool keyFound(struct KeyValue* tempKeyValue, string key) {
	if (tempKeyValue->key == key) {
		return true;
	}
	return false;
}

struct KeyValue* addKeyValue(struct KeyValue* traceKeyValue, string key, string value, bool isArray) {
	bool exhausted = false;
	struct KeyValue* keyNode = NULL;
	struct KeyValue* endNode = NULL;
	if (traceKeyValue != NULL) {
		struct KeyValue* tempKeyValue = traceKeyValue;
		if (keyFound(traceKeyValue, key)) {
			keyNode = traceKeyValue;
		}
		while (! exhausted) {
			if (keyFound(tempKeyValue, key)) {
				keyNode = tempKeyValue;
			}
			if (tempKeyValue->next == NULL) {
				endNode = tempKeyValue;
				exhausted = true;
			}
			tempKeyValue = tempKeyValue->next;
		}
	} else {
		traceKeyValue = new KeyValue;
		traceKeyValue->start = traceKeyValue;
		traceKeyValue->prev = NULL;
		traceKeyValue->next = NULL;
	}
	if (keyNode == NULL) {
		keyNode = new KeyValue;
		traceKeyValue->endNode->next = keyNode;
		keyNode->prev = traceKeyValue->end;
		keyNode->start = traceKeyValue->start;
	}
	if (isArray) {
		if (isArray) {
			struct ArrayOfString* tempArrayOfString;
			tempArrayOfString = new ArrayOfString;
			currentArrayOfString = tempArrayOfString;
			keyNode->arrayValue->child = tempArrayOfString;
			tempArrayOfString->parent = keyNode->arrayValue;
			keyNode->arrayValue = tempArrayOfString;
		}
		keyNode->arrayValue->value.push_back(value);
	} else {
		keyNode->value = value;
	}
	return 1;
}

