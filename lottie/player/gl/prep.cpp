#include "triangulate.cpp"

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

//int prepVAO(GLfloat* vertices, unsigned int* indices, GLfloat* colors, struct ShaderProgram* passedShaderProgram, struct Buffers* passedBuffers, int count, int idxCount) {
void prepVAO(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices, std::vector<GLfloat>& colors, struct ShaderProgram* passedShaderProgram, struct Buffers* passedBuffers, int count, int idxCount) {
	//EM_ASM_({console.log("VAO 1.0 " + $0 + " " + $1);}, count, passedBuffers->idxCount);
	//int refIndex = lastRefIndex + 1;

	GLuint tvao, tvbo, tibo, tcbo;
	glGenVertexArraysOES(1, &tvao);
	glBindVertexArrayOES(tvao);


	GLuint tempShaderProgram;
	if (passedShaderProgram == NULL) {
		tempShaderProgram = mainShader;
	} else {
		tempShaderProgram = *passedShaderProgram->shader;
	}

	GLint tempPosAttrib = glGetAttribLocation(tempShaderProgram, "position");
	glEnableVertexAttribArray(tempPosAttrib);
	GLint tempColAttrib = glGetAttribLocation(tempShaderProgram, "color");
	glEnableVertexAttribArray(tempColAttrib);

	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(GLfloat)), &vertices[0], GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexAttribPointer(tempPosAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &tcbo);
	glBindBuffer(GL_ARRAY_BUFFER, tcbo);
	glBufferData(GL_ARRAY_BUFFER, (colors.size() * sizeof(GLfloat)), &colors[0], GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors[0], GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexAttribPointer(tempColAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &tibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices.size() * sizeof(unsigned int)), &indices[0], GL_DYNAMIC_DRAW);

	passedBuffers->posAttrib = &tempPosAttrib;
	passedBuffers->colAttrib = &tempColAttrib;

	passedBuffers->vao = new GLuint;
	passedBuffers->vbo = new GLuint;
	passedBuffers->ibo = new GLuint;
	passedBuffers->cbo = new GLuint;

	*(passedBuffers->vao) = tvao;
	*(passedBuffers->vbo) = tvbo;
	*(passedBuffers->ibo) = tibo;
	*(passedBuffers->cbo) = tcbo;

	passedBuffers->shapesTransform = currentShapesTransform;
	passedBuffers->layersTransform = currentLayersTransform;

	//EM_ASM_({console.log("--......--> done loading buffers " + $0 + " " + $1);}, idxCount, indices.size());

	//passedBuffers->vao = tvao;
	//passedBuffers->vbo = tvbo;
	//passedBuffers->ibo = tibo;

	//EM_ASM({console.log("--......--> done loading buffers 1.0");});
	passedBuffers->idx = indices;
	//EM_ASM({console.log("--......--> done loading buffers 1.1");});
	passedBuffers->idxCount = idxCount;
	//EM_ASM({console.log("--......--> done loading buffers 1.2");});
	glBindVertexArrayOES(0);

	//return refIndex;
}

float* getFill(struct ShapesItem* passedShapesItem) {
	if (passedShapesItem == NULL) {
		return NULL;
	}
	struct ShapesItem* tempShapesItem;
	tempShapesItem = passedShapesItem->start;
	float* tempFloat = new float[4];

	bool exhausted = false;
	while (! exhausted) {
		if (tempShapesItem->ty == _fill) {
			//EM_ASM({console.log("////-------> looking for color");});
			if (tempShapesItem->c != NULL) {
				if (tempShapesItem->c->k_count > 0) {
					//EM_ASM_({console.log("////-------> color " + $0 + " " + $1 + " " + $2);}, *(tempShapesItem->c->k), *(tempShapesItem->c->k + 1), *(tempShapesItem->c->k + 2));
					*(tempFloat + 0) = *(tempShapesItem->c->k + 0);
					*(tempFloat + 1) = *(tempShapesItem->c->k + 1);
					*(tempFloat + 2) = *(tempShapesItem->c->k + 2);
					if (tempShapesItem->c->k_count < 4) {
						*(tempFloat + 3) = 1;
					} else {
						*(tempFloat + 3) = *(tempShapesItem->c->k + 0);
					}
				} else {

				}
				if (*(tempFloat + 0) == 0 &&
					*(tempFloat + 1) == 0 &&
					*(tempFloat + 2) == 0)
					{
						*(tempFloat + 0) = 1;
						*(tempFloat + 1) = 1;
						*(tempFloat + 2) = 1;
						*(tempFloat + 3) = 1;
				}
				return tempFloat;
			}
		}
		
		if (tempShapesItem->next == NULL) {
			exhausted = true;
		} else {
			tempShapesItem = tempShapesItem->next;
		}
	}
	/*
	*(tempFloat + 0) = 1;
	*(tempFloat + 1) = 1;
	*(tempFloat + 2) = 1;
	*(tempFloat + 3) = 1;
	*/
	return tempFloat;
}

