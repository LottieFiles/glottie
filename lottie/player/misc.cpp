
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
	if (tempKeyValue != NULL) {
		if (strlen(tempKeyValue->key) != 0) {
			if (strcmp(tempKeyValue->key, key.c_str()) == 0) {
				return true;
			}
		}
	}
	return false;
}

struct KeyValue* addChildArray(struct KeyValue* traceKeyValue) {
	//EM_ASM({console.log("addingchildarray 901.1");});
	struct ArrayOfString* tempArrayOfString;
	tempArrayOfString = new ArrayOfString;
	//EM_ASM({console.log("addingchildarray 901.5");});
	if (traceKeyValue == NULL) {
		traceKeyValue = new KeyValue;
		traceKeyValue->arrayValue = tempArrayOfString;
		traceKeyValue->arrayValue->root = tempArrayOfString;
		return traceKeyValue;
	}
	if (traceKeyValue->arrayValue == NULL) {
		//EM_ASM({console.log("addingchildarray 901.9");});
		traceKeyValue->arrayValue = tempArrayOfString;
		traceKeyValue->arrayValue->root = tempArrayOfString;
		return traceKeyValue;
	}
	//EM_ASM({console.log("addingchildarray 901.10");});
	tempArrayOfString->root = traceKeyValue->arrayValue->root;
	currentArrayOfString = tempArrayOfString;
	//EM_ASM({console.log("addingchildarray 901.15");});
	tempArrayOfString->parent = traceKeyValue->arrayValue;

	traceKeyValue->arrayValue->child = tempArrayOfString;
	traceKeyValue->arrayValue = tempArrayOfString;
	return traceKeyValue;
}

int gotoParentArray(struct KeyValue* traceKeyValue) {
	if (traceKeyValue == NULL) {
		return 1;
	}
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
		//EM_ASM({console.log("newkvtrail 401.1");});
		currentKeyValueTrail = new KeyValueTrail;
		//EM_ASM({console.log("newkvtrail 401.2");});
		currentKeyValueTrail->start = currentKeyValueTrail;
		//EM_ASM({console.log("newkvtrail 401.3");});
		currentKeyValueTrail->next = NULL;
		//EM_ASM({console.log("newkvtrail 401.4");});
		currentKeyValueTrail->prev = NULL;
		//
		
	} else {
		//EM_ASM({console.log("newkvtrail 402.1");});
		struct KeyValueTrail* tempKeyValueTrail;
		//EM_ASM({console.log("newkvtrail 402.2");});
		tempKeyValueTrail = new KeyValueTrail;
		//EM_ASM({console.log("newkvtrail 402.3");});
		currentKeyValueTrail->next = tempKeyValueTrail;
		//EM_ASM({console.log("newkvtrail 402.4");});
		tempKeyValueTrail->prev = currentKeyValueTrail;
		//EM_ASM({console.log("newkvtrail 402.5");});
		tempKeyValueTrail->start = currentKeyValueTrail->start;
		//EM_ASM({console.log("newkvtrail 402.6");});
		currentKeyValueTrail = tempKeyValueTrail;
		
		
	}
	return 1;
}

int deleteArrayValuesVector(struct ValuesVector* passedValuesVector) {
	//EM_ASM({console.log("deleteArrayValues 1101");});
	struct ValuesVector* tempValuesVector;
	passedValuesVector = passedValuesVector->start;

	while (passedValuesVector != NULL && passedValuesVector->next != NULL) {
		
		tempValuesVector = passedValuesVector;
		
		passedValuesVector = passedValuesVector->next;
		
		delete tempValuesVector;
		
	}
	//EM_ASM({console.log("deleteArrayValues 1102");});
	
	if (passedValuesVector != NULL) {
		delete passedValuesVector;
	}
	return 1;
}

