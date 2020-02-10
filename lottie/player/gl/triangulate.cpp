struct Dimensions* findDimensions(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray) {
	struct Dimensions* passedDimensions;
	passedDimensions = new Dimensions;

	bool clockwise;
	bool directionFound = false;
	passedArray = passedArray->start;
	bool exhausted = false;
	while (! exhausted) {
		//EM_ASM({console.log("finddim 1.1");});
		GLfloat currX = passedArray->vertex->position[0];
		GLfloat currY = passedArray->vertex->position[1];
		//EM_ASM({console.log("finddim 1.2");});
		if (currX > passedDimensions->maxXval) {
			if (! directionFound) {
				if (passedDimensions->maxYval > 0) {
					clockwise = false;
					directionFound = true;
				} else if (passedDimensions->minYval > 0) {
					clockwise = true;
					directionFound = true;
				}
			}
			passedDimensions->maxXval = currX;
		}
		if (currX < passedDimensions->minXval) {
			if (! directionFound) {
				if (passedDimensions->maxYval > 0) {
					clockwise = true;
					directionFound = true;
				} else if (passedDimensions->minYval > 0) {
					clockwise = false;
					directionFound = true;
				}
			}
			passedDimensions->minXval = currX;
		}
		//EM_ASM({console.log("finddim 1.4");});
		if (currY > passedDimensions->maxYval) {
			if (! directionFound) {
				if (passedDimensions->maxXval > 0) {
					clockwise = true;
					directionFound = true;
				} else if (passedDimensions->minXval > 0) {
					clockwise = false;
					directionFound = true;
				}
			}
			passedDimensions->topVertex = passedArray;
			passedDimensions->maxYval = currY;
		}
		//EM_ASM({console.log("finddim 1.5");});
		if (currY < passedDimensions->minYval) {
			if (! directionFound) {
				if (passedDimensions->maxXval > 0) {
					clockwise = false;
					directionFound = true;
				} else if (passedDimensions->minXval > 0) {
					clockwise = true;
					directionFound = true;
				}
			}
			passedDimensions->minYval = currY;
		}
		//EM_ASM_({console.log("finddim 1.3 " + $0 + " " + $1);}, passedDimensions->maxXval, passedDimensions->maxXord);
		if (passedArray->next == NULL) {
			exhausted = true;
		} else {
			passedArray = passedArray->next;
		}
	}
	passedArray->next = passedArray->start;
	passedArray->start->prev = passedArray;
	//EM_ASM({console.log("finddim 2");});
	passedBuffers->clockwise = clockwise;
	return passedDimensions;
}


float distanceBetweenPoints(struct Vertex* pointA, struct Vertex* pointB) {
	float distance = ( sqrt(pow(((float)pointA->position[0] - (float)pointB->position[0]), 2) + pow(((float)pointA->position[1] - (float)pointB->position[1]), 2)) );
	
	//EM_ASM_({console.log("    ///////////> " + $0 + " " + $1 + " " + $2 + " " + $3 + " " + $4);}, distance, pointA->position[0], pointB->position[0], pointA->position[1], pointB->position[1]);
	return distance;
}

int convex(struct Vertex* origin, struct Vertex* next, struct Vertex* nextnext, struct Vertex* prev) {
	float a, di, ds, bi, bs;
	a = distanceBetweenPoints(origin, prev);
	di = distanceBetweenPoints(prev, next);
	ds = distanceBetweenPoints(prev, nextnext);
	bi = distanceBetweenPoints(origin, next);
	bs = distanceBetweenPoints(origin, nextnext);
	float firstAngle = ((pow(a,2) + pow(bi,2) - pow(di,2)) / (2 * a * bi));
	float secondAngle = ((pow(a,2) + pow(bs,2) - pow(ds,2)) / (2 * a * bs));
	//EM_ASM_({console.log("///////////> " + $0 + " " + $1 + " : " + $2 + " " + $3 + " " + $4 + " " + " " + $5 + " " + $6 + " --- " + $7 + " : " + $8);}, firstAngle, secondAngle, a, di, bi, ds, bs, origin->position[0], origin->position[1]);
	if ((firstAngle == 0 || isnan(firstAngle)) && (secondAngle == 0 || isnan(secondAngle))) {
		if (	
				a == 0 &&
				di == 0 &&
				bi == 0 &&
				ds == 0 &&
				bs == 0
			) {
				return 3;
		}
	}
	if (firstAngle < secondAngle) {
		return 1;
	} else {
		return 0;
	}
}

