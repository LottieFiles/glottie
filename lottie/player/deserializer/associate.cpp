
int associateKeyValues() {
	switch (theScope->scope) {
		case animation:
			break;
		case assets:
			
			break;
		case assets_layers_shapes:
			
			break;
		case assets_layers_shapes_ks:
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
			break;
		case layers_shapes_ks:


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
	//popKeyValueTrail();

	return 1;
}

int associateBack(void* object) {
	struct scopeBefore 
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
				EM_ASM({console.log("-----------------> associated back: assets ks");});
			}
			break;
		case assets_layers_shapes_ks_k:
			if (theScope->scope == layers_shapes_ks_k_e) {
				currentPropertiesShape->keyframe->e = (struct PropertiesShapeProp*) object;
				currentPropertiesShape->isKeyframe = true;
				EM_ASM({console.log("-----------------> associated back: assets ks_k");});
			} else if (theScope->scope == layers_shapes_ks_k_s) {
				currentPropertiesShape->keyframe->s = (struct PropertiesShapeProp*) object;
				currentPropertiesShape->isKeyframe = true;
			}
			break;
		//
		case layers:
			if (theScope->scope == layers_shapes) {
				currentLayers->shapes = (struct LayersShapes*) object;
				EM_ASM({console.log("-----------------> encountered layers");});
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
				EM_ASM({console.log("-----------------> associated back: layers ks");});
			}
			break;
		case layers_shapes_ks_k:
			if (theScope->scope == layers_shapes_ks_k_e) {
				currentPropertiesShape->keyframe->e = (struct PropertiesShapeProp*) object;
				currentPropertiesShape->isKeyframe = true;
				EM_ASM({console.log("-----------------> associated back: assets ks_k");});
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
	/*
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
				EM_ASM({console.log("-----------------> container prepped: assets ks");});
			break;
		case assets_layers_shapes_ks_k: 
			associateBack(newPropertiesShapeProp());
				EM_ASM({console.log("-----------------> container prepped: assets ks_k");});
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
				EM_ASM({console.log("-----------------> container prepped: ks_k");});
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
	*/
	struct scopeBefore previousScope = lastScopeBeforeObject();
	
	if (previousScope.scopeNow->scope == animation) {
		theAnimation = new Animation;
	} else if (previousScope.scopeNow->scope == assets) {
		theAnimation->assets = newAssets();
	} else if (previousScope.scopeNow->scope == layers) {
		if (lastScopeBeforeThis(previousScope.scopeNow->prev) == assets) {
			currentAssets->precomps = newLayers();
		} else {
			theAnimation->layers = newLayers();
		}
	} else if (previousScope.scopeNow->scope == it) {
		if (lastScopeBeforeThis(previousScope.scopeNow->prev) == layers) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (lastScopeBeforeThis(previousScope.scopeNow->prev) == shapes) {
			currentLayersShapes->shapes = newShapesItem(currentShapesItem);
		}
	} else if (previousScope.scopeNow->scope == shapes) {
	} else if (theScope->scope == ty) {
	} else if (theScope->scope == ks) {
	} else if (theScope->scope == k) {
	} else if (theScope->scope == e) {
	} else if (theScope->scope == s) {
	}
	
	return 1;
}