int deleteArrayValue(struct ArrayOfString* passedArrayValue) {
	/*
	if (passedArrayValue == NULL || passedArrayValue->vector->start == NULL) {
		return 1;
	}
	
	if (passedArrayValue->child != NULL) {
		
		deleteArrayValue(passedArrayValue->child);
		if (passedArrayValue->vector != NULL) {
			deleteArrayValuesVector(passedArrayValue->vector->start);
		}
		delete passedArrayValue;
	} else {
		
		if (passedArrayValue->vector != NULL) {
			deleteArrayValuesVector(passedArrayValue->vector->start);
		}
		delete passedArrayValue;
		
	}
	*/
	
	struct ArrayOfString* tempArrayValue;
	if (passedArrayValue == NULL) {
		
		return 0;
	}
	while (passedArrayValue != NULL && passedArrayValue->child != NULL) {
		
		tempArrayValue = passedArrayValue;
	
		if (passedArrayValue->vector != NULL) {	
			deleteArrayValuesVector(passedArrayValue->vector->start);
		}
		
		passedArrayValue = passedArrayValue->child;
		
		delete tempArrayValue;
	}
	if (passedArrayValue != NULL) {
		
		if (passedArrayValue->vector != NULL) {
			deleteArrayValuesVector(passedArrayValue->vector->start);
		}
		delete passedArrayValue;
	}
	
	return 1;
}

