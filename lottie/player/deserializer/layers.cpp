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
	currentShapesItem->end = tempShapesItem;
	currentLayersShapes->shapesItemCount++;

        return currentLayersShapes;
}

struct Layers* newLayers() {
	struct Layers* tempLayers;
	tempLayers = new Layers;
	if (currentLayers == NULL) {
		currentLayers = tempLayers;
		currentLayers->start = tempLayers;
		currentLayers->prev = NULL;
	} else {
		tempLayers->prev = currentLayers;
		currentLayers->next = tempLayers;
		currentLayers = tempLayers;
		currentLayers->start = currentLayers->prev->start;
	}
	currentLayers->next = NULL;
	currentLayers->end = tempLayers;
	
	return currentLayers;
}

