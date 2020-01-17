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
	} else if (theScope->scope == _k) {
		if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes) || (theScope->prev->scope == _ks && theScope->prev->prev->scope == _it)) { // PropertiesShapeProp
			fillPropertiesShapeProp(currentShapesItem->ks->k);
		}
	} else if (theScope->scope == _e) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			fillPropertiesShapeProp(currentShapesItem->ks->keyframe->e);
		}
	} else if (theScope->scope == _s) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			fillPropertiesShapeProp(currentShapesItem->ks->keyframe->s);
		}
	}

	return 1;
}

int associateBack(void* object) {
	struct ScopeBefore previousScope = lastScopeBeforeObject();

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


struct Layers* tempAssetsLayers = NULL;
struct Layers* tempAnimationLayers = NULL;

int prepareContainer(bool arrayOfObjects) {
	
	if (theScope->scope == _animation) {
		preSwitch[0] = 0;
		EM_ASM({console.log("-----------------> animation");});
		currentLayers = NULL;
		theAnimation = new Animation;
	} else if (theScope->scope == _assets) {
		preSwitch[0] = 0;
		EM_ASM({console.log("-----------------> assets");});
		currentLayers = NULL;
		theAnimation->assets = newAssets(currentAssets);
	} else if (theScope->scope == _layers) {
		preSwitch[1] = 0;
		if (theScope->prev->scope == _assets) {
			EM_ASM({console.log("-----------------> layers within assets");});
			if (preSwitch[0] == 2) {
				tempAnimationLayers = currentLayers;
				currentLayers = tempAssetsLayers;
				currentShapesItem = NULL;
				preSwitch[0] = 1;
			} else if (preSwitch[0] != 1) {
				currentLayers = NULL;
				currentShapesItem = NULL;
				preSwitch[0] = 1;
			}
			currentAssets->precomps = newLayers(currentLayers);
		} else if (theScope->prev->scope == _animation) {
			EM_ASM({console.log("-----------------> layers");});
			if (preSwitch[0] == 1) {
				tempAssetsLayers = currentLayers;
				currentLayers = tempAnimationLayers;
				currentShapesItem = NULL;
				preSwitch[0] = 2;
			} else if (preSwitch[0] != 2) {
				currentLayers = NULL;
				currentShapesItem = NULL;
				preSwitch[0] = 2;
			}
			theAnimation->layers = newLayers(currentLayers);
		}
	} else if (theScope->scope == _it) {
		EM_ASM({console.log("-----------------> it");});
		if (theScope->prev->scope == _layers) {
			EM_ASM({console.log("-----------------> it within layers");});
			/*if (preSwitch[1] != 1) {
				preSwitch[1] = 1;
				currentShapesItem = NULL;
			}*/
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _shapes) {
			EM_ASM({console.log("-----------------> it within shapes");});
			/*if (preSwitch[1] != 2) {
				preSwitch[1] = 2;
				currentShapesItem = NULL;
			}*/
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _shapes) {
		if (theScope->prev->scope == _layers) {
			EM_ASM({console.log("-----------------> shapes in layers");});
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _k) {
			EM_ASM({console.log("-----------------> shapes in k");});
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _ty) {
	} else if (theScope->scope == _ks) {
		if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) { // PropertiesShape
			EM_ASM({console.log("-----------------> ks within shapes within layers");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) {
			EM_ASM({console.log("-----------------> ks within shapes within layers");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _layers) { // PropertiesShape
			EM_ASM({console.log("-----------------> ks within it within layers");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _shapes) { // PropertiesShape
			EM_ASM({console.log("-----------------> ks within it within shapes");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		}
	} else if (theScope->scope == _k) {
		if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes)) {
			EM_ASM({console.log("-----------------> k within ks within shapes");});
			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);
		} else if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _it)) { // PropertiesShapeProp
			EM_ASM({console.log("-----------------> k within ks within it");});
			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);
		}
	} else if (theScope->scope == _e) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->e = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->e, true);
		}
	} else if (theScope->scope == _s) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->s = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->s, true);
		}
	}
	
	return 1;
}


