
int prepParentLayers(struct Layers* passedLayers) {
	//EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- LAYERS found pre 1.0");});

	if (passedLayers == NULL || passedLayers->shapes == NULL) {
		return 0;
	}
	//EM_ASM({console.log("LAYERS found pre 1.1");});



	passedLayers = passedLayers->start;
	bool exhausted = false;
	while (! exhausted) {
		if (passedLayers->parentLayers != NULL) {
			//EM_ASM({console.log("composition prepping ");});
			composeParentTransformLayers(passedLayers, passedLayers->parentLayers);
		}

		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			passedLayers = passedLayers->next;
		}
	}
	//EM_ASM({console.log("LAYERS found 1.2 " + $0 +  " " + $1);}, passedLayers->currentBB->w, passedLayers->currentBB->h);

	return 1;
}

int prepParentAssets(struct Assets* passedAssets) {
	if (passedAssets == NULL) {
		return 0;
	}

	passedAssets = passedAssets->start;
	//EM_ASM({console.log("ASSETS found pre 1.1");});
	bool exhausted = false;
	while (! exhausted) {
		//EM_ASM({console.log("PRECOMP found");});
		if (passedAssets->precomps != NULL) {
			prepParentLayers(passedAssets->precomps->start);
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

int prepParentShapes() {
	//layersPosition.x = 0;
	//layersPosition.y = 0;
	//layersAnchor.x = 0;
	//layersAnchor.y = 0;

	currentLayersTransformReturn = new FillTransformReturn;

	if (theAnimation->assets != NULL) {
		//EM_ASM({console.log("ASSETS found");});
		prepParentAssets(theAnimation->assets);
	}
	if (theAnimation->layers != NULL) {
		//EM_ASM({console.log("ANIMLAYERS found");});
		prepParentLayers(theAnimation->layers);
	}
	//EM_ASM({console.log("ALL done");});

	return 1;
}


