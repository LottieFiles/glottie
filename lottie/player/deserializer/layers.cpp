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

struct Assets* newAssets() {
	struct Assets* tempAssets;
	tempAssets = new Assets;
	if (currentAssets == NULL) {
		tempAssets->start = tempAssets;
		currentAssets = tempAssets;
	} else {
		tempAssets->prev = currentAssets;
		currentAssets->next = tempAssets;
		tempAssets->start = currentAssets->start;
		currentAssets = tempAssets;
	}

	return currentAssets;
}


///////////////// assign values