int deleteKeyValues(struct KeyValueTrail* passedKeyValueTrail) {
	//EM_ASM({console.log("deleting key values 801");});
	char todisplay;
	char valdisplay;

	
	if (passedKeyValueTrail == NULL || passedKeyValueTrail->keyValue == NULL) {
		return 0;
	}
	struct KeyValue* tempKeyValue;
	struct KeyValue* temptempKeyValue;
	tempKeyValue = passedKeyValueTrail->keyValue;
	tempKeyValue = tempKeyValue->start;
	
	int counter = 0;
	//EM_ASM({console.log("deleting key values 802");});
	while (tempKeyValue != NULL && tempKeyValue->next != NULL) {
		
		if (strlen(tempKeyValue->key) > 0) {
			todisplay = tempKeyValue->key[0];
		} else {
			todisplay = ' ';
		}
		
		if (strlen(tempKeyValue->value) > 0) {
			valdisplay = tempKeyValue->value[0];
		} else {
			valdisplay = ' ';
		}
		
		counter++;
		
		temptempKeyValue = tempKeyValue;
		tempKeyValue = tempKeyValue->next;
		
		if (temptempKeyValue->arrayValue != NULL && temptempKeyValue->arrayValue->root != NULL) {
			deleteArrayValue(temptempKeyValue->arrayValue->root);
		}
		delete temptempKeyValue->arrayValue;
		delete temptempKeyValue;
	}
	//EM_ASM({console.log("deleting key values 803");});
	
	if (tempKeyValue != NULL) {
		//EM_ASM({console.log("deleting key values 803.1");});
		if (strlen(tempKeyValue->key) > 0) {
			todisplay = tempKeyValue->key[0];
		} else {
			todisplay = ' ';
		}
		//EM_ASM({console.log("deleting key values 803.2");});
		if (tempKeyValue->arrayValue != NULL && tempKeyValue->arrayValue->root != NULL) {
			//EM_ASM({console.log("deleting key values 803.2.1");});
			deleteArrayValue(tempKeyValue->arrayValue->root);
		}
		
		//EM_ASM_({console.log("deleting key values 803.3 " + $0);}, tempKeyValue);
		//delete tempKeyValue->arrayValue;
		delete tempKeyValue;
	}
	
	//EM_ASM({console.log("deleting key values 804");});
	if (passedKeyValueTrail->prev != NULL) {
		if (passedKeyValueTrail->next != NULL) {
			passedKeyValueTrail->next->prev = passedKeyValueTrail->prev;
		} else {
			//passedKeyValueTrail->next->prev = NULL;
		}
	}
	
	//EM_ASM({console.log("deleting key values 805");});
	if (passedKeyValueTrail->next != NULL) {
		if (passedKeyValueTrail->prev != NULL) {
			passedKeyValueTrail->prev->next = passedKeyValueTrail->next;
		} else {
			//passedKeyValueTrail->prev->next = NULL;
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

int pushValuesVector(struct ArrayOfString* traceArrayOfString, string tempString) {
	struct ValuesVector* tempVector;
	struct ValuesVector* traceVector;

	if (traceArrayOfString->vector != NULL) {
		traceVector = traceArrayOfString->vector;
	} else {
		traceArrayOfString->vector = new ValuesVector;
		traceArrayOfString->vector->start = traceArrayOfString->vector;
	}
	//
	if (traceVector == NULL) {
		
		traceVector = new ValuesVector;
		traceVector->start = traceVector;
		traceVector->next = NULL;
		traceVector->prev = NULL;
		if (tempString.length() > 30) {
			strcpy(tempVector->value, tempString.substr(0,20).c_str());
		} else {
			strcpy(tempVector->value, tempString.c_str());
		}
		traceArrayOfString->vector = traceVector;
		
	} else {
		
		tempVector = new ValuesVector;
		
		//tempVector->value = tempString;
		
		if (tempString.length() > 30) {
			strcpy(tempVector->value, tempString.substr(0,20).c_str());
		} else {
			strcpy(tempVector->value, tempString.c_str());
		}
		
		traceVector->next = tempVector;
		
		tempVector->prev = traceVector;
		
		tempVector->start = traceVector->start;
		
		traceVector = tempVector;
		
		traceArrayOfString->vector = traceVector;
		
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
	struct KeyValue* createdKeyValue = NULL;

	//EM_ASM({console.log("adding key value 300.1");});	
	if (traceKeyValue != NULL) {
		//EM_ASM({console.log("adding key value 301.1");});	
		struct KeyValue* tempKeyValue = traceKeyValue;
		//EM_ASM({console.log("adding key value 301.2");});	
		if (keyFound(traceKeyValue, key)) {
			
			keyNode = traceKeyValue;
		} else {
			//EM_ASM({console.log("adding key value 301.3");});	
			
			while (! exhausted) {
				
				if (keyFound(tempKeyValue, key)) {
					keyNode = tempKeyValue;
				}
				
				if (tempKeyValue->next == NULL) {
					endNode = tempKeyValue;
					exhausted = true;
				} else {
					tempKeyValue = tempKeyValue->next;
				}
			}
		}
		
	} else {
		//EM_ASM({console.log("adding key value 302.1");});	
		
		createdKeyValue = new KeyValue;
		//EM_ASM({console.log("adding key value 302.2");});	
		
		createdKeyValue->start = createdKeyValue;
		createdKeyValue->prev = NULL;
		createdKeyValue->next = NULL;
		keyNode = createdKeyValue;
		//keyNode->arrayValue = new ArrayOfString;
		//addChildArray(keyNode);
		if (key.length() > 30) {
			strcpy(keyNode->key, key.substr(0,20).c_str());
		} else {
			strcpy(keyNode->key, key.c_str());
		}
		
	}
	//EM_ASM({console.log("adding key value 303.1");});	
	
	if (keyNode == NULL) {
		keyNode = new KeyValue;
		
		endNode->next = keyNode;
		
		keyNode->prev = endNode;

		keyNode->arrayValue = new ArrayOfString;
		keyNode->arrayValue->root = keyNode->arrayValue;

		if (traceKeyValue != NULL) {
			
			keyNode->start = traceKeyValue->start;
		} else {
			
			keyNode->start = keyNode;
		}
		
		//addChildArray(keyNode);
		//keyNode->arrayValue = new ArrayOfString;
		
		if (key.length() > 30) {
			strcpy(keyNode->key, key.substr(0,20).c_str());
		} else {
			strcpy(keyNode->key, key.c_str());
		}
		
	}
	if (key == "shapes") {
		EM_ASM({console.log("shapes key " + String.fromCharCode($0));}, key[0]);
	}
	if (value.length() > 0) {
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
			if (keyNode->arrayValue == NULL) {
				keyNode->arrayValue = new ArrayOfString;
				keyNode->arrayValue->root = keyNode->arrayValue;
			}
			pushValuesVector(keyNode->arrayValue, value);
		} else {
			if (key.length() > 30) {
				strcpy(keyNode->value, value.substr(0,20).c_str());
			} else {
				strcpy(keyNode->value, value.c_str());
			}
		}
	}

	//EM_ASM({console.log("value " + String.fromCharCode($0));}, value[0]);	
	if (!value.empty()) {
		
	}
	//traceKeyValue = keyNode;
	//EM_ASM({console.log("adding key value 320.1");});	
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


