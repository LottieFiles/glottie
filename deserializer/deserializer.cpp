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

int resetCurrentValue() {
	input->currentValueLength = 0;
	input->currentValue[0] = '\0';

	return 1;
}

int assignReadValue() {
#ifdef DEBUG
#ifdef EMT
#else
	cout << "reset currentReadValue\n";
#endif
#endif
	input->currentReadValue[0] = '\0';
#ifdef DEBUG
#ifdef EMT
#else
	cout << "copy to currentReadValue\n";
#endif
#endif

	if (input->currentValueLength > 0) {
		strcpy(input->currentReadValue, input->currentValue);
	}
	else {
		input->currentReadValue[0] = '\0';
	}
#ifdef DEBUG
#ifdef EMT
#else
	cout << "reset currentValue\n";
#endif
#endif
	resetCurrentValue();
	return 1;
}

int assignReadKey() {
#ifdef DEBUG
#ifdef EMT
#else
	cout << "reset currentReadKey\n";
#endif
#endif
	input->currentReadKey[0] = '\0';
#ifdef DEBUG
#ifdef EMT
#else
	cout << "copy to currentReadKey\n";
#endif
#endif
	if (input->currentValueLength > 0) {
		strcpy(input->currentReadKey, input->currentValue);
	}
	else {
#ifdef DEBUG
#ifdef EMT
#else
		cout << "empty key\n";
#endif
#endif
		input->currentReadKey[0] = '\0';
	}
#ifdef DEBUG
#ifdef EMT
#else
	cout << "reset currentValue\n";
#endif
#endif
	resetCurrentValue();
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
	struct StateTrail* tempState = NULL;
	delete tempState;
	tempState = new StateTrail;
	tempState->prev = theState;

	theState->next = tempState;
	tempState->start = theState->start;
	tempState->stateNow = statePassed;
	theState = tempState;

	return 1;
}

int removeState() {
	if (theState != NULL && theState->prev != NULL) {
		struct StateTrail* tempState;
		tempState = theState;
		theState = theState->prev;
		theState->next = NULL;
		delete tempState;
		tempState = NULL;
	}
	else {
		if (theState != NULL) {
			delete theState;
		}
		theState = NULL;
		theState = new StateTrail;
		theState->start = theState;
		theState->stateNow = NoState;
	}

	return 1;
}

