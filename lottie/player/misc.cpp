
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
		tempArrayOfString->root = tempArrayOfString;
		traceKeyValue->arrayValue->root = tempArrayOfString;
		//EM_ASM_({console.log("addingchildarray 901.91 " + $0);}, traceKeyValue->arrayValue);
		return traceKeyValue;
	} else {
		if (traceKeyValue->arrayValue == NULL) {
			traceKeyValue->arrayValue = tempArrayOfString;
			tempArrayOfString->root = tempArrayOfString;
			traceKeyValue->arrayValue->root = tempArrayOfString;
			//EM_ASM_({console.log("addingchildarray 901.92 " + $0);}, traceKeyValue->arrayValue);
			return traceKeyValue;
		} else if (traceKeyValue->arrayValue->closed == true) {
			if (traceKeyValue->arrayValue->parent == NULL) {
				struct KeyValue* tempKeyValue;
				tempKeyValue = new KeyValue;
				tempKeyValue->start = traceKeyValue->start;
				traceKeyValue->next = tempKeyValue;
				tempKeyValue->prev = traceKeyValue;
				tempArrayOfString->root = traceKeyValue->arrayValue->root;
				//tempArrayOfString->root = tempArrayOfString;
				tempKeyValue->arrayValue = tempArrayOfString;
				
				traceKeyValue = tempKeyValue;
			} else {
				struct ValuesVector* tempValuesVector;
				tempValuesVector = new ValuesVector;
				//tempValuesVector->start = traceKeyValue->arrayValue->parent->start;
				tempValuesVector->start = tempValuesVector;
				tempValuesVector->prev = traceKeyValue->arrayValue->parent;
				traceKeyValue->arrayValue->parent->next = tempValuesVector;
				//tempValuesVector->root = traceKeyValue->arrayValue->parent->root;
				tempValuesVector->root = traceKeyValue->arrayValue->root;
				//tempValuesVector->root = tempValuesVector;
				tempValuesVector->parent = traceKeyValue->arrayValue->parent->parent;
				tempValuesVector->child = tempArrayOfString;
				tempArrayOfString->root = traceKeyValue->arrayValue->root;
				//tempArrayOfString->root = tempArrayOfString;
				traceKeyValue->arrayValue->parent->parent->vector = tempValuesVector;
				traceKeyValue->arrayValue = tempArrayOfString;
			}
			//EM_ASM_({console.log("addingchildarray 901.93 " + $0);}, traceKeyValue->arrayValue);
			return traceKeyValue;
		}
	}

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
		//EM_ASM_({console.log("addingchildarray 901.10 " + $0 + " from " + $1);}, tempArrayOfString, traceKeyValue->arrayValue);
		tempVectorValue->start = tempVectorValue;
	} else {
		//EM_ASM_({console.log("addingchildarray 901.11 " + $0 + " from " + $1);}, tempArrayOfString, traceKeyValue->arrayValue);
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
			//EM_ASM_({console.log("toparent current " + $0 + " has parent " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->start);
			if (traceKeyValue->arrayValue->parent->start->parent != NULL) {
				//EM_ASM_({console.log("toparent done " + $0 + " to " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->parent);
				traceKeyValue->arrayValue = traceKeyValue->arrayValue->parent->parent;
				currentArrayOfString = traceKeyValue->arrayValue;
			}
		} else {
			//EM_ASM_({console.log("toparent closed " + $0);}, traceKeyValue->arrayValue);
			traceKeyValue->arrayValue->closed = true;
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
	if (traceKeyValueTrail == NULL) {
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
	
	//currentKeyValueTrail = new KeyValueTrail;
	return currentKeyValueTrail;
}

int deleteArrayValue(struct ArrayOfString* passedArrayValue);

int deleteArrayValuesVector(struct ValuesVector* passedValuesVector) {
	//EM_ASM({console.log("deleteArrayValues 1101");});
	//struct ValuesVector* tempValuesVector;
	if (passedValuesVector == NULL) {
		return 0;
	}
	passedValuesVector = passedValuesVector->start;

	//EM_ASM({console.log("deletingArrayValuesVector 1.1");});
	bool exhausted = false;
	struct ValuesVector* tempValuesVector;
	//while (passedValuesVector != NULL && passedValuesVector->next != NULL) {
	while (! exhausted) {
		//EM_ASM({console.log("deletingArrayValuesVector 1.2");});
		if (passedValuesVector->child != NULL) {
			deleteArrayValue(passedValuesVector->child);
		}
		//EM_ASM({console.log("deletingArrayValuesVector 1.3");});
		
		tempValuesVector = passedValuesVector;
		if (passedValuesVector->next != NULL) {
			passedValuesVector = passedValuesVector->next;
		} else {
			exhausted = true;
		}
		
		delete tempValuesVector;
		//delete passedValuesVector;
	}
	//EM_ASM({console.log("deletingArrayValuesVector 1.4");});
	//EM_ASM({console.log("deleteArrayValues 1102");});
	//EM_ASM({console.log("deletingArrayValuesVector 1.3");});


	/*if (passedValuesVector != NULL) {
		delete passedValuesVector;
	}*/
	return 1;
}

int deleteArrayValue(struct ArrayOfString* passedArrayValue) {

	if (passedArrayValue != NULL) {
		if (passedArrayValue->vector != NULL) {	
			deleteArrayValuesVector(passedArrayValue->vector->start);
			//EM_ASM({console.log("deletingArrayValues 1.2");});
		}
		delete passedArrayValue;
	}
	//EM_ASM({console.log("deletingArrayValues 1.3");});
	
	return 1;
}

//void KeyValueTrail* deleteKeyValues(struct KeyValueTrail* passedKeyValueTrail) {
void deleteKeyValues(struct KeyValueTrail* passedKeyValueTrail) {
	//EM_ASM({console.log("deleting key values 801");});
	char todisplay;
	char valdisplay;

	
	if (passedKeyValueTrail == NULL || passedKeyValueTrail->keyValue == NULL) {
		return;
	}
	struct KeyValue* tempKeyValue;
	struct KeyValue* temptempKeyValue;
	tempKeyValue = passedKeyValueTrail->keyValue;
	tempKeyValue = tempKeyValue->start;
	
	int counter = 0;
	//EM_ASM({console.log("deleting key values 802");});
	//while (tempKeyValue != NULL && tempKeyValue->next != NULL) {
	bool exhausted = false;
	while (! exhausted) {
		//EM_ASM({console.log("deleting key values 802.0");});

		/*
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
		*/
		
		counter++;

		if (strlen(tempKeyValue->key) > 0) {
			//EM_ASM_({console.log("deleting key values 802.1 " + $0 + " : key: " + String.fromCharCode($2));}, tempKeyValue, tempKeyValue->key[0]);
		} else {
			//EM_ASM_({console.log("deleting key values 802.2 " + $0);}, tempKeyValue);
		}

		if (tempKeyValue->arrayValue != NULL) {
			//EM_ASM({console.log("deleting key values 802.2.0");});
			if (tempKeyValue->arrayValue->vector != NULL) {
				//EM_ASM({console.log("deleting key values 802.2.1");});
				if (tempKeyValue->arrayValue->root != NULL) {
					deleteArrayValue(tempKeyValue->arrayValue->root);
					tempKeyValue->arrayValue = NULL;
				}
			} else {
				delete tempKeyValue->arrayValue;
			}
		}
		
		if (tempKeyValue->next == NULL) {
			exhausted = true;
			delete tempKeyValue;
			tempKeyValue = NULL;
		} else {
			temptempKeyValue = tempKeyValue;
			tempKeyValue = tempKeyValue->next;
			delete temptempKeyValue;
		}
		
		/*
		if (temptempKeyValue->arrayValue != NULL) {
			//if (strlen(temptempKeyValue->value) < 1) {
			//EM_ASM({console.log("deleting key values 802.2.0");});
			if (temptempKeyValue->arrayValue->vector != NULL) {
				//EM_ASM({console.log("deleting key values 802.2.1");});
				if (temptempKeyValue->arrayValue->root != NULL) {
					deleteArrayValue(temptempKeyValue->arrayValue->root);
					temptempKeyValue->arrayValue = NULL;
				}
			} else {
				delete temptempKeyValue->arrayValue;
			}
		}
		*/
		//EM_ASM({console.log("deleting key values 802.2.2");});
	}
	//EM_ASM({console.log("deleting key values 803");});
	
	if (tempKeyValue != NULL) {
		//EM_ASM({console.log("deleting key values 803.1");});
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
		
		//EM_ASM_({console.log("deleting key values 802.3 " + $0 + " : " + $1 + " key: " + String.fromCharCode($2));}, tempKeyValue, tempKeyValue, tempKeyValue->key[0]);
		//EM_ASM({console.log("deleting key values 803.2");});
		/*if (tempKeyValue->arrayValue != NULL && tempKeyValue->arrayValue->root != NULL) {
			//EM_ASM({console.log("deleting key values 803.2.1");});
			if (tempKeyValue->arrayValue->root != NULL) {
				deleteArrayValue(tempKeyValue->arrayValue->root);
				tempKeyValue->arrayValue = NULL;
			}
		}*/
		if (tempKeyValue->arrayValue != NULL) {
			if (strlen(tempKeyValue->value) < 1) {
				if (tempKeyValue->arrayValue->root != NULL) {
					deleteArrayValue(tempKeyValue->arrayValue->root);
					tempKeyValue->arrayValue = NULL;
				}
			} else {
				delete tempKeyValue->arrayValue;
			}
		}
		
		//EM_ASM_({console.log("deleting key values 803.3 " + $0);}, tempKeyValue);
		//delete tempKeyValue->arrayValue;
		delete tempKeyValue;
	}


	/*	
	struct KeyValueTrail* temptempKeyValueTrail;
	//EM_ASM({console.log("deleting key values 804");});
	if (passedKeyValueTrail->prev != NULL) {
		temptempKeyValueTrail = passedKeyValueTrail;
		if (passedKeyValueTrail->next != NULL) {
			passedKeyValueTrail->next->prev = passedKeyValueTrail->prev;
			passedKeyValueTrail->prev->next = passedKeyValueTrail->next;
		} else {
			passedKeyValueTrail->prev->next = NULL;
		}
	} else {
		temptempKeyValueTrail = NULL;
	}
	
	//EM_ASM({console.log("deleting key values 805");});
	if (passedKeyValueTrail->next != NULL) {
		if (passedKeyValueTrail->prev != NULL) {
			passedKeyValueTrail->prev->next = passedKeyValueTrail->next;
			passedKeyValueTrail->next->prev = passedKeyValueTrail->prev;
		} else {
			passedKeyValueTrail->next->prev = NULL;
		}
		if (temptempKeyValueTrail != NULL) {
			temptempKeyValueTrail = passedKeyValueTrail;
		}
	}
	//delete passedKeyValueTrail;
	*/
	//return temptempKeyValueTrail;
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

//struct KeyValue* addKeyValue(struct KeyValue* traceKeyValue, string key, string value, bool isArray) {
struct KeyValue* addKeyValue(struct KeyValue* traceKeyValue, char* key, char* value, bool isArray) {
	bool exhausted = false;
	struct KeyValue* keyNode = NULL;
	struct KeyValue* endNode = NULL;
	struct KeyValue* createdKeyValue = NULL;

	if (strcmp(key, "ty") == 0) {
		/*if (strcmp(value, "tr") == 0) {
			EM_ASM({console.log("transform KV");});	
		}*/
		memset(input->currentTy, 0, sizeof(input->currentTy));
		strcat(input->currentTy, value);
		memset(theScope->currentTy, 0, sizeof(theScope->currentTy));
		strcat(theScope->currentTy, value);
	}

	//EM_ASM({console.log("adding key value 300.1");});	
	if (traceKeyValue != NULL) {
		//EM_ASM({console.log("adding key value 301.1");});	
		struct KeyValue* tempKeyValue = traceKeyValue->start;
		//EM_ASM({console.log("adding key value 301.2");});	
		if (keyFound(traceKeyValue, key)) {
			//EM_ASM({console.log("adding key value 301.3");});	
			
			keyNode = traceKeyValue;
		} else {
			//EM_ASM({console.log("adding key value new 301.3");});	
			
			while (! exhausted) {
				
				if (keyFound(tempKeyValue, key)) {
					//EM_ASM({console.log("adding key value 301.4");});	
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

		/*
		if (key.length() >= 20) {
			strcpy(keyNode->key, key.substr(0,20).c_str());
		} else {
			strcpy(keyNode->key, key.c_str());
		}
		*/
		strcpy(keyNode->key, key);
		
	}
	//EM_ASM({console.log("adding key value 303.1");});	

	if (keyNode == NULL) {
		if (traceKeyValue != NULL && strlen(traceKeyValue->key) < 1) {
			//EM_ASM({console.log("adding key value 303.1.1");});	
			keyNode = traceKeyValue;
			/*
			if (key.length() >= 20) {
				//EM_ASM({console.log("adding key value added 303.2");});	
				strcpy(keyNode->key, key.substr(0,20).c_str());
			} else {
				strcpy(keyNode->key, key.c_str());
			}
			*/
			strcpy(keyNode->key, key);
		} else {

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
			
			//addChildArray(keyNode);
			//keyNode->arrayValue = new ArrayOfString;
			//EM_ASM({console.log("adding key value 303.8");});
			/*
			if (key.length() >= 20) {
				//EM_ASM_({console.log("adding key value 303.7.5" + String.fromCharCode($0));}, key[0]);	
				
				strcpy(keyNode->key, key.substr(0,20).c_str());
			} else {
				strcpy(keyNode->key, key.c_str());
			}
			*/
			strcpy(keyNode->key, key);
		}
	}
	//EM_ASM({console.log("adding key value 303.8.1");});	
	if (isArray && ! justStartedArray) {
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
		//EM_ASM({console.log("adding key value 303.8.2");});
		/*
		if (value.length() >= 20) {
			strcpy(keyNode->value, value.substr(0,20).c_str());
		} else {
			strcpy(keyNode->value, value.c_str());
		}
		*/
		if (justStartedArray) {
			if (strlen(value) <= 0) {
				value = 0;
			}
		}
		strcpy(keyNode->value, value);
		//EM_ASM_({console.log("adding key value 303.7 " + String.fromCharCode($0));}, value[0]);
		
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
		//EM_ASM({console.log("found an empty vertex");};);
		passedVertex = new ArrayOfVertex;
		passedVertex->start = passedVertex;
	} else {
		//EM_ASM({console.log("found a non-empty vertex");};);
		//bool exhausted = false;
		/*while (! exhausted) {
			if (passedVertex->next == NULL) {
				exhausted = true;
			} else {
				passedVertex = passedVertex->next;
			}
		}*/
		tempAOV = new ArrayOfVertex;
		tempAOV->prev = passedVertex;
		passedVertex->next = tempAOV;
		tempAOV->start = passedVertex->start;
		passedVertex = tempAOV;
	}

	if (passedVertex->vertex == NULL) {
		passedVertex->vertex = new Vertex;
	}
	//}


	passedVertex->vertex->x = vertex[0];
	passedVertex->vertex->y = vertex[1];
	passedVertex->vertex->z = vertex[2];
	passedVertex->vertex->a = vertex[3];

	if (passedVertex->prev == NULL) {
		passedVertex->order = 0;
	} else {
		passedVertex->order = passedVertex->prev->order + 1;
	}
	//EM_ASM_({console.log("coords ))) " + $0 + " " + $1 + " :: " + $2);}, passedVertex->vertex->x, passedVertex->vertex->y, passedVertex->order);

	/*
	passedVertex->vertex->x = vertex[0];
	passedVertex->vertex->y = vertex[1];
	passedVertex->vertex->z = vertex[2];
	passedVertex->vertex->a = vertex[3];
	*/

	return passedVertex;
}

GLfloat* vertexToGLfloat(struct ArrayOfVertex* passedArrayOfVertex, int sizeOfArray) {
	if (passedArrayOfVertex == NULL) {
		return NULL;
	}
	passedArrayOfVertex = passedArrayOfVertex->start;
	bool exhausted = false;
	//EM_ASM({console.log("vertextofloat 1.1");});
	/*
	int factor = static_cast<int>((sizeOfArray * 4 * 4)/256);
	int alignSize;
	if (((sizeOfArray * 4 * 4)/256) > factor) {
		alignSize = (factor + 1) * 256;
	} else {
		alignSize = factor * 256;
	}
	static const int alignSizeConst = alignSize;
	*/
	//sizeOfArray = sizeOfArray * 4;
	GLfloat* tempArray = new GLfloat[(sizeOfArray * 4)];
	//EM_ASM({console.log("vertextofloat 1.4");});
	int index = 0;
	//EM_ASM({console.log("-=-=-=-=> starting");});
	while (! exhausted) {
		*(tempArray + index) = (passedArrayOfVertex->vertex->x / theAnimation->w) - 0.5;
		index = index + 1;
		*(tempArray + index) = (passedArrayOfVertex->vertex->y / theAnimation->h) - 0.5;
		//EM_ASM({console.log("val " + $0 + " " + $1 + " " + $2);}, *(tempArray + index - 1), *(tempArray + index), passedArrayOfVertex->vertex->x);
		index = index + 1;
		if (theAnimation->ddd) {
			if (theAnimation->z > 0) {
				*(tempArray + index) = (passedArrayOfVertex->vertex->z / theAnimation->z) - 0.5;
			} else {
				*(tempArray + index) = (passedArrayOfVertex->vertex->z / theAnimation->h) - 0.5;
			}
		} else {
			if (passedArrayOfVertex->order > 0) {
				*(tempArray + index) = (passedArrayOfVertex->order / 10000);
			}
		}
		index = index + 1;
		*(tempArray + index) = passedArrayOfVertex->vertex->a;
		index = index + 1;
		if (passedArrayOfVertex->next == NULL) {
			exhausted = true;
		} else {
			passedArrayOfVertex = passedArrayOfVertex->next;
		}
	}
	//EM_ASM({console.log("-=-=-=-=> ended");});

	return tempArray;
}

//////////// type converters

float stringToFloat(char* passedString) {
	string tempString(passedString);
	return stof(tempString);
}

int stringToInt(char* passedString) {
	string tempString(passedString);
	return stoi(tempString);
}

//////////// helpers for populating json objects

struct ArrayOfVertex* populateVertices(struct ArrayOfString* traceArrayValue, struct ArrayOfVertex* targetVertex, struct PropertiesShapeProp* passedPropertiesShapeProp) {
	struct ValuesVector* baseVector;
	if (traceArrayValue == NULL) {
		return 0;
	}

	baseVector = traceArrayValue->vector->start;

	bool exhausted = false;
	currentUniversalCount = 0;
	while (! exhausted) {
		if (baseVector->child == NULL) {
			break;
		}
		currentUniversalCount = currentUniversalCount + 1;

		string xvals(baseVector->child->vector->start->value);
		float xval = 0;
		if (xvals.length() < 1) {
			xval = 0;
		} else {
			if (! xvals.empty()) {
				xval = stof(xvals);
			} else {
				xval = 0;
			}
		}
		string yvals(baseVector->child->vector->start->next->value);
		float yval = 0;
		if (yvals.length() < 1) {
			yval = 0;
		} else {
			if (! yvals.empty()) {
				yval = stof(yvals);
			} else {
				yval = 0;
			}
		}
		float vertex[4] = {xval, yval, 0.0f, 1.0f};
		targetVertex = pushVertex(targetVertex, vertex);
		if (xval < passedPropertiesShapeProp->lowestX) {
			passedPropertiesShapeProp->lowestX = xval;
		}
		if (yval < passedPropertiesShapeProp->lowestY) {
			passedPropertiesShapeProp->lowestY = yval;
		}

		//EM_ASM_({console.log("**** populating values " + $0 + " " + $1);}, xval, yval);

		if (baseVector->next == NULL) {	
			exhausted = true;
		} else {
			baseVector = baseVector->next;
		}
	}
	targetVertex->next = targetVertex->start;
	targetVertex->start->prev = targetVertex;
	if (targetVertex != NULL) {
		return targetVertex->start;
	} else {
		return NULL;
	}
}

float populateFloat(char* tempStr) {
	string xvals(tempStr);
	
	float xval = 0;
	if (xvals.length() < 1) {
		xval = 0;
	} else {
	if (! xvals.empty()) {
			xval = stof(xvals);
		} else {
			xval = 0;
		}
	}

	return xval;
}

struct FloatArrayReturn* populateFloatArray(struct ArrayOfString* traceArrayValue, bool positive) {
	struct ValuesVector* baseVector;
	struct FloatArrayReturn* tempFloatArray;
	int tempCount = 0;
	tempFloatArray = new FloatArrayReturn;
	if (traceArrayValue == NULL) {
		return 0;
	}

	baseVector = traceArrayValue->vector->start;

	bool exhausted = false;
	float* tempFloat;
	while (! exhausted) {
		tempCount++;
		if (baseVector->next == NULL) {	
			exhausted = true;
		} else {
			baseVector = baseVector->next;
		}
	}
	tempFloatArray->count = tempCount;
	tempFloatArray->floatArray = new float[tempCount];

	//EM_ASM({console.log("->>-->> count " + $0);}, tempCount);
	baseVector = traceArrayValue->vector->start;
	exhausted = false;
	currentUniversalCount = 0;
	while (! exhausted) {
		/*if (baseVector->child == NULL) {
			break;
		}*/

		string xvals(baseVector->value);
		float xval = 0;
		if (xvals.length() < 1) {
			xval = 0;
		} else {
			if (! xvals.empty()) {
				xval = stof(xvals);
			} else {
				xval = 0;
			}
		}
		/*string yvals(baseVector->child->vector->start->next->value);
		float yval = 0;
		if (yvals[0] == '0' || yvals.length() < 1) {
			yval = 0;
		} else {
			if (! yvals.empty()) {
				yval = stof(yvals);
			} else {
				yval = 0;
			}
		}*/
		//float vertex[4] = {xval, yval, 0.0f, 1.0f};
		//targetVertex = pushVertex(targetVertex, vertex);
		if (positive && xval < 0) {
			xval = xval * -1;
		}
		*(tempFloatArray->floatArray + currentUniversalCount) = xval;
		currentUniversalCount = currentUniversalCount + 1;
		//EM_ASM({console.log("->>-->> found k value " + $0);}, xval);

		if (baseVector->next == NULL) {	
			exhausted = true;
		} else {
			baseVector = baseVector->next;
		}
	}
	return tempFloatArray;
}


// common functions related to geometry

float distanceBetweenPoints(struct Vertex* pointA, struct Vertex* pointB) {
	float distance = ( sqrt(pow(((float)pointA->x - (float)pointB->x), 2) + pow(((float)pointA->y - (float)pointB->y), 2)) );
	//EM_ASM_({console.log("    ///////////> " + $0 + " " + $1 + " " + $2 + " " + $3 + " " + $4);}, distance, pointA->x, pointB->x, pointA->y, pointB->y);
	return distance;
}

void getBBArray (struct ArrayOfVertex* passedAOV, struct BoundingBox* currentBB) {
	bool exhausted = false;
	int count = 0;
	while (! exhausted) {
		if (passedAOV->vertex != NULL) {
			//if ((passedAOV->vertex->x - currentBB->initX) > currentBB->w)
			count++;
			if (passedAOV->vertex->x > currentBB->w) {
				//EM_ASM_({console.log("-------------------------------------------------->> new maxW " + $0);}, currentBB->w);
				currentBB->w = passedAOV->vertex->x;
			}
			if (passedAOV->vertex->y > currentBB->w) {
				//EM_ASM_({console.log("-------------------------------------------------->> new maxH " + $0);}, currentBB->h);
				currentBB->h = passedAOV->vertex->y;
			}
		}
		if (passedAOV->next == passedAOV->start) {
			exhausted = true;
		} else {
			passedAOV = passedAOV->next;
		}
	}
}

void getBBProp (struct PropertiesShapeProp* passedPropertiesShapeProp, struct BoundingBox* currentBB) {
	bool exhausted = false;
	while (! exhausted) {
		if (passedPropertiesShapeProp->v != NULL) {
			getBBArray(passedPropertiesShapeProp->v->start, currentBB);
		}
		if (passedPropertiesShapeProp->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp = passedPropertiesShapeProp->next;
		}
	}
}

void getBBPropShape (struct PropertiesShape* passedPropertiesShape, struct BoundingBox* currentBB) {
	bool exhausted = false;
	while (! exhausted) {
		if (passedPropertiesShape->k != NULL) {
			getBBProp(passedPropertiesShape->k->start, currentBB);
		}
		if (passedPropertiesShape->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShape = passedPropertiesShape->next;
		}
	}
}

void getBoundingBox(struct ShapesItem* passedShapesItem, struct BoundingBox* currentBB) {
	bool exhausted = false;
	while (! exhausted) {
		if (passedShapesItem->it != NULL) {
			getBoundingBox(passedShapesItem->it->start, currentBB);
		}
		if (passedShapesItem->ks != NULL) {
			getBBPropShape(passedShapesItem->ks, currentBB);
		}
		if (passedShapesItem->next == NULL) {
			exhausted = true;
		} else {
			passedShapesItem = passedShapesItem->next;
		}
	}
	//return currentBB;
}


// related to animating
void bezierSegment(struct ArrayOfVertex* v, struct ArrayOfVertex* i, struct ArrayOfVertex* o, int* v_count, int* bezier_count, float* segSizePassed) {
	bool exhausted = false;
	v = v->start;
	i = i->start;
	o = o->start;
	
	struct ArrayOfVertex *o1, *o2, *p1, *p2;

	bool startedCycling = false;
	struct ArrayOfVertex* startPoint = v->start;
	//struct ArrayOfVertex* nextVertex = NULL;
	struct ArrayOfVertex* lastIntermediate = NULL;
	struct ArrayOfVertex* intermediate = NULL;
	struct ArrayOfVertex* intermediateStart = NULL;

	float oneTcube, oneTsquare, Tcube, Tsquare, oneT;
	float segSize;

	int segCounter = 0;
	while (! exhausted) {
		if (v == startPoint && startedCycling == true) {
						break;
			//continue;
				if (
						(
							i->vertex->x == 0 && 
							i->vertex->y == 0 &&
							o->vertex->x == 0 &&
							o->vertex->y == 0
						) &&
						(
							i->prev->vertex->x == 0 && 
							i->prev->vertex->y == 0 &&
							o->prev->vertex->x == 0 &&
							o->prev->vertex->y == 0
						)
					) {
						break;
				} else {
					i = i->next;
					o = o->next;
					v = v->next;
					//EM_ASM({console.log("breakout ");});
					exhausted = true;
				}
		} else {
				if (
						(
							i->vertex->x == 0 && 
							i->vertex->y == 0 &&
							o->vertex->x == 0 &&
							o->vertex->y == 0
						) &&
						(
							i->prev->vertex->x == 0 && 
							i->prev->vertex->y == 0 &&
							o->prev->vertex->x == 0 &&
							o->prev->vertex->y == 0
						)
					) {
						i = i->next;
						o = o->next;
						v = v->next;
						//EM_ASM({console.log("non-bezier ");});
						startedCycling = true;
						segCounter++;
						continue;
				} else {
					i = i->next;
					o = o->next;
					v = v->next;
					//EM_ASM({console.log("breakout ");});
				}

		}
		startedCycling = true;
		o1 = v->prev;
		o2 = v;
		p1 = o->prev;
		p2 = i;

		//float segSize = 0.10;
		segCounter++;
		segSize = *(segSizePassed + segCounter);
		float segments = 1 / segSize;
		//float segNow = segSize;
		float segNow = segSize;

		float p1x = p1->vertex->x + o1->vertex->x;
		float p2x = p2->vertex->x + o2->vertex->x;
		float p1y = p1->vertex->y + o1->vertex->y;
		float p2y = p2->vertex->y + o2->vertex->y;

		intermediateStart = NULL;
		lastIntermediate = NULL;
		while (segNow < 1) {
			intermediate = new ArrayOfVertex;
			intermediate->vertex = new Vertex;
			intermediate->start = o1->start;

			//intermediate->vertex->x = ( (((pt2->x - pt1->x) / segments) * segNow) + pt1->x );
			//intermediate->vertex->y = ( (((pt2->y - pt1->y) / segments) * segNow) + pt1->y );

			oneT = 1 - segNow;
			Tcube = pow(segNow, 3);
			Tsquare = pow(segNow, 2);
			oneTcube = pow(oneT, 3);
			oneTsquare = pow(oneT, 2);

			intermediate->vertex->x = 	(oneTcube * 			o1->vertex->x) + 
							(3 * oneTsquare * segNow * 	p1x) + 
							(3 * oneT * Tsquare * 		p2x) + 
							(Tcube * 			o2->vertex->x);

			intermediate->vertex->y = 	(oneTcube * 			o1->vertex->y) + 
							(3 * oneTsquare * segNow * 	p1y) + 
							(3 * oneT * Tsquare * 		p2y) + 
							(Tcube * 			o2->vertex->y);
			EM_ASM_({console.log("[[[[[[[[[[[[[==========> adding intermediate " + $0 + " " + $1);}, intermediate->vertex->x, intermediate->vertex->y);
			intermediate->vertex->z = 0;
			intermediate->vertex->a = 1;

			intermediate->bezier = true;

			
			if (lastIntermediate != NULL) {
				lastIntermediate->next = intermediate;
				intermediate->prev = lastIntermediate;
			}
			lastIntermediate = intermediate;

			//passedPropertiesShapeProp->v = intermediate;
			segNow = segNow + segSize;
			v_count++;
			bezier_count++;
			if (intermediateStart == NULL) {
				intermediateStart = intermediate;
			}
		}
		/*if (intermediateStart != NULL) {
			intermediateStart->prev = o1;
			o1->next = intermediateStart;
			intermediate->next = o2;
			o2->prev = intermediate;
		}*/
		//return intermediate;
	}
}

double seconds() {
	struct timeval tempRef;
	gettimeofday(&tempRef, NULL);

	return (double)tempRef.tv_sec + ((double)tempRef.tv_usec / 1000000);
}

