/////////////////////////////////////////////////////////
/////////                                       /////////
/////////  ******            *****************  /////////
/////////   ****              ***************   /////////
/////////    ***               ***         **   /////////
/////////    ***               ***              /////////
/////////    ***               ***     **       /////////
/////////    ***               **********       /////////
/////////    ***               **********       /////////
/////////    ***               ***     **       /////////
/////////    ***               ***              /////////
/////////    ***       **      ***              /////////
/////////   **************    *****             /////////
/////////  ****************  *******            /////////
/////////                                       /////////
/////////////////////////////////////////////////////////
///////  Created by: https://github.com/shaafiee  ///////
///////      Copyright 2020, lottiefiles.com      ///////
/////////////////////////////////////////////////////////

void rawcopy(char* targetChar, char* sourceChar) {
	/*if (sourceChar >= 1) {
	} else {
		targetChar = 0;
		*targetChar = '\0';
		return;
	}*/
	targetChar = 0;
#ifdef DEBUG
#ifdef EMT
#else
	std::cout << "starting copy\n";
#endif
#endif
	for (sourceChar = 0; *sourceChar != '\0'; sourceChar++) {
#ifdef DEBUG
#ifdef EMT
#else
		std::cout << "copying " << sourceChar;
#endif
#endif
		* targetChar = *sourceChar;
		targetChar++;
	}
	*targetChar = '\0';
}

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
	struct ArrayOfString* tempArrayOfString;
	tempArrayOfString = new ArrayOfString;
#ifdef DEBUGREADARRAY
	cout << "Adding child - ";
#endif
	if (traceKeyValue == NULL) {
		traceKeyValue = new KeyValue;
		traceKeyValue->start = traceKeyValue;
		traceKeyValue->arrayValue = tempArrayOfString;
		tempArrayOfString->root = tempArrayOfString;
		traceKeyValue->arrayValue->root = tempArrayOfString;
#ifdef DEBUGREADARRAY
		cout << "null keyValue - \n";
#endif
		return traceKeyValue;
	}
	else {
		if (traceKeyValue->arrayValue == NULL) {
			traceKeyValue->arrayValue = tempArrayOfString;
			tempArrayOfString->root = tempArrayOfString;
			traceKeyValue->arrayValue->root = tempArrayOfString;
			return traceKeyValue;
		}
		else if (traceKeyValue->arrayValue->parent == NULL) {
			if (traceKeyValue->arrayValue->closed == true) {
				struct KeyValue* tempKeyValue;
				tempKeyValue = new KeyValue;
				tempKeyValue->start = traceKeyValue->start;
				traceKeyValue->next = tempKeyValue;
				tempKeyValue->prev = traceKeyValue;
				tempArrayOfString->root = traceKeyValue->arrayValue->root;
				tempKeyValue->arrayValue = tempArrayOfString;

				traceKeyValue = tempKeyValue;

				tempArrayOfString = new ArrayOfString;


#ifdef DEBUGREADARRAY
				cout << " <without parent>";
#endif
			}
			else {
				struct KeyValue* tempKeyValue;
				tempKeyValue = new KeyValue;
				tempKeyValue->start = traceKeyValue->start;
				traceKeyValue->next = tempKeyValue;
				tempKeyValue->prev = traceKeyValue;
				tempArrayOfString->root = traceKeyValue->arrayValue->root;
				tempKeyValue->arrayValue = tempArrayOfString;

				traceKeyValue = tempKeyValue;

				tempArrayOfString = new ArrayOfString;


#ifdef DEBUGREADARRAY
				cout << " <without parent and not closed>";
#endif
				//return traceKeyValue;
			}
		}
		else {
				struct ValuesVector* tempValuesVector;
				tempValuesVector = new ValuesVector;
				tempValuesVector->start = tempValuesVector;
				tempValuesVector->prev = traceKeyValue->arrayValue->parent;
				traceKeyValue->arrayValue->parent->next = tempValuesVector;
				tempValuesVector->root = traceKeyValue->arrayValue->root;
				tempValuesVector->parent = traceKeyValue->arrayValue->parent->parent;
				tempValuesVector->child = tempArrayOfString;
				tempArrayOfString->root = traceKeyValue->arrayValue->root;
				traceKeyValue->arrayValue->parent->parent->vector = tempValuesVector;
				traceKeyValue->arrayValue = tempArrayOfString;

				currentArrayOfString = traceKeyValue->arrayValue;

				return traceKeyValue;
			
		}
	}

	tempArrayOfString->root = traceKeyValue->arrayValue->root;

	struct ValuesVector* tempVectorValue;
	tempVectorValue = new ValuesVector;

	if (traceKeyValue->arrayValue->vector == NULL) {
		tempVectorValue->start = tempVectorValue;
#ifdef DEBUGREADARRAY
		cout << " <null vector>";
#endif
	}
	else {
		tempVectorValue->start = traceKeyValue->arrayValue->vector->start;
		tempVectorValue->prev = traceKeyValue->arrayValue->vector;
		traceKeyValue->arrayValue->vector->next = tempVectorValue;
	}

	tempVectorValue->root = traceKeyValue->arrayValue->root;
	tempVectorValue->parent = traceKeyValue->arrayValue;
	tempVectorValue->child = tempArrayOfString;
	tempArrayOfString->parent = tempVectorValue;

	traceKeyValue->arrayValue->vector = tempVectorValue;

	traceKeyValue->arrayValue = tempArrayOfString;

	currentArrayOfString = traceKeyValue->arrayValue;