int removeReadStates() {
	struct StateTrail* tempState;
	while (theState->stateNow == KVReading || theState->stateNow == KVReadOpen) {

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

	if (theState->stateNow == KVReading || theState->stateNow == KVReadOpen) {
		removeState();
	}

	return 1;
}

int addScope(enum Scopes scopePassed) {

	struct ScopeTrail* tempScope;
	if (scopePassed == NULL) {
		tempScope = new ScopeTrail;
		tempScope->start = tempScope;
		theScope = tempScope;
		theScope->currentState = theState;
	}
	else {
		tempScope = new ScopeTrail;
		tempScope->prev = theScope;
		tempScope->next = NULL;
		theScope->next = tempScope;
		tempScope->start = theScope->start;
		theScope = tempScope;
		theScope->currentState = theState;
	}

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

	struct ScopeTrail* tempScope;

	if (theScope == NULL) {
		addScope(_noscope);
		addScope(_animation);
		return 1;
	}

	tempScope = theScope;

	if (theScope->prev != NULL) {
		if (theScope->currentKeyValueTrail != NULL) {
			theScope->currentKeyValueTrail = NULL;
			currentKeyValueTrail = theScope->currentKeyValueTrail;
		}
		theScope = theScope->prev;
		tempScope->prev = NULL;
		theScope->next = NULL;
		currentKeyValueTrail = theScope->currentKeyValueTrail;
		delete tempScope;
		tempScope = NULL;
	}
	else {
		theScope->next = NULL;
		theScope->currentKeyValueTrail = NULL;
	}

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
#include "helpers.cpp"
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

bool keyIs(char const* passedKey) {
	if (strcmp(input->currentReadKey, passedKey) == 0) {
		return true;
	}
	else {
		return false;
	}
}

int checkScope() {
	struct ScopeBefore previousScope = lastScopeBeforeObject();
	scopeChanged = true;
	if (previousScope.scopeNow->scope == _noscope) {
		addScope(_animation);
	}
	else if (keyIs("assets")) {
		addScope(_assets);
	}
	else if (keyIs("layers")) {
		addScope(_layers);
	}
	else if (keyIs("shapes")) {
		addScope(_shapes);
	}
	else if (keyIs("it")) {
		addScope(_it);
	}
	else if (keyIs("ty")) {
		addScope(_ty);
	}
	else if (keyIs("ks")) {
		addScope(_ks);
	}
	else if (keyIs("k")) {
		addScope(_k);
	}
	else if (keyIs("e")) {
		addScope(_e);
	}
	else if (keyIs("s")) {
		addScope(_s);
	}
	else if (keyIs("a")) {
		addScope(_a);
	}
	else if (keyIs("p")) {
		addScope(_p);
	}
	else if (keyIs("r")) {
		addScope(_r);
	}
	else if (keyIs("o")) {
		addScope(_o);
	}
	else if (keyIs("sk")) {
		addScope(_sk);
	}
	else if (keyIs("sa")) {
		addScope(_sa);
	}
	else if (keyIs("c")) {
		addScope(_c);
	}
	else if (keyIs("px")) {
		addScope(_px);
	}
	else if (keyIs("py")) {
		addScope(_py);
	}
	else if (keyIs("pz")) {
		addScope(_pz);
	}
	else if (keyIs("i")) {
		addScope(_i);
	}
	else {
		addScope(_object);
		scopeChanged = false;
	}

	return 1;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

int readingDone() {
	struct KeyValue* tempKeyValue;
	if (readingArray) {
#ifdef DEBUGREADARRAY
		cout << input->currentReadValue << "(";
#endif
		tempKeyValue = addKeyValue(theScope->currentKeyValueTrail->keyValue, input->currentReadKey, input->currentReadValue, true);
#ifdef DEBUGREADARRAY
		cout << "), ";
#endif
	}
	else {
		tempKeyValue = addKeyValue(theScope->currentKeyValueTrail->keyValue, input->currentReadKey, input->currentReadValue, false);
	}
	theScope->currentKeyValueTrail->keyValue = tempKeyValue;
	return 1;
}

bool isReadingDone() {
	if ((theState->stateNow == KVReading || theState->stateNow == KVReadOpen) || strlen(input->currentValue) > 0) {
		if (kvState == Value) {
#ifdef DEBUG
#ifdef EMT
#else
			cout << "assigning read values\n";
#endif
#endif
			assignReadValue();
			lastTypeEncountered[0] = '\0';
#ifdef DEBUG
#ifdef EMT
#else
			cout << "strcat\n";
#endif
#endif
			strcat(lastTypeEncountered, input->currentReadValue);
#ifdef DEBUG
#ifdef EMT
#else
			cout << "reading done\n";
#endif
#endif
			readingDone();
#ifdef DEBUG
#ifdef EMT
#else
			cout << "reset current value\n";
#endif
#endif
			resetCurrentValue();
		}
		else {
#ifdef DEBUG
#ifdef EMT
#else
			cout << "assign read key\n";
#endif
#endif
			assignReadKey();
#ifdef DEBUG
#ifdef EMT
#else
			cout << "reset current value\n";
#endif
#endif
			resetCurrentValue();
		}
		return true;
	}
	else {
	}
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

int checkCharacter(char currentChar) {
	#ifdef EMT
	#else
		#ifdef DEBUGCHECKCHARACTER
			cout << currentChar << " -- \n";
		#endif
	#endif
	switch (currentChar) {
	case '{':
		#ifdef DEBUG
			#ifdef EMT
			#else
					cout << "opening object\n";
			#endif
		#endif
		colonEncountered = false;
#ifdef DEBUG
#ifdef EMT
#else
		cout << "reading states\n";
#endif
#endif
		if (isReadingDone()) {
			removeReadStates();
		}

		kvState = Key;
		readingArray = false;

#ifdef DEBUG
#ifdef EMT
#else
		cout << "checking states\n";
#endif
#endif
		if (theState->reservedKeySet && theState->stateNow == ArrayOpen) {
			input->currentReadKey[0] = '\0';
#ifdef DEBUG
#ifdef EMT
#else
			cout << "before strcat\n";
#endif
#endif
			strcat(input->currentReadKey, theState->reservedKey);
#ifdef DEBUG
#ifdef EMT
#else
			cout << "after strcat\n";
#endif
#endif
		}

		if (theState->stateNow == ArrayOpen) {
			addState(ScopeOpenInArray); //// ADD STATE
		}
		else {
			addState(ScopeOpen); //// ADD STATE
		}

		checkScope();

		if (theState->stateNow == ScopeOpenInArray) {
			prepareContainer(true);
		}
		else {
			prepareContainer(false);
		}

		struct KeyValueTrail* tempKeyValueTrail;
		tempKeyValueTrail = newKeyValueTrail(theScope->currentKeyValueTrail);
		theScope->currentKeyValueTrail = tempKeyValueTrail;
		currentKeyValueTrail = theScope->currentKeyValueTrail;

		readingArray = false;
		justStartedArray = false;
		colonEncountered = false;

		previousScopeClosure = false;
#ifdef DEBUG
#ifdef EMT
#else
		cout << "closing object\n";
#endif
#endif
		break;
	case '}':
#ifdef DEBUG
#ifdef EMT
#else
		cout << "closing begins \n";
#endif
#endif
		justStartedArray = false;
		colonEncountered = false;

		if (isReadingDone()) {
			removeReadStates();
		}
#ifdef DEBUG
#ifdef EMT
#else
		cout << "closing 1 \n";
#endif
#endif
#ifdef DEBUGREADARRAY
		cout << theScope->scope << " - ";
#endif
		associateKeyValues();
#ifdef DEBUG
#ifdef EMT
#else
		cout << "closing 2 \n";
#endif
#endif
		removeScope();
#ifdef DEBUG
#ifdef EMT
#else
		cout << "closing 3 \n";
#endif
#endif
		removeState();
		currentKeyValueTrail = theScope->currentKeyValueTrail;

		previousScopeClosure = true;
#ifdef DEBUG
#ifdef EMT
#else
		cout << "closed \n";
#endif
#endif
		break;
	case '[':
		if (colonEncountered) {
			justStartedArray = true;
		}
		else {
			justStartedArray = false;
		}

		if (isReadingDone()) {
			removeReadStates();
		}
		readingArray = true;
		kvState = Value;
		
		theScope->currentKeyValueTrail->keyValue = addChildArray(theScope->currentKeyValueTrail->keyValue);
		addState(ArrayOpen); //// ADD STATE

		previousScopeClosure = false;
		colonEncountered = false;

		if (strlen(input->currentReadKey) > 0) {
			theState->reservedKey[0] = '\0';
			strcat(theState->reservedKey, input->currentReadKey);
			theState->reservedKeySet = true;
		}
		else {
			if (theState->prev->reservedKeySet) {
				theState->reservedKey[0] = '\0';
				strcat(theState->reservedKey, theState->prev->reservedKey);
				theState->reservedKeySet = true;
			}
		}

#ifdef DEBUGREADARRAY
		cout << "readKey : " << input->currentReadKey << " value : ";
#endif

		break;
	case ']':
		if (!justStartedArray) {
			if (isReadingDone()) {
				removeReadStates();
			}
			if (currentShapesItem != NULL && currentShapesItem->parent != NULL && closureCount > 0) {
				currentShapesItem = currentShapesItem->parent;
				closureCount--;
			}
		}
		else {
			removeReadStates();
		}
		kvState = Key;
		readingArray = false;
#ifdef DEBUGREADARRAY
		if (theScope->currentKeyValueTrail->keyValue->arrayValue != NULL && theScope->currentKeyValueTrail->keyValue->arrayValue->vector != NULL) {
			cout << "\nlast: " << theScope->currentKeyValueTrail->keyValue->arrayValue->vector->value;
		}
#endif
		//if (theScope->currentKeyValueTrail->keyValue->arrayValue->vector != NULL) {
			theScope->currentKeyValueTrail->keyValue->arrayValue = gotoParentArray(theScope->currentKeyValueTrail->keyValue->arrayValue);
		//}
		theState->reservedKeySet = false;
		theState->reservedKey[0] = '\0';

		removeState();
		if (theState->stateNow == ArrayOpen) {
			readingArray = true;
#ifdef DEBUGNESTEDARRAY
			cout << " <closed>";
#endif
		}
		else {
			//theScope->currentKeyValueTrail->keyValue->arrayValue->closed = false;
#ifdef DEBUGNESTEDARRAY
			if (theScope->currentKeyValueTrail->keyValue != NULL && theScope->currentKeyValueTrail->keyValue->arrayValue != NULL && theScope->currentKeyValueTrail->keyValue->arrayValue->vector != NULL) {
				theScope->currentKeyValueTrail->keyValue->arrayValue = theScope->currentKeyValueTrail->keyValue->arrayValue->root;
				cout << "nested key: " << theScope->currentKeyValueTrail->keyValue->key << " ==> ";
				debugNestedArray(theScope->currentKeyValueTrail->keyValue->arrayValue->vector->start, 0);
				cout << "\n-------\n";
			}
#endif
		}
		previousScopeClosure = false;
		justStartedArray = false;

#ifdef DEBUGREADARRAY
		cout << "\n";
#endif

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
	case '"':
		justStartedArray = false;
		colonEncountered = false;

		if (quoteOpened && (theState->stateNow == KVReading || theState->stateNow == KVReadOpen)) {
			quoteOpened = false;
			removeReadStates();
		}
		else {
			quoteOpened = true;
			addState(KVReadOpen); //// ADD STATE
			resetCurrentValue();
		}

		previousScopeClosure = false;
		break;
	case ',':
		justStartedArray = false;
		colonEncountered = false;
		if (isReadingDone()) {
			removeReadStates();
		}

		if (readingArray == true) {
			kvState = Value;
		}
		else {
			kvState = Key;
		}

		theState->keyEncountered = false;
		previousScopeClosure = false;
		break;
	default:
		if (currentChar != ' ' &&
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
		}
		else {
			if (theState->stateNow == KVReading || theState->stateNow == KVReadOpen) {
				//EM_ASM({console.log("DEFAULT 10.3 ");});
				addState(KVReading); //// ADD STATE
				//EM_ASM({console.log("DEFAULT 10.4 ");});
			}
		}
		//EM_ASM({console.log("DEFAULT 10.9 ");});
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

	//EM_ASM({console.log("DEFAULT 10.4 ");});
#ifdef DEBUG
#ifdef EMT
#else
	cout << "character processed\n";
#endif
#endif


	return 1;
}


int deserialize() {
	//struct ScopeTrail* theScope;
	//struct StateTrail* theState;
	theScope = new ScopeTrail;
	theState = new StateTrail;
	theScope->prev = NULL;
	theScope->next = NULL;
	theScope->scope = _noscope;
	theScope->start = theScope;
	struct KeyValueTrail* tempKeyValueTrail;
	tempKeyValueTrail = newKeyValueTrail(theScope->currentKeyValueTrail);
	theScope->currentKeyValueTrail = tempKeyValueTrail;
	currentKeyValueTrail = theScope->currentKeyValueTrail;


	theState->stateNow = Start;
	theState->start = theState;
	kvState = Key;
	input = new CurrentValues;
	//EM_ASM_({console.log("start state " + $0);}, theState);

		//EM_ASM({console.log('deserializing');});

	for (char& currentChar : jsonString) {

		checkCharacter(currentChar);

	}
	return 1;
}


int deserializeChar(char* theString, int theLength) {
	//struct ScopeTrail* theScope;
	//struct StateTrail* theState;
	theScope = new ScopeTrail;
	theState = new StateTrail;
	theScope->prev = NULL;
	theScope->next = NULL;
	theScope->scope = _noscope;
	theScope->start = theScope;
	struct KeyValueTrail* tempKeyValueTrail;
	tempKeyValueTrail = newKeyValueTrail(theScope->currentKeyValueTrail);
	theScope->currentKeyValueTrail = tempKeyValueTrail;
	currentKeyValueTrail = theScope->currentKeyValueTrail;


	theState->stateNow = Start;
	theState->start = theState;
	kvState = Key;
	input = new CurrentValues;
	//EM_ASM_({console.log("start state " + $0 + " " + $1);}, theState, theLength);


#ifdef DEBUG
#ifdef EMT
#else
	cout << "Deserializing begins here... " << theLength << "\n";
#endif
#endif
	char tempChar;
	for (int i = 0; i < theLength; i++) {
		tempChar = theString[i];
#ifdef DEBUG
#ifdef EMT
#else
		cout << tempChar << "\n";
#endif
#endif
		//EM_ASM_({console.log("deserializing" + String.fromCharCode($0));}, theString[i]);

		//std::strcat(tempChar, theString[i]);
		checkCharacter(tempChar);
	}
	return 1;
}

