
struct ShaderProgram* newShaderProgram() {
	struct ShaderProgram* tempShaderProgram;
	tempShaderProgram = new ShaderProgram;
	if (lastShaderProgramCreated == NULL) {
		tempShaderProgram->start = tempShaderProgram;
	} else {
		tempShaderProgram->start = lastShaderProgramCreated->start;
		lastShaderProgramCreated->next = tempShaderProgram;
		tempShaderProgram->prev = lastShaderProgramCreated;
	}
	lastShaderProgramCreated = tempShaderProgram;
	return lastShaderProgramCreated;
}

int prepVAO(GLfloat* vertices, unsigned int* indices, struct ShaderProgram* passedShaderProgram, struct Buffers* passedBuffers, int count) {
	EM_ASM_({console.log("VAO 1.0 " + $0 + " " + $1);}, count, passedBuffers->idxCount);
	int refIndex = lastRefIndex + 1;

	/*
	for (int i = 0; i < count * 4; i++) {
		EM_ASM_({console.log("VBO " + $0);}, *(vertices + i));
	}
	for (int i = 0; i < passedBuffers->idxCount; i++) {
		EM_ASM_({console.log("INDEX " + $1);}, *(indices + i));
	}
	*/

	GLuint tvao, tvbo, tibo;
	glGenVertexArraysOES(1, &tvao);
	glBindVertexArrayOES(tvao);

	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * count * 4, vertices, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &tibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tibo);
	EM_ASM({console.log("VAO 1.1");});

	GLuint tempShaderProgram;
	if (passedShaderProgram == NULL) {
		tempShaderProgram = mainShader;
	} else {
		tempShaderProgram = *passedShaderProgram->shader;
	}
	
	EM_ASM_({console.log("VAO 1.1.1 " + $0);}, *(vertices + 0));
	GLint tempPosAttrib = glGetAttribLocation(tempShaderProgram, "position");
	EM_ASM({console.log("VAO 1.1.2");});
	glEnableVertexAttribArray(tempPosAttrib);
	EM_ASM({console.log("VAO 1.1.3");});
	glVertexAttribPointer(tempPosAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
	EM_ASM({console.log("VAO 1.1.3.1");});
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * passedBuffers->idxCount, indices, GL_DYNAMIC_DRAW);
	EM_ASM({console.log("VAO 1.1.3.2");});
	passedBuffers->posAttrib = &tempPosAttrib;
	EM_ASM({console.log("VAO 1.2");});

	passedBuffers->vao = new GLuint;
	passedBuffers->vbo = new GLuint;
	passedBuffers->ibo = new GLuint;

	*(passedBuffers->vao) = tvao;
	*(passedBuffers->vbo) = tvbo;
	*(passedBuffers->ibo) = tibo;

	//passedBuffers->vao = tvao;
	//passedBuffers->vbo = tvbo;
	//passedBuffers->ibo = tibo;

	passedBuffers->idx = indices; 
		EM_ASM({console.log("done prepping " + $0 + " " + $1);}, tvao, *(passedBuffers->vao));
	glBindVertexArrayOES(0);

	return refIndex;
}

struct Dimensions* findDimensions(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray) {
	struct Dimensions* passedDimensions;
	passedDimensions = new Dimensions;

	bool clockwise;
	bool directionFound = false;
	passedArray = passedArray->start;
	bool exhausted = false;
	while (! exhausted) {
		EM_ASM({console.log("finddim 1.1");});
		GLfloat currX = passedArray->vertex->position[0];
		GLfloat currY = passedArray->vertex->position[1];
		EM_ASM({console.log("finddim 1.2");});
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
		EM_ASM({console.log("finddim 1.4");});
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
		EM_ASM({console.log("finddim 1.5");});
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
		EM_ASM_({console.log("finddim 1.3 " + $0 + " " + $1);}, passedDimensions->maxXval, passedDimensions->maxXord);
		if (passedArray->next == NULL) {
			exhausted = true;
		} else {
			passedArray = passedArray->next;
		}
	}
	passedArray->next = passedArray->start;
	passedArray->start->prev = passedArray;
	EM_ASM({console.log("finddim 2");});
	passedBuffers->clockwise = clockwise;
	return passedDimensions;
}

