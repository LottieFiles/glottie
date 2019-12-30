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
	EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			EM_ASM({console.log("========================> iteration");});
		}
		if (strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}
		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "w") == 0) {
			string width(tempKeyValue->value);
			theAnimation->w = stoi(width);
			EM_ASM_({console.log("========================> fill 80.1 " + $0);}, theAnimation->w);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "h") == 0) {
			string height(tempKeyValue->value);
			theAnimation->h = stoi(height);
			EM_ASM_({console.log("========================> fill 80.1 " + $0);}, theAnimation->h);

		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}
	//deleteKeyValues(theScope->currentKeyValueTrail);

	return 1;
}

