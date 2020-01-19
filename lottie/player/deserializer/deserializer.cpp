


/////////////////////////////////////////////////////////////////////////////

int assignReadValue() {
	input->currentReadValue[0] = '\0';
	strcat(input->currentReadValue, input->currentValue);
	return 1;
}

int assignReadKey() {
	input->currentReadKey[0] = '\0';
	strcat(input->currentReadKey, input->currentValue);
	return 1;
}

int resetCurrentValue() {
	input->currentValueLength = 0;
	input->currentValue[0] = '\0';

	return 1;
}

int appendCurrentValue(char passedChar) {
	if (input->currentValueLength >= KVLEN - 1) {
		return 0;
	}
	input->currentValue[input->currentValueLength] = passedChar;
	input->currentValue[input->currentValueLength + 1] = '\0';
	input->currentValueLength = input->currentValueLength + 1;
	return 1;
}

int addState(enum States statePassed) {
	if (theState->stateNow == KVReading && statePassed == KVReading) {
		return 0;
	}
	//EM_ASM_({console.log("adding tempState->prev 1.0 " + $0);}, theState);
	struct StateTrail* tempState;
	//EM_ASM_({console.log("adding tempState->prev 1.1 " + $0);}, theState);
	tempState = new StateTrail;
	//EM_ASM_({console.log("adding tempState->prev 1.2 " + $0);}, theState);
	/*if (theState == NULL) {
		theState = tempState;
		theState->start = theState;
		theState->stateNow = NoState;
		return 1;
	}*/
	tempState->prev = theState;

	//EM_ASM_({console.log("adding theState->next 1.1 " + $0);}, tempState);
	theState->next = tempState;
	//EM_ASM_({console.log("adding theState->start 1.1 " + $0);}, theState->start);
	tempState->start = theState->start;
	tempState->stateNow = statePassed;
	theState = tempState;
	//EM_ASM_({console.log("adding theState->start 1.5 " + $0);}, theState->start);

	return 1;
}

int removeState() {
	if (theState != NULL && theState->prev != NULL) {
		struct StateTrail* tempState;
		tempState = theState;
		theState = theState->prev;
		theState->next = NULL;
		//EM_ASM_({console.log("removed state 700.1 " + $0);}, theState);
		delete tempState;
		//EM_ASM_({console.log("removed state 700.2 " + $0);}, theState);
	} else {
		if (theState != NULL) {
			delete theState;
		}
		theState = new StateTrail;
		theState->start = theState;
		theState->stateNow = NoState;
	}

	return 1;
}

int removeReadStates() {
	struct StateTrail* tempState;
	while (theState->stateNow == KVReading || theState->stateNow == KVReadOpen) {
		//EM_ASM_({console.log("looping " + $0);}, theState->stateNow);
	
		if (theState->prev == NULL) {
			theState->next = NULL;
			theState->stateNow = NoState;
			break;
		}

		tempState = theState;
		theState = theState->prev;
		theState->next = NULL;
		delete tempState;
	}
	/*if (theState->prev == NULL && (theState->stateNow == KVReading || theState->stateNow == KVReadOpen)) {
		delete theState;
		theState = new StateTrail;
		theState->start = theState;
	}*/
	if (theState->stateNow == KVReading || theState->stateNow == KVReadOpen) {
		removeState();
	}
	
	//EM_ASM_({console.log("remove read states done 1.5 " + $0);}, theState->stateNow);


	return 1;
}

int addScope(enum Scopes scopePassed) {

	struct ScopeTrail* tempScope;
	tempScope = new ScopeTrail;
	tempScope->prev = theScope;
	tempScope->next = NULL;
	theScope->next = tempScope;
	tempScope->start = theScope->start;
	theScope = tempScope;
	theScope->currentState = theState;

	/*
	struct ScopeTrail* tempScope;
	tempScope = new ScopeTrail;
	theScope->next = tempScope;
	tempScope->prev = theScope;
	theScope = tempScope;
	theScope->next = NULL;
	theScope->currentState = theState;
	theScope->start = theScope->prev->start;
	*/

	theScope->scope = scopePassed;

	return 1;
}

