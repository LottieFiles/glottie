
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

//struct KeyValue* addChildArray(struct KeyValue* traceKeyValue) {
	
//}

struct KeyValue* addChildArray(struct KeyValue* traceKeyValue) {
	//EM_ASM({console.log("addingchildarray 901.1");});
	struct ArrayOfString* tempArrayOfString;
	tempArrayOfString = new ArrayOfString;
	if (traceKeyValue == NULL) {
		traceKeyValue = new KeyValue;
		traceKeyValue->start = traceKeyValue;
		traceKeyValue->arrayValue = tempArrayOfString;
		traceKeyValue->arrayValue->root = tempArrayOfString;
		EM_ASM_({console.log("addingchildarray 901.91 " + $0);}, traceKeyValue->arrayValue);
		return traceKeyValue;
	} else if (traceKeyValue->arrayValue == NULL) {
		traceKeyValue->arrayValue = tempArrayOfString;
		traceKeyValue->arrayValue->root = tempArrayOfString;
		EM_ASM_({console.log("addingchildarray 901.92 " + $0);}, traceKeyValue->arrayValue);
		return traceKeyValue;
	}
	EM_ASM_({console.log("addingchildarray 901.10 " + $0 + " from " + $1);}, tempArrayOfString, traceKeyValue->arrayValue);

	/*if (traceKeyValue->arrayValue->child != NULL) {
		tempArrayOfString->root = traceKeyValue->arrayValue->root;
		traceKeyValue->arrayValue = tempArrayOfString;
		traceKeyValue->arrayValue->root = ;
		tempArrayOfString = new ArrayOfString;
	}*/

	tempArrayOfString->root = traceKeyValue->arrayValue->root;
	//EM_ASM({console.log("addingchildarray 901.15");});
	//struct KeyValue* tempKeyValue;
	//tempKeyValue = traceKeyValue;




	// if an ArrayOfString already exists, then add a ValuesVector to it
	// and add a fresh ArrayOfString to the latter.

	struct ValuesVector* tempVectorValue;
	tempVectorValue = new ValuesVector;

	if (traceKeyValue->arrayValue->vector == NULL) {
		tempVectorValue->start = tempVectorValue;
	} else {
		tempVectorValue->start = traceKeyValue->arrayValue->vector->start;
		tempVectorValue->prev = traceKeyValue->arrayValue->vector;
		traceKeyValue->arrayValue->vector->next = tempVectorValue;
	}
		//traceKeyValue->arrayValue->vector->rootKey = tempKeyValue;

	tempVectorValue->root = traceKeyValue->arrayValue->root;
	tempVectorValue->parent = traceKeyValue->arrayValue;
	tempVectorValue->child = tempArrayOfString;
	tempArrayOfString->parent = tempVectorValue;

	traceKeyValue->arrayValue->vector = tempVectorValue;


	//tempArrayOfString->vector = new ValuesVector;
	//tempArrayOfString->vector->start = tempArrayOfString->vector;

	traceKeyValue->arrayValue = tempArrayOfString;

	currentArrayOfString = traceKeyValue->arrayValue;


	return traceKeyValue;
}

