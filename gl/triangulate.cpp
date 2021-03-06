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

struct Dimensions* findDimensions(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray) {
	struct Dimensions* passedDimensions;
	passedDimensions = new Dimensions;

	bool clockwise;
	bool directionFound = false;
	passedArray = passedArray->start;
	bool exhausted = false;
	while (! exhausted) {
		//EM_ASM({console.log("finddim 1.1");});
		GLfloat currX = passedArray->vertex->x;
		GLfloat currY = passedArray->vertex->y;
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

/*
float distanceBetweenPoints(struct Vertex* pointA, struct Vertex* pointB) {
	float distance = ( sqrt(pow(((float)pointA->x - (float)pointB->x), 2) + pow(((float)pointA->y - (float)pointB->y), 2)) );
	
	//EM_ASM_({console.log("    ///////////> " + $0 + " " + $1 + " " + $2 + " " + $3 + " " + $4);}, distance, pointA->x, pointB->x, pointA->y, pointB->y);
	return distance;
}
*/

int convex(struct Vertex* origin, struct Vertex* next, struct Vertex* nextnext, struct Vertex* prev) {
	float a, di, ds, bi, bs;
	a = distanceBetweenPoints(origin, prev);
	di = distanceBetweenPoints(prev, next);
	ds = distanceBetweenPoints(prev, nextnext);
	bi = distanceBetweenPoints(origin, next);
	bs = distanceBetweenPoints(origin, nextnext);
	float firstAngle = ((pow(a,2) + pow(bi,2) - pow(di,2)) / (2 * a * bi));
	float secondAngle = ((pow(a,2) + pow(bs,2) - pow(ds,2)) / (2 * a * bs));
	//EM_ASM_({console.log("///////////> " + $0 + " " + $1 + " : " + $2 + " " + $3 + " " + $4 + " " + " " + $5 + " " + $6 + " --- " + $7 + " : " + $8);}, firstAngle, secondAngle, a, di, bi, ds, bs, origin->x, origin->y);
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
 
void prepTriangulate(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray, float* defaultFill, int order, struct PropertiesShapeProp* passedProp, struct BoundingBox* currentBB, struct BoundingBox* currentShapesBB) {
//struct TriangulateReturn* prepTriangulate(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray, float* defaultFill, int order, struct PropertiesShapeProp* passedProp) {

	//struct TriangulateReturn* tempTriangulateReturn;
	//tempTriangulateReturn = new TriangulateReturn;

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
	if (count <= 2) {
		return;
	}
	struct ArrayOfArrayOfVertex* reserve = NULL;
	struct ArrayOfArrayOfVertex* reserveEnd = NULL;
	//passedArray = dimensions->topVertex;
	struct ArrayOfVertex* startPoint = passedArray->start;
	struct ArrayOfVertex* lastPassedArray;
	struct ArrayOfVertex* actualStartPoint = passedArray->start;
	struct ArrayOfVertex* reservePrevArray;
	struct ArrayOfVertex* reserveNextArray;
	passedArray = startPoint;
	//passedArray = passedArray->start->prev->prev;
	bool exhausted = false;
	int coreCount = count;
	int angleOne, angleTwo;
	bool outlierEncountered = false;
	bool startPointNextEncountered = false;
	int outlierCount = 0;
	//EM_ASM({console.log("pretri 2 " + $0);}, count);
	if (count > 2) {
		bool entered = true;
		bool startEncountered = false;
		int cyclesAfterStartEncountered = 0;
		
		while (! exhausted) {
			outlierEncountered = false;
			if (! passedArray->reserved) {
				angleOne = (convex(passedArray->vertex, passedArray->next->vertex, passedArray->next->next->vertex, passedArray->prev->vertex));
				angleTwo = (convex(passedArray->vertex, passedArray->prev->vertex, passedArray->prev->prev->vertex, passedArray->next->vertex));
				if (angleOne == 3 && angleTwo == 3) {
					//if (startEncountered > 1) {
					//	cyclesAfterStartEncountered++;
					//}
					coreCount = coreCount - 1;
				} else {
					if (angleOne == 1 && angleTwo == 1) {
						//if (startEncountered > 1) {
						//	cyclesAfterStartEncountered++;
						//}
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
						passedArray = reservePrevArray;
						coreCount = coreCount - 1;
						outlierCount++;
						//EM_ASM({console.log("outlier found");});
						outlierEncountered = true;
					}
				}
			}
				if (passedArray == startPoint->next && startPointNextEncountered) {
					exhausted = true;
				} else {
					if (passedArray == startPoint->next) {
						startPointNextEncountered = true;
					}
					if (outlierEncountered) {
						outlierEncountered = false;
					} else {
						passedArray = passedArray->next;

						while (passedArray->reserved) {
							if (passedArray == startPoint->next && startPointNextEncountered) {
								exhausted = true;
							} else {
								passedArray = passedArray->next;
							}
						}
					}
				}
		}
		lastBuffersCreated->filled = true;
	} else {
		return;
	}
	reserveEnd = reserve;

	//EM_ASM_({console.log("done checking for outliers 1 - " + $0 + " " + $1 + " " + wasmTable.length);}, count, outlierCount);

	//if (outlierEncountered) {
		passedArray = startPoint;
	//}
	/*int growBy = ( (256 * ((count * 3) + outlierCount + 10)) / (65535/ALIGNSIZE));
	if (growBy > 0) {
		//EM_ASM({console.log("grow by 1.1 " + $0);}, growBy);
		//EM_ASM({console.log("to grow by " + $0);}, growBy);
		//EM_ASM({var memory=;}, growBy);
	}*/
	/*
	//EM_ASM({console.log("done checking for outliers 1.1 " + $0);}, count);
	struct Vertex* tempVBO = NULL;
	tempVBO = new Vertex[count + 1]();
	//GLfloat* tempVBO = new GLfloat[(count * 4)];
	//EM_ASM({console.log("done checking for outliers 1.2 " + $0);}, count);
	struct Vertex* tempCBO = NULL;
	tempCBO = new Vertex[count + 1]();
	//GLfloat* tempCBO = new GLfloat[(count * 4)];
	//EM_ASM({console.log("done checking for outliers 1.3 " + $0);}, (count + outlierCount));
	struct IndexArray* tempIndex = NULL;
	//tempIndex = new IndexArray[(count + outlierCount)]();
	//unsigned int* tempIndex = new unsigned int[(count * 3)];
	*/

	/*
	std::vector<GLfloat> tempVBO;
	std::vector<GLfloat> tempCBO;
	std::vector<unsigned int> tempIndex;
	*/

	globalObjCount = globalObjCount + count + outlierCount;
	//EM_ASM_({console.log("sorted 1 " + $0 + " " + $1 + " " + $2);}, count, outlierCount, globalObjCount);
	passedProp->gl_v.reserve((count) * 4);
	//EM_ASM({console.log("sorted 2");});
	passedProp->gl_v_fill.reserve((count) * 4);
	//EM_ASM({console.log("sorted 3");});
	passedProp->gl_v_idx.reserve((count + outlierCount) * 3);

	int Bcounter = 0;
	
	//EM_ASM({console.log("done checking for outliers");});
	exhausted = false;
	//int readItems = 0;
	int Icounter = 0;
	float halfW = theAnimation->w / 2;
	float halfH = theAnimation->w / 2;
	//float currentXPosition = (2 * ((layersPosition.x + shapesPosition.x) - halfW)) / theAnimation->w;
	//float currentYPosition = ((2 * ((layersPosition.y + shapesPosition.y) - halfH)) / theAnimation->h) * -1;
	//float currentXPosition = (layersPosition.x - (currentBB->w / 2)) + shapesPosition.x;
	//float currentYPosition = (layersPosition.y - (currentBB->h / 2)) + shapesPosition.y;
	//float currentXPosition = (layersPosition.x - (currentBB->w / 2) - currentBB->anchorX) + shapesPosition.x;
	//float currentYPosition = (layersPosition.y - (currentBB->h / 2) - currentBB->anchorY) + shapesPosition.y;
	float currentXPosition, currentYPosition;
			//currentXPosition = (layersPosition.x - (currentBB->w / 2)) + shapesPosition.x;
			//currentYPosition = (layersPosition.y - (currentBB->h / 2)) + shapesPosition.y;
	
	/*if (currentBB->anchorX != 0 || currentBB->anchorY != 0) {
			currentXPosition = (layersPosition.x - ((currentBB->w / 2) + currentBB->anchorX)) + shapesPosition.x;
			currentYPosition = (layersPosition.y - ((currentBB->h / 2) + currentBB->anchorY)) + shapesPosition.y;
	} else {*/
			//currentXPosition = (layersPosition.x - (currentBB->w / 2)) + (shapesPosition.x - shapesAnchor.x);
			//currentYPosition = (layersPosition.y - (currentBB->h / 2)) + (shapesPosition.y - shapesAnchor.y);
	//}
	float tempShapesX = 0;
	float tempShapesY = 0;
	float tempLayersX = 0;
	float tempLayersY = 0;

	/*
	if (shapesPosition.x != 0 || shapesPosition.y != 0) {
		if (shapesAnchor.x != 0 || shapesAnchor.y != 0) {
			tempShapesX = shapesPosition.x - shapesAnchor.x;
			tempShapesY = shapesPosition.y - shapesAnchor.y;
		} else {
			tempShapesX = shapesPosition.x - (currentBB->w / 2);
			tempShapesY = shapesPosition.y - (currentBB->h / 2);
		}
	}
	if (layersPosition.x != 0 || layersPosition.y != 0) {
		if (currentBB->anchorX != 0 || currentBB->anchorY != 0) {
			tempLayersX = layersPosition.x - currentBB->anchorX;
			tempLayersY = layersPosition.y - currentBB->anchorX;
		} else {
			tempLayersX = layersPosition.x - (currentBB->w / 2);
			tempLayersY = layersPosition.y - (currentBB->h / 2);
		}
	}
	*/


	//currentXPosition = currentShapesBB->translatedX;
	//currentYPosition = currentShapesBB->translatedY;



	struct ReturnPosition* tempPos = getRelativePosition(currentBB, currentShapesBB, false);

	currentXPosition = tempPos->layers->x + tempPos->shapes->x;
	currentYPosition = tempPos->layers->y + tempPos->shapes->y;

	//currentShapesBB->initX = currentXPosition;
	//currentShapesBB->initY = currentYPosition;

	if (currentShapesBB != NULL) {
		//currentShapesBB->baseX = tempPos->shapes->x;
		//currentShapesBB->baseY = tempPos->shapes->y;

		currentShapesBB->initXc = currentXPosition;
		currentShapesBB->initYc = currentYPosition;

		currentShapesBB->initXfc = currentShapesBB->initXc;
		currentShapesBB->initYfc = currentShapesBB->initYc;


		currentShapesBB->initX = tempPos->layers->x + cumulativeShapesDelta.x;
		currentShapesBB->initY = tempPos->layers->y + cumulativeShapesDelta.y;

		currentShapesBB->initXf = currentShapesBB->initX;
		currentShapesBB->initYf = currentShapesBB->initY;
	}

	if (currentBB != NULL) {
		currentBB->initXc = tempPos->layers->x;
		currentBB->initYc = tempPos->layers->y;

		currentBB->initXfc = currentBB->initXc;
		currentBB->initYfc = currentBB->initYc;
	}

	/*
	if (currentBB != NULL) {
		currentXPosition = currentBB->initXc + currentShapesBB->initXc;
		currentYPosition = currentBB->initYc + currentShapesBB->initYc;
	} else {
		currentXPosition = currentShapesBB->initXc;
		currentYPosition = currentShapesBB->initYc;
	}
	*/

	/*
	if (currentBB != NULL) {
		//EM_ASM_({console.log("shapes position --> " + $0 + " : " + $1 + "  /  " + $2 + " : " + $3);}, currentShapesBB->initXc, currentShapesBB->initYc, currentBB->initXc, currentBB->initYc);
	} else {
		//EM_ASM_({console.log("shapes position --> " + $0 + " : " + $1);}, currentShapesBB->initXc, currentShapesBB->initYc);
	}
	*/

	/*
		if (currentBB->anchorX != 0 || currentBB->anchorY != 0) {
			currentXPosition = (layersPosition.x - currentBB->anchorX) + shapesPosition.x;
			currentYPosition = (layersPosition.y - currentBB->anchorY) + shapesPosition.y;
		} else {
			currentXPosition = layersPosition.x + shapesPosition.x;
			currentYPosition = layersPosition.y + shapesPosition.y;
		}
	*/

	/*
	if (currentBB->anchorX != 0 || currentBB->anchorY != 0) {
		if (shapesAnchor.x != 0 || shapesAnchor.y != 0) {
			currentXPosition = (layersPosition.x - currentBB->anchorX) + (shapesPosition.x - shapesAnchor.x);
			currentYPosition = (layersPosition.y - currentBB->anchorY) + (shapesPosition.y - shapesAnchor.y);
		} else {
			currentXPosition = (layersPosition.x - currentBB->anchorX) + shapesPosition.x;
			currentYPosition = (layersPosition.y - currentBB->anchorY) + shapesPosition.y;
		}
	} else {
		if (shapesAnchor.x != 0 || shapesAnchor.y != 0) {
			currentXPosition = (layersPosition.x - (currentBB->w / 2)) + (shapesPosition.x - shapesAnchor.x);
			currentYPosition = (layersPosition.y - (currentBB->h / 2)) + (shapesPosition.y - shapesAnchor.y);
		} else {
			currentXPosition = (layersPosition.x - (currentBB->w / 2)) + shapesPosition.x;
			currentYPosition = (layersPosition.y - (currentBB->h / 2)) + shapesPosition.y;
		}
	}
	*/
	//float heightOffset = ((theAnimation->h * theAnimation->scaleFactorY) / theAnimation->h) / 2;
	//float widthOffset = ((theAnimation->w * theAnimation->scaleFactorX) / theAnimation->w) / 2;
	//
	//float heightOffset = ((theAnimation->h * theAnimation->scaleFactorY) / theAnimation->h);
	//float widthOffset = ((theAnimation->w * theAnimation->scaleFactorX) / theAnimation->w);
	float heightOffset = 1;
	float widthOffset = 1;
	//float heightOffset = 0.5;
	while (! exhausted) {
		/*
		*(passedProp->gl_v + ((Bcounter * 4) + 0)) = ((2 * passedArray->vertex->x) / theAnimation->w);
		*(passedProp->gl_v + ((Bcounter * 4) + 1)) = ((2 * passedArray->vertex->y) / theAnimation->h) * -1;
		if (passedArray->vertex->z == 0) {
			*(passedProp->gl_v + ((Bcounter * 4) + 2)) = ((float)order / 100000);
			//EM_ASM({console.log("depth ------> " + $0 + " " + $1);}, *(passedProp->gl_v + ((Bcounter * 4) + 2)), order);
		} else {
			*(passedProp->gl_v + ((Bcounter * 4) + 2)) = passedArray->vertex->z;
		}
		*(passedProp->gl_v + ((Bcounter * 4) + 3)) = 1;
		*/
		//passedProp->gl_v.resize((Bcounter + 1) * 4);

		//passedProp->gl_v.push_back(((passedArray->vertex->x + currentXPosition) * theAnimation->scaleFactorX / theAnimation->w) - widthOffset);
		//passedProp->gl_v.push_back((((passedArray->vertex->y + currentYPosition) * theAnimation->scaleFactorY / theAnimation->h) - heightOffset) * -1);
		passedProp->gl_v.push_back((2 * ((passedArray->vertex->x + currentXPosition) * theAnimation->scaleFactorX / theAnimation->w)) - widthOffset);
		passedProp->gl_v.push_back(((2 * ((passedArray->vertex->y + currentYPosition) * theAnimation->scaleFactorY / theAnimation->h)) - heightOffset) * -1);
		if (passedArray->vertex->z == 0) {
			passedProp->gl_v.push_back((float)order / 100000);
		} else {
			passedProp->gl_v.push_back(passedArray->vertex->z * theAnimation->scaleFactorZ);
		}
		passedProp->gl_v.push_back(1);

		//EM_ASM({console.log("adding regulars 1.1 ");});
		/*
		*(passedProp->gl_v_fill + ((Bcounter * 4) + 0)) = *(defaultFill + 0);
		*(passedProp->gl_v_fill + ((Bcounter * 4) + 1)) = *(defaultFill + 1);
		*(passedProp->gl_v_fill + ((Bcounter * 4) + 2)) = *(defaultFill + 2);
		*(passedProp->gl_v_fill + ((Bcounter * 4) + 3)) = *(defaultFill + 3);
		*/

		//passedProp->gl_v_fill.resize((Bcounter + 1) * 4);

		//EM_ASM({console.log("adding regulars 1.2 ");});
		passedProp->gl_v_fill.push_back(*(defaultFill + 0));
		//EM_ASM({console.log("adding regulars 1.2 ");});
		passedProp->gl_v_fill.push_back(*(defaultFill + 1));
		//EM_ASM({console.log("adding regulars 1.2 ");});
		passedProp->gl_v_fill.push_back(*(defaultFill + 2));
		//EM_ASM({console.log("adding regulars 1.2 ");});
		passedProp->gl_v_fill.push_back(*(defaultFill + 3));
		passedArray->idxOrder = Bcounter;
		//EM_ASM({console.log("adding regulars 1.3 ");});
		if (Bcounter > 1) {
			//passedProp->gl_v_idx.resize((Icounter + 1) * 3);
			passedProp->gl_v_idx.push_back(startPoint->idxOrder);
			passedProp->gl_v_idx.push_back(passedArray->prev->idxOrder);
			passedProp->gl_v_idx.push_back(passedArray->idxOrder);
			Icounter++;
		}
		Bcounter++;
		//EM_ASM({console.log("adding regulars 1.4 ");});
		//readItems++;
		if (passedArray->next == startPoint) {
			exhausted = true;
		} else {
			passedArray = passedArray->next;
			//delete passedArray->prev;
		}
	}

	//EM_ASM({console.log("done adding regulars");});
	if (reserve != NULL) {
		exhausted = false;
		reserve = reserveEnd;
		int BcounterReserveStart = Bcounter;

		while (! exhausted) {
			/*
			*(passedProp->gl_v + ((Bcounter * 4) + 0)) = ((2 * reserve->arrayItem->vertex->x) / theAnimation->w);
			*(passedProp->gl_v + ((Bcounter * 4) + 1)) = ((2 * reserve->arrayItem->vertex->y) / theAnimation->h) * -1;

			if (passedArray->vertex->z == 0) {
				*(passedProp->gl_v + ((Bcounter * 4) + 2)) = ((float)order / 100000);
			} else {
				*(passedProp->gl_v + ((Bcounter * 4) + 2)) = passedArray->vertex->z;
			}
			*(passedProp->gl_v + ((Bcounter * 4) + 3)) = 1;
			*/
			//passedProp->gl_v.resize((Bcounter + 1) * 4);

			//EM_ASM({console.log("adding regulars 2 " + $0);}, reserve->arrayItem->vertex->x);
			//passedProp->gl_v.push_back(((reserve->arrayItem->vertex->x + currentXPosition) * theAnimation->scaleFactorX / theAnimation->w) - widthOffset);
			//passedProp->gl_v.push_back((((reserve->arrayItem->vertex->y + currentYPosition) * theAnimation->scaleFactorY / theAnimation->h) - heightOffset) * -1);
			passedProp->gl_v.push_back((2 * ((reserve->arrayItem->vertex->x + currentXPosition) * theAnimation->scaleFactorX / theAnimation->w)) - widthOffset);
			passedProp->gl_v.push_back(((2 * ((reserve->arrayItem->vertex->y + currentYPosition) * theAnimation->scaleFactorY / theAnimation->h)) - heightOffset) * -1);
			if (passedArray->vertex->z == 0) {
				passedProp->gl_v.push_back(1 - ((float)order / 100000));
			} else {
				passedProp->gl_v.push_back(reserve->arrayItem->vertex->z * theAnimation->scaleFactorZ);
			}
			passedProp->gl_v.push_back(1);

			/*
			*(passedProp->gl_v_fill + ((Bcounter * 4) + 0)) = *(defaultFill + 0);
			*(passedProp->gl_v_fill + ((Bcounter * 4) + 1)) = *(defaultFill + 1);
			*(passedProp->gl_v_fill + ((Bcounter * 4) + 2)) = *(defaultFill + 2);
			*(passedProp->gl_v_fill + ((Bcounter * 4) + 3)) = *(defaultFill + 3);
			*/

			//passedProp->gl_v_fill.resize((Bcounter + 1) * 4);

			passedProp->gl_v_fill.push_back(*(defaultFill + 0));
			passedProp->gl_v_fill.push_back(*(defaultFill + 1));
			passedProp->gl_v_fill.push_back(*(defaultFill + 2));
			passedProp->gl_v_fill.push_back(*(defaultFill + 3));

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
		//EM_ASM({console.log("done adding outliers, now for indices");});
		while (! exhausted) {
			/*
			*(passedProp->gl_v_idx + ((Icounter * 3) + 0)) = reserve->arrayItem->idxOrder;
			*(passedProp->gl_v_idx + ((Icounter * 3) + 1)) = reserve->arrayItem->bindPrev->idxOrder;
			*(passedProp->gl_v_idx + ((Icounter * 3) + 2)) = reserve->arrayItem->bindNext->idxOrder;
			*/
			//passedProp->gl_v_idx.resize((Icounter + 1) * 3);

			passedProp->gl_v_idx.push_back(reserve->arrayItem->idxOrder);
			passedProp->gl_v_idx.push_back(reserve->arrayItem->bindPrev->idxOrder);
			passedProp->gl_v_idx.push_back(reserve->arrayItem->bindNext->idxOrder);
			//EM_ASM_({console.log("adding index " + $0);}, Icounter);
			Icounter++;
			reserve->arrayItem->next->prev = reserve->arrayItem;
			reserve->arrayItem->prev->next = reserve->arrayItem;
			reserve->arrayItem->reserved = false;
			if (reserve->prev == NULL) {
				exhausted = true;
				//delete reserve;
			} else {
				reserve = reserve->prev;
				//delete reserve->next;
			}
		}
	}

	passedArray = passedArray->start;
	exhausted = false;
	while (! exhausted) {
		if (passedArray->next == passedArray->start) {
			exhausted = true;
			delete passedArray;
		} else {
			passedArray = passedArray->next;
			delete passedArray->prev;
		}
	}
	if (reserve != NULL) {
		reserve = reserveEnd;
		exhausted = false;
		while (! exhausted) {
			if (reserve->prev == NULL) {
				exhausted = true;
				delete reserve;
			} else {
				reserve = reserve->prev;
				delete reserve->next;
			}
		}
	}

	passedBuffers->idxCount = Icounter;
	//EM_ASM({console.log("done all additions ");});

	/*
	tempTriangulateReturn->vbo = tempVBO;
	tempTriangulateReturn->cbo = tempCBO;
	tempTriangulateReturn->index = tempIndex;
	tempTriangulateReturn->idxCount = Icounter;
	*/


	//return tempTriangulateReturn;
}

