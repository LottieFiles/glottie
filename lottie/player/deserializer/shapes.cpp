// functions

void createRectangle(struct ShapesItem*);

struct ShapesItem* newShapesItem(struct ShapesItem* passedShapesItem, bool shapesGroup) {
	//EM_ASM({console.log("========================> shapes entered");});
	if (passedShapesItem == NULL) {
		passedShapesItem = new ShapesItem;
		passedShapesItem->start = passedShapesItem;
	} else {
		if (shapesGroup || passedShapesItem->parent != NULL) {
			if (passedShapesItem->parent == NULL) {
				grClosed = false;
				passedShapesItem->it = new ShapesItem;
				passedShapesItem->it->parent = passedShapesItem;
				passedShapesItem->it->start = passedShapesItem->it;
				passedShapesItem = passedShapesItem->it;
				//EM_ASM({console.log("=========> new shape group");});
			} else {
				passedShapesItem->next = new ShapesItem;
				passedShapesItem->next->start = passedShapesItem->start;
				passedShapesItem->next->prev = passedShapesItem;
				passedShapesItem->next->parent = passedShapesItem->parent;
				passedShapesItem = passedShapesItem->next;
				//EM_ASM({console.log("=========> added within shape group " + $0);}, passedShapesItem->parent);
			}
		} else {
				passedShapesItem->next = new ShapesItem;
				passedShapesItem->next->start = passedShapesItem->start;
				passedShapesItem->next->prev = passedShapesItem;
				//passedShapesItem->next->parent = passedShapesItem->parent;
				passedShapesItem = passedShapesItem->next;
				//EM_ASM({console.log("---> ungrouped - regular");});
		}
	}
	currentOrderIndex++;
	passedShapesItem->order = currentOrderIndex;
	currentShapesItem = passedShapesItem;
	//EM_ASM({console.log("========================> shapes exit");});
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
		//EM_ASM({console.log("==========> transform");});
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
				enum ShapesTy tempTy = passedShapesItem->ty;
				passedShapesItem->ty = getShapesTy(tempKeyValue->value);
				//EM_ASM({console.log("==========-------------========> shape type recorded " + $0 + " " + String.fromCharCode($1) + String.fromCharCode($2) + " " + $3 + " [" + $4 + "]");}, passedShapesItem->ty, tempKeyValue->value[0], tempKeyValue->value[1], tempTy, closureCount);
			} else if (strcmp(tempKeyValue->key, "nm") == 0) {
				
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

	if (passedShapesItem->ty == _ellipse) {
	}
	if (passedShapesItem->ty == _rect) {
		createRectangle(passedShapesItem);
	}

	/*
	if (passedShapesItem->parent == NULL) {
		passedShapesItem = currentLayers->shapes;
	} else {
		passedShapesItem = passedShapesItem->parent;
	}
	*/

	return 1;
}


//////////// assign values



