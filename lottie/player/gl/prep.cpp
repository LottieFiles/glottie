
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
	EM_ASM({console.log("VAO 1.0");});
	int refIndex = lastRefIndex + 1;

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
	EM_ASM({console.log("VAO 1.1.1");});
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

unsigned int distanceBetweenPoints(struct Vertex* pointA, struct Vertex* pointB) {
	return sqrt(pow(((float)pointA->position[0] - (float)pointB->position[0]), 2) + pow(((float)pointA->position[1] - (float)pointB->position[2]), 2));
}

bool convex(struct Vertex* origin, struct Vertex* next, struct Vertex* nextnext, struct Vertex* prev) {
	float a, di, ds, bi, bs;
	a = (float)distanceBetweenPoints(origin, prev);
	di = (float)distanceBetweenPoints(prev, next);
	ds = (float)distanceBetweenPoints(prev, nextnext);
	bi = (float)distanceBetweenPoints(origin, next);
	bs = (float)distanceBetweenPoints(origin, nextnext);
	if 	(
			((pow(a,2) + pow(bi,2) - pow(di,2)) / (2 * a * bi)) <
			((pow(a,2) + pow(bs,2) - pow(ds,2)) / (2 * a * bs))
		) {
		return true;
	} else {
		return false;
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
	struct Dimensions* dimensions;
	enum Phase phase = _maxY;
	struct TriangulateReturn* tempTriangulateReturn;
	tempTriangulateReturn = new TriangulateReturn;

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

	struct ArrayOfArrayOfVertex* reserve = NULL;
	passedArray = dimensions->topVertex;
	struct ArrayOfVertex* startPoint = passedArray;
	struct ArrayOfVertex* actualStartPoint = passedArray->start;
	bool exhausted = false;
	int coreCount = count;
	if (count > 4) {
		while (! exhausted) {
			// then determine the rotation direction
			/*
			if (dimensions->clockwise) {
				// finally determine ears
				if (phase == _maxY) {
					if (passedArray->prev->vertex->position[1] < passedArray->vertex->position[1] && passedArray->prev->prev->vertex->position[0] 
				} else if (phase == _passedMaxY) {
				} else if (phase == _maxX) {
				} else if (phase == _passedMaxX) {
				} else if (phase == _minY) {
				} else if (phase == _passedMinY) {
				} else if (phase == _minX) {
				} else if (phase == _passedMinX) {
				}
			} else {
				// finally determine ears
				if (phase == _maxY) {
				} else if (phase == _passedMaxY) {
				} else if (phase == _minX) {
				} else if (phase == _passedMinX) {
				} else if (phase == _minY) {
				} else if (phase == _passedMinY) {
				} else if (phase == _maxX) {
				} else if (phase == _passedMaxX) {
				}
			}
			*/

			if 	(
					! (convex(passedArray->vertex, passedArray->next->vertex, passedArray->next->next->vertex, passedArray->prev->vertex)) ||
					! (convex(passedArray->vertex, passedArray->prev->vertex, passedArray->prev->prev->vertex, passedArray->next->vertex)) 
				) {
				reserve = newReserve(reserve);
				reserve->arrayItem = passedArray;
				passedArray->prev->next = passedArray->next;
				passedArray->next->prev = passedArray->prev;
				passedArray = passedArray->prev->prev;
				coreCount = coreCount - 1;
			}

			if (passedArray->next == startPoint) {
				exhausted = true;
			} else {
				if (passedArray->next == NULL) {
					passedArray = passedArray->start;
				} else {
					passedArray = passedArray->next;
				}
			}

			/*
			// first determine the phase (qaudrant)
			if (passedVertex->order == dimensions->maxXord) {
				phase = _maxX;
			} else if (passedVertex->order == dimensions->minXord) {
				phase = _minX;
			} else if (passedVertex->order == dimensions->maxYord) {
				phase = _maxY;
			} else if (passedVertex->order == dimensions->minYord) {
				phase = _minY;
			} else if (phase == _maxX) {
				phase = _passedMaxX;
			} else if (phase == _minX) {
				phase = _passedMinX;
			} else if (phase == _maxY) {
				phase = _passedMaxY;
			} else if (phase == _minY) {
				phase = _passedMinY;
			}
			*/
		}
	} else {
	}

	startPoint = passedArray;
	GLfloat* tempVBO = new GLfloat[count * 4];
	unsigned int* tempIndex = new unsigned int[(count * 3) * 2];
	unsigned int Bcounter = 0;
	unsigned int Icounter = 0;
	
	exhausted = false;
	*(tempVBO + ((Bcounter * 4) + 0)) = passedArray->vertex->position[0];
	*(tempVBO + ((Bcounter * 4) + 1)) = passedArray->vertex->position[1];
	*(tempVBO + ((Bcounter * 4) + 2)) = 0;
	*(tempVBO + ((Bcounter * 4) + 3)) = 1;
	passedArray->order = Bcounter;
	passedArray = passedArray->next;
	*(tempVBO + ((Bcounter * 4) + 0)) = passedArray->vertex->position[0];
	*(tempVBO + ((Bcounter * 4) + 1)) = passedArray->vertex->position[1];
	*(tempVBO + ((Bcounter * 4) + 2)) = 0;
	*(tempVBO + ((Bcounter * 4) + 3)) = 1;
	passedArray->order = Bcounter;
	passedArray = passedArray->next;
	while (! exhausted) {
		*(tempVBO + ((Bcounter * 4) + 0)) = passedArray->vertex->position[0];
		*(tempVBO + ((Bcounter * 4) + 1)) = passedArray->vertex->position[1];
		*(tempVBO + ((Bcounter * 4) + 2)) = 0;
		*(tempVBO + ((Bcounter * 4) + 3)) = 1;
		passedArray->order = Bcounter;
		*(tempIndex + ((Icounter * 3) + 0)) = startPoint->order;
		*(tempIndex + ((Icounter * 3) + 0)) = passedArray->prev->order;
		*(tempIndex + ((Icounter * 3) + 0)) = passedArray->order;
		Bcounter++;
		Icounter++;
		if (passedArray->next == startPoint) {
			exhausted = true;
		} else {
			passedArray = passedArray->next;
		}
	}

	if (reserve != NULL) {
		exhausted = false;
		reserve = reserve->start;
		while (! exhausted) {
			*(tempVBO + ((Bcounter * 4) + 0)) = reserve->arrayItem->vertex->position[0];
			*(tempVBO + ((Bcounter * 4) + 1)) = reserve->arrayItem->vertex->position[1];
			*(tempVBO + ((Bcounter * 4) + 2)) = 0;
			*(tempVBO + ((Bcounter * 4) + 3)) = 1;
			reserve->arrayItem->order = Bcounter;
			*(tempIndex + ((Icounter * 3) + 0)) = reserve->arrayItem->order;
			*(tempIndex + ((Icounter * 3) + 0)) = reserve->arrayItem->prev->order;
			*(tempIndex + ((Icounter * 3) + 0)) = reserve->arrayItem->next->order;
			reserve->arrayItem->prev->next = reserve->arrayItem;
			reserve->arrayItem->next->prev = reserve->arrayItem;
			Bcounter++;
			Icounter++;
			
			if (reserve->next == NULL) {
				exhausted = true;
			} else {
				reserve = reserve->next;
				delete reserve->prev;
			}
		}
	}

	passedArray->start->prev->next = NULL;
	passedArray->start->prev = NULL;
	passedArray = passedArray->start;

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	/*
	EM_ASM({console.log("pretri 2.1");});
	unsigned int* tempIndex;
	EM_ASM({console.log("pretri 2.1.1");});
	*(tempIndex + 0) = dimensions->minXord;
	EM_ASM({console.log("pretri 2.1.2");});
	*(tempIndex + 1) = dimensions->minYord;
	EM_ASM({console.log("pretri 2.1.3");});
	*(tempIndex + 2) = dimensions->maxXord;
	*(tempIndex + 3) = dimensions->maxXord;
	*(tempIndex + 4) = dimensions->maxYord;
	*(tempIndex + 5) = dimensions->minXord;
	EM_ASM({console.log("pretri 2.2");});
	*/

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
			passedPropertiesShapeProp->gl_i = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_i_idx = tempTriangulateReturn->index;
			EM_ASM({console.log("looping 1.1.1 i");});
			prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, NULL, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i_count);
			EM_ASM({console.log("looping 1.1.2 i");});
		}

		if (passedPropertiesShapeProp->o != NULL) {
			passedPropertiesShapeProp->buffers_o = newBuffers();
			//passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->o_count);
			EM_ASM({console.log("looping 1.1 o");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->o_count, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o);
			passedPropertiesShapeProp->gl_o = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_o_idx = tempTriangulateReturn->index;
			EM_ASM({console.log("looping 1.1.1 o");});
			prepVAO(passedPropertiesShapeProp->gl_o, passedPropertiesShapeProp->gl_o_idx, NULL, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o_count);
			EM_ASM({console.log("looping 1.1.2 o");});
		}

		if (passedPropertiesShapeProp->v != NULL) {
			passedPropertiesShapeProp->buffers_v = newBuffers();
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->v_count);
			EM_ASM({console.log("looping 1.1 v");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v);
			passedPropertiesShapeProp->gl_v = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_v_idx = tempTriangulateReturn->index;
			EM_ASM({console.log("looping 1.1.1 v");});
			prepVAO(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->gl_v_idx, NULL, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v_count);
			EM_ASM({console.log("looping 1.1.2 v");});
		}
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
	if (passedShapesItem->ks == NULL) {
		return 0;
	}
	bool exhausted = false;
	passedShapesItem = passedShapesItem->start;
	while (! exhausted) {
		EM_ASM({console.log("SHAPESITEM found");});
		prepPropertiesShape(passedShapesItem->ks);
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
		EM_ASM({console.log("LAYERS found 1.0");});
		if (passedLayers->shapes != NULL) {
			prepShapesItem(passedLayers->shapes);
		}
		EM_ASM({console.log("LAYERS found 1.1");});
		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			passedLayers = passedLayers->next;
		}
		EM_ASM({console.log("LAYERS found 1.2");});
	}
	EM_ASM({console.log("LAYERS found 1.3");});

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

