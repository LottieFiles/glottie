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
		} else if (theScope->prev->scope == _layers) { // PropertiesShape
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
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesMultiDimensional(currentLayers->ks->s);
		} else if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			fillPropertiesShapeProp(currentShapesItem->ks->keyframe->s);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->s);
		}
	} else if (theScope->scope == _it) {
		if (theScope->prev->scope == _layers) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _shapes) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _it) {
			fillShapesItem(currentShapesItem);
		}
		if (strcmp(theScope->prev->currentTy, "el") == 0) {
			createEllipse(currentShapesItem);
		}
		if (strcmp(theScope->currentTy, "gr") == 0) {
			if (currentShapesItem->parent != NULL) {
				currentShapesItem = currentShapesItem->parent;
				EM_ASM({console.log("//-------> shape group unwrapped");});
				grClosed = true;
			}
		}
	} else if (theScope->scope == _shapes) {
		if (theScope->prev->scope == _layers) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _k) {
			fillShapesItem(currentShapesItem);
		} else if (theScope->prev->scope == _it) {
			fillShapesItem(currentShapesItem);
		}
		if (strcmp(theScope->prev->currentTy, "el") == 0) {
			createEllipse(currentShapesItem);
		}
		if (strcmp(theScope->currentTy, "gr") == 0) {
			if (currentShapesItem->parent != NULL) {
				currentShapesItem = currentShapesItem->parent;
				grClosed = true;
				EM_ASM({console.log("//----------------> group closed");});
			}
		}
	} else if (theScope->scope == _s) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesMultiDimensional(currentLayers->ks->s);
		} else if (strcmp(theScope->prev->currentTy, "el") == 0) {
			//EM_ASM({console.log("//----------------> filling multidim");});
			fillPropertiesMultiDimensional(currentShapesItem->s);
		}
	} else if (theScope->scope == _a) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesMultiDimensional(currentLayers->ks->a);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->a);
		}
	} else if (theScope->scope == _p) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesMultiDimensional(currentLayers->ks->p);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			//EM_ASM({console.log("//----------------> filling multidim p");});
			fillPropertiesMultiDimensional(currentShapesItem->p);
		} else if (strcmp(theScope->currentTy, "el") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->p);
		}
	} else if (theScope->scope == _r) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->r);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			fillPropertiesValue(currentShapesItem->r);
		}
	} else if (theScope->scope == _o) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->o);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			fillPropertiesValue(currentShapesItem->o);
		}
	} else if (theScope->scope == _sk) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->sk);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			fillPropertiesValue(currentShapesItem->sk);
		}
	} else if (theScope->scope == _sa) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->sa);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			fillPropertiesValue(currentShapesItem->sa);
		}
	} else if (theScope->scope == _px) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->px);
		}
	} else if (theScope->scope == _py) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->py);
		}
	} else if (theScope->scope == _pz) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->pz);
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
		theAnimation->assets = newAssets(theAnimation->assets);
	} else if (theScope->scope == _layers) {
		preSwitch[1] = 0;
		if (theScope->prev->scope == _assets) {
			theAnimation->assets->precomps = newLayers(theAnimation->assets->precomps);
			currentLayers = theAnimation->assets->precomps;
			currentShapesItem = NULL;
		} else if (theScope->prev->scope == _animation) {
			theAnimation->layers = newLayers(theAnimation->layers);
			currentLayers = theAnimation->layers;
			currentShapesItem = NULL;
		}
	} else if (theScope->scope == _it) {
		//EM_ASM({console.log("----------------------------------------------------> it");});
		bool inGroup = false;
		if (strcmp(theScope->prev->currentTy, "gr") == 0) {
			inGroup = true;
		}
		if (theScope->prev->scope == _layers) {
			currentShapesItem = newShapesItem(currentShapesItem, inGroup);
		} else if (theScope->prev->scope == _shapes) {
			currentShapesItem = newShapesItem(currentShapesItem, inGroup);
		} else if (theScope->prev->scope == _it) {
			currentShapesItem = newShapesItem(currentShapesItem, inGroup);
		}
	} else if (theScope->scope == _shapes) {
		//EM_ASM({console.log("----------------------------------------------------> shapes");});
		if (theScope->prev->scope == _layers) {
			if (currentShapesItem != NULL) {
				currentShapesItem = newShapesItem(currentShapesItem, false);
			} else {
				currentLayers->shapes = newShapesItem(currentShapesItem, false);
			}
		} else if (theScope->prev->scope == _k) {
			if (currentShapesItem != NULL) {
				currentShapesItem = newShapesItem(currentShapesItem, false);
			} else {
				currentLayers->shapes = newShapesItem(currentShapesItem, false);
			}
		} else if (theScope->prev->scope == _it) {
			if (currentShapesItem != NULL) {
				currentShapesItem = newShapesItem(currentShapesItem, false);
			} else {
				currentLayers->shapes = newShapesItem(currentShapesItem, false);
			}
		}
	} else if (theScope->scope == _ty) {
	} else if (theScope->scope == _ks) {
		if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) {
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _layers) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _shapes) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _it) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		} else if (theScope->prev->scope == _layers) { // PropertiesShape
			currentLayers->ks = newHelpersTransform(currentLayers->ks);
		}
	} else if (theScope->scope == _k) {
		if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes)) {
			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);
		} else if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _it)) { // PropertiesShapeProp
			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);
		}
	} else if (theScope->scope == _e) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->e = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->e, true);
		}
	} else if (theScope->scope == _s) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->s = newPropertiesMultiDimensional();
		} else if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->s = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->s, true);
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			currentShapesItem->s = newPropertiesMultiDimensional();
		} else if (strcmp(theScope->prev->currentTy, "el") == 0) {
			currentShapesItem->s = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _a) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->a = newPropertiesMultiDimensional();
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			currentShapesItem->a = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _p) {
			//EM_ASM_({console.log("-----------------> p found " + String.fromCharCode($0) + String.fromCharCode($1));}, input->currentTy[0], input->currentTy[1]);
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->p = newPropertiesMultiDimensional();
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			//EM_ASM({console.log("-----------------> TRANSFORM p");});
			currentShapesItem->p = newPropertiesMultiDimensional();
		} else if (strcmp(theScope->prev->currentTy, "el") == 0) {
			currentShapesItem->p = newPropertiesMultiDimensional();
		}
	} else if (theScope->scope == _r) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->r = newPropertiesValue();
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			//EM_ASM({console.log("-----------------> TRANSFORM r");});
			currentShapesItem->r = newPropertiesValue();
		}
	} else if (theScope->scope == _o) {
		//EM_ASM_({console.log("-----------------> p found " + String.fromCharCode($0) + String.fromCharCode($1));}, theScope->prev->currentTy[0], theScope->prev->currentTy[1]);
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->o = newPropertiesValue();
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			currentShapesItem->o = newPropertiesValue();
		}
	} else if (theScope->scope == _sk) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->sk = newPropertiesValue();
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			currentShapesItem->sk = newPropertiesValue();
		}
	} else if (theScope->scope == _sa) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->sa = newPropertiesValue();
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			currentShapesItem->sa = newPropertiesValue();
		}
	} else if (theScope->scope == _px) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->px = newPropertiesValue();
		}
	} else if (theScope->scope == _py) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->py = newPropertiesValue();
		}
	} else if (theScope->scope == _pz) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->pz = newPropertiesValue();
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


