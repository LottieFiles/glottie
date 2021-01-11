/////////////////////////////////////////////////////////
/////////                                       /////////
/////////  ******            *****************  /////////
/////////   ****              ***************   /////////
/////////    ***               ***         **   /////////
/////////    ***               ***              /////////
/////////    ***               ***     **       /////////
/////////    ***               **********       /////////
/////////    ***               **********       /////////
/////////    ***               ***     **       /////////
/////////    ***               ***              /////////
/////////    ***       **      ***              /////////
/////////   **************    *****             /////////
/////////  ****************  *******            /////////
/////////                                       /////////
/////////////////////////////////////////////////////////
///////  Created by: https://github.com/shaafiee  ///////
///////      Copyright 2020, lottiefiles.com      ///////
/////////////////////////////////////////////////////////

struct Layers* tempAssetsLayers = NULL;
struct Layers* tempAnimationLayers = NULL;
int shapesItemRelated;

void unwrapShape(bool inGroup) {
	closureCount++;
	if (currentShapesItem != NULL && currentShapesItem->parent != NULL) {
		if (closureCount > 1) {
			currentShapesItem = currentShapesItem->parent;
			//EM_ASM({console.log("-***----> unwrapped to parent " + $0);}, closureCount);
			closureCount--;
		}
		else {
			/*if (closedArray) {
				currentShapesItem = currentShapesItem->parent;
				//EM_ASM({console.log("-***----> unwrapped to parent_| " + $0);}, closureCount);
				closureCount--;
			} else {*/
			if (!inGroup) {
				currentShapesItem = currentShapesItem->parent;
				//EM_ASM({console.log("-//***----> unwrapped to parent_ " + $0);}, closureCount);
			}
			//}
		}
	}
	else {
		if (currentShapesItem == NULL && currentShapesItem->parent == NULL) {
			shapesItemRelated = 0;
		}
		else if (currentShapesItem->parent == NULL) {
			shapesItemRelated = 2;
		}
	}
	fillShapesItem(currentShapesItem);
	closedArray = false;
	//if (inGroup && currentShapesItem != NULL &&  currentShapesItem->parent != NULL) {
		//closureCount++;
	//}
	/*grClosed = false;
	if (closureCount > 1) {

	}*/
	//if (currentShapesItem->parent != NULL) {
		/*if (closureCount > 1) {
			//closureCount = 0;
			//EM_ASM_({console.log("//-------> shape group unwrapped " + $0);}, currentShapesItem->ty);
			currentShapesItem = currentShapesItem->parent;
			grClosed = true;
			if (closureCount > 0) {
				closureCount--;
			}
		}*/
		//closureCount++;
	//}
}

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
	cout << "entering association\n";
#ifdef EMT
#else
#ifdef DEBUG2
	cout << " " << theScope->scope << "\n";