struct ArrayOfArrayOfVertex* newReserve(struct ArrayOfArrayOfVertex* tempReserve) {
	if (tempReserve == NULL) {
		tempReserve = new ArrayOfArrayOfVertex;
		tempReserve->start = tempReserve;
	} else {
		tempReserve->next = new ArrayOfArrayOfVertex;
		tempReserve->next->prev = tempReserve;
		tempReserve->next->start = tempReserve->start;
		tempReserve = tempReserve->next;
	}

	return tempReserve;
}
 
struct TriangulateReturn* prepTriangulate(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray, float* defaultFill, int order) {

	struct TriangulateReturn* tempTriangulateReturn;
	tempTriangulateReturn = new TriangulateReturn;

	/*
	struct Dimensions* dimensions;
	enum Phase phase = _maxY;
	//EM_ASM({console.log("pretri 1.1");});
	if (passedBuffers->changed || passedBuffers->dimensions == NULL) {
		//EM_ASM({console.log("pretri 1.2");});
		dimensions = findDimensions(count, passedBuffers, passedArray);
		//EM_ASM({console.log("pretri 1.3");});
		//EM_ASM({console.log("pretri 1.4");});
		passedBuffers->dimensions = dimensions;
		//EM_ASM({console.log("pretri 1.5");});
		passedBuffers->changed = false;
	} else {
		dimensions = passedBuffers->dimensions;
	}
	*/
	struct ArrayOfArrayOfVertex* reserve = NULL;
	struct ArrayOfArrayOfVertex* reserveEnd = NULL;
	//passedArray = dimensions->topVertex;
	struct ArrayOfVertex* startPoint = passedArray->start;
	struct ArrayOfVertex* lastPassedArray;
	struct ArrayOfVertex* actualStartPoint = passedArray->start;
	struct ArrayOfVertex* reservePrevArray;
	struct ArrayOfVertex* reserveNextArray;
	bool exhausted = false;
	int coreCount = count;
	int angleOne, angleTwo;
	bool outlierEncountered = false;
	//EM_ASM({console.log("pretri 2");});
	if (count > 3) {
		//EM_ASM({console.log("pretri 2.1");});
		bool entered = true;
		bool startEncountered = false;
		int cyclesAfterStartEncountered = 0;
		while (! exhausted) {
			angleOne = (convex(passedArray->vertex, passedArray->next->vertex, passedArray->next->next->vertex, passedArray->prev->vertex));
			angleTwo = (convex(passedArray->vertex, passedArray->prev->vertex, passedArray->prev->prev->vertex, passedArray->next->vertex));
			if (angleOne == 3 && angleTwo == 3) {
				if (startEncountered) {
					cyclesAfterStartEncountered++;
				}
				coreCount = coreCount - 1;
			} else {
				if (
					angleOne == 1 && angleTwo == 1
				) {
					if (startEncountered) {
						cyclesAfterStartEncountered++;
					}
				} else {
					reserve = newReserve(reserve);
					reserve->arrayItem = passedArray;
					reservePrevArray = passedArray->prev;
					while (reservePrevArray->reserved) {
						reservePrevArray = reservePrevArray->prev;
					}
					passedArray->bindPrev = reservePrevArray;
					reserveNextArray = passedArray->next;
					while (reserveNextArray->reserved) {
						reserveNextArray = reserveNextArray->next;
					}
					passedArray->bindNext = reserveNextArray;
					reservePrevArray->next = reserveNextArray;
					reserveNextArray->prev = reservePrevArray;
					if (passedArray == startPoint) {
						startPoint = reserveNextArray;
					}
					passedArray->reserved = true;
					passedArray = reserveNextArray;
					coreCount = coreCount - 1;
					//EM_ASM({console.log("outlier found");});
					outlierEncountered = true;
				}
			}
			if (startEncountered) {
				if (cyclesAfterStartEncountered > 3) {
					exhausted = true;
				} else {
					if (outlierEncountered) {
						outlierEncountered = false;
					} else {
						passedArray = passedArray->next;
					}
				}
			} else {
				if (passedArray->next == startPoint) {
					startEncountered = true;
				} else {
					if (outlierEncountered) {
						outlierEncountered = false;
					} else {
						passedArray = passedArray->next;
					}
				}
			}
		}
	} else {
		//EM_ASM({console.log("skipped " + $0);}, count);
		if (count < 3) {
			return NULL;
		}
	}
	reserveEnd = reserve;