void createEllipse(struct ShapesItem* passedShapesItem) {
	return;
	if (passedShapesItem->basicShapeGenerated == true) {
		return;
	}
	if (passedShapesItem->p == NULL || passedShapesItem->s == NULL) {
		return;
	}
	passedShapesItem->basicShapeGenerated = true;

	passedShapesItem->ks = newPropertiesShape(passedShapesItem->ks);
	passedShapesItem->ks->k = newPropertiesShapeProp(passedShapesItem->ks, passedShapesItem->ks->k, false);
	//passedShapesItem->p -- position (PropertiesMultiDimensional*)
	//passedShapesItem->s -- size (PropertiesMultiDimensional*)

	float xorig = *(passedShapesItem->p->k + 0);
	float yorig = *(passedShapesItem->p->k + 1);

	float xsize = *(passedShapesItem->s->k + 0);
	float ysize = *(passedShapesItem->s->k + 1);
	if (ysize == 0) {
		ysize = xsize;
	}

	int segments = 30;
	float angleDelta = 90/segments;
	float xy = xorig * yorig;
	float xx = xorig * xorig;
	float yy = yorig * yorig;
	float xval, yval;
	float radius;
	float angle;

	struct Vertex* currVertex = NULL;
	struct Vertex* prevVertex = NULL;

	struct ArrayOfVertex* q1PrevArray = NULL;
	struct ArrayOfVertex* q2PrevArray = NULL;
	struct ArrayOfVertex* q3PrevArray = NULL;
	struct ArrayOfVertex* q4PrevArray = NULL;
	struct ArrayOfVertex* q1 = NULL;
	struct ArrayOfVertex* q2 = NULL;
	struct ArrayOfVertex* q3 = NULL;
	struct ArrayOfVertex* q4 = NULL;
	struct ArrayOfVertex* q1Start = NULL;
	struct ArrayOfVertex* q2Start = NULL;
	struct ArrayOfVertex* q3Start = NULL;
	struct ArrayOfVertex* q4Start = NULL;
	struct ArrayOfVertex* start = NULL;

	for (int i = 1; i < 30; i++) {
		//EM_ASM({console.log("===&&&&&&&&&&===> ellipse");});
		angle = angleDelta * i;
		radius = xy / ( (xx * pow(sin(angle), 2)) + (yy * pow(cos(angle),2)) );

		xsize = radius * cos(angle);
		ysize = radius * sin(angle);

		q1PrevArray = q1;
		q1 = new ArrayOfVertex;
		q1->vertex = new Vertex;
		q1->prev = q1PrevArray;
		if (q1PrevArray != NULL) {
			q1PrevArray->next = q1;
		} else {
			start = q1;
			q1Start = q1;
		}
		q1->start = start;
		q1->vertex->x = xsize + xorig;
		q1->vertex->y = ysize + yorig;
	
		q2PrevArray = q2;
		q2 = new ArrayOfVertex;
		q2->vertex = new Vertex;
		q2->next = q2PrevArray;
		if (q2PrevArray != NULL) {
			q2PrevArray->prev = q2;
		} else {
			q2Start = q2;
		}
		q2->start = start;
		q2->vertex->x = xsize + xorig;
		q2->vertex->y = ysize - yorig;
	
		q3PrevArray = q3;
		q3 = new ArrayOfVertex;
		q3->vertex = new Vertex;
		q3->next = q3PrevArray;
		if (q3PrevArray != NULL) {
			q3PrevArray->prev = q3;
		} else {
			q3Start = q3;
		}
		q3->start = start;
		q3->vertex->x = xsize - xorig;
		q3->vertex->y = ysize + yorig;
	
		q4PrevArray = q4;
		q4 = new ArrayOfVertex;
		q4->vertex = new Vertex;
		q4->prev = q4PrevArray;
		if (q4PrevArray != NULL) {
			q4PrevArray->next = q4;
		} else {
			q4Start = q4;
		}
		q4->start = start;
		q4->vertex->x = xsize - xorig;
		q4->vertex->y = ysize + yorig;

	}

	q1Start->prev = q2Start;
	q2Start->next = q1Start;

	q1->next = q3;
	q3->prev = q1;

	q3Start->next = q4Start;
	q4Start->prev = q3Start;

	q4->next = q2;
	q2->prev = q4;

	passedShapesItem->ks->k->v = q1->start;
}