#endif
#endif

	if (theScope->scope == _animation) {
		//EM_ASM({console.log("//----------------> filling animation");});
		fillAnimation();
	}
	else if (theScope->scope == _layers) {
		fillLayers(currentLayers);
	}
	else if (theScope->scope == _ks) {
		if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) { // PropertiesShape
		}
		else if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) {
		}
		else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _layers) { // PropertiesShape
		}
		else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _shapes) { // PropertiesShape
		}
		else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _it) { // PropertiesShape
		}
		else if (theScope->prev->scope == _layers) { // PropertiesShape
		}
	}
	else if (theScope->scope == _k) {
#ifdef EMT
#else
#ifdef DEBUG2
		cout << "kpop \n";
#endif
#endif
		if (theScope->prev->scope == _a && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill OffsetKeyframe in a");});
			fillPropertiesOffsetKeyframe(currentShapesItem->a->keyframe);
		}
		else if (theScope->prev->scope == _a && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill OffsetKeyframe in a in layers");});
			fillPropertiesOffsetKeyframe(currentLayers->ks->a->keyframe);

		}
		else if (theScope->prev->scope == _p && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill OffsetKeyframe in p");});
			fillPropertiesOffsetKeyframe(currentShapesItem->p->keyframe);
		}
		else if (theScope->prev->scope == _p && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill OffsetKeyframe in p in layers");});
			fillPropertiesOffsetKeyframe(currentLayers->ks->p->keyframe);

		}
		else if (theScope->prev->scope == _r && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill ValueKeyframe in r");});
			fillPropertiesValueKeyframe(currentShapesItem->r->keyframe);
		}
		else if (theScope->prev->scope == _r && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill ValueKeyframe in r in layers");});
			fillPropertiesValueKeyframe(currentLayers->ks->r->keyframe);

		}
		else if (theScope->prev->scope == _s && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill ValueKeyframe in r");});
			fillPropertiesOffsetKeyframe(currentShapesItem->s->keyframe);
		}
		else if (theScope->prev->scope == _s && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill ValueKeyframe in r in layers");});
			fillPropertiesOffsetKeyframe(currentLayers->ks->s->keyframe);

		}
		else if (theScope->prev->scope == _o && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill ValueKeyframe in r");});
			fillPropertiesValueKeyframe(currentShapesItem->o->keyframe);
		}
		else if (theScope->prev->scope == _o && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill ValueKeyframe in r in layers");});
			fillPropertiesValueKeyframe(currentLayers->ks->o->keyframe);

		}
		else if (theScope->prev->scope == _s && strcmp(theScope->prev->prev->currentTy, "el") == 0) {
			//EM_ASM({console.log("-//***----> fill ValueKeyframe in r");});
			fillPropertiesOffsetKeyframe(currentShapesItem->s->keyframe);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes) {
			//EM_ASM({console.log("-//***----> fill OffsetKeyframe in a in layers");});
			fillPropertiesShapeProp(currentShapesItem->ks->k);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _it) {
			//EM_ASM({console.log("-//***----> fill OffsetKeyframe in a in layers");});
			fillPropertiesShapeProp(currentShapesItem->ks->k);


		}
		else if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes)) {
#ifdef EMT
#else
#ifdef DEBUG2
			cout << "attempting store \n";
#endif
#endif
			//EM_ASM({console.log("//---------------> k within ks within shapes");});
			fillPropertiesShapeProp(currentShapesItem->ks->k);
		}
		else if ((theScope->prev->scope == _ks && theScope->prev->prev->scope == _it)) { // PropertiesShapeProp
#ifdef EMT
#else
#ifdef DEBUG2
			cout << "attempting store 1\n";
#endif
#endif
			//EM_ASM({console.log("//----------------> k within ks within it");});
			fillPropertiesShapeProp(currentShapesItem->ks->k);
#ifdef EMT
#else
#ifdef DEBUG2
			cout << "attempting store 2\n";
#endif
#endif
		}
	}
	else if (theScope->scope == _i) {

		if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in a");});
			fillBezierCurve(currentShapesItem->a->keyframe->i);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in a in layers");});
			fillBezierCurve(currentLayers->ks->a->keyframe->i);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in p");});
			fillBezierCurve(currentShapesItem->p->keyframe->i);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in p in layers");});
			fillBezierCurve(currentLayers->ks->p->keyframe->i);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in r");});
			fillBezierCurve(currentShapesItem->r->keyframe->i);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in r in layers");});
			fillBezierCurve(currentLayers->ks->r->keyframe->i);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in r");});
			fillBezierCurve(currentShapesItem->s->keyframe->i);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in r in layers");});
			fillBezierCurve(currentLayers->ks->s->keyframe->i);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in r");});
			fillBezierCurve(currentShapesItem->o->keyframe->i);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> fill BexierCurve in i in r in layers");});
			fillBezierCurve(currentLayers->ks->o->keyframe->i);

		}
	}
	else if (theScope->scope == _e) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			fillPropertiesShapeProp(currentShapesItem->ks->keyframe->e);
		}
	}
	else if (theScope->scope == _s) {
#ifdef DEBUGASSOC
		cout << "_s found\n";
#endif
		if (strcmp(theScope->prev->currentTy, "el") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->s);
		}
		else if (strcmp(theScope->prev->currentTy, "rc") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->s);

		}
		else if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("//----------------> filling multidim s");});
			fillPropertiesMultiDimensional(currentShapesItem->s);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("//----------------> filling multidim s in layer");});
			fillPropertiesMultiDimensional(currentLayers->ks->s);

		}
		else if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			fillPropertiesShapeProp(currentShapesItem->ks->keyframe->s);

		}
		else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->s);
		}
	}
	else if (theScope->scope == _it) {
		if (theScope->prev->scope == _layers) {
			unwrapShape(true);
		}
		else if (theScope->prev->scope == _shapes) {
			unwrapShape(true);
		}
		else if (theScope->prev->scope == _it) {
			unwrapShape(true);
		}
		if (currentShapesItem != NULL && strcmp(theScope->currentTy, "el") == 0) {
			//EM_ASM({console.log("//----------------> creating ellipse");});
			createEllipse(currentShapesItem);
		}


	}
	else if (theScope->scope == _shapes) {
		if (theScope->prev->scope == _layers) {
			unwrapShape(false);
		}
		else if (theScope->prev->scope == _k) {
			unwrapShape(false);
		}
		else if (theScope->prev->scope == _it) {
			unwrapShape(false);
		}
		if (currentShapesItem != NULL && strcmp(theScope->currentTy, "el") == 0) {
			//EM_ASM({console.log("//----------------> creating ellipse");});
			createEllipse(currentShapesItem);
		}
		/*if (strcmp(theScope->currentTy, "gr") == 0) {
			if (currentShapesItem->parent != NULL) {
				currentShapesItem = currentShapesItem->parent;
				grClosed = true;
				//EM_ASM({console.log("//----------------> group closed");});
			}
		}*/

	}
	else if (theScope->scope == _a) {


		if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			fillPropertiesMultiDimensional(currentShapesItem->a);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesMultiDimensional(currentLayers->ks->a);

		}
	}
	else if (theScope->scope == _p) {
		if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("//----------------> filling multidim p");});
			fillPropertiesMultiDimensional(currentShapesItem->p);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("//----------------> filling multidim p in layer");});
			fillPropertiesMultiDimensional(currentLayers->ks->p);
		}
		else if (strcmp(theScope->prev->currentTy, "rc") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->p);
		}
		else if (strcmp(theScope->prev->currentTy, "el") == 0) {
			fillPropertiesMultiDimensional(currentShapesItem->p);
			//} else if (theScope->prev->scope == _shapes) {
			//	fillPropertiesMultiDimensional(currentShapesItem->p);
		}
	}
	else if (theScope->scope == _r) {
		if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			fillPropertiesValue(currentShapesItem->r);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->r);
		}
		else if (strcmp(theScope->prev->currentTy, "rc") == 0) {
			fillPropertiesValue(currentShapesItem->r);

		}
	}
	else if (theScope->scope == _o) {
#ifdef DEBUGASSOC
	cout << "_o found\n";
#endif


		if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			fillBezierCurve(currentShapesItem->a->keyframe->o);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			fillBezierCurve(currentLayers->ks->a->keyframe->o);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			fillBezierCurve(currentShapesItem->p->keyframe->o);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			fillBezierCurve(currentLayers->ks->p->keyframe->o);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			fillBezierCurve(currentShapesItem->r->keyframe->o);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			fillBezierCurve(currentLayers->ks->r->keyframe->o);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			fillBezierCurve(currentShapesItem->s->keyframe->o);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			fillBezierCurve(currentLayers->ks->s->keyframe->o);

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			fillBezierCurve(currentShapesItem->o->keyframe->o);
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			fillBezierCurve(currentLayers->ks->o->keyframe->o);

		}
		else if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("//----------------> filling multidim o");});
			fillPropertiesValue(currentShapesItem->o);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("//----------------> filling multidim o in layer");});
			fillPropertiesValue(currentLayers->ks->o);


			/*
			} else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
				fillPropertiesValue(currentLayers->ks->o);
			} else if (currentShapesItem != NULL && strcmp(theScope->prev->currentTy, "tr") == 0) {
				fillPropertiesValue(currentShapesItem->o);
			*/
		}
	}
	else if (theScope->scope == _sk) {
		if (currentShapesItem != NULL && strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			fillPropertiesValue(currentShapesItem->sk);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->sk);

		}
	}
	else if (theScope->scope == _sa) {
		if (currentShapesItem != NULL && strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			fillPropertiesValue(currentShapesItem->sa);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->sa);

		}
	}
	else if (theScope->scope == _px) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->px);
		}
	}
	else if (theScope->scope == _py) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->py);
		}
	}
	else if (theScope->scope == _pz) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			fillPropertiesValue(currentLayers->ks->pz);
		}
	}
	else if (theScope->scope == _c) {
		if (currentShapesItem != NULL && theScope->prev->scope == _shapes) {
			fillPropertiesMultiDimensional(currentShapesItem->c);
		}
		else if (currentShapesItem != NULL && theScope->prev->scope == _it) {
			fillPropertiesMultiDimensional(currentShapesItem->c);
		}
		else if (strcmp(theScope->prev->currentTy, "fl") == 0) {
			//EM_ASM({console.log("//----------------> c populating");});
			fillPropertiesMultiDimensional(currentShapesItem->c);
		}
	}

	cout << "exiting\n";

	return 1;
}