struct ScopeTrail* removeObjectsFromScope(struct ScopeTrail* passedScope) {
	struct ScopeTrail* tempScope;
	while (passedScope->prev != NULL && passedScope->scope == _object) {
		tempScope = passedScope;
		passedScope = passedScope->prev;
		passedScope->next = NULL;
		delete tempScope;
	}
	return passedScope;
}

int removeScope() {
	//EM_ASM_({console.log($0);}, (int)theScope->scope);

	struct ScopeTrail* tempScope;

	if (theScope == NULL) {
		addScope(_noscope);
		addScope(_animation);
		return 1;
	}

	//EM_ASM({console.log("removing scope 1.1 ");});
	tempScope = theScope;

	//EM_ASM({console.log("removing scope 1.2 ");});
	if (theScope->prev != NULL) {
		//EM_ASM({console.log("removing scope 1.1 ");});
		if (theScope->currentKeyValueTrail != NULL) {
			//EM_ASM({console.log("removing scope 1.1.0 ");});
			theScope->currentKeyValueTrail = deleteKeyValues(theScope->currentKeyValueTrail);
			//EM_ASM({console.log("removing scope 1.1.1 ");});
			currentKeyValueTrail = theScope->currentKeyValueTrail;
			if (theScope->currentKeyValueTrail != NULL && theScope->currentKeyValueTrail->keyValue != NULL) {
				currentKeyValue = theScope->currentKeyValueTrail->keyValue;
				//EM_ASM({console.log("removing scope 1.1.3 ");});
				if (theScope->currentKeyValueTrail->keyValue->arrayValue != NULL) {
					currentArrayOfString = theScope->currentKeyValueTrail->keyValue->arrayValue;
					//EM_ASM({console.log("removing scope 1.1.4 ");});
				}
			}
		}
		//EM_ASM({console.log("removing scope 1.3 ");});
		theScope = theScope->prev;
		tempScope->prev = NULL;
		theScope->next = NULL;
		delete tempScope;
	} else {
		theScope->next = NULL;
	}
	//EM_ASM_({console.log("left behind " + $0);}, theScope->scope);

	return 1;
}

int addArray() {
	struct ArrayTrail* tempArray;
	tempArray = new ArrayTrail;
	arrayNow->next = tempArray;
	tempArray->prev = arrayNow;
	arrayNow = arrayNow->next;
	arrayNow->start = arrayNow->prev->start;
	arrayNow->next = NULL;

	return 1;
}

int removeArray() {
	struct ArrayTrail* tempArray;
	tempArray = arrayNow;
	tempArray->prev = NULL;
	arrayNow = arrayNow->prev;
	arrayNow->next = NULL;
	delete tempArray;

	return 1;
}

#include "properties.cpp"
#include "layers.cpp"
#include "shapes.cpp"
#include "associate.cpp"

struct ScopeTrail* lastScopeBeforeThis(struct ScopeTrail* tempScopeTrail) {
	if (tempScopeTrail == NULL) {
		return NULL;
	}
	int counter = 0;
	while (tempScopeTrail->prev != NULL && tempScopeTrail->scope == _object) {
		counter = counter + 1;
		tempScopeTrail = tempScopeTrail->prev;
	}
	return tempScopeTrail;
}

struct ScopeBefore lastScopeBeforeObject() {
	struct ScopeBefore result;
	struct ScopeTrail* tempScopeTrail;
	tempScopeTrail = theScope;
	long counter = 0;
	while (tempScopeTrail->prev != NULL && tempScopeTrail->scope == _object) {
		counter = counter + 1;
		tempScopeTrail = tempScopeTrail->prev;
	}
	result.scopeNow = tempScopeTrail;
	result.objectCount = counter;
	return result;
}

bool keyIs(char const *passedKey) {
	if (strcmp(input->currentReadKey, passedKey) == 0) {
		return true;
	} else {
		return false;
	}
}