	EM_ASM({console.log("done checking for outliers 1 " + $0);}, count);

	//if (outlierEncountered) {
		passedArray = startPoint;
	//}
	//EM_ASM({console.log("done checking for outliers 1.1 " + $0);}, count);

	GLfloat* tempVBO = new GLfloat[(count * 4)];
	//EM_ASM({console.log("done checking for outliers 1.2 " + $0);}, count);
	GLfloat* tempCBO = new GLfloat[(count * 4)];
	//EM_ASM({console.log("done checking for outliers 1.3 " + $0);}, count);
	unsigned int* tempIndex = new unsigned int[(count * 3)];
	unsigned int Bcounter = 0;
	
	EM_ASM({console.log("done checking for outliers");});
	exhausted = false;
	//int readItems = 0;
	while (! exhausted) {
		*(tempVBO + ((Bcounter * 4) + 0)) = ((2 * passedArray->vertex->position[0]) / theAnimation->w);
		*(tempVBO + ((Bcounter * 4) + 1)) = ((2 * passedArray->vertex->position[1]) / theAnimation->h) * -1;
		if (passedArray->vertex->position[2] == 0) {
			*(tempVBO + ((Bcounter * 4) + 2)) = 1 - ((float)order / 100000);
			//EM_ASM({console.log("depth ------> " + $0 + " " + $1);}, *(tempVBO + ((Bcounter * 4) + 2)), order);
		} else {
			*(tempVBO + ((Bcounter * 4) + 2)) = passedArray->vertex->position[2];
		}
		//*(tempVBO + ((Bcounter * 4) + 2)) = 1;
		*(tempVBO + ((Bcounter * 4) + 3)) = 1;

		*(tempCBO + ((Bcounter * 4) + 0)) = *(defaultFill + 0);
		*(tempCBO + ((Bcounter * 4) + 1)) = *(defaultFill + 1);
		*(tempCBO + ((Bcounter * 4) + 2)) = *(defaultFill + 2);
		*(tempCBO + ((Bcounter * 4) + 3)) = *(defaultFill + 3);
		//EM_ASM({console.log("colors ---> " + $0 + " " + $1 + " " + $2 + " " + $3);}, *(tempCBO + ((Bcounter * 4) + 0)), *(tempCBO + ((Bcounter * 4) + 1)), *(tempCBO + ((Bcounter * 4) + 2)), *(tempCBO + ((Bcounter * 4) + 3)));
		passedArray->idxOrder = Bcounter;
		if (Bcounter > 1) {
			*(tempIndex + ((Bcounter * 3) + 0)) = startPoint->idxOrder;
			*(tempIndex + ((Bcounter * 3) + 1)) = passedArray->prev->idxOrder;
			*(tempIndex + ((Bcounter * 3) + 2)) = passedArray->idxOrder;
		}
		EM_ASM_({console.log("RENDER index " + $0 + " - " + $1 + " - " + $2 + " " + $3 + ":" + $4 + " ---- " + $5 + " " + $6 + " " + $7 + " horiz: " + $8);}, *(tempIndex + ((Bcounter * 3) + 0)), *(tempIndex + ((Bcounter * 3) + 1)), *(tempIndex + ((Bcounter * 3) + 2)), *(tempVBO + ((Bcounter * 4) + 0)), *(tempVBO + ((Bcounter * 4) + 1)), startPoint->order, passedArray->prev->order, passedArray->idxOrder, passedArray->vertex->position[0]);
		Bcounter++;
		//readItems++;
		if (passedArray->next == startPoint) {
			exhausted = true;
		} else {
			passedArray = passedArray->next;
		}
	}

