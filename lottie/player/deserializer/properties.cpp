
struct PropertiesShape* newPropertiesShape(struct PropertiesShape* passedPropertiesShape) {
	if (passedPropertiesShape == NULL) {
		passedPropertiesShape = new PropertiesShape;
		passedPropertiesShape->start = passedPropertiesShape;
	} else {
		passedPropertiesShape->next = new PropertiesShape;
		passedPropertiesShape->next->start = passedPropertiesShape->start;
		passedPropertiesShape->next->prev = passedPropertiesShape;
		passedPropertiesShape = passedPropertiesShape->next;
	}
	passedPropertiesShape->keyframe = new PropertiesShapePropKeyframe;
	
	return passedPropertiesShape;
}

struct PropertiesShapeProp* newPropertiesShapeProp(struct PropertiesShape* passedPropertiesShape, struct PropertiesShapeProp* passedPropertiesShapeProp, bool isKeyframe) {
	if (passedPropertiesShapeProp == NULL) {
		passedPropertiesShapeProp = new PropertiesShapeProp;
		passedPropertiesShapeProp->start = passedPropertiesShapeProp;
	} else {
		passedPropertiesShapeProp->next = new PropertiesShapeProp;
		passedPropertiesShapeProp->next->start = passedPropertiesShapeProp->start;
		passedPropertiesShapeProp->next->prev = passedPropertiesShapeProp;
		passedPropertiesShapeProp = passedPropertiesShapeProp->next;
	}
	if (isKeyframe) {
		passedPropertiesShape->isKeyframe = true;
	}

	return passedPropertiesShapeProp;
}

struct PropertiesMultiDimensional* newPropertiesMultiDimensional() {
	struct PropertiesMultiDimensional* tempPropertiesMultiDimensional;
	tempPropertiesMultiDimensional = new PropertiesMultiDimensional;
	return tempPropertiesMultiDimensional;
}

struct PropertiesShapePropKeyframe* newPropertiesShapePropKeyframe() {
	struct PropertiesShapePropKeyframe* tempPropertiesShapePropKeyframe;
	tempPropertiesShapePropKeyframe = new PropertiesShapePropKeyframe;
	currentPropertiesShapePropKeyframe = tempPropertiesShapePropKeyframe;

	return tempPropertiesShapePropKeyframe;
}

//////////////////// assign values


int fillPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp) {
	EM_ASM({console.log("[[[[[[[[[[[[[========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			EM_ASM({console.log("========================> iteration");});
		}
		if (strlen(tempKeyValue->key) == 0) {
			EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}
		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "c") == 0) {
			EM_ASM({console.log("========================> fill 80.1");});
				if (strcmp(tempKeyValue->value, "true") == 0) {
					passedPropertiesShapeProp->c = true;
				} else {
					passedPropertiesShapeProp->c = false;
				}
				EM_ASM({console.log("========================> fill 80.1.1");});
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "i") == 0) {
			EM_ASM({console.log("========================> fill 80.2 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->i = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->i, passedPropertiesShapeProp);
			passedPropertiesShapeProp->i_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->count);

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "o") == 0) {
			EM_ASM({console.log("========================> fill 80.3 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->o = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->o, passedPropertiesShapeProp);
			passedPropertiesShapeProp->o_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->count);

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "v") == 0) {
			EM_ASM({console.log("========================> fill 80.4 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->v = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->v, passedPropertiesShapeProp);
			passedPropertiesShapeProp->v_count = currentUniversalCount;


	
			bool subExhausted = false;
			passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start;
			/*
			while (! subExhausted) {
				EM_ASM_({console.log("**** associating values " + $0 + " " + $1 + " " + $2 + " " + $3);}, passedPropertiesShapeProp->v->vertex->x, passedPropertiesShapeProp->v->vertex->y, passedPropertiesShapeProp->lowestX, passedPropertiesShapeProp->lowestY);
				if (passedPropertiesShapeProp->v->next == passedPropertiesShapeProp->v->start) {
					subExhausted = true;
				} else {
					passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
				}
			}
			*/
			/*
			bool subExhausted = false;
			passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start;
			while (! subExhausted) {
				if (passedPropertiesShapeProp->v->vertex->x < passedPropertiesShapeProp->lowestX) {
					passedPropertiesShapeProp->lowestX = passedPropertiesShapeProp->v->vertex->x;
				}
				if (passedPropertiesShapeProp->v->vertex->y < passedPropertiesShapeProp->lowestY) {
					passedPropertiesShapeProp->lowestY = passedPropertiesShapeProp->v->vertex->y;
				}
				EM_ASM_({console.log("**** associating values " + $0 + " " + $1 + " " + $2 + " " + $3);}, passedPropertiesShapeProp->v->vertex->x, passedPropertiesShapeProp->v->vertex->y, passedPropertiesShapeProp->lowestX, passedPropertiesShapeProp->lowestY);
				if (passedPropertiesShapeProp->v->next == passedPropertiesShapeProp->v->start) {
					subExhausted = true;
				} else {
					passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
				}
			}
			*/
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->count);
		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}

	//	return 1;
	if (passedPropertiesShapeProp->i == NULL || passedPropertiesShapeProp->o == NULL || passedPropertiesShapeProp->v == NULL) {
		return 1;
	}

	exhausted = false;

	//passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->start->prev;
	//passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->start->prev;
	//passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start->prev;
	passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->start;
	passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->start;
	passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start;
	/*
	struct PropertiesShapeProp* o1;
	struct PropertiesShapeProp* o2;
	struct PropertiesShapeProp* p1;
	struct PropertiesShapeProp* p2;
	*/

	int xoff = 0;
	int yoff = 0;
	if (passedPropertiesShapeProp->lowestX < 0) {
		xoff = passedPropertiesShapeProp->lowestX * -1;
	}
	if (passedPropertiesShapeProp->lowestY < 0) {
		yoff = passedPropertiesShapeProp->lowestY * -1;
	}
	EM_ASM({console.log("===***===> offsets " + $0 + " " + $1);}, xoff, yoff);
	struct ArrayOfVertex *o1, *o2, *p1, *p2;
	float op1y, op1x, op2y, op2x;
	float op1ys, op1xs, op2ys, op2xs;
	float d1x, d1y, d2x, d2y, ooy, oox;
	float d1xs, d1ys, d2xs, d2ys, ooys, ooxs;

	struct Vertex *ps1, *ps2, *ps3, *pt1, *pt2;
	struct ArrayOfVertex* intermediate;
	ps1 = new Vertex;
	ps2 = new Vertex;
	ps3 = new Vertex;
	pt1 = new Vertex;
	pt2 = new Vertex;
	bool startedCycling = false;

	//struct ArrayOfVertex* nextVertex = NULL;
	struct ArrayOfVertex* lastIntermediate = NULL;

	float oneTcube, oneTsquare, Tcube, Tsquare, oneT;

	while (! exhausted) {
		if (		
				(
					//passedPropertiesShapeProp->v->next == passedPropertiesShapeProp->v->start ||
					passedPropertiesShapeProp->v == passedPropertiesShapeProp->v->start
				)
				&& startedCycling == true
			) {
			//passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->next;
			//passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->next;
			//if (nextVertex != NULL) {
			//	passedPropertiesShapeProp->v = nextVertex;
			//} else {
			//	passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
			//}
			break;
			exhausted = true;
			continue;
		} else {
				if (
						(
							passedPropertiesShapeProp->i->vertex->x == 0 && 
							passedPropertiesShapeProp->i->vertex->y == 0 &&
							passedPropertiesShapeProp->o->vertex->x == 0 &&
							passedPropertiesShapeProp->o->vertex->y == 0
						) &&
						(
							passedPropertiesShapeProp->i->prev->vertex->x == 0 && 
							passedPropertiesShapeProp->i->prev->vertex->y == 0 &&
							passedPropertiesShapeProp->o->prev->vertex->x == 0 &&
							passedPropertiesShapeProp->o->prev->vertex->y == 0
						)
					) {
						passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->next;
						passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->next;
						passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
						EM_ASM({console.log("non-bezier ");});
						startedCycling = true;
						continue;
				} else {
					passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->next;
					passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->next;
					passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
					EM_ASM({console.log("breakout ");});
				}

		}
		startedCycling = true;
		o1 = passedPropertiesShapeProp->v->prev;
		o2 = passedPropertiesShapeProp->v;
		p1 = passedPropertiesShapeProp->o->prev;
		p2 = passedPropertiesShapeProp->i;
		//nextVertex = passedPropertiesShapeProp->v;

		EM_ASM_({console.log("[[[[[[[[[[[[[========================> starting " + $0 + " , " + $1 + " : " + $2 + " , " + $3 + " : " + $4 + " , " + $5 + " : " + $6 + " , " + $7);}, o1->vertex->x, o1->vertex->y, p1->vertex->x, p1->vertex->y, o2->vertex->x, o2->vertex->y, p2->vertex->x, p2->vertex->y);

		/*
		o1->vertex->x = o1->vertex->x + xoff;
		o1->vertex->y = o1->vertex->y + yoff;
		o2->vertex->x = o2->vertex->x + xoff;
		o2->vertex->y = o2->vertex->y + yoff;
		p1->vertex->x = p1->vertex->x + xoff;
		p1->vertex->y = p1->vertex->y + yoff;
		p2->vertex->x = p2->vertex->x + xoff;
		p2->vertex->y = p2->vertex->y + yoff;
		*/

		/*
		float odist = distanceBetweenPoints(o1->vertex, o2->vertex) / 2;
		if (odist < 0) {
			odist = odist * -1;
		}

		if (p1->vertex->x > odist) {
			
		}
		*/

		float segSize = 0.10;
		float segments = 1 / segSize;
		//float segNow = segSize;
		float segNow = segSize;

		while (segNow < 1) {
			intermediate = new ArrayOfVertex;
			intermediate->vertex = new Vertex;
			
			//intermediate->vertex->x = ( (((pt2->x - pt1->x) / segments) * segNow) + pt1->x );
			//intermediate->vertex->y = ( (((pt2->y - pt1->y) / segments) * segNow) + pt1->y );

			oneT = 1 - segNow;
			Tcube = pow(segNow, 3);
			Tsquare = pow(segNow, 2);
			oneTcube = pow(oneT, 3);
			oneTsquare = pow(oneT, 2);

			intermediate->vertex->x = (oneTcube * o1->vertex->x) + (3 * oneTsquare * segNow * p1->vertex->x) + (3 * oneT * Tsquare * p2->vertex->x) + (Tcube * o2->vertex->x);
			intermediate->vertex->y = (oneTcube * o1->vertex->y) + (3 * oneTsquare * segNow * p1->vertex->y) + (3 * oneT * Tsquare * p2->vertex->y) + (Tcube * o2->vertex->y);
			EM_ASM_({console.log("[[[[[[[[[[[[[========================> adding intermediate " + $0 + " " + $1);}, intermediate->vertex->x, intermediate->vertex->y);
			intermediate->vertex->z = 0;
			intermediate->vertex->a = 1;

			intermediate->bezier = true;

			intermediate->start = passedPropertiesShapeProp->v->start;
			if (lastIntermediate == NULL) {
				intermediate->prev = passedPropertiesShapeProp->v->prev;
				passedPropertiesShapeProp->v->prev->next = intermediate;
				passedPropertiesShapeProp->v->prev = intermediate;
			} else {
				intermediate->prev = lastIntermediate;
				lastIntermediate->next = intermediate;
				passedPropertiesShapeProp->v->prev = intermediate;
			}
			intermediate->next = passedPropertiesShapeProp->v;
			lastIntermediate = intermediate;

			//passedPropertiesShapeProp->v = intermediate;
			segNow = segNow + segSize;
			passedPropertiesShapeProp->v_count++;
			passedPropertiesShapeProp->bezier_count++;
		}

		/*
		op1x = p1->vertex->x - o1->vertex->x;
		op1y = p1->vertex->y - o1->vertex->y;
		op2x = p2->vertex->x - o2->vertex->x;
		op2y = p2->vertex->y - o2->vertex->y;
		oox = p2->vertex->x - p1->vertex->x;
		ooy = p2->vertex->y - p1->vertex->y;

		op1xs = op1x / segments;
		op1ys = op1y / segments;
		op2xs = op2x / segments;
		op2ys = op2y / segments;
		ooxs = oox / segments;
		ooys = ooy / segments;

		while (segNow < segments) {
			intermediate = new ArrayOfVertex;
			intermediate->vertex = new Vertex;
			ps1->x = (op1xs * segNow) + o1->vertex->x;
			ps1->y = (op1ys * segNow) + o1->vertex->y;
			ps2->x = (ooxs * segNow) + o2->vertex->x;
			ps2->y = (ooys * segNow) + o2->vertex->y;
			ps3->x = (op2xs * segNow) + p1->vertex->x;
			ps3->y = (op2ys * segNow) + p1->vertex->y;

			pt1->x = ( ((ps2->x - ps1->x) / segments) * segNow) + ps1->x;
			pt1->y = ( ((ps2->y - ps1->y) / segments) * segNow) + ps1->y;
			pt2->x = ( ((ps3->x - ps2->x) / segments) * segNow) + ps2->x;
			pt2->y = ( ((ps3->y - ps2->y) / segments) * segNow) + ps2->y;

			//intermediate->vertex->x = ( (((pt2->x - pt1->x) / segments) * segNow) + pt1->x ) - xoff;
			//intermediate->vertex->y = ( (((pt2->y - pt1->y) / segments) * segNow) + pt1->y ) - yoff;
			intermediate->vertex->x = ( (((pt2->x - pt1->x) / segments) * segNow) + pt1->x );
			intermediate->vertex->y = ( (((pt2->y - pt1->y) / segments) * segNow) + pt1->y );
			EM_ASM_({console.log("[[[[[[[[[[[[[========================> adding intermediate " + $0 + " " + $1);}, intermediate->vertex->x, intermediate->vertex->y);
			intermediate->vertex->z = 0;
			intermediate->vertex->a = 1;

			intermediate->bezier = true;

			intermediate->start = passedPropertiesShapeProp->v->start;
			if (lastIntermediate == NULL) {
				intermediate->prev = passedPropertiesShapeProp->v->prev;
				passedPropertiesShapeProp->v->prev->next = intermediate;
				passedPropertiesShapeProp->v->prev = intermediate;
			} else {
				intermediate->prev = lastIntermediate;
				lastIntermediate->next = intermediate;
				passedPropertiesShapeProp->v->prev = intermediate;
			}
			intermediate->next = passedPropertiesShapeProp->v;
			lastIntermediate = intermediate;

			//passedPropertiesShapeProp->v = intermediate;

			//EM_ASM_({console.log("[[[[[[[[[[[[[========================> adding intermediate " + $0);}, intermediate);
			segNow++;
			passedPropertiesShapeProp->v_count++;
			passedPropertiesShapeProp->bezier_count++;
		}
		*/


		//EM_ASM({console.log("[[[[[[[[[[[[[========================> segment added ----");});
	}

	/*
	exhausted = false;
	passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start;
	while (! exhausted) {
		EM_ASM({console.log("[[[[[[[[[========> vertices " + $0 + " " + $1);}, passedPropertiesShapeProp->v->vertex->x, passedPropertiesShapeProp->v->vertex->y);
		if (passedPropertiesShapeProp->v->next == passedPropertiesShapeProp->v->start) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;	
		}
	}
	*/

	EM_ASM({console.log("[[[[[[[[[[[[[========================> done");});
	//deleteKeyValues(theScope->currentKeyValueTrail);

	return 1;
}

int fillPropertiesMultiDimensional(struct PropertiesMultiDimensional* passedPropertiesMultiDimensional) {
	EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	struct FloatArrayReturn* tempFloatArray = NULL;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			EM_ASM({console.log("========================> iteration 99");});
		}
		if (strlen(tempKeyValue->key) == 0) {
			EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}

		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "k") == 0) {
			EM_ASM({console.log("========================> found k in c");});
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			passedPropertiesMultiDimensional->k = tempFloatArray->floatArray;
			passedPropertiesMultiDimensional->k_count = tempFloatArray->count;
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ti") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, false);
			passedPropertiesMultiDimensional->ti = tempFloatArray->floatArray;
			passedPropertiesMultiDimensional->ti_count = tempFloatArray->count;
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "to") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, false);
			passedPropertiesMultiDimensional->to = tempFloatArray->floatArray;
			passedPropertiesMultiDimensional->to_count = tempFloatArray->count;
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "a") == 0) {
			passedPropertiesMultiDimensional->a = stringToInt(tempKeyValue->value);
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "e") == 0) {
			if (passedPropertiesMultiDimensional->keyframe == NULL) {
				passedPropertiesMultiDimensional->keyframe = new PropertiesMultiDimensionalKeyframe;
			}
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			passedPropertiesMultiDimensional->keyframe->e = tempFloatArray->floatArray;
			passedPropertiesMultiDimensional->keyframe->e_count = tempFloatArray->count;
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "s") == 0) {
			if (passedPropertiesMultiDimensional->keyframe == NULL) {
				passedPropertiesMultiDimensional->keyframe = new PropertiesMultiDimensionalKeyframe;
			}
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			passedPropertiesMultiDimensional->keyframe->s = tempFloatArray->floatArray;
			passedPropertiesMultiDimensional->keyframe->s_count = tempFloatArray->count;
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "x") == 0) {
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ix") == 0) {
		}
		

		if (tempFloatArray != NULL) {
			delete tempFloatArray;
			tempFloatArray = NULL;
		}

		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}
	return 1;
}

void createEllipse(struct ShapesItem* passedShapesItem) {
	return;
	if (passedShapesItem->basicShapeGenerated == true) {
		return;
	}
	if (passedShapesItem->p == NULL || passedShapesItem->s == NULL) {
		EM_ASM({console.log("===&&&&&&&&&&===> no multidim object");});
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
		angle = angleDelta * i;
		radius = xy / ( (xx * pow(sin(angle), 2)) + (yy * pow(cos(angle),2)) );

		xsize = radius * cos(angle);
		ysize = radius * sin(angle);

		q1PrevArray = q1;
		q1 = new ArrayOfVertex;
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

