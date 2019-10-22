
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
	if (traceKeyValue->arrayValue == NULL) {
		traceKeyValue->arrayValue = tempArrayOfString;
		return 1;
	}
	currentArrayOfString = tempArrayOfString;
	tempArrayOfString->parent = traceKeyValue->arrayValue;
	traceKeyValue->arrayValue->child = tempArrayOfString;
	traceKeyValue->arrayValue = tempArrayOfString;
	return 1;
}

int gotoParentArray(struct KeyValue* traceKeyValue) {
	if (traceKeyValue->arrayValue != NULL) {
		if (traceKeyValue->arrayValue->parent != NULL) {
			traceKeyValue->arrayValue = traceKeyValue->arrayValue->parent;
		}
	}
	return 1;
}

int popKeyValueTrail() {
	if (currentKeyValueTrail->prev == NULL) {
		if (currentKeyValueTrail != NULL) {
			delete currentKeyValueTrail;
			currentKeyValue = NULL;
			currentKeyValueTrail = NULL;
		}
		return 1;
	}
	currentKeyValueTrail = currentKeyValueTrail->prev;
	delete currentKeyValueTrail->next;
	currentKeyValueTrail->next = NULL;
	currentKeyValue = currentKeyValueTrail->keyValue;
	while (currentKeyValue->next != NULL) {
		currentKeyValue = currentKeyValue->next;
	}
	return 1;
}

int newKeyValueTrail() {
	if (currentKeyValueTrail == NULL) {
		currentKeyValueTrail = new KeyValueTrail;
		currentKeyValueTrail->start = currentKeyValueTrail;
		currentKeyValueTrail->next = NULL;
		currentKeyValueTrail->prev = NULL;
		EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> key trail created");});
		
	} else {
		struct KeyValueTrail* tempKeyValueTrail;
		tempKeyValueTrail = new KeyValueTrail;
		currentKeyValueTrail->next = tempKeyValueTrail;
		tempKeyValueTrail->prev = currentKeyValueTrail;
		tempKeyValueTrail->start = currentKeyValueTrail->start;
		currentKeyValueTrail = tempKeyValueTrail;
		EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> key trail extended");});
		
	}
	return 1;
}

int deleteArrayValue(struct ArrayOfString* passedArrayValue) {
	if (passedArrayValue->child != NULL) {
		deleteArrayValue(passedArrayValue->child);
		delete passedArrayValue;
	} else {
		delete passedArrayValue;
	}
	EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> deleted arrayofstring");});
	return 1;
}

int deleteKeyValues(struct KeyValueTrail* passedKeyValueTrail) {
	EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> deleting kv");});
	if (passedKeyValueTrail == NULL) {
		return 0;
	}
	struct KeyValue* tempKeyValue;
	struct KeyValue* temptempKeyValue;
	tempKeyValue = passedKeyValueTrail->keyValue;
	tempKeyValue = tempKeyValue->start;
	EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> deleting kv 0.1");});
	int counter = 0;
	while (tempKeyValue->next != NULL) {
		counter++;
		EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> deleting kv 0.0.1 " + $0);}, counter);
		temptempKeyValue = tempKeyValue;
		tempKeyValue = tempKeyValue->next;
		//deleteArrayValue(temptempKeyValue->arrayValue);
		delete temptempKeyValue;
	}
	EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> deleting kv 0.2");});
	delete temptempKeyValue->arrayValue;
	delete temptempKeyValue;
	EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> deleting kv 0.3");});
	if (passedKeyValueTrail->prev != NULL) {
		if (passedKeyValueTrail->next != NULL) {
			passedKeyValueTrail->next->prev = passedKeyValueTrail->prev;
		} else {
			passedKeyValueTrail->next->prev = NULL;
		}
	}
	EM_ASM({console.log(">>>>>>>>>>>>>>>>>>>> deleting kv 0.4");});
	if (passedKeyValueTrail->next != NULL) {
		if (passedKeyValueTrail->prev != NULL) {
			passedKeyValueTrail->prev->next = passedKeyValueTrail->next;
		} else {
			passedKeyValueTrail->prev->next = NULL;
		}
	}
		
	delete passedKeyValueTrail;
	return 1;
}

int removeKeyValueTrail() { // to be called from within associateKeyValue()
	struct KeyValueTrail* tempKeyValueTrail;
	tempKeyValueTrail = currentKeyValueTrail;
	if (currentKeyValueTrail->prev != NULL) {
		currentKeyValueTrail = currentKeyValueTrail->prev;
		currentKeyValue = currentKeyValueTrail->keyValue;
		//currentKeyValue->next = NULL;
		currentArrayOfString = currentKeyValueTrail->keyValue->arrayValue;
		currentKeyValueTrail->next = NULL;

		//deleteKeyValues(tempKeyValueTrail);
		delete tempKeyValueTrail;
	}

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

int pushValuesVector(struct ValuesVector* traceVector, string tempString) {
	struct ValuesVector* tempVector;
	tempVector = new ValuesVector;
	if (traceVector == NULL) {
		traceVector = new ValuesVector;
		traceVector->start = traceVector;
		traceVector->next = NULL;
		traceVector->prev = NULL;
		traceVector->value.reserve(30);
		traceVector->value = tempString;
	} else {
		traceVector->value.reserve(30);
		tempVector->value = tempString;
		traceVector->next = tempVector;
		tempVector->prev = traceVector;
		tempVector->start = traceVector->start;
		traceVector = tempVector;
	}
	return 1;
}

string popValuesVector(struct ValuesVector* traceVector) {
	if (traceVector != NULL) {
		struct ValuesVector* tempVector;
		tempVector = traceVector;
		string tempString = tempVector->value;
		if (traceVector->prev != NULL) {
			traceVector = traceVector->prev;
			traceVector->next = NULL;
			return tempString;
		} else {
			return tempString;
		}
		delete tempVector;
	}
	return NULL;
}

struct KeyValue* addKeyValue(struct KeyValue* traceKeyValue, string key, string value, bool isArray) {
	bool exhausted = false;
	struct KeyValue* keyNode = NULL;
	struct KeyValue* endNode = NULL;
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
		keyNode->arrayValue = new ArrayOfString;
		keyNode->key = key;
		EM_ASM_({console.log(">>>>>>>>>>>>>>>>>>>> first key added " + String.fromCharCode($0));}, keyNode->key.at(0));
	}
	if (keyNode == NULL) {
		endNode->next = keyNode;
		keyNode->prev = endNode;
		keyNode->start = traceKeyValue->start;
		keyNode->arrayValue = new ArrayOfString;
		keyNode->key = key;
		EM_ASM_({console.log(">>>>>>>>>>>>>>>>>>>> new key added " + String.fromCharCode($0));}, keyNode->key.at(0));
	}
	if (isArray) {
		/*
			struct ArrayOfString* tempArrayOfString;
			tempArrayOfString = new ArrayOfString;
			currentArrayOfString = tempArrayOfString;
			keyNode->arrayValue->child = tempArrayOfString;
			tempArrayOfString->parent = keyNode->arrayValue;
			keyNode->arrayValue = tempArrayOfString;
		*/
		//keyNode->arrayValue->value.push_back(value);
		pushValuesVector(keyNode->arrayValue->vector, value);
	} else {
		keyNode->value = value;
	}
	if (!value.empty()) {
		EM_ASM_({console.log(">>>>>>>>>>>>>>>>>>>> with value " + String.fromCharCode($0));}, value.at(0));
	}
	//traceKeyValue = keyNode;
	return keyNode;
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