#ifdef DEBUGREADARRAY
	cout << " -- addchildarray done\n";
#endif

	return traceKeyValue;
}



struct correspondingKeyValueReturn {
	struct KeyValue* keyNode = NULL;
	struct KeyValue* endNode = NULL;
};

struct correspondingKeyValueReturn* findCorrespondingKeyValue(struct KeyValue* traceKeyValue, char* key) {
	struct correspondingKeyValueReturn* ckvr = new correspondingKeyValueReturn;
	struct KeyValue* keyNode = NULL;
	struct KeyValue* endNode = NULL;

	bool exhausted = false;

	struct KeyValue* tempKeyValue = traceKeyValue->start;
	/*
	if (keyFound(traceKeyValue, key)) {

		keyNode = traceKeyValue;
	}
	else {
	*/

		while (!exhausted) {

			if (keyFound(tempKeyValue, key)) {
				keyNode = tempKeyValue;
			}

			if (tempKeyValue->next == NULL) {
				endNode = tempKeyValue;
				exhausted = true;
			}
			else {
				tempKeyValue = tempKeyValue->next;
			}
		}
	//}

	ckvr->endNode = endNode;
	ckvr->keyNode = keyNode;

	return ckvr;
}

struct ValuesVector* findLastValuesVector(struct ValuesVector* passedValuesVector) {
	if (passedValuesVector == NULL) {
		return NULL;
	}
	bool exhausted = false;
	while (!exhausted) {
		if (passedValuesVector->next == NULL) {
			exhausted = true;
		}
		else {
			passedValuesVector = passedValuesVector->next;
		}
	}
	return passedValuesVector;
}


struct ArrayOfString* leafArrayValue(struct ArrayOfString* traceArrayValue) {
	bool exhausted = false;

	while (!exhausted) {

		if (traceArrayValue->vector != NULL) {
			traceArrayValue->vector = findLastValuesVector(traceArrayValue->vector);
		}

		if (traceArrayValue->vector->child != NULL) {
			traceArrayValue = traceArrayValue->vector->child;
		}
		else {
			exhausted = true;
			if (traceArrayValue->vector != NULL) {
				traceArrayValue->vector = findLastValuesVector(traceArrayValue->vector);
			}
		}
	}

	return traceArrayValue;
}

struct ArrayOfString* gotoParentArray(struct KeyValue* traceKeyValue) {
	if (traceKeyValue == NULL) {
		return NULL;
	}

#ifdef DEBUGREADARRAY
	cout << " << going to parent";
#endif

