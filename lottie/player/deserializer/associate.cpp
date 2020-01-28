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
			//EM_ASM({console.log("ks_k");});
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
		//EM_ASM({console.log("//----------------> filling animation");});
		fillAnimation();
	} else if (theScope->scope == _ks) {
		if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) { // PropertiesShape
		} else if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) {
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _layers) { // PropertiesShape
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _shapes) { // PropertiesShape
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _it) { // PropertiesShape
		}
	} else if (theScope->scope == _k) {
		if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes)) {
			//EM_ASM({console.log("//---------------> k within ks within shapes");});
			fillPropertiesShapeProp(currentShapesItem->ks->k);
		} else if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _it)) { // PropertiesShapeProp
			//EM_ASM({console.log("//----------------> k within ks within it");});
			fillPropertiesShapeProp(currentShapesItem->ks->k);
		}
	} else if (theScope->scope == _e) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			fillPropertiesShapeProp(currentShapesItem->ks->keyframe->e);
		}
	} else if (theScope->scope == _s) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->s);
		} else if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			fillPropertiesShapeProp(currentShapesItem->ks->keyframe->s);
		}
	} else if (theScope->scope == _it) {
		if (theScope->prev->scope == _layers) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _shapes) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _it) {
			fillShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _shapes) {
		if (theScope->prev->scope == _layers) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _k) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _it) {
			fillShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _a) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->a);
		}
	} else if (theScope->scope == _p) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->p);
		}
	} else if (theScope->scope == _r) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//fillPropertiesMultiDimensional(currentShapesItem->r);
		}
	} else if (theScope->scope == _o) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//fillPropertiesMultiDimensional(currentShapesItem->o);
		}
	} else if (theScope->scope == _sk) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//fillPropertiesMultiDimensional(currentShapesItem->sk);
		}
	} else if (theScope->scope == _sa) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//fillPropertiesMultiDimensional(currentShapesItem->sa);
		}
	} else if (theScope->scope == _c) {
		if (theScope->prev->scope == _shapes) {
			fillPropertiesMultiDimensional(currentShapesItem->c);
		} else if (theScope->prev->scope == _it) {
			fillPropertiesMultiDimensional(currentShapesItem->c);
		} else if (strcmp(theScope->prev->currentTy,"fl") == 0) {
			//EM_ASM({console.log("//----------------> c populating");});
			fillPropertiesMultiDimensional(currentShapesItem->c);
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
		//EM_ASM({console.log("-----------------> animation");});
		currentLayers = NULL;
		theAnimation = new Animation;
	} else if (theScope->scope == _assets) {
		preSwitch[0] = 0;
		//EM_ASM({console.log("-----------------> assets");});
		currentLayers = NULL;
		theAnimation->assets = newAssets(currentAssets);
	} else if (theScope->scope == _layers) {
		preSwitch[1] = 0;
		if (theScope->prev->scope == _assets) {
			//EM_ASM({console.log("-----------------> layers within assets");});
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
			//EM_ASM({console.log("-----------------> layers");});
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
		//EM_ASM({console.log("----------------------------------------------------> it");});
		if (theScope->prev->scope == _layers) {
			//EM_ASM({console.log("-----------------> it within layers");});
			/*if (preSwitch[1] != 1) {
				preSwitch[1] = 1;
				currentShapesItem = NULL;
			}*/
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _shapes) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _shapes) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _shapes) {
		//EM_ASM({console.log("----------------------------------------------------> shapes");});
		if (theScope->prev->scope == _layers) {
			//EM_ASM({console.log("-----------------> shapes in layers");});
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _k) {
			//EM_ASM({console.log("-----------------> shapes in k");});
			currentLayers->shapes = newShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _it) {
			currentLayers->shapes = newShapesItem(currentShapesItem);
		}
	} else if (theScope->scope == _ty) {
	} else if (theScope->scope == _ks) {
		if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) { // PropertiesShape
			//EM_ASM({console.log("-----------------> ks within shapes within layers");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-----------------> ks within shapes within layers");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _layers) { // PropertiesShape
			//EM_ASM({console.log("-----------------> ks within it within layers");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _shapes) { // PropertiesShape
			//EM_ASM({console.log("-----------------> ks within it within shapes");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _it) { // PropertiesShape
			//EM_ASM({console.log("-----------------> ks within it within shapes");});
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		}
	} else if (theScope->scope == _k) {
		if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes)) {
			//EM_ASM({console.log("-----------------> k within ks within shapes");});
			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);
		} else if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _it)) { // PropertiesShapeProp
			//EM_ASM({console.log("-----------------> k within ks within it");});
			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);
		}
	} else if (theScope->scope == _e) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->e = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->e, true);
		}
	} else if (theScope->scope == _s) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			currentShapesItem->s = newPropertiesMultiDimensional();
		} else if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->s = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->s, true);
		}
	} else if (theScope->scope == _a) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			currentShapesItem->a = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _p) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			currentShapesItem->p = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _r) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//currentShapesItem->r = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _o) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//currentShapesItem->o = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _sk) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//currentShapesItem->sk = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _sa) {
		if (strcmp(theScope->currentTy, "tr") == 0) {
			//currentShapesItem->sa = newPropertiesMultiDimensional();
		}
	
	} else if (theScope->scope == _c) {
		//EM_ASM({console.log("-----------------> c ");});
		if (theScope->prev->scope == _shapes) {
			//EM_ASM({console.log("-----------------> c within shapes");});
			currentShapesItem->c = newPropertiesMultiDimensional();
		} else if (theScope->prev->scope == _it) {
			//EM_ASM({console.log("-----------------> c within it");});
			currentShapesItem->c = newPropertiesMultiDimensional();
		} else if (strcmp(theScope->prev->currentTy,"fl") == 0) {
			//EM_ASM({console.log("-----------------> c within it");});
			currentShapesItem->c = newPropertiesMultiDimensional();
		}
	}
	
	return 1;
}