void createRectangle(struct ShapesItem* passedShapesItem) {
	EM_ASM({console.log("trying");});
	if (passedShapesItem->basicShapeGenerated == true) {
		return;
	}
	EM_ASM({console.log("filled rectangle 1");});
	if (passedShapesItem->p == NULL || passedShapesItem->s == NULL) {
		return;
	}
	EM_ASM({console.log("found rectangle 2");});
	passedShapesItem->basicShapeGenerated = true;

	passedShapesItem->ks = newPropertiesShape(passedShapesItem->ks);
	EM_ASM({console.log("found rectangle 3");});
	passedShapesItem->ks->k = newPropertiesShapeProp(passedShapesItem->ks, passedShapesItem->ks->k, false);
	EM_ASM({console.log("found rectangle 4");});
	//passedShapesItem->p -- position (PropertiesMultiDimensional*)
	//passedShapesItem->s -- size (PropertiesMultiDimensional*)

	float xorig = *(passedShapesItem->p->k + 0);
	float yorig = *(passedShapesItem->p->k + 1);

	float width = *(passedShapesItem->s->k + 0);
	float height = *(passedShapesItem->s->k + 1);
	if (height == 0) {
		width = height;
	}

	EM_ASM({console.log("found rectangle pre1");});
	struct ArrayOfVertex* currVertex = NULL;
	EM_ASM({console.log("found rectangle pre2");});
	currVertex = new ArrayOfVertex;
	currVertex->vertex = new Vertex;
	EM_ASM({console.log("found rectangle pre3");});
	currVertex->start = currVertex;
	EM_ASM({console.log("found rectangle pre4");});
	currVertex->vertex->x = xorig;
	EM_ASM({console.log("found rectangle pre5");});
	currVertex->vertex->y = yorig;
	EM_ASM({console.log("found rectangle 5");});

	currVertex->next = new ArrayOfVertex;
	currVertex->next->vertex = new Vertex;
	currVertex->next->start = currVertex->start;
	currVertex->next->prev = currVertex;
	currVertex = currVertex->next;
	currVertex->vertex->x = xorig + width;
	currVertex->vertex->y = yorig;
	EM_ASM({console.log("found rectangle 6");});

	currVertex->next = new ArrayOfVertex;
	currVertex->next->vertex = new Vertex;
	currVertex->next->start = currVertex->start;
	currVertex->next->prev = currVertex;
	currVertex = currVertex->next;
	currVertex->vertex->x = xorig + width;
	currVertex->vertex->y = yorig + height;
	EM_ASM({console.log("found rectangle 7");});

	currVertex->next = new ArrayOfVertex;
	currVertex->next->vertex = new Vertex;
	currVertex->next->start = currVertex->start;
	currVertex->next->prev = currVertex;
	currVertex = currVertex->next;
	currVertex->vertex->x = xorig;
	currVertex->vertex->y = yorig + height;

	currVertex->next = currVertex->start;
	currVertex->start->prev = currVertex;

	passedShapesItem->ks->k->v = currVertex->start;
	EM_ASM({console.log("found rectangle 8");});


	currVertex = new ArrayOfVertex;
	currVertex->vertex = new Vertex;
	currVertex->start = currVertex;
	currVertex->vertex->x = 0;
	currVertex->vertex->y = 0;

	currVertex->next = new ArrayOfVertex;
	currVertex->next->vertex = new Vertex;
	currVertex->next->start = currVertex->start;
	currVertex->next->prev = currVertex;
	currVertex = currVertex->next;
	currVertex->vertex->x = 0;
	currVertex->vertex->y = 0;

	currVertex->next = new ArrayOfVertex;
	currVertex->next->vertex = new Vertex;
	currVertex->next->start = currVertex->start;
	currVertex->next->prev = currVertex;
	currVertex = currVertex->next;
	currVertex->vertex->x = 0;
	currVertex->vertex->y = 0;

	currVertex->next = new ArrayOfVertex;
	currVertex->next->vertex = new Vertex;
	currVertex->next->start = currVertex->start;
	currVertex->next->prev = currVertex;
	currVertex = currVertex->next;
	currVertex->vertex->x = 0;
	currVertex->vertex->y = 0;

	currVertex->next = currVertex->start;
	currVertex->start->prev = currVertex;

	passedShapesItem->ks->k->i = currVertex->start;
	passedShapesItem->ks->k->o = currVertex->start;


	passedShapesItem->ks->k->v_count = 4;
	passedShapesItem->ks->k->i_count = 4;
	passedShapesItem->ks->k->o_count = 4;
	EM_ASM({console.log("filled rectangle");});
}