	if (reserve != NULL) {
		exhausted = false;
		reserve = reserveEnd;
		int BcounterReserveStart = Bcounter;
		while (! exhausted) {
			*(tempVBO + ((Bcounter * 4) + 0)) = ((2 * reserve->arrayItem->vertex->position[0]) / theAnimation->w);
			*(tempVBO + ((Bcounter * 4) + 1)) = ((2 * reserve->arrayItem->vertex->position[1]) / theAnimation->h) * -1;

			if (passedArray->vertex->position[2] == 0) {
				*(tempVBO + ((Bcounter * 4) + 2)) = 1 - ((float)order / 100000);
			} else {
				*(tempVBO + ((Bcounter * 4) + 2)) = passedArray->vertex->position[2];
			}
			//*(tempVBO + ((Bcounter * 4) + 2)) = 1;
			*(tempVBO + ((Bcounter * 4) + 3)) = 1;

			*(tempCBO + ((Bcounter * 4) + 0)) = *(defaultFill + 0);
			*(tempCBO + ((Bcounter * 4) + 1)) = *(defaultFill + 1);
			*(tempCBO + ((Bcounter * 4) + 2)) = *(defaultFill + 2);
			*(tempCBO + ((Bcounter * 4) + 3)) = *(defaultFill + 3);

			reserve->arrayItem->idxOrder = Bcounter;
			Bcounter++;
			if (reserve->prev == NULL) {
				exhausted = true;
			} else {
				reserve = reserve->prev;
			}
		}
		exhausted = false;
		reserve = reserveEnd;
		Bcounter = BcounterReserveStart;
		while (! exhausted) {
			*(tempIndex + ((Bcounter * 3) + 0)) = reserve->arrayItem->idxOrder;
			*(tempIndex + ((Bcounter * 3) + 1)) = reserve->arrayItem->bindPrev->idxOrder;
			*(tempIndex + ((Bcounter * 3) + 2)) = reserve->arrayItem->bindNext->idxOrder;
			EM_ASM_({console.log("RENDER index earcut " + $0 + " - " + $1 + " - " + $2 + " " + $3 + ":" + $4 + " " + $5);}, *(tempIndex + ((Bcounter * 3) + 0)), *(tempIndex + ((Bcounter * 3) + 1)), *(tempIndex + ((Bcounter * 3) + 2)), *(tempVBO + ((Bcounter * 4) + 0)), *(tempVBO + ((Bcounter * 4) + 1)), reserve->arrayItem->idxOrder);
			Bcounter++;
			reserve->arrayItem->next->prev = reserve->arrayItem;
			reserve->arrayItem->prev->next = reserve->arrayItem;
			reserve->arrayItem->reserved = false;
			if (reserve->prev == NULL) {
				exhausted = true;
				delete reserve;
			} else {
				reserve = reserve->prev;
				delete reserve->next;
			}
		}
	}

	passedBuffers->idxCount = Bcounter;
	EM_ASM_({console.log("--......--> index count " + $0);}, passedBuffers->idxCount);

	tempTriangulateReturn->vbo = tempVBO;
	tempTriangulateReturn->cbo = tempCBO;
	tempTriangulateReturn->index = tempIndex;
	tempTriangulateReturn->idxCount = Bcounter;

	return tempTriangulateReturn;
}

