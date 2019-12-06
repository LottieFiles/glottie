int associateKeyValues() {
	/*
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
	*/
	//popKeyValueTrail();

	if (theScope->scope == _animation) {
		fillAnimation();
	}

	return 1;
}

int associateBack(void* object) {
	struct ScopeBefore previousScope = lastScopeBeforeObject();

	/*
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
	*/
	//resetReferences(); // this is now done at the end of assigning values in associateValues()
	return 1;
}

int associateType() {
	/*
	switch (theScope->prev->scope) {
		case assets_layers_shapes: //LayersShapes in assets
			currentShapesItem->ty = currentReadValue;
			newShapesShape();
			break;
		case layers_shapes: //LayersShapes
		default:
			break;

	}
	*/

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
	/*
	struct ScopeBefore previousScope = lastScopeBeforeObject();
	
	EM_ASM({console.log("-----------------> CHECKING");});
	if (previousScope.scopeNow->scope == _animation) {
		EM_ASM({console.log("-----------------> animation");});
		theAnimation = new Animation;
	} else if (previousScope.scopeNow->scope == _assets) {
		EM_ASM({console.log("-----------------> assets");});
		theAnimation->assets = newAssets();
	} else if (previousScope.scopeNow->scope == _layers) {
		if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _assets) {
			EM_ASM({console.log("-----------------> layers within assets");});
			currentAssets->precomps = newLayers(currentLayers);
		} else {
			EM_ASM({console.log("-----------------> layers");});
			theAnimation->layers = newLayers(currentLayers);
		}
	} else if (previousScope.scopeNow->scope == _it) {
		EM_ASM({console.log("-----------------> it");});
		if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _layers) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _shapes) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (previousScope.scopeNow->scope == _shapes) {
		if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _layers) {
			EM_ASM({console.log("-----------------> shapes");});
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _ty) {
	} else if (theScope->scope == _ks) {
		//if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _shapes) { // PropertiesShape
			struct ScopeTrail* first;
			struct ScopeTrail* second;
			first = lastScopeBeforeThis(previousScope.scopeNow->prev);
			second = lastScopeBeforeThis(first->prev);
			if ((first->scope == _shapes && second->scope == _layers) || (first->scope == _it && second->scope == _layers) || (first->scope == _it && second->scope == _shapes)) {
				EM_ASM({console.log("-----------------> ks within shapes");});
				currentShapesItem->ks = newPropertiesShape();
			}
		//} else if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _it) { // HelpersTransform
		//	EM_ASM({console.log("-----------------> ks");});
		//}
	} else if (theScope->scope == _k) {
	} else if (theScope->scope == _e) {
	} else if (theScope->scope == _s) {
	}
	*/

	
	if (theScope->scope == _animation) {
		EM_ASM({console.log("-----------------> animation");});
		theAnimation = new Animation;
	} else if (theScope->scope == _assets) {
		EM_ASM({console.log("-----------------> assets");});
		theAnimation->assets = newAssets();
	} else if (theScope->scope == _layers) {
		if (theScope->prev->scope == _assets) {
			EM_ASM({console.log("-----------------> layers within assets");});
			currentAssets->precomps = newLayers(currentLayers);
		} else {
			EM_ASM({console.log("-----------------> layers");});
			theAnimation->layers = newLayers(currentLayers);
		}
	} else if (theScope->scope == _it) {
		EM_ASM({console.log("-----------------> it");});
		if (theScope->prev->scope == _layers) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _shapes) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _shapes) {
		if (theScope->prev->scope == _layers) {
			EM_ASM({console.log("-----------------> shapes");});
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _ty) {
	} else if (theScope->scope == _ks) {
		//if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _shapes) { // PropertiesShape
			if ((theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) || (theScope->prev->scope == _it && theScope->prev->prev->scope == _layers) || (theScope->prev->scope == _it && theScope->prev->prev->scope == _shapes)) {
				EM_ASM({console.log("-----------------> ks within shapes");});
				currentShapesItem->ks = newPropertiesShape();
			}
		//} else if (lastScopeBeforeThis(previousScope.scopeNow->prev)->scope == _it) { // HelpersTransform
		//	EM_ASM({console.log("-----------------> ks");});
		//}
	} else if (theScope->scope == _k) {
	} else if (theScope->scope == _e) {
	} else if (theScope->scope == _s) {
	}
	
	return 1;
}