struct Buffers* newBuffers() {
	struct Buffers* tempBuffers;
	//EM_ASM({console.log("creating buffer 1.0 ");});
	tempBuffers = new Buffers;
	if (lastBuffersCreated == NULL) {
		tempBuffers->start = tempBuffers;
	} else {
		tempBuffers->start = lastBuffersCreated->start;
		lastBuffersCreated->next = tempBuffers;
		tempBuffers->prev = lastBuffersCreated;
	}
	tempBuffers->next = tempBuffers->start;
	tempBuffers->start->prev = tempBuffers;
	lastBuffersCreated = tempBuffers;
	//EM_ASM({console.log("buffer created ");});
	return lastBuffersCreated;
}

int prepPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp, struct ShapesItem* passedShapesItem, struct BoundingBox* currentBB, struct BoundingBox* currentShapesBB) {
	if (passedPropertiesShapeProp == NULL) {
		return 0;
	}
	passedPropertiesShapeProp = passedPropertiesShapeProp->start;
	bool exhausted = false;
	//struct TriangulateReturn* tempTriangulateReturn;


	float* defaultFill = getFill(passedShapesItem);
	int elementCount = 0;
	while (! exhausted) {
		elementCount++;

		//EM_ASM({console.log("tracing 3 ");});
		if (passedPropertiesShapeProp->v != NULL) {
			passedPropertiesShapeProp->buffers_v = newBuffers();
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->v_count);
			//EM_ASM({console.log("looping 1.1 v");});
			prepTriangulate(passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v, defaultFill, passedShapesItem->order, passedPropertiesShapeProp, currentBB, currentShapesBB);
			//EM_ASM({console.log("looping 1.1.0 v");});
			//if (tempTriangulateReturn == NULL) {return 0;}
			
			//passedPropertiesShapeProp->gl_v = tempTriangulateReturn->vbo;
			//passedPropertiesShapeProp->gl_v_fill = tempTriangulateReturn->cbo;
			//passedPropertiesShapeProp->gl_v_idx = tempTriangulateReturn->index;
			//EM_ASM({console.log("looping 1.1.1 v");});
			//prepVAO(passedPropertiesShapeProp);
			prepVAO(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->gl_v_idx, passedPropertiesShapeProp->gl_v_fill, NULL, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v->idxCount);
			//EM_ASM({console.log("looping 1.1.2 v " + $0);}, passedPropertiesShapeProp->gl_v.size());
			//delete tempTriangulateReturn;
		}

		if (passedPropertiesShapeProp->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp = passedPropertiesShapeProp->next;
		}
	}
	delete defaultFill;
	//EM_ASM({console.log("all prep done");});
	
	return 1;
}

int prepPropertiesShape(struct PropertiesShape* passedPropertiesShape, struct ShapesItem* passedShapesItem, struct BoundingBox* currentBB, struct BoundingBox* currentShapesBB) {
	if (passedPropertiesShape == NULL) {
		return 0;
	}
	bool exhausted = false;
	passedPropertiesShape = passedPropertiesShape->start;
	while (! exhausted) {
		if (passedPropertiesShape->isKeyframe) {
			//EM_ASM({console.log("SHAPEPROPKEYFRAME found");});
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->s, passedShapesItem, currentBB, currentShapesBB);
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->e, passedShapesItem, currentBB, currentShapesBB);
		} else {
			//EM_ASM({console.log("SHAPEPROP found");});
			prepPropertiesShapeProp(passedPropertiesShape->k, passedShapesItem, currentBB, currentShapesBB);
		}
		if (passedPropertiesShape->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShape = passedPropertiesShape->next;
		}
	}
	return 1;
}

