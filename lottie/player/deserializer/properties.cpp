
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
	cout << "--- 1 \n";
	//if (passedPropertiesShapeProp == NULL) {
		cout << "--- 2 \n";
		passedPropertiesShapeProp = new PropertiesShapeProp;
		cout << "--- 3 \n";
		passedPropertiesShapeProp->start = passedPropertiesShapeProp;
	/*} else {
		cout << "--- 4 \n";
		passedPropertiesShapeProp->next = new PropertiesShapeProp;
		cout << "--- 5 \n";
		passedPropertiesShapeProp->next->start = passedPropertiesShapeProp->start;
		cout << "--- 6 \n";
		passedPropertiesShapeProp->next->prev = passedPropertiesShapeProp;
		cout << "--- 7 \n";
		passedPropertiesShapeProp = passedPropertiesShapeProp->next;
	}*/
	if (isKeyframe && passedPropertiesShape != NULL) {
		cout << "--- 8 \n";
		passedPropertiesShape->isKeyframe = true;
	}

		cout << "--- 9 \n";
	return passedPropertiesShapeProp;
}

struct PropertiesMultiDimensional* newPropertiesMultiDimensional() {
	currentPropertiesOffsetKeyframe = NULL;
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

struct PropertiesValue* newPropertiesValue() {
	currentPropertiesValueKeyframe = NULL;
	struct PropertiesValue* tempPropertiesValue;
	tempPropertiesValue = new PropertiesValue;
	return tempPropertiesValue;
}

struct PropertiesOffsetKeyframe* newPropertiesOffsetKeyframe() {
	//struct PropertiesOffsetKeyframe* tempPropertiesOffsetKeyframe;
	if (currentPropertiesOffsetKeyframe == NULL) {
		currentPropertiesOffsetKeyframe = new PropertiesOffsetKeyframe;
		currentPropertiesOffsetKeyframe->start = currentPropertiesOffsetKeyframe;
	} else {
		currentPropertiesOffsetKeyframe->next = new PropertiesOffsetKeyframe;
		currentPropertiesOffsetKeyframe->next->start = currentPropertiesOffsetKeyframe->start;
		currentPropertiesOffsetKeyframe->next->prev = currentPropertiesOffsetKeyframe;
		currentPropertiesOffsetKeyframe = currentPropertiesOffsetKeyframe->next;
	}
	return currentPropertiesOffsetKeyframe;
}

struct PropertiesValueKeyframe* newPropertiesValueKeyframe() {
	//struct PropertiesValueKeyframe* tempPropertiesValueKeyframe;
	if (currentPropertiesValueKeyframe == NULL) {
		currentPropertiesValueKeyframe = new PropertiesValueKeyframe;
		currentPropertiesValueKeyframe->start = currentPropertiesValueKeyframe;
	} else {
		currentPropertiesValueKeyframe->next = new PropertiesValueKeyframe;
		currentPropertiesValueKeyframe->next->start = currentPropertiesValueKeyframe->start;
		currentPropertiesValueKeyframe->next->prev = currentPropertiesValueKeyframe;
		currentPropertiesValueKeyframe = currentPropertiesValueKeyframe->next;
	}
	return currentPropertiesValueKeyframe;
}

struct BezierCurve* newBezierCurve() {
	struct BezierCurve* tempBezierCurve;
	tempBezierCurve = new BezierCurve;
	return tempBezierCurve;
}

//////////////////// assign values


int fillPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp) {
	//EM_ASM({console.log("[[[[[[[[[[[[[========================> entered");});
	#ifdef EMT
	#else
		cout << "fillshapeprop 1 \n";
	#endif
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	#ifdef EMT
	#else
		cout << "fillshapeprop 2 \n";
	#endif
	while (! exhausted) {
		if (tempKeyValue) {
			//EM_ASM({console.log("========================> iteration");});
		}
		#ifdef EMT
		#else
			cout << "fillshapeprop 3 \n";
		#endif
		if (strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}
		#ifdef EMT
		#else
			cout << "fillshapeprop 4 \n";
		#endif
		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "c") == 0) {
			#ifdef EMT
			#else
				cout << "fillshapeprop 4.1 \n";
			#endif
			//EM_ASM({console.log("========================> fill 80.1");});
				if (strcmp(tempKeyValue->value, "true") == 0) {
					passedPropertiesShapeProp->c = true;
				} else {
					passedPropertiesShapeProp->c = false;
				}
				//EM_ASM({console.log("========================> fill 80.1.1");});
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "i") == 0) {
			#ifdef EMT
			#else
				cout << "fillshapeprop 4.2 \n";
			#endif
			//EM_ASM({console.log("========================> fill 80.2 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->i = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->i, passedPropertiesShapeProp);
			passedPropertiesShapeProp->i_count = currentUniversalCount;

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "o") == 0) {
			#ifdef EMT
			#else
				cout << "fillshapeprop 4.3 \n";
			#endif
			//EM_ASM({console.log("========================> fill 80.3 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->o = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->o, passedPropertiesShapeProp);
			passedPropertiesShapeProp->o_count = currentUniversalCount;

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "v") == 0) {
			#ifdef EMT
			#else
				cout << "fillshapeprop 4.4 \n";
			#endif
			//EM_ASM({console.log("========================> fill 80.4 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->v = 
				populateVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->v, passedPropertiesShapeProp);
			passedPropertiesShapeProp->v_count = currentUniversalCount;


	
			bool subExhausted = false;
			if (passedPropertiesShapeProp->v != NULL) {
				passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start;
			}
			/*
			while (! subExhausted) {
				//EM_ASM_({console.log("**** associating values " + $0 + " " + $1 + " " + $2 + " " + $3);}, passedPropertiesShapeProp->v->vertex->x, passedPropertiesShapeProp->v->vertex->y, passedPropertiesShapeProp->lowestX, passedPropertiesShapeProp->lowestY);
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
				//EM_ASM_({console.log("**** associating values " + $0 + " " + $1 + " " + $2 + " " + $3);}, passedPropertiesShapeProp->v->vertex->x, passedPropertiesShapeProp->v->vertex->y, passedPropertiesShapeProp->lowestX, passedPropertiesShapeProp->lowestY);
				if (passedPropertiesShapeProp->v->next == passedPropertiesShapeProp->v->start) {
					subExhausted = true;
				} else {
					passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
				}
			}
			*/
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->count);
		}

		#ifdef EMT
		#else
			cout << "fillshapeprop 5 \n";
		#endif


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