int checkScope() {
	struct ScopeBefore previousScope = lastScopeBeforeObject();
	scopeChanged = true;
	if (previousScope.scopeNow->scope == _noscope) {
		addScope(_animation);
	} else if (keyIs("assets")) {
		EM_ASM({console.log("-/--> found assets");});
		addScope(_assets);
	} else if (keyIs("layers")) {
		EM_ASM({console.log("-/--> found layers");});
		addScope(_layers);
	} else if (keyIs("shapes")) {
		EM_ASM({console.log("-/--> found shapes");});
		addScope(_shapes);
	} else if (keyIs("it")) {
		EM_ASM({console.log("-/--> found it");});
		addScope(_it);
	} else if (keyIs("ty")) {
		addScope(_ty);
	} else if (keyIs("ks")) {
		EM_ASM({console.log("-/--> found ks");});
		addScope(_ks);
	} else if (keyIs("k")) {
		EM_ASM({console.log("-/--> found k");});
		addScope(_k);
	} else if (keyIs("e")) {
		addScope(_e);
	} else if (keyIs("s")) {
		addScope(_s);




	} else {
		addScope(_object);
		scopeChanged = false;	
	}

	return 1;
}

/*
int checkScope_old() {
	bool scopeChanged = false;
	struct ScopeBefore previousScope = lastScopeBeforeObject();
	//EM_ASM_({console.log("TRYING SCOPE " + $0 + " : " + $1 + " - " + $2);}, previousScope.objectCount, previousScope.scopeNow, currentReadKey[0]);
	if (previousScope.objectCount <= 1) {
				//EM_ASM_({console.log("scope hit " + $0 + " : " + $1 + " / " + String.fromCharCode($2));}, previousScope.objectCount, previousScope.scopeNow, currentReadKey[0]);
	switch (previousScope.scopeNow->scope) {
		case noscope:
			//theScope->scope = animation;
			addScope(animation);
			scopeChanged = true;

			//determineCurrentScope();
			break;
		case animation:
			if (strcmp(input->currentReadKey, "assets") == 0) {
				//EM_ASM({console.log('found assets');});
				addScope(assets);
				scopeChanged = true;
			} else if (strcmp(input->currentReadKey, "layers") == 0) {
				addScope(layers);
				scopeChanged = true;
			}
			break;
		//
		case assets:
			if (strcmp(input->currentReadKey, "layers") == 0) {
				//EM_ASM({console.log('found layers');});
				addScope(assets_layers);
				scopeChanged = true;
			}
			break;
		case assets_layers:
			if (strcmp(input->currentReadKey, "shapes") == 0) {
				//EM_ASM({console.log('found shapes');});
				addScope(assets_layers_shapes);
				scopeChanged = true;
			}
			break;
		case assets_layers_shapes_ty: //LayersShapes shape item's type found
			
			break;
		case assets_layers_shapes:
			if (strcmp(input->currentReadKey, "ks") == 0) {
				//EM_ASM({console.log('found ks');});
				addScope(assets_layers_shapes_ks);
				scopeChanged = true;
			} else if (strcmp(input->currentReadKey, "ty") == 0) {
				addScope(assets_layers_shapes_ty);
				scopeChanged = true;
			}
			break;
		case assets_layers_shapes_ks:
			if (strcmp(input->currentReadKey, "k") == 0) {
				addScope(assets_layers_shapes_ks_k);
				scopeChanged = true;
			}
			break;
		case assets_layers_shapes_ks_k:
			if (strcmp(input->currentReadKey, "e") == 0) {
				addScope(assets_layers_shapes_ks_k_e);
				scopeChanged = true;
			}
			if (strcmp(input->currentReadKey, "s") == 0) {
				addScope(assets_layers_shapes_ks_k_s);
				scopeChanged = true;
			}
			break;
		//
		case layers:
			if (strcmp(input->currentReadKey, "shapes") == 0) {
				//EM_ASM({console.log('found layers');});
				addScope(layers_shapes);
				scopeChanged = true;
			}
			break;
		case layers_shapes_ty: //LayersShapes shape item's type found
			
			break;
		case layers_shapes:
			if (strcmp(input->currentReadKey, "ks") == 0) {
				//EM_ASM({console.log("found layers ks");});
				addScope(layers_shapes_ks);
				scopeChanged = true;
			} else if (strcmp(input->currentReadKey, "ty") == 0) {
				addScope(layers_shapes_ty);
				scopeChanged = true;
			}
			break;
		case layers_shapes_ks:
			if (strcmp(input->currentReadKey, "k") == 0) {
				//EM_ASM({console.log("found layers ks k");});
				addScope(layers_shapes_ks_k);
				scopeChanged = true;
			}
			break;
		case layers_shapes_ks_k:
			if (strcmp(input->currentReadKey, "e") == 0) {
				addScope(layers_shapes_ks_k_e);
				scopeChanged = true;
			}
			if (strcmp(input->currentReadKey, "s") == 0) {
				addScope(layers_shapes_ks_k_s);
				scopeChanged = true;
			}
			break;
		default:
			break;
	}
	}
	if (!scopeChanged) {
		addScope(object);
	}
	//EM_ASM_({console.log("-->found this " + $0 + " : " + $1 + " : " + $2);}, (int)previousScope.scopeNow, previousScope.objectCount, theScope->scope);

	return 1;
}
*/