struct ShapesItem* findShapesTransform(struct ShapesItem* passedShapesItem) {
	//EM_ASM({console.log("///// entering findShapesTransform ");});
	bool exhausted = false;
	passedShapesItem = passedShapesItem->start;
	while (! exhausted) {
		//EM_ASM({console.log("shape type " + $0);}, passedShapesItem->ty);
		if (passedShapesItem->ty == _transform) {
			currentShapesTransform = fillTransformShapes(passedShapesItem);
			//EM_ASM({console.log("SHAPEPROP TRANSFORM found");});

			/*shapesPosition.x = passedShapesItem->p->k[0];
			shapesPosition.y = passedShapesItem->p->k[1];
			shapesAnchor.x = passedShapesItem->a->k[0];
			shapesAnchor.y = passedShapesItem->a->k[1];*/

			if (passedShapesItem->p != NULL && passedShapesItem->p->k != NULL) {
				//shapesPosition.x = shapesPosition.x + passedShapesItem->p->k[0];
				//shapesPosition.y = shapesPosition.y + passedShapesItem->p->k[1];
				shapesPosition.x = passedShapesItem->p->k[0];
				shapesPosition.y = passedShapesItem->p->k[1];
			}
			if (passedShapesItem->a != NULL && passedShapesItem->a->k != NULL) {
				shapesAnchor.x = passedShapesItem->a->k[0];
				shapesAnchor.y = passedShapesItem->a->k[1];
			}

			/*shapesPosition.x = passedShapesItem->p->k[0];
			shapesPosition.y = passedShapesItem->p->k[1];
			shapesAnchor.x = passedShapesItem->a->k[0];
			shapesAnchor.y = passedShapesItem->a->k[1];*/
			//EM_ASM({console.log("SHAPE TRANSFORM found " + $0 + " " + $1 + " " + $2 + " " + $3);}, shapesPosition.x, shapesPosition.y, shapesAnchor.x, shapesAnchor.y);
			return passedShapesItem;
		}
		if (passedShapesItem->next == NULL) {
			exhausted = true;
		} else {
			passedShapesItem = passedShapesItem->next;
		}
	}
	//EM_ASM({console.log("///// exiting findShapesTransform ");});

	return NULL;
}

int prepShapesItem(struct ShapesItem* passedShapesItem, struct ShapesItem* tempBaseTransform, bool freshStart, struct BoundingBox* currentBB) {
	currentShapesTransform = NULL;
	//EM_ASM({console.log("SHAPESITEM found pre 1.0");});
	//EM_ASM({console.log("----- entering prepShapesItem ");});
	if (passedShapesItem == NULL) {
		//EM_ASM({console.log("----- exiting NULL prepShapesItem ");});
		return 0;
	}
	bool exhausted = false;

	if (freshStart) {
			shapesPosition.x = 0;
			shapesPosition.y = 0;
			shapesAnchor.x = 0;
			shapesAnchor.y = 0;
			freshStart = false;
	}

	//EM_ASM({console.log("LAYERS found 1.0.2");});

	struct ShapesItem* currentBaseTransform = findShapesTransform(passedShapesItem);
	
	passedShapesItem = passedShapesItem->start;
	float currentShapesPosX, currentShapesPosY, currentShapesAncX, currentShapesAncY;
	while (! exhausted) {
		//EM_ASM({console.log("SHAPESITEM found");});
		if (passedShapesItem->it != NULL) {
			currentShapesPosX = shapesPosition.x;
			currentShapesPosY = shapesPosition.y;
			currentShapesAncX = shapesAnchor.x;
			currentShapesAncY = shapesAnchor.y;
			/*shapesPosition.x = 0;
			shapesPosition.y = 0;
			shapesAnchor.x = 0;
			shapesAnchor.y = 0;
			*/
			prepShapesItem(passedShapesItem->it, currentBaseTransform, freshStart, currentBB);
			shapesPosition.x = currentShapesPosX;
			shapesPosition.y = currentShapesPosY;
			shapesAnchor.x = currentShapesAncX;
			shapesAnchor.y = currentShapesAncY;
		}
		if (passedShapesItem->ks != NULL) {
			if (passedShapesItem->currentBB == NULL) {
				passedShapesItem->currentBB = new BoundingBox;
			}
			getBBPropShape(passedShapesItem->ks, passedShapesItem->currentBB);
			prepPropertiesShape(passedShapesItem->ks, passedShapesItem, currentBB, passedShapesItem->currentBB);
		}

		passedShapesItem->baseTransform = currentBaseTransform;

		if (passedShapesItem->next == NULL) {
			exhausted = true;
		} else {
			passedShapesItem = passedShapesItem->next;
		}
	}
	//EM_ASM({console.log("----- exiting prepShapesItem ");});

	return 1;
}