/*
struct alignas(ALIGNSIZE) IntPoint {
	double X, Y;
	//GLfloat X, Y;
};

namespace mapbox {
namespace util {

template <>
struct nth<0, IntPoint> {
    inline static auto get(const IntPoint &t) {
        return t.X;
    };
};
template <>
struct nth<1, IntPoint> {
    inline static auto get(const IntPoint &t) {
        return t.Y;
    };
};

}
}
*/

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
	EM_ASM_({console.log("///////////> " + $0 + " " + $1 + " : " + $2 + " " + $3 + " " + $4 + " " + " " + $5 + " " + $6);}, firstAngle, secondAngle, a, di, bi, ds, bs);
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
 
struct TriangulateReturn* prepTriangulate(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray) {

	struct TriangulateReturn* tempTriangulateReturn;
	tempTriangulateReturn = new TriangulateReturn;

	/*
	struct Dimensions* dimensions;
	enum Phase phase = _maxY;
	EM_ASM({console.log("pretri 1.1");});
	if (passedBuffers->changed || passedBuffers->dimensions == NULL) {
		EM_ASM({console.log("pretri 1.2");});
		dimensions = findDimensions(count, passedBuffers, passedArray);
		EM_ASM({console.log("pretri 1.3");});
		EM_ASM({console.log("pretri 1.4");});
		passedBuffers->dimensions = dimensions;
		EM_ASM({console.log("pretri 1.5");});
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
	if (count > 3) {
		EM_ASM({console.log("pretri 2.1");});
		bool entered = true;
		while (! exhausted) {
			angleOne = (convex(passedArray->vertex, passedArray->next->vertex, passedArray->next->next->vertex, passedArray->prev->vertex));
			angleTwo = (convex(passedArray->vertex, passedArray->prev->vertex, passedArray->prev->prev->vertex, passedArray->next->vertex));
			if (angleOne == 3 && angleTwo == 3) {
				coreCount = coreCount - 1;
			} else {
				if (
					angleOne == 1 && angleTwo == 1
				) {
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
					EM_ASM({console.log("outlier found");});
					outlierEncountered = true;
				}
			}
			if (passedArray->next == startPoint) {
				exhausted = true;
			} else {
				if (outlierEncountered) {
					outlierEncountered = false;
				} else {
					passedArray = passedArray->next;
				}
			}
		}
	} else {
		if (count < 3) {
			return NULL;
		}
	}
	reserveEnd = reserve;

	EM_ASM({console.log("done checking for outliers");});
	/*
	if (outlierEncountered) {
		startPoint = reserveNextArray;
	} else {
		startPoint = passedArray;
	}
	*/

	passedArray = startPoint;

	GLfloat* tempVBO = new GLfloat[(count * 4) + 2]();
	unsigned int* tempIndex = new unsigned int[(count * 3) * 2]();
	unsigned int Bcounter = 0;
	unsigned int Icounter = 0;
	