struct ArrayOfString* gotoParentArray(struct KeyValue* traceKeyValue) {
	if (traceKeyValue == NULL) {
		return NULL;
	}
	if (traceKeyValue->arrayValue != NULL) {
		if (traceKeyValue->arrayValue->parent != NULL) {
			EM_ASM_({console.log("toparent current " + $0 + " has parent " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->start);
			if (traceKeyValue->arrayValue->parent->start->parent != NULL) {
				EM_ASM_({console.log("toparent done " + $0 + " from " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->parent);
				traceKeyValue->arrayValue = traceKeyValue->arrayValue->parent->parent;
				currentArrayOfString = traceKeyValue->arrayValue;
			}
		}
	}
	return traceKeyValue->arrayValue;
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

struct KeyValueTrail* newKeyValueTrail(struct KeyValueTrail* traceKeyValueTrail) {
	if (currentKeyValueTrail == NULL) {
		//EM_ASM({console.log("newkvtrail 401.1");});
		traceKeyValueTrail = new KeyValueTrail;
		traceKeyValueTrail->start = traceKeyValueTrail;
		traceKeyValueTrail->next = NULL;
		traceKeyValueTrail->prev = NULL;
		
	} else {
		//EM_ASM({console.log("newkvtrail 402.1");});
		struct KeyValueTrail* tempKeyValueTrail;
		tempKeyValueTrail = new KeyValueTrail;
		traceKeyValueTrail->next = tempKeyValueTrail;
		tempKeyValueTrail->prev = traceKeyValueTrail;
		tempKeyValueTrail->start = traceKeyValueTrail->start;
		traceKeyValueTrail = tempKeyValueTrail;
		
	}
	currentKeyValueTrail = traceKeyValueTrail;
	return traceKeyValueTrail;
}

int deleteArrayValue(struct ArrayOfString* passedArrayValue);

int deleteArrayValuesVector(struct ValuesVector* passedValuesVector) {
	//EM_ASM({console.log("deleteArrayValues 1101");});
	//struct ValuesVector* tempValuesVector;
	passedValuesVector = passedValuesVector->start;

	while (passedValuesVector != NULL && passedValuesVector->next != NULL) {
		if (passedValuesVector->child != NULL) {
			deleteArrayValue(passedValuesVector->child);
		}
		
		//tempValuesVector = passedValuesVector;
		
		passedValuesVector = passedValuesVector->next;
		
		//delete tempValuesVector;
		delete passedValuesVector->prev;
		
	}
	//EM_ASM({console.log("deleteArrayValues 1102");});


	if (passedValuesVector != NULL) {
		delete passedValuesVector;
	}
	return 1;
}

int deleteArrayValue(struct ArrayOfString* passedArrayValue) {

	if (passedArrayValue != NULL) {
		if (passedArrayValue->vector != NULL) {	
			deleteArrayValuesVector(passedArrayValue->vector->start);
		}
		delete passedArrayValue;
	}

	
	/*
struct ArrayOfString* tempArrayValue;
	if (passedArrayValue == NULL) {
		
		return 0;
	}
	//EM_ASM({console.log("pre deleteArrayValues 1104");});
	while (passedArrayValue != NULL && passedArrayValue->child != NULL) {
		
		tempArrayValue = passedArrayValue;
	

		
		//EM_ASM_({console.log("deleteArrayValues 1105 " + $0 + " : " + $1);}, passedArrayValue, passedArrayValue->child);
		passedArrayValue = passedArrayValue->child;
		//EM_ASM_({console.log("deleteArrayValues 1105.1 " + $0 + " : " + $1);}, passedArrayValue, passedArrayValue->child);
		
		delete tempArrayValue;
		//EM_ASM_({console.log("deleteArrayValues 1106 " + $0 + " : " + $1);}, passedArrayValue, passedArrayValue->child);
	}
	//EM_ASM({console.log("pre deleteArrayValues 1105");});
		
		if (passedArrayValue->vector != NULL) {
			deleteArrayValuesVector(passedArrayValue->vector->start);
		}
		delete passedArrayValue;
	}
	*/
	
	return 1;
}

struct KeyValueTrail* deleteKeyValues(struct KeyValueTrail* passedKeyValueTrail) {
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
		if (strlen(temptempKeyValue->key) > 0) {
			EM_ASM_({console.log("deleting key values 802.2 " + $0 + " : " + $1 + " key: " + String.fromCharCode($2));}, temptempKeyValue, tempKeyValue, temptempKeyValue->key[0]);
		} else {
			EM_ASM_({console.log("deleting key values 802.2 " + $0 + " : " + $1);}, temptempKeyValue, tempKeyValue);
		}
		if (temptempKeyValue->arrayValue != NULL && strlen(temptempKeyValue->value) < 1) {
			if (temptempKeyValue->arrayValue->root != NULL) {
				deleteArrayValue(temptempKeyValue->arrayValue->root);
				temptempKeyValue->arrayValue = NULL;
			}
		}
		//delete temptempKeyValue->arrayValue;
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
			passedKeyValueTrail->prev->next = passedKeyValueTrail->next;
		} else {
			//passedKeyValueTrail->next->prev = NULL;
		}
	}
	
	//EM_ASM({console.log("deleting key values 805");});
	if (passedKeyValueTrail->next != NULL) {
		if (passedKeyValueTrail->prev != NULL) {
			passedKeyValueTrail->prev->next = passedKeyValueTrail->next;
			passedKeyValueTrail->next->prev = passedKeyValueTrail->prev;
		} else {
			//passedKeyValueTrail->prev->next = NULL;
		}
	}
	struct KeyValueTrail* temptempKeyValueTrail;
	temptempKeyValueTrail = passedKeyValueTrail->prev;
	delete passedKeyValueTrail;
	return temptempKeyValueTrail;
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

	traceVector = new ValuesVector;

	if (traceArrayOfString->vector != NULL) {
		traceVector->start = traceArrayOfString->vector->start;
		traceArrayOfString->vector->next = traceVector;
		traceVector->prev = traceArrayOfString->vector;
		//EM_ASM_({console.log("pushValuesVector 1.0 " + String.fromCharCode($0) + " : " + $1);}, traceArrayOfString->vector->value[0], traceArrayOfString->vector->next);	
	} else {
		//EM_ASM({console.log("pushValuesVector 1.0 ");});
		traceVector->start = traceVector;
	}

	if (tempString.length() >= 20) {
		strcpy(traceVector->value, tempString.substr(0,20).c_str());
	} else {
		strcpy(traceVector->value, tempString.c_str());
	}

	traceArrayOfString->vector = traceVector;

		//EM_ASM_({console.log("pushValuesVector 2.0 " + String.fromCharCode($0));}, traceArrayOfString->vector->value[0]);	
	return 1;
}

string popValuesVector(struct ValuesVector* traceVector) {
	//EM_ASM({console.log("adding array vector ");});	
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
		
		createdKeyValue->start = createdKeyValue;
		createdKeyValue->prev = NULL;
		createdKeyValue->next = NULL;
		keyNode = createdKeyValue;
		//keyNode->arrayValue = new ArrayOfString;
		//addChildArray(keyNode);
		/*
		if (keyNode->arrayValue == NULL) {
			keyNode->arrayValue = new ArrayOfString;
			keyNode->arrayValue->root = keyNode->arrayValue;
		}
		*/
		
		if (key.length() >= 20) {
			strcpy(keyNode->key, key.substr(0,20).c_str());
		} else {
			strcpy(keyNode->key, key.c_str());
		}
		
	}
	//EM_ASM({console.log("adding key value 303.1");});	
	
	if (keyNode == NULL) {
		//EM_ASM({console.log("adding key value 303.2");});	
		keyNode = new KeyValue;
		
		//EM_ASM({console.log("adding key value 303.3");});	
		if (endNode != NULL) {
			endNode->next = keyNode;
			//EM_ASM({console.log("adding key value 303.4");});	
			keyNode->prev = endNode;
			//EM_ASM({console.log("adding key value 303.5");});	
			keyNode->start = endNode->start;
		} else {
			//EM_ASM({console.log("adding key value 303.6");});	
			keyNode->start = keyNode;
		}

		//EM_ASM({console.log("adding key value 303.7");});	
		/*
		keyNode->arrayValue = new ArrayOfString;
		if (endNode != NULL) {
			//EM_ASM({console.log("adding key value 303.7.1");});	
			keyNode->arrayValue->root = endNode->arrayValue->root;
		} else {
			//EM_ASM({console.log("adding key value 303.7.2");});	
			keyNode->arrayValue->root = keyNode->arrayValue;
		}
		*/

		if (traceKeyValue != NULL) {
			//EM_ASM({console.log("adding key value 303.7.3");});	
			keyNode->start = traceKeyValue->start;
		} else {
			//EM_ASM({console.log("adding key value 303.7.4");});	
			keyNode->start = keyNode;
		}
		//EM_ASM({console.log("adding key value 303.7.5");});	
		
		//addChildArray(keyNode);
		//keyNode->arrayValue = new ArrayOfString;
		//EM_ASM({console.log("adding key value 303.8");});	
		if (key.length() >= 20) {
			strcpy(keyNode->key, key.substr(0,20).c_str());
		} else {
			strcpy(keyNode->key, key.c_str());
		}
		
	}
	if (isArray) {
		if (keyNode->arrayValue == NULL) {
			struct ArrayOfString* tempArrayOfString;
			tempArrayOfString = new ArrayOfString;
			tempArrayOfString->root = tempArrayOfString;
			currentArrayOfString = tempArrayOfString;
			keyNode->arrayValue = tempArrayOfString;
		}
		//keyNode->arrayValue->value.push_back(value);
		//if (keyNode->arrayValue == NULL) {
			//keyNode = addChildArray(keyNode);
			//keyNode->arrayValue->root = keyNode->arrayValue;
		//}
		pushValuesVector(keyNode->arrayValue, value);
		//EM_ASM_({console.log("adding key value by array 303.6 " + String.fromCharCode($0));}, value[0]);
	} else {
		if (key.length() >= 20) {
			strcpy(keyNode->value, value.substr(0,20).c_str());
		} else {
			strcpy(keyNode->value, value.c_str());
		}
		//EM_ASM_({console.log("adding key value 303.7 " + String.fromCharCode($0));}, value[0]);
		
	}
	if (!value.empty()) {
		
	}
	//traceKeyValue = keyNode;
	//EM_ASM({console.log("adding key value 320.1");});	
	return keyNode;
}

struct ArrayOfVertex* pushVertex(struct ArrayOfVertex* passedVertex, float vertex[4]) {
	struct ArrayOfVertex* tempAOV;
	/*if (passedVertex == NULL) {
		passedVertex = tempAOV;
		passedVertex->start = tempAOV;
		passedVertex->prev = NULL;
		passedVertex->next = NULL;
	} else {*/
	if (passedVertex == NULL) {
		EM_ASM({console.log("found an empty vertex");};);
		passedVertex = new ArrayOfVertex;
		passedVertex->start = passedVertex;
		passedVertex->end = passedVertex;
	} else {
		EM_ASM({console.log("found an non-empty vertex");};);
		//bool exhausted = false;
		/*while (! exhausted) {
			if (passedVertex->next == NULL) {
				exhausted = true;
			} else {
				passedVertex = passedVertex->next;
			}
		}*/
		passedVertex = passedVertex->end;
		tempAOV->prev = passedVertex;
		passedVertex->next = tempAOV;
		tempAOV->start = passedVertex->start;
		tempAOV->end = tempAOV;
		passedVertex = tempAOV;
	}

	if (passedVertex->vertex == NULL) {
		passedVertex->vertex = new Vertex;
	}
	//}



	passedVertex->vertex->position[0] = vertex[0];
	passedVertex->vertex->position[1] = vertex[1];
	passedVertex->vertex->position[2] = vertex[2];
	passedVertex->vertex->position[3] = vertex[3];

	return passedVertex;
}

//////////// type converters


