// functions

struct Layers* newLayers(struct Layers* passedLayers) {
	if (passedLayers == NULL) {
		passedLayers = new Layers;
		passedLayers->start = passedLayers;
	} else {
		passedLayers->next = new Layers;
		passedLayers->next->start = passedLayers->start;
		passedLayers->next->prev = passedLayers;
		passedLayers = passedLayers->next;
	}

	currentLayers = passedLayers;
        return passedLayers;
}

struct Assets* newAssets(struct Assets* passedAssets) {
	if (passedAssets == NULL) {
		passedAssets = new Assets;
		passedAssets->start = passedAssets;
	} else {
		passedAssets->next = new Assets;
		passedAssets->next->start = passedAssets->start;
		passedAssets->next->prev = passedAssets;
		passedAssets = passedAssets->next;
	}

	currentAssets = passedAssets;
	return passedAssets;
}


///////////////// assign values

int fillAnimation() {
	//EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			//EM_ASM({console.log("========================> iteration");});
		}
			//EM_ASM({console.log("========================> iteration pre");});
		if (tempKeyValue->arrayValue == NULL && strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}
			//EM_ASM({console.log("========================> iteration predone");});
		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "w") == 0) {
			string width(tempKeyValue->value);
			theAnimation->w = stoi(width);
			//EM_ASM_({console.log("========================> fill 80.1 " + $0);}, theAnimation->w);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "h") == 0) {
			string height(tempKeyValue->value);
			theAnimation->h = stoi(height);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ip") == 0) {
			theAnimation->ip = stringToFloat(tempKeyValue->value);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "op") == 0) {
			theAnimation->op = stringToFloat(tempKeyValue->value);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "fr") == 0) {
			theAnimation->fr = stringToFloat(tempKeyValue->value);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "z") == 0) {
			theAnimation->z = stringToInt(tempKeyValue->value);
			//EM_ASM_({console.log("========================> fill 80.1 " + $0);}, theAnimation->h);

		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}

	/*if (theAnimation->fr > 30) {
		theAnimation->op = theAnimation->op * (30 / theAnimation->fr);
		theAnimation->fr = 30;
	}*/

	theAnimation->fr = theAnimation->fr * theAnimation->frMultiplier;
	theAnimation->ip = theAnimation->ip * theAnimation->lengthMultiplier;
	theAnimation->op = theAnimation->op * theAnimation->lengthMultiplier;
	theAnimation->frameTime = 1 / theAnimation->fr;
	theAnimation->frameTimeMS = theAnimation->frameTime * 1000;

	theAnimation->totalTime = theAnimation->op * theAnimation->frameTime;

	if (theAnimation->customWidth > 0) {
		theAnimation->w = theAnimation->customWidth;
	}
	if (theAnimation->customHeight > 0) {
		theAnimation->h = theAnimation->customHeight;
	}
	theAnimation->halfW = theAnimation->w / 2;
	theAnimation->halfH = theAnimation->h / 2;

	theAnimation->h = theAnimation->h * theAnimation->scaleFactorY;
	theAnimation->w = theAnimation->w * theAnimation->scaleFactorX;

	//EM_ASM_({console.log("========================> theAnimation " + $0 + " " + $1);}, theAnimation->ip, theAnimation->op);
	//deleteKeyValues(theScope->currentKeyValueTrail);

	return 1;
}

int fillLayers(struct Layers* passedLayers) {
	//EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			//EM_ASM({console.log("========================> iteration");});
		}
			//EM_ASM({console.log("========================> iteration pre");});
		if (tempKeyValue->arrayValue == NULL && strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}
			//EM_ASM({console.log("========================> iteration predone");});
		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "parent") == 0) {
			passedLayers->parent = stringToInt(tempKeyValue->value);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ind") == 0) {
			passedLayers->ind = stringToInt(tempKeyValue->value);
		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}

	return 1;
}