//void bezierSegment(struct ArrayOfVertex* v, struct ArrayOfVertex* i, struct ArrayOfVertex* o, int* v_count, int* bezier_count, float* segSizePassed, bool fillNulls, bool isGeometry, bool autoSegSize) {
			//passedPropertiesShapeProp->v_count++;
			//passedPropertiesShapeProp->bezier_count++;
	float segSize = 0.1;
	bezierSegment(passedPropertiesShapeProp->v, passedPropertiesShapeProp->i, passedPropertiesShapeProp->o, &(passedPropertiesShapeProp->v_count), &(passedPropertiesShapeProp->bezier_count), &segSize, false, true, true, 3, false);
	return 1;

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
	struct ArrayOfVertex *o1, *o2, *p1, *p2;

	/*
	int xoff = 0;
	int yoff = 0;
	if (passedPropertiesShapeProp->lowestX < 0) {
		xoff = passedPropertiesShapeProp->lowestX * -1;
	}
	if (passedPropertiesShapeProp->lowestY < 0) {
		yoff = passedPropertiesShapeProp->lowestY * -1;
	}
	//EM_ASM({console.log("===***===> offsets " + $0 + " " + $1);}, xoff, yoff);
	float op1y, op1x, op2y, op2x;
	float op1ys, op1xs, op2ys, op2xs;
	float d1x, d1y, d2x, d2y, ooy, oox;
	float d1xs, d1ys, d2xs, d2ys, ooys, ooxs;

	struct Vertex *ps1, *ps2, *ps3, *pt1, *pt2;
	ps1 = new Vertex;
	ps2 = new Vertex;
	ps3 = new Vertex;
	pt1 = new Vertex;
	pt2 = new Vertex;
	*/

	bool startedCycling = false;
	struct ArrayOfVertex* startPoint = passedPropertiesShapeProp->v->start;
	//struct ArrayOfVertex* nextVertex = NULL;
	struct ArrayOfVertex* lastIntermediate = NULL;
	struct ArrayOfVertex* intermediate = NULL;
	struct ArrayOfVertex* intermediateStart = NULL;

	float oneTcube, oneTsquare, Tcube, Tsquare, oneT;

	while (! exhausted) {
		if (passedPropertiesShapeProp->v == startPoint && startedCycling == true) {
						break;
			//continue;
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
						break;
				} else {
					passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->next;
					passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->next;
					passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
					//EM_ASM({console.log("breakout ");});
					exhausted = true;
				}
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
						if (passedPropertiesShapeProp->v == startPoint && startedCycling == true) {
							break;
						}
						//EM_ASM({console.log("non-bezier ");});
						startedCycling = true;
						continue;
				} else {
					passedPropertiesShapeProp->i = passedPropertiesShapeProp->i->next;
					passedPropertiesShapeProp->o = passedPropertiesShapeProp->o->next;
					passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;
					//EM_ASM({console.log("breakout ");});
				}

		}
		startedCycling = true;
		o1 = passedPropertiesShapeProp->v->prev;
		o2 = passedPropertiesShapeProp->v;
		p1 = passedPropertiesShapeProp->o->prev;
		p2 = passedPropertiesShapeProp->i;

		//float segSize = 0.10;
		float segments = 1 / segSize;
		//float segNow = segSize;
		float segNow = segSize;

		float p1x = p1->vertex->x + o1->vertex->x;
		float p2x = p2->vertex->x + o2->vertex->x;
		float p1y = p1->vertex->y + o1->vertex->y;
		float p2y = p2->vertex->y + o2->vertex->y;

		intermediateStart = NULL;
		lastIntermediate = NULL;
		while (segNow < 1) {
			intermediate = new ArrayOfVertex;
			intermediate->vertex = new Vertex;
			intermediate->start = o1->start;

			//intermediate->vertex->x = ( (((pt2->x - pt1->x) / segments) * segNow) + pt1->x );
			//intermediate->vertex->y = ( (((pt2->y - pt1->y) / segments) * segNow) + pt1->y );

			oneT = 1 - segNow;
			Tcube = pow(segNow, 3);
			Tsquare = pow(segNow, 2);
			oneTcube = pow(oneT, 3);
			oneTsquare = pow(oneT, 2);

			intermediate->vertex->x = 	(oneTcube * 			o1->vertex->x) + 
							(3 * oneTsquare * segNow * 	p1x) + 
							(3 * oneT * Tsquare * 		p2x) + 
							(Tcube * 			o2->vertex->x);

			intermediate->vertex->y = 	(oneTcube * 			o1->vertex->y) + 
							(3 * oneTsquare * segNow * 	p1y) + 
							(3 * oneT * Tsquare * 		p2y) + 
							(Tcube * 			o2->vertex->y);
			//EM_ASM_({console.log("[[[[[[[[[[[[[========================> adding intermediate " + $0 + " " + $1);}, intermediate->vertex->x, intermediate->vertex->y);
			intermediate->vertex->z = 0;
			intermediate->vertex->a = 1;

			intermediate->bezier = true;

			
			if (lastIntermediate != NULL) {
				lastIntermediate->next = intermediate;
				intermediate->prev = lastIntermediate;
			}
			lastIntermediate = intermediate;

			//passedPropertiesShapeProp->v = intermediate;
			segNow = segNow + segSize;
			passedPropertiesShapeProp->v_count++;
			passedPropertiesShapeProp->bezier_count++;
			if (intermediateStart == NULL) {
				intermediateStart = intermediate;
			}
		}
		if (intermediateStart != NULL) {
			intermediateStart->prev = o1;
			o1->next = intermediateStart;
			intermediate->next = o2;
			o2->prev = intermediate;
		}


		//EM_ASM({console.log("[[[[[[[[[[[[[========================> segment added ----");});
	}


	/*
	exhausted = false;
	passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->start;
	while (! exhausted) {
		//EM_ASM({console.log("[[[[[[[[[========> vertices " + $0 + " " + $1);}, passedPropertiesShapeProp->v->vertex->x, passedPropertiesShapeProp->v->vertex->y);
		if (passedPropertiesShapeProp->v->next == passedPropertiesShapeProp->v->start) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp->v = passedPropertiesShapeProp->v->next;	
		}
	}
	*/

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
	//EM_ASM({console.log("========================> entered");});
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
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesMultiDimensional->k = tempFloatArray->floatArray;
				passedPropertiesMultiDimensional->k_count = tempFloatArray->count;
				//EM_ASM_({console.log("========================> found k " + $0 + " " + $1);}, passedPropertiesMultiDimensional->k[0], passedPropertiesMultiDimensional->k[1]);
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ti") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, false);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesMultiDimensional->ti = tempFloatArray->floatArray;
				passedPropertiesMultiDimensional->ti_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "to") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, false);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesMultiDimensional->to = tempFloatArray->floatArray;
				passedPropertiesMultiDimensional->to_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "a") == 0) {
			passedPropertiesMultiDimensional->a = stringToInt(tempKeyValue->value);
		/*
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "e") == 0) {
			if (passedPropertiesMultiDimensional->keyframe == NULL) {
				passedPropertiesMultiDimensional->keyframe = new PropertiesMultiDimensionalKeyframe;
			}
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesMultiDimensional->keyframe->e = tempFloatArray->floatArray;
				passedPropertiesMultiDimensional->keyframe->e_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "s") == 0) {
			if (passedPropertiesMultiDimensional->keyframe == NULL) {
				passedPropertiesMultiDimensional->keyframe = new PropertiesMultiDimensionalKeyframe;
			}
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesMultiDimensional->keyframe->s = tempFloatArray->floatArray;
				passedPropertiesMultiDimensional->keyframe->s_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "x") == 0) {
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ix") == 0) {
		*/
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
	//EM_ASM({console.log("========================> entered ii");});
	return 1;
}

