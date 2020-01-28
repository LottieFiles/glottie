// functions

struct ShapesItem* newShapesItem(struct ShapesItem* passedShapesItem) {
	if (passedShapesItem == NULL) {
		passedShapesItem = new ShapesItem;
		passedShapesItem->start = passedShapesItem;
	} else {
		passedShapesItem->next = new ShapesItem;
		passedShapesItem->next->start = passedShapesItem->start;
		passedShapesItem->next->prev = passedShapesItem;
		passedShapesItem = passedShapesItem->next;
	}
	currentShapesItem = passedShapesItem;
	return passedShapesItem;
}



	

int updateShapesItemType(enum ShapesTy passedTy, struct ShapesItem* passedShapesItem) {
	if (passedTy == _shape) {
	} else if (passedTy == _group) {
	} else if (passedTy == _ellipse) {
	} else if (passedTy == _rect) {
	} else if (passedTy == _star) {
	} else if (passedTy == _fill) {
	} else if (passedTy == _gFill) {
	} else if (passedTy == _gStroke) {
	} else if (passedTy == _stroke) {
	} else if (passedTy == _merge) {
	} else if (passedTy == _trim) {
	} else if (passedTy == _roundedCorners) {
	} else if (passedTy == _repeater) {
	} else if (passedTy == _transform) {
	} 
        return 1;
}


enum ShapesTy getShapesTy(char* passedTy) {
	enum ShapesTy tempShapesTy;
	if (strcmp(passedTy, "gr") == 0) {
		tempShapesTy = _group;
	} else if (strcmp(passedTy, "sh") == 0) {
		tempShapesTy = _shape;
	} else if (strcmp(passedTy, "el") == 0) {
		tempShapesTy = _ellipse;
	} else if (strcmp(passedTy, "rc") == 0) {
		tempShapesTy = _rect;
	} else if (strcmp(passedTy, "sr") == 0) {
		tempShapesTy = _star;
	} else if (strcmp(passedTy, "fl") == 0) {
		tempShapesTy = _fill;
	} else if (strcmp(passedTy, "gf") == 0) {
		tempShapesTy = _gFill;
	} else if (strcmp(passedTy, "gs") == 0) {
		tempShapesTy = _gStroke;
	} else if (strcmp(passedTy, "st") == 0) {
		tempShapesTy = _stroke;
	} else if (strcmp(passedTy, "mm") == 0) {
		tempShapesTy = _merge;
	} else if (strcmp(passedTy, "tm") == 0) {
		tempShapesTy = _trim;
	} else if (strcmp(passedTy, "rd") == 0) {
		tempShapesTy = _roundedCorners;
	} else if (strcmp(passedTy, "rp") == 0) {
		tempShapesTy = _repeater;
	} else if (strcmp(passedTy, "tr") == 0) {
		tempShapesTy = _transform;
	} else {
		tempShapesTy = _noshape;
	}
	return tempShapesTy;
}


int fillShapesItem(struct ShapesItem* passedShapesItem) {
	//EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue;
	bool foundExternalHandler = false;
	///////// first check whether this is a specialized shapes subobject - and call the appropriate handler
	while (! exhausted) {
		if (tempKeyValue) {
			//EM_ASM({console.log("========================> iteration");});
		}
		/*if (strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}*/


		if (strlen(tempKeyValue->key) > 0) {
			if (strcmp(tempKeyValue->key, "ty") == 0) {
				//EM_ASM({console.log("==========-------------========> shape type recorded " + $0 + " " + String.fromCharCode($1));}, passedShapesItem->ty, tempKeyValue->value[0]);
				passedShapesItem->ty = getShapesTy(tempKeyValue->value);
			} else if (strcmp(tempKeyValue->key, "tr") == 0) {
			}
		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}

	//deleteKeyValues(theScope->currentKeyValueTrail);
	////////// fill this ShapesItem only if an external handler isn't found
	if (! foundExternalHandler) {
	}

	return 1;
}


//////////// assign values

