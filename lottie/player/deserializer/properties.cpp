
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
	//EM_ASM({console.log("[[[[[[[[[[[[[========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			//EM_ASM({console.log("========================> iteration");});
		}
		if (strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}
		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "c") == 0) {
			//EM_ASM({console.log("========================> fill 80.1");});
				if (strcmp(tempKeyValue->value, "true") == 0) {
					passedPropertiesShapeProp->c = true;
				} else {
					passedPropertiesShapeProp->c = false;
				}
				//EM_ASM({console.log("========================> fill 80.1.1");});
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "i") == 0) {
			//EM_ASM({console.log("========================> fill 80.2 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->i = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->i);
			passedPropertiesShapeProp->i_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->count);

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "o") == 0) {
			//EM_ASM({console.log("========================> fill 80.3 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->o = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->o);
			passedPropertiesShapeProp->o_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->count);

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "v") == 0) {
			//EM_ASM({console.log("========================> fill 80.4 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->v = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->v);
			passedPropertiesShapeProp->v_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->count);
		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}

		return 1;
	if (passedPropertiesShapeProp->i == NULL || passedPropertiesShapeProp->o == NULL || passedPropertiesShapeProp->v == NULL) {
		return 1;
	}

	exhausted = false;

	passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->start;
	passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->start;
	passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start;
	/*
	struct PropertiesShapeProp* o1;
	struct PropertiesShapeProp* o2;
	struct PropertiesShapeProp* p1;
	struct PropertiesShapeProp* p2;
	*/
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

	while (! exhausted) {
		if ((passedPropertiesShapeProp->v->next == passedPropertiesShapeProp->v->start) && startedCycling) {
			exhausted = true;
		} else {
			if (passedPropertiesShapeProp->i->next != NULL &&
				passedPropertiesShapeProp->o->next != NULL) {
				if (passedPropertiesShapeProp->i->vertex->x == 0 && 
					passedPropertiesShapeProp->i->vertex->y == 0 &&
					passedPropertiesShapeProp->o->vertex->x == 0 &&
					passedPropertiesShapeProp->o->vertex->y == 0) {
						passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->next;
						passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->next;
						passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
						//EM_ASM({console.log("non-bezier ");});
						startedCycling = true;
						continue;
				} else {
					if (startedCycling) {
						passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->next;
						passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->next;
						passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
					} else {
						startedCycling = true;
					}
				}
			} else {
				break;
			}
			startedCycling = true;
		}
		o1 = passedPropertiesShapeProp->v->prev;
		o2 = passedPropertiesShapeProp->v;
		p1 = passedPropertiesShapeProp->o->prev;
		p2 = passedPropertiesShapeProp->i;

		op1x = p1->vertex->x - o1->vertex->x;
		op1y = p1->vertex->y - o1->vertex->y;
		op2x = p2->vertex->x - o2->vertex->x;
		op2y = p2->vertex->y - o2->vertex->y;
		oox = p2->vertex->x - p1->vertex->x;
		ooy = p2->vertex->y - p1->vertex->y;
		float segSize = 0.10;
		float segments = 1 / segSize;
		float segNow = 1;
		op1xs = op1x / segments;
		op1ys = op1y / segments;
		op2xs = op2x / segments;
		op2ys = op2y / segments;
		ooxs = oox / segments;
		ooys = ooy / segments;

		//EM_ASM_({console.log("[[[[[[[[[[[[[========================> starting " + $0 + " " + $1 + " " + $2 + " " + $3);}, o1->vertex->x, p1->vertex->x, o2->vertex->y, p2->vertex->y);
		while (segNow < segments) {
			intermediate = new ArrayOfVertex;
			intermediate->vertex = new Vertex;
			ps1->x = (op1xs * segNow) + o1->vertex->x;
			ps1->y = (op1ys * segNow) + o1->vertex->y;
			ps2->x = (ooxs * segNow) + p1->vertex->x;
			ps2->y = (ooys * segNow) + p1->vertex->y;
			ps3->x = (op2xs * segNow) + o2->vertex->x;
			ps3->y = (op2ys * segNow) + o2->vertex->y;
			
			pt1->x = (((ps2->x - ps1->x) / segments) * segNow) + ps1->x;
			pt1->y = (((ps2->y - ps1->y) / segments) * segNow) + ps1->y;
			pt2->x = (((ps3->x - ps2->x) / segments) * segNow) + ps2->x;
			pt2->y = (((ps3->y - ps2->y) / segments) * segNow) + ps2->y;

			intermediate->vertex->x = (((pt2->x - pt1->x) / segments) * segNow) + pt1->x;
			intermediate->vertex->y = (((pt2->y - pt1->y) / segments) * segNow) + pt2->y;
			//EM_ASM_({console.log("[[[[[[[[[[[[[========================> adding intermediate " + $0 + " " + $1);}, intermediate->vertex->x, intermediate->vertex->y);
			intermediate->vertex->z = 0;
			intermediate->vertex->a = 1;

			intermediate->bezier = true;

			intermediate->start = passedPropertiesShapeProp->v->start;
			
			//intermediate->prev = passedPropertiesShapeProp->v;
			//intermediate->next = passedPropertiesShapeProp->v->next;

			intermediate->prev = passedPropertiesShapeProp->v;
			intermediate->next = passedPropertiesShapeProp->v->next;

			passedPropertiesShapeProp->v->next = intermediate;
			intermediate->next->prev = intermediate;

			passedPropertiesShapeProp->v = intermediate;
			

			//EM_ASM_({console.log("[[[[[[[[[[[[[========================> adding intermediate " + $0);}, intermediate);
			segNow++;
			passedPropertiesShapeProp->v_count++;
			passedPropertiesShapeProp->bezier_count++;
		}
		
		//EM_ASM({console.log("[[[[[[[[[[[[[========================> segment added ----");});
	}

	//EM_ASM({console.log("[[[[[[[[[[[[[========================> done");});
	//deleteKeyValues(theScope->currentKeyValueTrail);

	return 1;
}

int fillPropertiesMultiDimensional(struct PropertiesMultiDimensional* passedPropertiesMultiDimensional) {
	//EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	struct FloatArrayReturn* tempFloatArray = NULL;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			//EM_ASM({console.log("========================> iteration 99");});
		}
		if (strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}

		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "k") == 0) {
			//EM_ASM({console.log("========================> found k in c");});
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