int fillPropertiesValue(struct PropertiesValue* passedPropertiesValue) {
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
			if (strlen(tempKeyValue->value) > 0) {
				passedPropertiesValue->k = populateFloat(tempKeyValue->value);
			}
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

int fillPropertiesOffsetKeyframe(struct PropertiesOffsetKeyframe* passedPropertiesOffsetKeyframe) {
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	struct FloatArrayReturn* tempFloatArray = NULL;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue != NULL) {
			//EM_ASM({console.log("========================> OffsetKeyframe " + String.fromCharCode($0));}, tempKeyValue->value[0]);
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

		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "s") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesOffsetKeyframe->s = tempFloatArray->floatArray;
				passedPropertiesOffsetKeyframe->s_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "t") == 0) {
			if (strlen(tempKeyValue->value) > 0) {
				passedPropertiesOffsetKeyframe->t = populateFloat(tempKeyValue->value);
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ti") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesOffsetKeyframe->ti = tempFloatArray->floatArray;
				passedPropertiesOffsetKeyframe->ti_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "to") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesOffsetKeyframe->to = tempFloatArray->floatArray;
				passedPropertiesOffsetKeyframe->to_count = tempFloatArray->count;
			}
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

int fillPropertiesValueKeyframe(struct PropertiesValueKeyframe* passedPropertiesValueKeyframe) {
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	struct FloatArrayReturn* tempFloatArray = NULL;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue != NULL) {
			//EM_ASM({console.log("========================> OffsetKeyframe " + String.fromCharCode($0));}, tempKeyValue->value[0]);
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

		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "s") == 0) {
			//*(passedPropertiesValueKeyframe->s + 0) = stringToFloat(tempKeyValue->value);
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesValueKeyframe->s = tempFloatArray->floatArray;
				passedPropertiesValueKeyframe->s_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "t") == 0) {
			if (strlen(tempKeyValue->value) > 0) {
				passedPropertiesValueKeyframe->t = populateFloat(tempKeyValue->value);
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "ti") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesValueKeyframe->ti = tempFloatArray->floatArray;
				passedPropertiesValueKeyframe->ti_count = tempFloatArray->count;
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "to") == 0) {
			tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, true);
			if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
				passedPropertiesValueKeyframe->to = tempFloatArray->floatArray;
				passedPropertiesValueKeyframe->to_count = tempFloatArray->count;
			}
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

int fillBezierCurve(struct BezierCurve* passedBezierCurve) {
	if (passedBezierCurve == NULL) {
		passedBezierCurve = new BezierCurve;
	}
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

		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "x") == 0) {
			if (tempKeyValue->arrayValue != NULL) {
				tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, false);
				if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
					passedBezierCurve->x = tempFloatArray->floatArray;
				}
			} else if (strlen(tempKeyValue->value) > 0) {
				passedBezierCurve->x = new float[1];
				*(passedBezierCurve->x + 0) = populateFloat(tempKeyValue->value);
			}
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "y") == 0) {
			if (tempKeyValue->arrayValue != NULL) {
				tempFloatArray = populateFloatArray(tempKeyValue->arrayValue, false);
				if (tempFloatArray != NULL && tempFloatArray->floatArray != NULL) {
					passedBezierCurve->y = tempFloatArray->floatArray;
				}
			} else if (strlen(tempKeyValue->value) > 0) {
				passedBezierCurve->y = new float[1];
				*(passedBezierCurve->y + 0) = populateFloat(tempKeyValue->value);
			}
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