int associateBack(void* object) {
	struct ScopeBefore previousScope = lastScopeBeforeObject();

	//resetReferences(); // this is now done at the end of assigning values in associateValues()
	return 1;
}

int associateType() {

	return 1;
}





void wrapShape(bool inGroup) {

	if (currentShapesItem != NULL && currentShapesItem->parent != NULL) {
		if (inGroup) {
			if (closureCount == 0) {
				//currentShapesItem = currentShapesItem->parent;
				//EM_ASM({console.log("-//***----> unwrapped to parent_ _ " + $0);}, closureCount);
			}
			currentShapesItem = newShapesItem(currentShapesItem, inGroup);
		}
		else {
			closureCount = 0;
			currentShapesItem = currentShapesItem->parent;
			//EM_ASM({console.log("-//***----> unwrapped to parent_ _ _ " + $0);}, closureCount);
			currentShapesItem = newShapesItem(currentShapesItem, false);
		}
	}
	else if (currentShapesItem != NULL && currentShapesItem->parent == NULL) {
		if (currentShapesItem->parent == NULL) {
			//EM_ASM({console.log("-//*****************************----> reset closureCount " + $0);}, closureCount);
			closureCount = 0;
		}
		if (inGroup) {
			currentShapesItem = newShapesItem(currentShapesItem, inGroup);
			shapesItemRelated = 1;
		}
		else {
			//if (currentShapesItem->parent == NULL) {
			closureCount = 0;
			//}
			currentShapesItem = newShapesItem(currentShapesItem, false);
			shapesItemRelated = 2;
		}
		//	} else if (currentShapesItem == NULL) {
	}
	else {
		//EM_ASM({console.log("-//********************-------------------------------------------> new shapesitem in layer " + $0);}, closureCount);
		currentLayers->shapes = newShapesItem(currentShapesItem, false);
		closureCount = 0;
		shapesItemRelated = 2;
	}
	if (closureCount > 0) {
		closureCount--;
	}
}


