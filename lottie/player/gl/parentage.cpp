
int parentLayers(struct Layers* passedLayers) {
	//EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- LAYERS found pre 1.0");});

	if (passedLayers == NULL || passedLayers->shapes == NULL) {
		return 0;
	}
	//EM_ASM({console.log("LAYERS found pre 1.1");});



	passedLayers = passedLayers->start;
	bool exhausted = false;
	while (! exhausted) {
		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			passedLayers = passedLayers->next;
		}
	}
	//EM_ASM({console.log("LAYERS found 1.2 " + $0 +  " " + $1);}, passedLayers->currentBB->w, passedLayers->currentBB->h);

	return 1;
}

int parentAssets(struct Assets* passedAssets) {
	if (passedAssets == NULL) {
		return 0;
	}

	passedAssets = passedAssets->start;
	//EM_ASM({console.log("ASSETS found pre 1.1");});
	bool exhausted = false;
	while (! exhausted) {
		//EM_ASM({console.log("PRECOMP found");});
		if (passedAssets->precomps != NULL) {
			prepLayers(passedAssets->precomps->start);
		}
		
		if (passedAssets->next == NULL) {
			exhausted = true;
		} else {
			passedAssets = passedAssets->next;
		}
	}
	//EM_ASM({console.log("PRECOMP done");});

	return 1;
}

int parentShapes() {
	//layersPosition.x = 0;
	//layersPosition.y = 0;
	//layersAnchor.x = 0;
	//layersAnchor.y = 0;

	currentLayersTransformReturn = new FillTransformReturn;

	if (theAnimation->assets != NULL) {
		//EM_ASM({console.log("ASSETS found");});
		prepAssets(theAnimation->assets);
	}
	if (theAnimation->layers != NULL) {
		//EM_ASM({console.log("ANIMLAYERS found");});
		prepLayers(theAnimation->layers);
	}
	//EM_ASM({console.log("ALL done");});

	return 1;
}


