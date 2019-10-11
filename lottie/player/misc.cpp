
struct XY {
	int x;
	int y;
};

struct ArrayOfFloat {
	struct ArrayOfFloat* parent = NULL; // only one
	struct ArrayOfFloat* child = NULL; // only one
	float isSubArray = false;
	vector<float> value;
} *currentArrayOfFloat;

struct ArrayOfString {
	struct ArrayOfString* parent = NULL; // only one
	struct ArrayOfString* child = NULL; // only one
	float isSubArray = false;
	vector<string> value;
} *currentArrayOfString;

struct KeyValue {
	struct KeyValue* start = NULL;
	struct KeyValue* next = NULL;
	struct KeyValue* prev = NULL;

	string key;
	string value = NULL;
	struct ArrayOfString* arrayValue;
} *currentKeyValue;

struct KeyValueTrail {
	struct KeyValueTrail* start = NULL;
	struct KeyValueTrail* next = NULL;
	struct KeyValueTrail* prev = NULL;

	struct KeyValue* keyValue = NULL;
} *currentKeyValueTrail;

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

int addChildArray(struct KeyValue* traceKeyValue) {
	struct ArrayOfString* tempArrayOfString;
	tempArrayOfString = new ArrayOfString;
	currentArrayOfString = tempArrayOfString;
	tempArrayOfString->parent = traceKeyValue->arrayValue;
	traceKeyValue->arrayValue->child = tempArrayOfString;
	traceKeyValue->arrayValue = tempArrayOfString;

	return 1;
}

int gotoParentArray(struct KeyValue* traceKeyValue) {
	if (traceKeyValue->arrayValue->parent != NULL) {
		traceKeyValue->arrayValue = traceKeyValue->arrayValue->parent;
	}
	return 1;
}

int newKeyValueTrail() {
	if (currentKeyValueTrail == NULL) {
		currentKeyValueTrail = new KeyValueTrail;
		currentKeyValueTrail->start = currentKeyValueTrail;

		struct KeyValue* tempKeyValue;
		tempKeyValue = new KeyValue;
		tempKeyValue->start = tempKeyValue;
		currentKeyValueTrail->keyValue = tempKeyValue;
		currentKeyValue = tempKeyValue;
	} else {
		struct KeyValueTrail* tempKeyValueTrail;
		tempKeyValueTrail = new KeyValueTrail;
		currentKeyValueTrail->next = tempKeyValueTrail;
		tempKeyValueTrail->prev = currentKeyValueTrail;
		currentValueTrail = tempKeyValueTrail;
		
		struct KeyValue* tempKeyValue;
		tempKeyValue = new KeyValue;
		tempKeyValue->start = tempKeyValue;
		currentKeyValueTrail->keyValue = tempKeyValue;
		currentKeyValue = tempKeyValue;
	}
	return 1;
}

int removeKeyValueTrail() { // to be called from within associateKeyValue()
	struct KeyValueTrail* tempKeyValueTrail;
	tempKeyValueTrail = currentKeyValueTrail;
	currentKeyValueTrail = currentKeyValueTrail->prev;
	currentKeyValueTrail->next = NULL;
	delete tempKeyValueTrail;
}

int removeKeyValue() {
	struct KeyValue* tempKeyValue;
	currentKeyValue->prev->next = currentKeyValue->next;
	if (currentKeyValue->next != NULL) {
		currentKeyValue->next->prev = currentKeyValue->prev;
	}
	tempKeyValue = currentKeyValue->prev;
	delete currentKeyValue;
	currentKeyValue = tempKeyValue;
}

int addKeyValue(struct KeyValue* traceKeyValue, string key, string value, bool isArray) {
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
		keyNode->arrayValue = new ArrayOfString;
	}
	if (isArray) {
		/*if (isArray) {
			struct ArrayOfString* tempArrayOfString;
			tempArrayOfString = new ArrayOfString;
			currentArrayOfString = tempArrayOfString;
			keyNode->arrayValue->child = tempArrayOfString;
			tempArrayOfString->parent = keyNode->arrayValue;
			keyNode->arrayValue = tempArrayOfString;
		}*/
		keyNode->arrayValue->value.push_back(value);
	} else {
		keyNode->value = value;
	}
	return 1;
}