//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################



int prepareContainer(bool arrayOfObjects) {
#ifdef EMT
#else
	//cout << "Preparing container...\n";
#endif
	if (theScope->scope == _animation) {
		preSwitch[0] = 0;
		//EM_ASM({console.log("-----------------> animation");});
		currentLayers = NULL;
		theAnimation = new Animation;
	}
	else if (theScope->scope == _assets) {
		preSwitch[0] = 0;
		//EM_ASM({console.log("-----------------> assets");});
		currentLayers = NULL;
		theAnimation->assets = newAssets(theAnimation->assets);
	}
	else if (theScope->scope == _layers) {
		preSwitch[1] = 0;
		//EM_ASM({console.log("-----------------> layers");});
		if (theScope->prev->scope == _assets) {
			theAnimation->assets->precomps = newLayers(theAnimation->assets->precomps);
			currentLayers = theAnimation->assets->precomps;
			currentShapesItem = NULL;
		}
		else if (theScope->prev->scope == _animation) {
			theAnimation->layers = newLayers(theAnimation->layers);
			currentLayers = theAnimation->layers;
			currentShapesItem = NULL;
		}
	}
	else if (theScope->scope == _it) {

		//EM_ASM({console.log("----------------------------------------------------> it");});
		/*bool inGroup = false;
		if (strcmp(theScope->prev->currentTy, "gr") == 0 || currentShapesItem->) {
			inGroup = true;
		}*/
		if (theScope->prev->scope == _layers) {
			//currentShapesItem = newShapesItem(currentShapesItem, inGroup);
			wrapShape(true);
		}
		else if (theScope->prev->scope == _shapes) {
			//currentShapesItem = newShapesItem(currentShapesItem, inGroup);
			wrapShape(true);
		}
		else if (theScope->prev->scope == _it) {
			//currentShapesItem = newShapesItem(currentShapesItem, inGroup);
			wrapShape(true);
		}
		/*if (closureCount > 0) {
			closureCount--;
		}*/
	}
	else if (theScope->scope == _shapes) {
		/*if (closureCount > 0) {
			closureCount--;
		}*/
		//EM_ASM({console.log("----------------------------------------------------> shapes");});
		if (theScope->prev->scope == _layers) {
			if (currentShapesItem != NULL && currentShapesItem->parent != NULL) {
				currentShapesItem = currentShapesItem->parent;
				//EM_ASM({console.log("-//***----> unwrapped to parent_ _ _ _ " + $0);}, closureCount);
			}
			wrapShape(false);
		}
		else if (theScope->prev->scope == _k) {
			if (currentShapesItem != NULL && currentShapesItem->parent != NULL) {
				currentShapesItem = currentShapesItem->parent;
				//EM_ASM({console.log("-//***----> unwrapped to parent_ _ _ _ _ " + $0);}, closureCount);
			}
			wrapShape(true);
		}
		else if (theScope->prev->scope == _it) {
			wrapShape(true);
		}
		//EM_ASM({console.log("-//***----> shapes found_ _ _ _ " + $0);}, closureCount);
		/*if (closureCount > 0) {
			closureCount--;
		}*/
	}
	else if (theScope->scope == _ty) {
	}
	else if (theScope->scope == _ks) {
		if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		}
		else if (theScope->prev->scope == _shapes && theScope->prev->prev->scope == _layers) {
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		}
		else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _layers) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		}
		else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _shapes) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		}
		else if (theScope->prev->scope == _it && theScope->prev->prev->scope == _it) { // PropertiesShape
			currentShapesItem->ks = newPropertiesShape(currentShapesItem->ks);
		}
		else if (theScope->prev->scope == _layers) { // PropertiesShape
			currentLayers->ks = newHelpersTransform(currentLayers->ks);
		}
	}
	else if (theScope->scope == _k) {
#ifdef EMT
#else
#ifdef DEBUG2
	cout << "START Creating container for k...\n";
#endif
#endif

		//EM_ASM({console.log("-//***----> k discovered " + $0);}, theScope->prev->scope);
		if (theScope->prev->scope == _a && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in a");});
			currentShapesItem->a->keyframe = newPropertiesOffsetKeyframe();
		}
		else if (theScope->prev->scope == _a && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in a in layers ");});
			currentLayers->ks->a->keyframe = newPropertiesOffsetKeyframe();

		}
		else if (theScope->prev->scope == _p && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in p");});
			currentShapesItem->p->keyframe = newPropertiesOffsetKeyframe();
		}
		else if (theScope->prev->scope == _p && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in p in layers ");});
			currentLayers->ks->p->keyframe = newPropertiesOffsetKeyframe();

		}
		else if (theScope->prev->scope == _r && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> ValueKeyframe in r");});
			currentShapesItem->r->keyframe = newPropertiesValueKeyframe();
		}
		else if (theScope->prev->scope == _r && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> ValueKeyframe in r in layers ");});
			currentLayers->ks->r->keyframe = newPropertiesValueKeyframe();

		}
		else if (theScope->prev->scope == _s && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in p");});
			currentShapesItem->s->keyframe = newPropertiesOffsetKeyframe();
		}
		else if (theScope->prev->scope == _s && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in p in layers ");});
			currentLayers->ks->s->keyframe = newPropertiesOffsetKeyframe();

		}
		else if (theScope->prev->scope == _o && strcmp(theScope->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in p");});
			currentShapesItem->o->keyframe = newPropertiesValueKeyframe();
		}
		else if (theScope->prev->scope == _o && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> OffsetKeyframe in p in layers ");});
			currentLayers->ks->o->keyframe = newPropertiesValueKeyframe();


		}
		else if (theScope->prev->scope == _s && strcmp(theScope->prev->prev->currentTy, "el") == 0) {
			//EM_ASM({console.log("-//***----> ValueKeyframe in r");});
			currentShapesItem->s->keyframe = newPropertiesOffsetKeyframe();




		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _shapes) {

			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _it) {

			currentShapesItem->ks->k = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->k, false);

		}
		
	}
	else if (theScope->scope == _i) {

		if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in a");});
			currentShapesItem->a->keyframe->i = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in a in layers");});
			currentLayers->ks->a->keyframe->i = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in p");});
			currentShapesItem->p->keyframe->i = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in p in layers");});
			currentLayers->ks->p->keyframe->i = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in r");});
			currentShapesItem->r->keyframe->i = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in r in layers");});
			currentLayers->ks->r->keyframe->i = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in p");});
			currentShapesItem->s->keyframe->i = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in p in layers");});
			currentLayers->ks->s->keyframe->i = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in p");});
			currentShapesItem->o->keyframe->i = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-//***----> BezierCurve i in k in p in layers");});
			currentLayers->ks->o->keyframe->i = newBezierCurve();


		}
	}
	else if (theScope->scope == _e) {
		if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->e = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->e, true);
		}
	}
	else if (theScope->scope == _s) {
		if (strcmp(theScope->prev->currentTy, "el") == 0) {
			currentShapesItem->s = newPropertiesMultiDimensional();
		}
		else if (strcmp(theScope->prev->currentTy, "rc") == 0) {
			currentShapesItem->s = newPropertiesMultiDimensional();
		}
		else if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM s");});
			currentShapesItem->s = newPropertiesMultiDimensional();
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM s in LAYER");});
			currentLayers->ks->s = newPropertiesMultiDimensional();

		}
		else if ((theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _shapes) || (theScope->prev->scope == _k && theScope->prev->prev->scope == _ks && theScope->prev->prev->prev->scope == _it)) { // PropertiesShapePropKeyframe
			currentShapesItem->ks->keyframe->s = newPropertiesShapeProp(currentShapesItem->ks, currentShapesItem->ks->keyframe->s, true);
		}
		else if (strcmp(theScope->prev->currentTy, "tr") == 0) {
			//EM_ASM({console.log("-----------------> TRANSFORM s");});
			currentShapesItem->s = newPropertiesMultiDimensional();

		}
	}
	else if (theScope->scope == _a) {
		/*if (strcmp(theScope->prev->currentTy, "el") == 0) {
			currentShapesItem->s = newPropertiesMultiDimensional();
		} else if (strcmp(theScope->prev->currentTy, "rc") == 0) {
			currentShapesItem->s = newPropertiesMultiDimensional();*/
		if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			currentShapesItem->a = newPropertiesMultiDimensional();
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->a = newPropertiesMultiDimensional();

		}
	}
	else if (theScope->scope == _p) {
		//EM_ASM_({console.log("-----------------> p found " + String.fromCharCode($0) + String.fromCharCode($1));}, input->currentTy[0], input->currentTy[1]);
		if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM p in shape in LAYER");});
			currentShapesItem->p = newPropertiesMultiDimensional();
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM p in LAYER");});
			currentLayers->ks->p = newPropertiesMultiDimensional();
		}
		else if (strcmp(theScope->prev->currentTy, "el") == 0) {
			//EM_ASM({console.log("-----------------> TRANSFORM p in shape");});
			currentShapesItem->p = newPropertiesMultiDimensional();
		}
		else if (strcmp(theScope->prev->currentTy, "rc") == 0) {
			//EM_ASM({console.log("-----------------> TRANSFORM p in rc shape");});
			currentShapesItem->p = newPropertiesMultiDimensional();

		}
	}
	else if (theScope->scope == _r) {
		if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM r");});
			currentShapesItem->r = newPropertiesValue();

		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM r layers ");});
			currentLayers->ks->r = newPropertiesValue();
		}
		else if (strcmp(theScope->prev->currentTy, "rc") == 0) {
			//EM_ASM({console.log("-----------------> TRANSFORM r found in rc");});
			currentShapesItem->r = newPropertiesValue();

		}
		/*if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM r");});
			currentShapesItem->r = newPropertiesValue();
		} else if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _shapes) {
			//EM_ASM({console.log("-----------------> TRANSFORM r");});
			currentShapesItem->r = newPropertiesValue();
		} else if (strcmp(theScope->prev->currentTy, "rc") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM r");});
			currentShapesItem->r = newPropertiesValue();
		} else if (strcmp(theScope->prev->currentTy, "rc") == 0 && theScope->prev->prev->scope != _shapes) {
			//EM_ASM({console.log("-----------------> TRANSFORM r");});
			currentShapesItem->r = newPropertiesValue();
		} else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->r = newPropertiesValue();

		}*/
	}
	else if (theScope->scope == _o) {


		if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			currentShapesItem->a->keyframe->o = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _a && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			currentLayers->ks->a->keyframe->o = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			currentShapesItem->p->keyframe->o = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _p && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			currentLayers->ks->p->keyframe->o = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			currentShapesItem->r->keyframe->o = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _r && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			currentLayers->ks->r->keyframe->o = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			currentShapesItem->s->keyframe->o = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _s && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			currentLayers->ks->s->keyframe->o = newBezierCurve();

		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && strcmp(theScope->prev->prev->prev->currentTy, "tr") == 0 && theScope->prev->prev->prev->prev->scope != _layers) {
			currentShapesItem->o->keyframe->o = newBezierCurve();
		}
		else if (theScope->prev->scope == _k && theScope->prev->prev->scope == _o && theScope->prev->prev->prev->scope == _ks && theScope->prev->prev->prev->prev->scope == _layers) {
			currentLayers->ks->o->keyframe->o = newBezierCurve();

		}
		else if (strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM p");});
			currentShapesItem->o = newPropertiesValue();
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			//EM_ASM({console.log("-----------------> TRANSFORM p in LAYER");});
			currentLayers->ks->o = newPropertiesValue();
			//EM_ASM_({console.log("-----------------> p found " + String.fromCharCode($0) + String.fromCharCode($1));}, theScope->prev->currentTy[0], theScope->prev->currentTy[1]);

			/*
			} else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
				currentLayers->ks->o = newPropertiesValue();
			} else if (currentShapesItem != NULL && strcmp(theScope->prev->currentTy, "tr") == 0) {
				currentShapesItem->o = newPropertiesValue();
			*/
		}
	}
	else if (theScope->scope == _sk) {
		if (currentShapesItem != NULL && strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			currentShapesItem->sk = newPropertiesValue();
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->sk = newPropertiesValue();

		}
	}
	else if (theScope->scope == _sa) {
		if (currentShapesItem != NULL && strcmp(theScope->prev->currentTy, "tr") == 0 && theScope->prev->prev->scope != _layers) {
			currentShapesItem->sa = newPropertiesValue();
		}
		else if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->sa = newPropertiesValue();

		}
	}
	else if (theScope->scope == _px) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->px = newPropertiesValue();
		}
	}
	else if (theScope->scope == _py) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->py = newPropertiesValue();
		}
	}
	else if (theScope->scope == _pz) {
		if (theScope->prev->scope == _ks && theScope->prev->prev->scope == _layers) {
			currentLayers->ks->pz = newPropertiesValue();
		}

	}
	else if (theScope->scope == _c) {
		//EM_ASM({console.log("-----------------> c ");});
		if (theScope->prev->scope == _shapes) {
			//EM_ASM({console.log("-----------------> c within shapes");});
			currentShapesItem->c = newPropertiesMultiDimensional();
		}
		else if (currentShapesItem != NULL && theScope->prev->scope == _it) {
			//EM_ASM({console.log("-----------------> c within it");});
			currentShapesItem->c = newPropertiesMultiDimensional();
		}
		else if (currentShapesItem != NULL && strcmp(theScope->prev->currentTy, "fl") == 0) {
			//EM_ASM({console.log("-----------------> c within it");});
			currentShapesItem->c = newPropertiesMultiDimensional();
		}
	}
	if (shapesItemRelated == 1) {
		//EM_ASM({console.log("-//********************-------------------------------------------> SHAPE IN GROUP " + $0);}, closureCount);
	}
	else if (shapesItemRelated == 2) {
		//EM_ASM({console.log("-//********************-------------------------------------------> SHAPE " + $0);}, closureCount);
	}
	else if (shapesItemRelated == 3) {
		//EM_ASM({console.log("-//********************-------------------------------------------> NEW SHAPE - LAYER " + $0);}, closureCount);
	}
	else {
		//EM_ASM({console.log("-//********************-------------------------------------------> NOT shapesitem related " + $0);}, closureCount);
	}

	return 1;
}

