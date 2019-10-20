
int associateKeyValues() {
	switch (theScope->scope) {
		case animation:
			break;
		case assets:
			
			break;
		case assets_layers_shapes:
			currentLayersShapes = NULL;
			currentShapesItem = NULL;
			currentShapesShape = NULL;
			
			break;
		case assets_layers_shapes_ks:
			currentPropertiesShape = NULL;
			break;
		case assets_layers_shapes_ks_k:
			EM_ASM({console.log("ks_k");});
			fillPropertiesShapeProp();
			break;
		case assets_layers_shapes_ks_k_e:
			fillPropertiesShapeProp();
			break;
		case assets_layers_shapes_ks_k_s:
			fillPropertiesShapeProp();
			break;
		//
		case layers_shapes:
			currentLayersShapes = NULL;
			currentShapesItem = NULL;
			currentShapesShape = NULL;
			break;
		case layers_shapes_ks:


			currentPropertiesShape = NULL;
			break;
		case layers_shapes_ks_k:

			fillPropertiesShapeProp();
			break;
		case layers_shapes_ks_k_e:
			fillPropertiesShapeProp();
			break;
		case layers_shapes_ks_k_s:
			fillPropertiesShapeProp();
			break;
		default:
			break;
	}
	popKeyValueTrail();

	return 1;
}

int associateBack(void* object) {
	switch (theScope->prev->scope) {
		case animation:
			break;
		case assets_layers:
			if (theScope->scope == assets_layers_shapes) {
				currentLayers->shapes = (struct LayersShapes*) object;
				EM_ASM({console.log("-----------------> encountered assets_layers");});
			}
			break;
		case assets_layers_shapes:
			if (theScope->scope == assets_layers_shapes_ks) {
				currentShapesShape->ks = (struct PropertiesShape*) object;
			}
			break;
		case assets_layers_shapes_ks:
			if (theScope->scope == assets_layers_shapes_ks_k) {
				currentPropertiesShape->k = (struct PropertiesShapeProp*) object;
			}
			break;
		//
		case layers:
			if (theScope->scope == layers_shapes) {
				currentLayers->shapes = (struct LayersShapes*) object;
			}
			break;
		case layers_shapes:
			if (theScope->scope == assets_layers_shapes_ks) {
				currentShapesShape->ks = (struct PropertiesShape*) object;
			}
			break;
		case layers_shapes_ks:
			if (theScope->scope == layers_shapes_ks_k) {
				currentPropertiesShape->k = (struct PropertiesShapeProp*) object;
			}
			break;
		case layers_shapes_ks_k:
			if (theScope->scope == layers_shapes_ks_k_e) {
				currentPropertiesShape->keyframe->e = (struct PropertiesShapeProp*) object;
				currentPropertiesShape->isKeyframe = true;
			} else if (theScope->scope == layers_shapes_ks_k_s) {
				currentPropertiesShape->keyframe->s = (struct PropertiesShapeProp*) object;
				currentPropertiesShape->isKeyframe = true;
			}
			break;
		default:
			break;
	}
	//resetReferences(); // this is now done at the end of assigning values in associateValues()
	return 1;
}

int associateType() {
	switch (theScope->prev->scope) {
		case assets_layers_shapes: //LayersShapes in assets
			currentShapesItem->ty = currentReadValue;
			newShapesShape();
			break;
		case layers_shapes: //LayersShapes
		default:
			break;

	}

	return 1;
}

/* // now defined in main.cpp
int readingDone() {
	switch (theScope->scope) {
		case assets_layers_shapes_ty:
			associateType();
			break;
		case layers_shapes_ty:
			associateType();
			break;
		default:
			theScope->currentKeyValue->key = currentReadKey;
			theScope->currentKeyValue->value = currentReadValue;

			break;
	}

	return 1;
}
*/

int prepareContainer(bool arrayOfObjects) {
	switch (theScope->scope) {
		case noscope:
			break;
		case assets_layers:
			associateBack(newLayers());
			break;
		case assets_layers_shapes: //LayersShapes in assets
			associateBack(newLayersShapes());
			break;
		case assets_layers_shapes_ks: 
			associateBack(newPropertiesShape());
			break;
		case assets_layers_shapes_ks_k: 
			associateBack(newPropertiesShapeProp());
			break;
		case assets_layers_shapes_ks_k_e: 
			associateBack(newPropertiesShapeProp());
			break;
		case assets_layers_shapes_ks_k_s: 
			associateBack(newPropertiesShapeProp());
			break;
		//
		case layers:
			associateBack(newLayers());
			break;
		case layers_shapes: //LayersShapes
			associateBack(newLayersShapes());
		case layers_shapes_ks: 
			associateBack(newPropertiesShape());
			break;
		case layers_shapes_ks_k: 
			associateBack(newPropertiesShapeProp());
			break;
		case layers_shapes_ks_k_e: 
			associateBack(newPropertiesShapeProp());
			break;
		case layers_shapes_ks_k_s: 
			associateBack(newPropertiesShapeProp());
			break;

		default:
			break;	
	}
	return 1;
}


