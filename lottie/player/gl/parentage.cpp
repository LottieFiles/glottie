/*int parentShapes(struct ShapesItem* passedShapesItem, struct BoundingBox* passedLayersBB) {
	bool exhausted = false;

	while (! exhausted) {
		if (passedShapesItem->currentBB != NULL) {
			if (passedLayersBB != NULL) {
				passedShapesItem->currentBB->initXc = passedShapesItem->currentBB->initXc + passedLayersBB->cu;
			}
		}

		if (passedShapesItem->next != NULL) {
			passedShapesItem = passedShapesItem->next;
		} else {
			exhausted = true;
		}
	}

}*/

int parentLayers(struct Layers* passedLayers, bool findIndex, int indexToFind, struct Layers* parentRef) {
	//EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- LAYERS found pre 1.0");});

	if (passedLayers == NULL || passedLayers->shapes == NULL) {
		return 0;
	}
	//EM_ASM({console.log("LAYERS found pre 1.1");});



	passedLayers = passedLayers->start;
	bool exhausted = false;
	while (! exhausted) {
		if (! findIndex) {
			if (passedLayers->parent >= 0) {
				//EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- searching for parent " + $0);}, passedLayers->parent);
				parentLayers(passedLayers, true, passedLayers->parent, passedLayers);
			}
		} else {
			if (passedLayers->ind == indexToFind) {
				EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- parent found " + $0);}, passedLayers->ind);
				parentRef->parentLayers = passedLayers;
				return 1;
			}
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
			parentLayers(passedAssets->precomps->start, false, 0, NULL);
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
		parentAssets(theAnimation->assets);
	}
	if (theAnimation->layers != NULL) {
		//EM_ASM({console.log("ANIMLAYERS found");});
		parentLayers(theAnimation->layers, false, -1, NULL);
	}
	//EM_ASM({console.log("ALL done");});

	return 1;
}