int readingDone() {
		struct KeyValue* tempKeyValue;
		if (readingArray) {
			tempKeyValue = addKeyValue(theScope->currentKeyValueTrail->keyValue, input->currentReadKey, input->currentReadValue, true);
		} else {
			tempKeyValue = addKeyValue(theScope->currentKeyValueTrail->keyValue, input->currentReadKey, input->currentReadValue, false);
		}
		theScope->currentKeyValueTrail->keyValue = tempKeyValue;
	return 1;
}

bool isReadingDone() {
			//EM_ASM({console.log("reading 100.1");});
			if ((theState->stateNow == KVReading || theState->stateNow == KVReadOpen) || strlen(input->currentValue) > 0) {
				//EM_ASM({console.log("reading 100.2");});
				if (kvState == Value) {
					//currentReadValue = input->currentValue;
					assignReadValue();
					//EM_ASM({console.log("reading 100.2.1");});
					readingDone();
					//EM_ASM({console.log("reading 100.2.2");});
					//currentValue.clear();
					//input->currentValue[0] = '\0';
					resetCurrentValue();
					//EM_ASM({console.log("reading 100.3");});
				} else {
					//currentReadKey = input->currentValue;
					assignReadKey();
					//EM_ASM_({console.log($0);}, (int)theScope->scope);
					//currentValue.clear();
					//input->currentValue[0] = '\0';
					resetCurrentValue();
				}
				//EM_ASM_({console.log("post-reading " + $0);}, theState->stateNow);
				return true;
			} else {
				//currentValue.clear();
			}
			//EM_ASM({console.log("reading 100.9");});
	return false;
}

enum States lastStateBeforeReading() {
	struct StateTrail* tempState;
	tempState = theState;
	if (tempState == NULL) {
		return NoState;
	}

	if (tempState->stateNow != KVReadOpen && tempState->stateNow != KVReading) {
		return tempState->stateNow;
	}
	while (tempState->prev != NULL && (tempState->stateNow == KVReadOpen || tempState->stateNow == KVReading)) {
		tempState = tempState->prev;
	}
	return tempState->stateNow;
}