void findLayersTransform(struct Layers* passedLayers) {
	//bool exhausted = false;
	//while (! exhausted) {
		if (passedLayers != NULL && passedLayers->ks != NULL) {
			if (passedLayers->ks->p != NULL && passedLayers->ks->p->k != NULL) {
				layersPosition.x = passedLayers->ks->p->k[0];
				layersPosition.y = passedLayers->ks->p->k[1];
				passedLayers->currentBB->initX = passedLayers->ks->p->k[0];
				passedLayers->currentBB->initY = passedLayers->ks->p->k[1];
				//EM_ASM({console.log("TRANSFORM LAYERS found 1.0.1");});
			}
			if (passedLayers->ks->a != NULL && passedLayers->ks->a->k != NULL) {
				layersAnchor.x = passedLayers->ks->a->k[0];
				layersAnchor.y = passedLayers->ks->a->k[1];
				passedLayers->currentBB->anchorX = passedLayers->ks->a->k[0];
				passedLayers->currentBB->anchorY = passedLayers->ks->a->k[1];
			}
			currentLayersTransform = fillTransformLayers(passedLayers);
		}
	/*
		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			//EM_ASM({console.log("LAYERS found 1.1");});
			passedLayers = passedLayers->next;
		}
	}*/
}

int prepLayers(struct Layers* passedLayers) {
	//EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- LAYERS found pre 1.0");});
	currentLayersTransform = NULL;

	if (passedLayers == NULL || passedLayers->shapes == NULL) {
		return 0;
	}
	//EM_ASM({console.log("LAYERS found pre 1.1");});


	//EM_ASM_({console.log("offsets " + $0 + " " + $1 + " " + $2 + " " + $3);}, layersOffset.x, layersOffset.y, layersAnchor.x, layersAnchor.y);

	passedLayers = passedLayers->start;
	bool exhausted = false;
	while (! exhausted) {
		layersPosition.x = 0;
		layersPosition.y = 0;
		layersAnchor.x = 0;
		layersAnchor.y = 0;
		if (passedLayers->currentBB == NULL) {
			passedLayers->currentBB = new BoundingBox;
			passedLayers->currentBB->w = 0;
			passedLayers->currentBB->h = 0;
			passedLayers->currentBB->initX = 0;
			passedLayers->currentBB->initY = 0;
		}
		if (passedLayers->ks != NULL) {
			findLayersTransform(passedLayers);
		}

		if (passedLayers->shapes != NULL) {
			/*shapesPosition.x = 0;
			shapesPosition.y = 0;
			shapesAnchor.x = 0;
			shapesAnchor.y = 0;*/


			//currentBB->initX = passedLayers->initX;
			//currentBB->initY = passedLayers->initY;
			getBoundingBox(passedLayers->shapes->start, passedLayers->currentBB);
			prepShapesItem(passedLayers->shapes->start, NULL, true, passedLayers->currentBB);
		}
		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			//EM_ASM({console.log("LAYERS found 1.1");});
			passedLayers = passedLayers->next;
		}
	}
	//EM_ASM({console.log("LAYERS found 1.2 " + $0 +  " " + $1);}, passedLayers->currentBB->w, passedLayers->currentBB->h);

	return 1;
}

int prepAssets(struct Assets* passedAssets) {
	if (passedAssets == NULL) {
		return 0;
	}

	passedAssets = passedAssets->start;
	//EM_ASM({console.log("ASSETS found pre 1.1");});
	bool exhausted = false;
	while (! exhausted) {
		//EM_ASM({console.log("PRECOMP found");});
		if (passedAssets->precomps != NULL) {
			prepLayers(passedAssets->precomps->start);
		}
		if (passedAssets->next == NULL) {
			exhausted = true;
		} else {
			passedAssets = passedAssets->next;
		}
	}
	//EM_ASM({console.log("PRECOMP done");});

	return 1;
}

int prepShapes() {
	//layersPosition.x = 0;
	//layersPosition.y = 0;
	//layersAnchor.x = 0;
	//layersAnchor.y = 0;

	if (theAnimation->assets != NULL) {
		//EM_ASM({console.log("ASSETS found");});
		prepAssets(theAnimation->assets);
	}
	if (theAnimation->layers != NULL) {
		//EM_ASM({console.log("ANIMLAYERS found");});
		prepLayers(theAnimation->layers);
	}
	//EM_ASM({console.log("ALL done");});

	return 1;
}