	EM_ASM({console.log("done checking for outliers");});
	exhausted = false;
	int readItems = 0;
	while (! exhausted) {
		*(tempVBO + ((Bcounter * 4) + 0)) = ((2 * passedArray->vertex->position[0]) / theAnimation->w);
		*(tempVBO + ((Bcounter * 4) + 1)) = ((2 * passedArray->vertex->position[1]) / theAnimation->h) * -1;
		
		//*(tempVBO + ((Bcounter * 4) + 0)) = passedArray->vertex->position[0] / theAnimation->w;
		//*(tempVBO + ((Bcounter * 4) + 1)) = passedArray->vertex->position[1] / theAnimation->h;
		*(tempVBO + ((Bcounter * 4) + 2)) = 1 - (Bcounter / 100000000);
		*(tempVBO + ((Bcounter * 4) + 3)) = 1;
		passedArray->idxOrder = Bcounter;
		if (readItems >= 2) {
			*(tempIndex + ((Icounter * 3) + 0)) = startPoint->idxOrder;
			*(tempIndex + ((Icounter * 3) + 1)) = passedArray->prev->idxOrder;
			*(tempIndex + ((Icounter * 3) + 2)) = passedArray->idxOrder;
		}
		EM_ASM_({console.log("RENDER index " + $0 + " - " + $1 + " - " + $2 + " " + $3 + ":" + $4 + " ---- " + $5 + " " + $6 + " " + $7 + " vert: " + $8);}, *(tempIndex + ((Icounter * 3) + 0)), *(tempIndex + ((Icounter * 3) + 1)), *(tempIndex + ((Icounter * 3) + 2)), *(tempVBO + ((Bcounter * 4) + 0)), *(tempVBO + ((Bcounter * 4) + 1)), startPoint->order, passedArray->prev->order, passedArray->idxOrder, passedArray->vertex->position[0]);
		Bcounter++;
		Icounter++;
		readItems++;
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
			//*(tempVBO + ((Bcounter * 4) + 0)) = reserve->arrayItem->vertex->position[0] / theAnimation->w;
			//*(tempVBO + ((Bcounter * 4) + 1)) = reserve->arrayItem->vertex->position[1] / theAnimation->h;
			//*(tempVBO + ((Bcounter * 4) + 2)) = 0;
			*(tempVBO + ((Bcounter * 4) + 2)) = 1 - (Bcounter / 100000000);
			*(tempVBO + ((Bcounter * 4) + 3)) = 1;
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
			*(tempIndex + ((Icounter * 3) + 0)) = reserve->arrayItem->idxOrder;
			*(tempIndex + ((Icounter * 3) + 1)) = reserve->arrayItem->bindPrev->idxOrder;
			*(tempIndex + ((Icounter * 3) + 2)) = reserve->arrayItem->bindNext->idxOrder;
			EM_ASM_({console.log("RENDER index earcut " + $0 + " - " + $1 + " - " + $2 + " " + $3 + ":" + $4 + " " + $5);}, *(tempIndex + ((Icounter * 3) + 0)), *(tempIndex + ((Icounter * 3) + 1)), *(tempIndex + ((Icounter * 3) + 2)), *(tempVBO + ((Bcounter * 4) + 0)), *(tempVBO + ((Bcounter * 4) + 1)), reserve->arrayItem->idxOrder);
			Icounter++;
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

	/*
	passedArray->start->prev->next = NULL;
	passedArray->start->prev = NULL;
	passedArray = passedArray->start;
	*/

	passedBuffers->idxCount = Icounter * 3;

	tempTriangulateReturn->vbo = tempVBO;
	tempTriangulateReturn->index = tempIndex;
	
	return tempTriangulateReturn;
	//return NULL;
}

struct Buffers* newBuffers() {
	struct Buffers* tempBuffers;
	tempBuffers = new Buffers;
	if (lastBuffersCreated == NULL) {
		tempBuffers->start = tempBuffers;
	} else {
		tempBuffers->start = lastBuffersCreated->start;
		lastBuffersCreated->next = tempBuffers;
		tempBuffers->prev = lastBuffersCreated;
	}
	lastBuffersCreated = tempBuffers;
	return lastBuffersCreated;
}

int prepPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp) {
	if (passedPropertiesShapeProp == NULL) {
		return 0;
	}
	passedPropertiesShapeProp = passedPropertiesShapeProp->start;
	bool exhausted = false;
	struct TriangulateReturn* tempTriangulateReturn;

	while (! exhausted) {
		
		if (passedPropertiesShapeProp->i != NULL) {
			passedPropertiesShapeProp->buffers_i = newBuffers();
			//passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->i_count);
			EM_ASM({console.log("looping 1.1 i");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->i_count, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_i = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_i_idx = tempTriangulateReturn->index;
			//delete tempTriangulateReturn;
			EM_ASM({console.log("looping 1.1.1 i");});
			prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, NULL, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i_count);
			EM_ASM({console.log("looping 1.1.2 i");});
		}

		if (passedPropertiesShapeProp->o != NULL) {
			passedPropertiesShapeProp->buffers_o = newBuffers();
			//passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->o_count);
			EM_ASM({console.log("looping 1.1 o");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->o_count, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_o = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_o_idx = tempTriangulateReturn->index;
			//delete tempTriangulateReturn;
			EM_ASM({console.log("looping 1.1.1 o");});
			prepVAO(passedPropertiesShapeProp->gl_o, passedPropertiesShapeProp->gl_o_idx, NULL, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o_count);
			EM_ASM({console.log("looping 1.1.2 o");});
		}

		if (passedPropertiesShapeProp->v != NULL) {
			passedPropertiesShapeProp->buffers_v = newBuffers();
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->v_count);
			EM_ASM({console.log("looping 1.1 v");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_v = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_v_idx = tempTriangulateReturn->index;
			//delete tempTriangulateReturn;
			EM_ASM({console.log("looping 1.1.1 v");});
			prepVAO(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->gl_v_idx, NULL, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v_count);
			EM_ASM({console.log("looping 1.1.2 v");});
		}

		delete tempTriangulateReturn;
		EM_ASM({console.log("looping 1.4");});

		if (passedPropertiesShapeProp->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp = passedPropertiesShapeProp->next;
		}
	}
	EM_ASM({console.log("all prep done");});
	
	return 1;
}

int prepPropertiesShape(struct PropertiesShape* passedPropertiesShape) {
	if (passedPropertiesShape == NULL) {
		return 0;
	}
	bool exhausted = false;
	passedPropertiesShape = passedPropertiesShape->start;
	while (! exhausted) {
		if (passedPropertiesShape->isKeyframe) {
			EM_ASM({console.log("SHAPEPROPKEYFRAME found");});
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->s);
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->e);
		} else {
			EM_ASM({console.log("SHAPEPROP found");});
			prepPropertiesShapeProp(passedPropertiesShape->k);
		}
		if (passedPropertiesShape->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShape = passedPropertiesShape->next;
		}
	}
	return 1;
}

int prepShapesItem(struct ShapesItem* passedShapesItem) {
	EM_ASM({console.log("SHAPESITEM found pre 1.0");});
	if (passedShapesItem == NULL) {
		return 0;
	}
	bool exhausted = false;
	passedShapesItem = passedShapesItem->start;
	while (! exhausted) {
		EM_ASM({console.log("SHAPESITEM found");});
		if (passedShapesItem->ks != NULL) {
			prepPropertiesShape(passedShapesItem->ks);
		}
		if (passedShapesItem->next == NULL) {
			exhausted = true;
		} else {
			passedShapesItem = passedShapesItem->next;
		}
	}

	return 1;
}

int prepLayers(struct Layers* passedLayers) {
	EM_ASM({console.log("LAYERS found pre 1.0");});
	if (passedLayers->shapes == NULL || passedLayers == NULL) {
		return 0;
	}
	EM_ASM({console.log("LAYERS found pre 1.1");});
	passedLayers = passedLayers->start;
	bool exhausted = false;
	while (! exhausted) {
		if (passedLayers->shapes != NULL) {
			EM_ASM({console.log("LAYERS found 1.0");});
			prepShapesItem(passedLayers->shapes);
		}
		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			EM_ASM({console.log("LAYERS found 1.1");});
			passedLayers = passedLayers->next;
		}
	}
	EM_ASM({console.log("LAYERS found 1.2");});

	return 1;
}

int prepAssets(struct Assets* passedAssets) {
	if (passedAssets == NULL) {
		return 0;
	}
	passedAssets = passedAssets->start;
	bool exhausted = false;
	while (! exhausted) {
		EM_ASM({console.log("PRECOMP found");});
		prepLayers(passedAssets->precomps);
		if (passedAssets->next == NULL) {
			exhausted = true;
		} else {
			passedAssets = passedAssets->next;
		}
	}
	EM_ASM({console.log("PRECOMP done");});

	return 1;
}

int prepShapes() {

	if (theAnimation->assets != NULL) {
		EM_ASM({console.log("ASSETS found");});
		prepAssets(theAnimation->assets);
	}
	if (theAnimation->layers != NULL) {
		EM_ASM({console.log("ANIMLAYERS found");});
		prepLayers(theAnimation->layers);
	}
	EM_ASM({console.log("ALL done");});

	return 1;
}