int checkCharacter(char& currentChar) {
	EM_ASM_({console.log("YAC +++++++++++++++++++++++++++++++++++++++> " + " [ " + $1 + " ] " + String.fromCharCode($0) + " " + $2 + " - " + $3 + " " + $4);}, currentChar, readingArray,theScope->currentKeyValueTrail, colonEncountered, justStartedArray);
	switch (currentChar) {
		case '{':
			colonEncountered = false;
			//EM_ASM_({console.log("OPENING object " + $0);}, theState->stateNow);
			//EM_ASM_({console.log($0);}, (int)theState->stateNow);
			if (isReadingDone()) {
				//readingDone();
				removeReadStates();
			}

			kvState = Key;
			readingArray = false;

			struct KeyValueTrail* tempKeyValueTrail;
			if (justStartedArray == true) {
				checkScope();
				tempKeyValueTrail = newKeyValueTrail(theScope->currentKeyValueTrail);
				theScope->currentKeyValueTrail = tempKeyValueTrail;
				currentKeyValueTrail = theScope->currentKeyValueTrail;
				//EM_ASM_({console.log("DONE adding new key value trail in array " + $0);}, currentKeyValueTrail);
				readingArray = true;
			}

				 //newKeyValueTrail(theScope->currentKeyValueTrail);
			//EM_ASM({console.log("DONE adding new key value trail");});
			//theScope->currentKeyValueTrail = currentKeyValueTrail;
			if (theState->stateNow == ArrayOpen || theState->stateNow == ScopeOpenInArray || readingArray || theState->stateNow == ScopeToBeRemoved) {
				//EM_ASM({console.log("opening object in array");});
				//if (theState->keyEncountered) {
				//}

				prepareContainer(true);
				addState(ScopeOpenInArray); //// ADD STATE
				readingArray = true;
			} else {
				if (! justStartedArray) {
					checkScope();
					tempKeyValueTrail = newKeyValueTrail(theScope->currentKeyValueTrail);
					theScope->currentKeyValueTrail = tempKeyValueTrail;
					currentKeyValueTrail = theScope->currentKeyValueTrail;
					//EM_ASM_({console.log("DONE adding new key value trail " + $0);}, currentKeyValueTrail);
				}

				prepareContainer(false);
				addState(ScopeOpen); //// ADD STATE
				readingArray = false;
			}
			justStartedArray = false;
			colonEncountered = false;

			//EM_ASM_({console.log($0);}, (int)theState->stateNow);
			//EM_ASM_({console.log("OPENED object " + $0);}, theState->stateNow);
			previousScopeClosure = false;
			break;
		case '}':
			justStartedArray = false;
			colonEncountered = false;

			//EM_ASM_({console.log("CLOSING object " + $0);}, theState->stateNow);
			if (isReadingDone()) {
				//readingDone();
				//EM_ASM_({console.log("CLOSING object reading " + $0);}, theState->stateNow);
				removeReadStates();
			}
			//EM_ASM_({console.log("CLOSING reading done " + $0);}, theState->stateNow);
			//EM_ASM_({console.log($0);}, (int)theState->stateNow);

				associateKeyValues();
				//EM_ASM_({console.log("CLOSING associated " + $0);}, theState->stateNow);
				//EM_ASM_({console.log("CLOSING removed scope " + $0);}, theState->stateNow);
				if (theState->stateNow == ScopeOpenInArray) {
					//EM_ASM_({console.log("CLOSING reverting to array " + $0);}, theState->stateNow);
					readingArray = true;
				} else {
					removeScope();
				}
				//if (! previousScopeClosure) {
					removeState();
				if (lastStateBeforeReading() == ScopeOpenInArray) {
					readingArray = false;
				}
					//EM_ASM_({console.log("CLOSING removed state " + $0);}, theState->stateNow);
				//}
				currentKeyValueTrail = theScope->currentKeyValueTrail;

			//EM_ASM_({console.log($0);}, (int)theState->stateNow);
			//EM_ASM_({console.log("CLOSED object " + $0);}, theState->stateNow);
			previousScopeClosure = true;
			break;
		case '[':
			if (colonEncountered) {
				justStartedArray = true;
				colonEncountered = false;
			} else {
				justStartedArray = false;
			}
			//EM_ASM_({console.log("[OPENING array " + $0);}, theState->stateNow);
			theScope->currentKeyValueTrail->keyValue = addChildArray(theScope->currentKeyValueTrail->keyValue);
			if (isReadingDone()) {
				//readingDone();
				removeReadStates();
			}
			readingArray = true;
			kvState = Value;
			//if (theState->stateNow == ArrayOpen) {
			//}
			addState(ArrayOpen); //// ADD STATE
			//EM_ASM_({console.log("[OPENED array " + $0);}, theState->stateNow);
			previousScopeClosure = false;
			break;
		case ']':
			//EM_ASM_({console.log("[CLOSING array " + $0);}, theState->stateNow);
			//EM_ASM_({console.log($0);}, (int)theState->stateNow);
			if (! justStartedArray) {
				if (isReadingDone()) {
					//readingDone();
					//readingDone();
					removeReadStates();
				}
			} else {
				/*
				if (theScope->currentKeyValueTrail->keyValue->arrayValue->vector != NULL) {
					theScope->currentKeyValueTrail->keyValue->arrayValue->vector->prev->next = NULL;
					delete theScope->currentKeyValueTrail->keyValue->arrayValue->vector;
				}
				delete theScope->currentKeyValueTrail->keyValue->arrayValue;
				*/
				struct KeyValue* tempKeyValue;
				input->currentReadValue[0] = '\0';
				strcat(input->currentReadValue, "0");
				tempKeyValue = addKeyValue(theScope->currentKeyValueTrail->keyValue, input->currentReadKey, input->currentReadValue, false);
				theScope->currentKeyValueTrail->keyValue = tempKeyValue;
				removeReadStates();
			}
			//EM_ASM({console.log("[CLOSING reading completed");});
			kvState = Key;
			readingArray = false;
			//EM_ASM({console.log("[CLOSING reading states removed");});
			if (! justStartedArray) {
				theScope->currentKeyValueTrail->keyValue->arrayValue = gotoParentArray(theScope->currentKeyValueTrail->keyValue);
			}
			//EM_ASM({console.log("[CLOSING gone to parent array");});
			removeState();
			//EM_ASM_({console.log("[CLOSED array " + $0);}, theState->stateNow);
			previousScopeClosure = false;
			justStartedArray = false;
			break;
		case ':':
			colonEncountered = true;
			justStartedArray = false;
			if (isReadingDone()) {
			}
			removeReadStates();
			theState->keyEncountered = true;
			kvState = Value;
			previousScopeClosure = false;
			break;
		case '\'':
			justStartedArray = false;
			colonEncountered = false;

			//EM_ASM({console.log("handling apostrophe 1");});
			if (quoteOpened && (theState->stateNow == KVReading || theState->stateNow == KVReadOpen)) {
				quoteOpened = false;
				removeReadStates();
			} else {
				quoteOpened = true;
				addState(KVReadOpen); //// ADD STATE
				//currentValue.clear();
				//input->currentValue[0] = '\0';
				resetCurrentValue();
			}

			previousScopeClosure = false;
			//EM_ASM({console.log("done handling apostrophe ");});
			break;
		case ',':
			justStartedArray = false;
			colonEncountered = false;
			//EM_ASM({console.log("handling comma ");});
			//addState(NewElement);
			if (isReadingDone()) {
				//readingDone();
				//readingDone();
			}
			removeReadStates();

			//EM_ASM_({console.log("handling comma 1 " + $0);}, theState->stateNow);
			//if (lastStateBeforeReading() == ArrayOpen || readingArray) {
			if (readingArray == true) {
						//EM_ASM({console.log("reading values into an array ");});
				kvState = Value;
			} else {
				kvState = Key;
			}

			theState->keyEncountered = false;
			//EM_ASM({console.log("done with comma ");});
			previousScopeClosure = false;
			break;
		default:
			if (	currentChar != ' ' &&
				currentChar != '\f' &&
				currentChar != '\n' &&
				currentChar != '\r' &&
				currentChar != '\t' &&
				currentChar != '\v') {
				justStartedArray = false;
				colonEncountered = false;
				//if (theState->stateNow == KVReadOpen) {
				//EM_ASM({console.log("DEFAULT 10.1 ");});
					addState(KVReading); //// ADD STATE
				//EM_ASM({console.log("DEFAULT 10.2 ");});
				//}
			} else {
				if (theState->stateNow == KVReading || theState->stateNow == KVReadOpen) {
					//EM_ASM({console.log("DEFAULT 10.3 ");});
					addState(KVReading); //// ADD STATE
					//EM_ASM({console.log("DEFAULT 10.4 ");});
				}
			}
			previousScopeClosure = false;
	}

	if (theState->stateNow == KVReading) {
		//currentValue = currentValue + currentChar;
		//currentValue.append((char *)currentChar);
		//currentValue.append(1, currentChar);
		//strcat(input->currentValue, currentChar);
		appendCurrentValue(currentChar);
		//EM_ASM_({console.log(String.fromCharCode($0));}, currentChar);
	}


	return 1;
}


int deserialize() {
	//struct ScopeTrail* theScope;
	//struct StateTrail* theState;
	theScope = new ScopeTrail;
	theState = new StateTrail;
	theScope->prev = 0;
	theScope->next = 0;
	theScope->scope = _noscope;
	theState->stateNow = Start;
	theState->start = theState;
	kvState = Key;
	input = new CurrentValues;
	//EM_ASM_({console.log("start state " + $0);}, theState);

		//EM_ASM({console.log('deserializing');});

	for(char& currentChar : jsonString) {

		checkCharacter(currentChar);
		
	}
	return 1;
}


