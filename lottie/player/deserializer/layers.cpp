// functions

struct LayersShapes* newLayersShapes() {
	struct LayersShapes* tempLayersShapes;
	tempLayersShapes = new LayersShapes;
	currentLayersShapes = tempLayersShapes;

	struct ShapesItem* tempShapesItem;
	tempShapesItem = new ShapesItem;

	if (currentLayersShapes->shapesItemCount == 0) {
		currentShapesItem = tempShapesItem;
		currentShapesItem->start = tempShapesItem;
		currentShapesItem->prev = NULL;
		currentLayersShapes->shapesItem = tempShapesItem;
	} else {
		tempShapesItem->prev = currentShapesItem;
		currentShapesItem->next = tempShapesItem;
		currentShapesItem = tempShapesItem;
		currentShapesItem->start = currentShapesItem->prev->start;
	}
	currentShapesItem->next = NULL;
	currentLayersShapes->shapesItemCount++;

        return currentLayersShapes;
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

struct Layers* newLayers() {
	struct Layers* tempLayers;
	tempLayers = new Layers;
	if (currentLayers == NULL) {
		tempLayers->start = tempLayers;
		currentLayers = tempLayers;
	} else {
		tempLayers->prev = currentLayers;
		currentLayers->next = tempLayers;
		tempLayers->start = currentLayers->start;
		currentLayers = tempLayers;
	}
	
	return currentLayers;
}

///////////////// assign values

