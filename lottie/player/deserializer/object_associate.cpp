int prepareContainer(bool arrayOfObjects) {
	switch (theScope->scope) {
		case noscope:
			break;
		case assets_layers:
			associateBack(newLayers());
			break;
		case assets_layers_shapes: //LayersShapes
			associateBack(newLayersShapes());
			break;
		case assets_layers_shapes_ks: //LayersShapes

		default:
			break;	
	}
	return 1;
}

int associateObject() {
	switch (theScope->scope) {
		case animation:
			break;
		case assets:
			
			break;
		case assets_layers_shapes:
			
			break;
		default:
			break;
	}

	return 1;
}

int associateBack(void* object) {
	switch (theScope->prev->scope) {
		case animation:
			break;
		case assets_layers:
			if (theScope->scope == assets_layers_shapes) {
				currentLayers->shapes = (struct LayersShapeS*) object;
			}
			break;
		case assets:
			
			break;
		default:
			break;
	}
	return 1;
}

int associateType() {
	switch (theScope->prev->scope) {
		case assets_layers_shapes: //LayersShapes
			currentShapesItem->ty = currentReadValue;
			break;
		default:
			break;

	}
}

int associateKeyValue() {
	
}

int readingDone() {
	switch (theScope->scope) {
		case assets_layers_shapes_ty:
			associateType();
			break;
		default:
			theScope->currentKeyValue->key = currentReadKey;
			theScope->currentKeyValue->value = currentReadValue;

			break;
	}

	return 1;
}

