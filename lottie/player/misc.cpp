
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
		currentKeyValueTrail = tempKeyValueTrail;
		
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

	return 1;
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

	return 1;
}

int addKeyValue(struct KeyValue* traceKeyValue, string key, string value, bool isArray) {
	bool exhausted = false;
	struct KeyValue* keyNode = NULL;
	keyNode = new KeyValue;
	struct KeyValue* endNode = NULL;
	endNode = new KeyValue;
	if (traceKeyValue != NULL) {
		struct KeyValue* tempKeyValue = traceKeyValue;
		if (keyFound(traceKeyValue, key)) {
			keyNode = traceKeyValue;
		} else {
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
		}
	} else {
		traceKeyValue = new KeyValue;
		traceKeyValue->start = traceKeyValue;
		traceKeyValue->prev = NULL;
		traceKeyValue->next = NULL;
		keyNode = traceKeyValue;
	}
	if (keyNode == NULL) {
		endNode->next = keyNode;
		keyNode->prev = endNode;
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
	                                EM_ASM_({
                                        console.log("keyvalue_done");
                                });
	return 1;
}

int pushVertex(struct ArrayOfVertex* passedVertex, float vertex[4]) {
	struct ArrayOfVertex* tempAOV;
	tempAOV = new ArrayOfVertex;
	if (passedVertex == NULL) {
		passedVertex = tempAOV;
		passedVertex->start = tempAOV;
		passedVertex->prev = NULL;
		passedVertex->next = NULL;
	} else {
		bool exhausted = false;
		while (! exhausted) {
			if (passedVertex->next == NULL) {
				exhausted = true;
			} else {
				passedVertex = passedVertex->next;
			}
		}
		tempAOV->prev = passedVertex;
		passedVertex->next = tempAOV;
		tempAOV->start = passedVertex->start;
		passedVertex = tempAOV;
	}

	passedVertex->vertex->position[0] = vertex[0];
	passedVertex->vertex->position[1] = vertex[1];
	passedVertex->vertex->position[2] = vertex[2];
	passedVertex->vertex->position[3] = vertex[3];

	return 1;
}

//////////// type converters