	if (theState->stateNow != ArrayOpen) {

		if (traceKeyValue->arrayValue != NULL) {
			if (traceKeyValue->arrayValue->parent != NULL) {
				//EM_ASM_({console.log("toparent current " + $0 + " has parent " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->start);
				if (traceKeyValue->arrayValue->parent->start->parent != NULL) {
					//EM_ASM_({console.log("toparent done " + $0 + " to " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->parent);
					traceKeyValue->arrayValue = traceKeyValue->arrayValue->parent->parent;
					currentArrayOfString = traceKeyValue->arrayValue;
				}
#ifdef DEBUGREADARRAY
				cout << " - non-array nested>>";
#endif
			}
			else {
				//EM_ASM_({console.log("toparent closed " + $0);}, traceKeyValue->arrayValue);
				traceKeyValue->arrayValue->closed = true;
#ifdef DEBUGREADARRAY
				cout << " - non-array root>>";
#endif
			}
		}
#ifdef DEBUGREADARRAY
		cout << "\n";
#endif

		return traceKeyValue->arrayValue;

	}
	else {

		struct KeyValue* tempKeyValue;

		struct correspondingKeyValueReturn* ckvr;
		ckvr = findCorrespondingKeyValue(traceKeyValue, input->currentReadKey);
		tempKeyValue = ckvr->keyNode;

		cout << " - 1.0 ";

		if (tempKeyValue == NULL) {
			return traceKeyValue->arrayValue;
		}
		else {
			if (tempKeyValue->arrayValue != NULL) {
				tempKeyValue->arrayValue = leafArrayValue(tempKeyValue->arrayValue);
			}
		}

		if (tempKeyValue->arrayValue != NULL) {
			if (tempKeyValue->arrayValue->parent != NULL) {
				cout << " - 1.1 ";
				//EM_ASM_({console.log("toparent current " + $0 + " has parent " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->start);
				if (tempKeyValue->arrayValue->parent->start->parent != NULL) {
					//EM_ASM_({console.log("toparent done " + $0 + " to " + $1);}, traceKeyValue->arrayValue, traceKeyValue->arrayValue->parent->parent);
					tempKeyValue->arrayValue = tempKeyValue->arrayValue->parent->parent;
					currentArrayOfString = tempKeyValue->arrayValue;
				}
#ifdef DEBUGREADARRAY
				cout << " - nested>>";
#endif
			}
			else {
				cout << " - 1.2 ";
				//EM_ASM_({console.log("toparent closed " + $0);}, traceKeyValue->arrayValue);
				tempKeyValue->arrayValue->closed = true;
#ifdef DEBUGREADARRAY
				cout << " - root>>";
#endif
			}
		}
#ifdef DEBUGREADARRAY
		cout << "\n";
#endif

		return tempKeyValue->arrayValue;

	}
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
	}
	else {
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
	if (passedValuesVector == NULL) {
		return 0;
	}
	passedValuesVector = passedValuesVector->start;

	bool exhausted = false;
	struct ValuesVector* tempValuesVector;
	while (!exhausted) {
		if (passedValuesVector->child != NULL) {
			deleteArrayValue(passedValuesVector->child);
		}

		tempValuesVector = passedValuesVector;
		if (passedValuesVector->next != NULL) {
			passedValuesVector = passedValuesVector->next;
		}
		else {
			exhausted = true;
		}

		delete tempValuesVector;
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

	return 1;
}

//void KeyValueTrail* deleteKeyValues(struct KeyValueTrail* passedKeyValueTrail) {
void deleteKeyValues(struct KeyValueTrail* passedKeyValueTrail) {
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
	bool exhausted = false;
	while (!exhausted) {

		counter++;

		if (tempKeyValue->arrayValue != NULL) {
			if (tempKeyValue->arrayValue->vector != NULL) {
				if (tempKeyValue->arrayValue->root != NULL) {
					deleteArrayValue(tempKeyValue->arrayValue->root);
					tempKeyValue->arrayValue = NULL;
				}
			}
			else {
				delete tempKeyValue->arrayValue;
			}
		}

		if (tempKeyValue->next == NULL) {
			exhausted = true;
			delete tempKeyValue;
			tempKeyValue = NULL;
		}
		else {
			temptempKeyValue = tempKeyValue;
			tempKeyValue = tempKeyValue->next;
			delete temptempKeyValue;
		}


	}

	if (tempKeyValue != NULL) {
		if (strlen(tempKeyValue->key) > 0) {
			todisplay = tempKeyValue->key[0];
		}
		else {
			todisplay = ' ';
		}
		if (strlen(tempKeyValue->value) > 0) {
			valdisplay = tempKeyValue->value[0];
		}
		else {
			valdisplay = ' ';
		}

		if (tempKeyValue->arrayValue != NULL) {
			if (strlen(tempKeyValue->value) < 1) {
				if (tempKeyValue->arrayValue->root != NULL) {
					deleteArrayValue(tempKeyValue->arrayValue->root);
					tempKeyValue->arrayValue = NULL;
				}
			}
			else {
				delete tempKeyValue->arrayValue;
			}
		}

		delete tempKeyValue;
	}



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
	}
	else {
		//EM_ASM({console.log("pushValuesVector 1.0 ");});
		traceVector->start = traceVector;
		traceVector->next = NULL;
		traceVector->prev = NULL;
	}

	if (tempString.length() >= 20) {
		strcpy(traceVector->value, tempString.substr(0, 20).c_str());
	}
	else {
		strcpy(traceVector->value, tempString.c_str());
	}

	traceArrayOfString->vector = traceVector;
#ifdef DEBUGREADARRAY
	cout << traceArrayOfString->vector->value;
#endif

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
		}
		else {
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
	struct correspondingKeyValueReturn* ckvr;

	if (strcmp(key, "ty") == 0) {
		memset(input->currentTy, 0, sizeof(input->currentTy));
		strcat(input->currentTy, value);
		memset(theScope->currentTy, 0, sizeof(theScope->currentTy));
		strcat(theScope->currentTy, value);
	}

	
	if (traceKeyValue != NULL) {
		ckvr = findCorrespondingKeyValue(traceKeyValue, key);
		endNode = ckvr->endNode;
		keyNode = ckvr->keyNode;
		/*
		struct KeyValue* tempKeyValue = traceKeyValue->start;
		if (keyFound(traceKeyValue, key)) {

			keyNode = traceKeyValue;
		}
		else {

			while (!exhausted) {

				if (keyFound(tempKeyValue, key)) {
					keyNode = tempKeyValue;
				}

				if (tempKeyValue->next == NULL) {
					endNode = tempKeyValue;
					exhausted = true;
				}
				else {
					tempKeyValue = tempKeyValue->next;
				}
			}
		}
		*/

	}
	else {

		createdKeyValue = new KeyValue;

		createdKeyValue->start = createdKeyValue;
		createdKeyValue->prev = NULL;
		createdKeyValue->next = NULL;
		keyNode = createdKeyValue;
		strcpy(keyNode->key, key);

	}

	if (keyNode == NULL) {
		if (traceKeyValue != NULL && strlen(traceKeyValue->key) < 1) {
			keyNode = traceKeyValue;
			strcpy(keyNode->key, key);
		}
		else {

			keyNode = new KeyValue;

			if (endNode != NULL) {
				endNode->next = keyNode;
				keyNode->prev = endNode;
				keyNode->start = endNode->start;
			}
			else {
				keyNode->start = keyNode;
			}

			if (traceKeyValue != NULL) {
				keyNode->start = traceKeyValue->start;
			}
			else {
				keyNode->start = keyNode;
			}

			strcpy(keyNode->key, key);
		}
	}

	if (strlen(value) <= 0) {
		value = 0;
	}

	if (isArray && !justStartedArray) { // commented to remove justStartedArray

		struct ArrayOfString* traceArrayValue;
		traceArrayValue = keyNode->arrayValue;

		if (keyNode->arrayValue == NULL) {
			struct ArrayOfString* tempArrayOfString;
			tempArrayOfString = new ArrayOfString;
			tempArrayOfString->root = tempArrayOfString;
			currentArrayOfString = tempArrayOfString;
			keyNode->arrayValue = tempArrayOfString;

			traceArrayValue = keyNode->arrayValue;
		}
		else {

			traceArrayValue = leafArrayValue(traceArrayValue);
			/*
			exhausted = false;

			while (!exhausted) {

				if (traceArrayValue->vector != NULL) {
					cout << "-->";
					traceArrayValue->vector = findLastValuesVector(traceArrayValue->vector);
				}

				if (traceArrayValue->vector->child != NULL) {
					traceArrayValue = traceArrayValue->vector->child;
				}
				else {
					exhausted = true;
				}
				cout << "==>";
			}
			*/

		}

		pushValuesVector(traceArrayValue, value);
	}
	else {

		if (justStartedArray) {
			if (strlen(value) <= 0) {
				value = 0;
			}
		}

		strcpy(keyNode->value, value);

	}
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
	}
	else {
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
	}
	else {
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
	while (!exhausted) {
		*(tempArray + index) = (passedArrayOfVertex->vertex->x / theAnimation->w) - 0.5;
		index = index + 1;
		*(tempArray + index) = (passedArrayOfVertex->vertex->y / theAnimation->h) - 0.5;
		//EM_ASM({console.log("val " + $0 + " " + $1 + " " + $2);}, *(tempArray + index - 1), *(tempArray + index), passedArrayOfVertex->vertex->x);
		index = index + 1;
		if (theAnimation->ddd) {
			if (theAnimation->z > 0) {
				*(tempArray + index) = (passedArrayOfVertex->vertex->z / theAnimation->z) - 0.5;
			}
			else {
				*(tempArray + index) = (passedArrayOfVertex->vertex->z / theAnimation->h) - 0.5;
			}
		}
		else {
			if (passedArrayOfVertex->order > 0) {
				*(tempArray + index) = (passedArrayOfVertex->order / 10000);
			}
		}
		index = index + 1;
		*(tempArray + index) = passedArrayOfVertex->vertex->a;
		index = index + 1;
		if (passedArrayOfVertex->next == NULL) {
			exhausted = true;
		}
		else {
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

#ifdef DEBUGPOPULATEVERTICES
	if (baseVector->child == NULL) {
		cout << "No vertex data for sure\n";
	}
	else {
		cout << "YAY found vertex data\n";
	}
#endif

	bool exhausted = false;
	currentUniversalCount = 0;

	while (!exhausted) {
		if (baseVector->child == NULL) {
			if (baseVector->next == NULL) {
				break;
			}
			else {
				baseVector = baseVector->next;
				continue;
			}
		}
		currentUniversalCount = currentUniversalCount + 1;

		string xvals(baseVector->child->vector->start->value);
		float xval = 0;
		if (xvals.length() < 1) {
			xval = 0;
		}
		else {
			if (!xvals.empty()) {
				xval = stof(xvals);
			}
			else {
				xval = 0;
			}
		}
		string yvals(baseVector->child->vector->start->next->value);
		float yval = 0;
		if (yvals.length() < 1) {
			yval = 0;
		}
		else {
			if (!yvals.empty()) {
				yval = stof(yvals);
			}
			else {
				yval = 0;
			}
		}
		float vertex[4] = { xval, yval, 0.0f, 1.0f };
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
		}
		else {
			baseVector = baseVector->next;
		}
	}

#ifdef DEBUG3
	//cout << "populateVertices " << currentUniversalCount << "\n";
#endif

	if (targetVertex != NULL) {
		targetVertex->next = targetVertex->start;
		targetVertex->start->prev = targetVertex;
	}

	if (targetVertex != NULL) {
		return targetVertex->start;
	}
	else {
		return NULL;
	}
}

float populateFloat(char* tempStr) {
	string xvals(tempStr);

	float xval = 0;
	if (xvals.length() < 1) {
		xval = 0;
	}
	else {
		if (!xvals.empty()) {
			xval = stof(xvals);
		}
		else {
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
	while (!exhausted) {
		tempCount++;
		if (baseVector->next == NULL) {
			exhausted = true;
		}
		else {
			baseVector = baseVector->next;
		}
	}
	tempFloatArray->count = tempCount;
	tempFloatArray->floatArray = new float[tempCount];

	//EM_ASM({console.log("->>-->> count " + $0);}, tempCount);
	baseVector = traceArrayValue->vector->start;
	exhausted = false;
	currentUniversalCount = 0;
	while (!exhausted) {
		/*if (baseVector->child == NULL) {
			break;
		}*/

		string xvals(baseVector->value);
		float xval = 0;
		if (xvals.length() < 1) {
			xval = 0;
		}
		else {
			if (!xvals.empty()) {
				xval = stof(xvals);
			}
			else {
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
		}
		else {
			baseVector = baseVector->next;
		}
	}
	return tempFloatArray;
}


// common functions related to geometry

float distanceBetweenPoints(struct Vertex* pointA, struct Vertex* pointB) {
	float distance = (sqrt(pow((((float)pointA->x * 2) - ((float)pointB->x) * 2), 2) + pow((((float)pointA->y * 2) - ((float)pointB->y * 2)), 2)));
	//EM_ASM_({console.log("    ///////////> " + $0 + " " + $1 + " " + $2 + " " + $3 + " " + $4);}, distance, pointA->x, pointB->x, pointA->y, pointB->y);
	return distance;
}

void getBBArray(struct ArrayOfVertex* passedAOV, struct BoundingBox* currentBB) {
	bool exhausted = false;
	int count = 0;
	while (!exhausted) {
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
		}
		else {
			passedAOV = passedAOV->next;
		}
	}
}

void getBBProp(struct PropertiesShapeProp* passedPropertiesShapeProp, struct BoundingBox* currentBB) {
	bool exhausted = false;
	while (!exhausted) {
		if (passedPropertiesShapeProp->v != NULL) {
			getBBArray(passedPropertiesShapeProp->v->start, currentBB);
		}
		if (passedPropertiesShapeProp->next == NULL) {
			exhausted = true;
		}
		else {
			passedPropertiesShapeProp = passedPropertiesShapeProp->next;
		}
	}
}

void getBBPropShape(struct PropertiesShape* passedPropertiesShape, struct BoundingBox* currentBB) {
	bool exhausted = false;
	while (!exhausted) {
		if (passedPropertiesShape->k != NULL) {
			getBBProp(passedPropertiesShape->k->start, currentBB);
		}
		if (passedPropertiesShape->next == NULL) {
			exhausted = true;
		}
		else {
			passedPropertiesShape = passedPropertiesShape->next;
		}
	}
}

void getBoundingBox(struct ShapesItem* passedShapesItem, struct BoundingBox* currentBB) {
	bool exhausted = false;
	while (!exhausted) {
		if (passedShapesItem->it != NULL) {
			getBoundingBox(passedShapesItem->it->start, currentBB);
		}
		if (passedShapesItem->ks != NULL) {
			getBBPropShape(passedShapesItem->ks, currentBB);
		}
		if (passedShapesItem->next == NULL) {
			exhausted = true;
		}
		else {
			passedShapesItem = passedShapesItem->next;
		}

	}
	//return currentBB;
}

struct ArrayOfVertex* bezierFillNulls(struct ArrayOfVertex* startV, struct ArrayOfVertex* endV, int segSize, int* v_count, int* bezier_count) {
	float vStepX = (endV->vertex->x - startV->vertex->x) / segSize;
	float vStepY = (endV->vertex->y - startV->vertex->y) / segSize;
	struct ArrayOfVertex* intermediate;
	struct ArrayOfVertex* lastIntermediate = NULL;
	for (int i = 0; i < segSize; i++) {
		intermediate = new ArrayOfVertex;
		intermediate->vertex = new Vertex;
		if (lastIntermediate == NULL) {
			startV->next = intermediate;
			intermediate->prev = startV;
		}
		else {
			lastIntermediate->next = intermediate;
			intermediate->prev = lastIntermediate;
		}
		intermediate->start = startV->start;

		intermediate->vertex->x = startV->vertex->x + vStepX;
		intermediate->vertex->y = startV->vertex->y + vStepY;

		intermediate->bezier = true;
		intermediate->vertex->z = 0;
		intermediate->vertex->a = 1;

		lastIntermediate = intermediate;
		(*v_count)++;
		(*bezier_count)++;
	}
	if (lastIntermediate != NULL) {
		lastIntermediate->next = endV;
		endV->prev = lastIntermediate;
	}
	return lastIntermediate;
}

void adjustScale(struct ArrayOfVertex* v, struct ArrayOfVertex* i, struct ArrayOfVertex* o) {
}

// related to animating
void bezierSegment(struct ArrayOfVertex* v, struct ArrayOfVertex* i, struct ArrayOfVertex* o, int* v_count, int* bezier_count, float* segSizePassed, bool fillNulls, bool isGeometry, bool autoSegSize, int bezierType, bool doTranslation) {
	/*
		bezierType:
			1 - linear
			2 - quadratic
			3 - cubic
	*/


	//EM_ASM({console.log("BZ 1 ");});
	bool exhausted = false;
	v = v->start;
	i = i->start;
	o = o->start;

	//EM_ASM({console.log("BZ 2 ");});
	struct ArrayOfVertex* o1, * o2, * p1, * p2;

	bool startedCycling = false;
	struct ArrayOfVertex* startPoint = v->start;
	//struct ArrayOfVertex* nextVertex = NULL;
	struct ArrayOfVertex* lastIntermediate = NULL;
	struct ArrayOfVertex* intermediate = NULL;
	struct ArrayOfVertex* intermediateStart = NULL;

	//EM_ASM({console.log("BZ 3 ");});
	float oneTcube, oneTsquare, Tcube, Tsquare, oneT;
	float segSize;

	int cycleCount = 0;

	int segCounter = 0;
	while (!exhausted) {
		i = i->next;
		o = o->next;
		v = v->next;
		if (v == startPoint) {
			cycleCount++;
		}
		/*
		if (isGeometry) {
			if (v == startPoint->next && startedCycling) {
				exhausted = true;
				break;
			}
		} else {
			if (v == startPoint && startedCycling) {
				exhausted = true;
				break;
			}
		}
		*/
		//continue;
		/*
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
				if (v == startPoint && startedCycling == true) {
					break;
				}
				exhausted = true;
			}
		*/
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
			startedCycling = true;
			segCounter++;
			if (fillNulls) {
				bezierFillNulls(v->prev, v, *(segSizePassed + segCounter), v_count, bezier_count);
			}
			/*
			i = i->next;
			o = o->next;
			v = v->next;
			*/
			/*
			if (isGeometry) {
				if (v == startPoint->next && cycleCount == 2) {
					exhausted = true;
					break;
				}
			} else {
				if (v == startPoint->next && startedCycling) {
					exhausted = true;
					break;
				}
			}
			*/
			//EM_ASM({console.log("non-bezier ");});
			if (isGeometry) {
				if (v == startPoint->next && cycleCount == 2) {
					exhausted = true;
					break;
				}
			}
			else {
				if (v == startPoint && cycleCount == 2) {
					exhausted = true;
					break;
				}
			}
			continue;
		}
		else {
			/*
			i = i->next;
			o = o->next;
			v = v->next;
			*/
			/*
			if (isGeometry) {
				if (v == startPoint->next && cycleCount == 2) {
					exhausted = true;
					break;
				}
			} else {
				if (v == startPoint->next && startedCycling) {
					exhausted = true;
					break;
				}
			}
			*/
			//EM_ASM({console.log("breakout ");});
			if (isGeometry) {
				if (v == startPoint->next && cycleCount == 2) {
					exhausted = true;
					break;
				}
			}
			else {
				if (v == startPoint && cycleCount == 2) {
					exhausted = true;
					break;
				}
			}
		}

		startedCycling = true;
		o1 = v->prev;
		o2 = v;
		p1 = o->prev;
		p2 = i;

		//float segSize = 0.10;
		segCounter++;
		float distNow;
		if (autoSegSize) {
			distNow = distanceBetweenPoints(v->prev->vertex, v->vertex);
			if (distNow < 0) {
				distNow = distNow * -1;
			}
			if (distNow >= 4) {
				segSize = 1 / (distNow / 2);
			}
			else {
				continue;
			}
			/*
			if (distNow >= 2) {
				segSize = 1 / (distNow / 2);
			} else {
				continue;
			}
			*/
		}
		else {
			segSize = *(segSizePassed + segCounter);
		}
		if (segSize == 0 || segSize < 0.0001) {
			continue;
		}
		float segments = 1 / segSize;
		//float segNow = segSize;
		float segNow = segSize;
		//EM_ASM_({console.log("segnow, segsize, distNow " + $0 + ", " + $1 + ". " + $2);}, segNow, segSize, distNow);

		float p1x;
		float p2x;
		float p1y;
		float p2y;

		switch (bezierType) {
		case 1:
			p1x = p1->vertex->x + o2->vertex->x;
			p1y = p1->vertex->y + o2->vertex->y;
			break;
		case 2:
			p1x = p1->vertex->x;
			p2x = p2->vertex->x;
			p1y = p1->vertex->y;
			p2y = p2->vertex->y;
			break;
		case 3:
			p1x = p1->vertex->x + o1->vertex->x;
			p2x = p2->vertex->x + o2->vertex->x;
			p1y = p1->vertex->y + o1->vertex->y;
			p2y = p2->vertex->y + o2->vertex->y;
			break;
		}

		intermediateStart = NULL;
		lastIntermediate = NULL;
		while (segNow <= 1) {
			intermediate = new ArrayOfVertex;
			intermediate->vertex = new Vertex;
			intermediate->start = v->start;

			//intermediate->vertex->x = ( (((pt2->x - pt1->x) / segments) * segNow) + pt1->x );
			//intermediate->vertex->y = ( (((pt2->y - pt1->y) / segments) * segNow) + pt1->y );

			oneT = 1 - segNow;
			Tcube = pow(segNow, 3);
			Tsquare = pow(segNow, 2);
			oneTcube = pow(oneT, 3);
			oneTsquare = pow(oneT, 2);

			switch (bezierType) {
			case 1:
				intermediate->vertex->x = (oneTsquare * o1->vertex->x) +
					(2 * oneT * segNow * p1x) +
					(Tsquare * o2->vertex->x);

				intermediate->vertex->y = (oneTsquare * o1->vertex->y) +
					(2 * oneT * segNow * p1y) +
					(Tsquare * o2->vertex->y);
				//EM_ASM_({console.log("[[[[[[[[[[[[[==========> ROTATE adding intermediate " + $0 + " " + $1);}, intermediate->vertex->x, intermediate->vertex->y);

				break;
			case 2:
				intermediate->vertex->x = (oneTcube * o1->vertex->x) +
					(3 * oneTsquare * segNow * p1x) +
					(3 * oneT * Tsquare * p2x) +
					(Tcube * o2->vertex->x);

				intermediate->vertex->y = (oneTcube * o1->vertex->y) +
					(3 * oneTsquare * segNow * p1y) +
					(3 * oneT * Tsquare * p2y) +
					(Tcube * o2->vertex->y);
				break;
			case 3:
				intermediate->vertex->x = (oneTcube * o1->vertex->x) +
					(3 * oneTsquare * segNow * p1x) +
					(3 * oneT * Tsquare * p2x) +
					(Tcube * o2->vertex->x);

				intermediate->vertex->y = (oneTcube * o1->vertex->y) +
					(3 * oneTsquare * segNow * p1y) +
					(3 * oneT * Tsquare * p2y) +
					(Tcube * o2->vertex->y);
				break;
			}

			//EM_ASM_({console.log("[[[[[[[[[[[[[==========> adding intermediate " + $0 + " " + $1);}, intermediate->vertex->x, intermediate->vertex->y);
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
			(*v_count)++;
			(*bezier_count)++;
			if (intermediateStart == NULL) {
				intermediateStart = intermediate;
			}
		}
		(*v_count)++;
		(*bezier_count)++;
		if (intermediateStart != NULL) {
			intermediateStart->prev = o1;
			o1->next = intermediateStart;
			intermediate->next = o2;
			o2->prev = intermediate;
		}

		//return intermediate;
	}
	/*
	if (intermediate != NULL) {
		v->start->prev = intermediate;
		intermediate->next = v->start;
	}
	*/

	if (doTranslation) {
		v = v->start;
		cycleCount = 0;
		exhausted = false;
		float heightOffset = ((theAnimation->h * theAnimation->scaleFactorY) / theAnimation->h);
		float widthOffset = ((theAnimation->w * theAnimation->scaleFactorX) / theAnimation->w);
		while (!exhausted) {
			//v->vertex->x = (2 * ((v->vertex->x * theAnimation->scaleFactorX) / theAnimation->w));
			//v->vertex->y = ((2 * ((v->vertex->y * theAnimation->scaleFactorY) / theAnimation->h))) * -1;
			//
			v->vertex->x = ((2 * ((v->vertex->x * theAnimation->scaleFactorX) / theAnimation->w)) - 1);
			v->vertex->y = ((2 * ((v->vertex->y * theAnimation->scaleFactorY) / theAnimation->h)) - 1) * -1;
			//
			//v->vertex->x = ( ((v->vertex->x * theAnimation->scaleFactorX) / theAnimation->w));
			//v->vertex->y = ((( ((v->vertex->y * theAnimation->scaleFactorY) / theAnimation->h)))) * -1;
			if (cycleCount == 0) {
				v = v->next;
				cycleCount = 1;
			}
			else {
				if (v->next == v->start) {
					exhausted = true;
				}
				else {
					v = v->next;
				}
			}
		}
	}
}

double seconds() {
	/*struct timeval tempRef;
	gettimeofday(&tempRef, NULL);

	return (double)tempRef.tv_sec + ((double)tempRef.tv_usec / 1000000);*/
	return 1;
}

struct ReturnPosition* getRelativePosition(struct BoundingBox* currentBB, struct BoundingBox* currentShapesBB, bool onlyAnchor) {
	struct ReturnPosition* temp = new ReturnPosition;
	temp->layers = new Vertex;
	temp->shapes = new Vertex;
	//temp->layersTranslated = new Vertex;
	//temp->shapesTranslated = new Vertex;

				//temp->layers->x = layersPosition.x - currentBB->anchorX + shapesPosition.x;
				//temp->layers->y = layersPosition.y - currentBB->anchorY + shapesPosition.y;


	if (!onlyAnchor) {

		if (currentBB != NULL) {
			if (currentBB->anchorSet) {
				temp->layers->x = layersPosition.x - currentBB->anchorX;
				temp->layers->y = layersPosition.y - currentBB->anchorY;
			}
			else {
				temp->layers->x = layersPosition.x - (currentBB->w / 2);
				temp->layers->y = layersPosition.y - (currentBB->h / 2);
				//temp->layers->x = layersPosition.x;
				//temp->layers->y = layersPosition.y;
			}

		}

		if (currentShapesBB != NULL) {
			if (currentShapesBB->anchorSet) {
				//temp->shapes->x = shapesPosition.x - currentShapesBB->anchorX;
				//temp->shapes->y = shapesPosition.y - currentShapesBB->anchorY;
				temp->shapes->x = cumulativeShapesDelta.x - currentShapesBB->anchorX;
				temp->shapes->y = cumulativeShapesDelta.y - currentShapesBB->anchorY;
			}
			else {
				//temp->shapes->x = shapesPosition.x;
				//temp->shapes->y = shapesPosition.x;

				//temp->shapes->x = shapesPosition.x - (currentShapesBB->w / 2);
				//temp->shapes->y = shapesPosition.y - (currentShapesBB->h / 2);
				temp->shapes->x = cumulativeShapesDelta.x - (currentShapesBB->w / 2);
				temp->shapes->y = cumulativeShapesDelta.y - (currentShapesBB->h / 2);
			}
		}

	}
	else {

		if (currentBB != NULL) {
			if (currentBB->anchorSet) {
				temp->layers->x = currentBB->anchorX;
				temp->layers->y = currentBB->anchorY;
			}
			else {
				temp->layers->x = (currentBB->w / 2);
				temp->layers->y = (currentBB->h / 2);
			}

		}

		if (currentShapesBB != NULL) {
			if (currentShapesBB->anchorSet) {
				temp->shapes->x = currentShapesBB->anchorX;
				temp->shapes->y = currentShapesBB->anchorY;
			}
			else {

				temp->shapes->x = (currentShapesBB->w / 2);
				temp->shapes->y = (currentShapesBB->h / 2);
			}
		}

		/*
		if (currentBB != NULL) {
			if (currentBB->anchorSet) {
				temp->layers->x = currentBB->anchorX * -1;
				temp->layers->y = currentBB->anchorY * -1;
			} else {
				temp->layers->x = (currentBB->w / 2) * -1;
				temp->layers->y = (currentBB->h / 2) * -1;
			}

		}

		if (currentShapesBB != NULL) {
			if (currentShapesBB->anchorSet) {
				temp->shapes->x = currentShapesBB->anchorX * -1;
				temp->shapes->y = currentShapesBB->anchorY * -1;
			} else {

				temp->shapes->x = (currentShapesBB->w / 2) * -1;
				temp->shapes->y = (currentShapesBB->h / 2) * -1;
			}
		}
		*/

	}

	/*
	temp->layersTranslated->x = ((temp->layers->x * theAnimation->scaleFactorX) / theAnimation->w) - heightOffset;
	temp->layersTranslated->y = ((temp->layers->y * theAnimation->scaleFactorY) / theAnimation->h) - widthOffset;
	temp->shapesTranslated->x = ((temp->shapes->x * theAnimation->scaleFactorX) / theAnimation->w) - heightOffset;
	temp->shapesTranslated->y = ((temp->shapes->y * theAnimation->scaleFactorY) / theAnimation->h) - widthOffset;
	*/

	/*
	if (glDimensions) {
		float heightOffset = ((theAnimation->h * theAnimation->scaleFactorY) / theAnimation->h) / 2;
		float widthOffset = ((theAnimation->w * theAnimation->scaleFactorX) / theAnimation->w) / 2;
		temp->layers->x = ((temp->layers->x * theAnimation->scaleFactorX) / theAnimation->w) - heightOffset;
		temp->layers->y = ((temp->layers->y * theAnimation->scaleFactorY) / theAnimation->h) - widthOffset;

		temp->shapes->x = ((temp->shapes->x * theAnimation->scaleFactorX) / theAnimation->w) - heightOffset;
		temp->shapes->y = ((temp->shapes->y * theAnimation->scaleFactorY) / theAnimation->h) - widthOffset;
	}
	*/


	/*
	if (currentBB->anchorSet) {
		if (currentShapesBB != NULL) {
			if (currentShapesBB->anchorSet) {
				temp->layers->x = layersPosition.x - currentBB->anchorX + (shapesPosition.x - currentShapesBB->anchorX);
				temp->layers->y = layersPosition.y - currentBB->anchorY + (shapesPosition.y - currentShapesBB->anchorY);
			} else {
				temp->layers->x = layersPosition.x - currentBB->anchorX + (shapesPosition.x - (currentShapesBB->w / 2));
				temp->layers->y = layersPosition.y - currentBB->anchorY + (shapesPosition.y - (currentShapesBB->h / 2));
			}
		} else {
			temp->layers->x = layersPosition.x - currentBB->anchorX + shapesPosition.x;
			temp->layers->y = layersPosition.y - currentBB->anchorY + shapesPosition.y;
		}
	} else {
		if (currentShapesBB != NULL) {
			if (currentShapesBB->anchorSet) {
				temp->layers->x = layersPosition.x - (currentBB->w / 2) + (shapesPosition.x - currentShapesBB->anchorX);
				temp->layers->y = layersPosition.y - (currentBB->h / 2) + (shapesPosition.y - currentShapesBB->anchorY);
			} else {
				temp->layers->x = layersPosition.x - (currentBB->w / 2) + (shapesPosition.x - (currentShapesBB->w / 2));
				temp->layers->y = layersPosition.y - (currentBB->h / 2) + (shapesPosition.y - (currentShapesBB->h / 2));
			}
		} else {
			temp->layers->x = layersPosition.x - (currentBB->w / 2) + shapesPosition.x;
			temp->layers->y = layersPosition.y - (currentBB->h / 2) + shapesPosition.y;
		}

	}
	*/

	/*
	if (shapesPosition.x != 0 || shapesPosition.y != 0) {
		if (shapesAnchor.x != 0 || shapesAnchor.y != 0) {
			temp->shapes->x = shapesPosition.x - shapesAnchor.x;
			temp->shapes->y = shapesPosition.y - shapesAnchor.y;
		} else {
			if (currentShapesBB != NULL) {
				temp->shapes->x = shapesPosition.x - (currentShapesBB->w / 2);
				temp->shapes->y = shapesPosition.y - (currentShapesBB->h / 2);
			}
		}
	}
	if (layersPosition.x != 0 || layersPosition.y != 0) {
		if (currentBB->anchorX != 0 || currentBB->anchorY != 0) {
			temp->layers->x = layersPosition.x - currentBB->anchorX;
			temp->layers->y = layersPosition.y - currentBB->anchorX;
		} else {
			temp->layers->x = layersPosition.x - (currentBB->w / 2);
			temp->layers->y = layersPosition.y - (currentBB->h / 2);
		}
	}
	*/
	return temp;
}