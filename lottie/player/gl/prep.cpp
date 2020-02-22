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
int prepVAO(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices, std::vector<GLfloat>& colors, struct ShaderProgram* passedShaderProgram, struct Buffers* passedBuffers, int count, int idxCount) {
	EM_ASM_({console.log("VAO 1.0 " + $0 + " " + $1);}, count, passedBuffers->idxCount);
	int refIndex = lastRefIndex + 1;

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

	EM_ASM_({console.log("--......--> done loading buffers " + $0 + " " + $1);}, idxCount, indices.size());

	//passedBuffers->vao = tvao;
	//passedBuffers->vbo = tvbo;
	//passedBuffers->ibo = tibo;

	passedBuffers->idx = indices;
	passedBuffers->idxCount = idxCount;
	glBindVertexArrayOES(0);

	return refIndex;
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
			EM_ASM({console.log("////-------> looking for color");});
			if (tempShapesItem->c != NULL) {
				if (tempShapesItem->c->k_count > 0) {
					EM_ASM_({console.log("////-------> color " + $0 + " " + $1 + " " + $2);}, *(tempShapesItem->c->k), *(tempShapesItem->c->k + 1), *(tempShapesItem->c->k + 2));
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
	EM_ASM({console.log("creating buffer 1.0 ");});
	tempBuffers = new Buffers;
	if (lastBuffersCreated == NULL) {
		tempBuffers->start = tempBuffers;
	} else {
		tempBuffers->start = lastBuffersCreated->start;
		lastBuffersCreated->next = tempBuffers;
		tempBuffers->prev = lastBuffersCreated;
	}
	lastBuffersCreated = tempBuffers;
	EM_ASM({console.log("buffer created ");});
	return lastBuffersCreated;
}

int prepPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp, struct ShapesItem* passedShapesItem) {
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

		/*
		EM_ASM({console.log("tracing 1 ");});
		EM_ASM({console.log("looping 1");});
		if (passedPropertiesShapeProp->i != NULL) {
			passedPropertiesShapeProp->buffers_i = newBuffers();
			//passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->i_count);
			EM_ASM({console.log("looping 1.1 i");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->i_count, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i, defaultFill, passedShapesItem->order);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_i = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_i_fill = tempTriangulateReturn->cbo;
			passedPropertiesShapeProp->gl_i_idx = tempTriangulateReturn->index;
			EM_ASM({console.log("looping 1.1.1 i");});
			prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, passedPropertiesShapeProp->gl_i_fill, NULL, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i_count, tempTriangulateReturn->idxCount);
			EM_ASM({console.log("looping 1.1.2 i");});
			EM_ASM({console.log("---------> stats " + $0 + " " + $1 + " " + $2 + " " + $3);}, *(tempTriangulateReturn->vbo + 0), *(tempTriangulateReturn->cbo + 0), *(tempTriangulateReturn->index + 0), tempTriangulateReturn->idxCount);
			delete tempTriangulateReturn;
		}

		EM_ASM({console.log("tracing 2 ");});
		if (passedPropertiesShapeProp->o != NULL) {
			passedPropertiesShapeProp->buffers_o = newBuffers();
			//passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->o_count);
			EM_ASM({console.log("looping 1.1 o");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->o_count, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o, defaultFill, passedShapesItem->order);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_o = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_o_fill = tempTriangulateReturn->cbo;
			passedPropertiesShapeProp->gl_o_idx = tempTriangulateReturn->index;
			EM_ASM({console.log("looping 1.1.1 o");});
			EM_ASM({console.log("looping 1.2 o");});
			prepVAO(passedPropertiesShapeProp->gl_o, passedPropertiesShapeProp->gl_o_idx, passedPropertiesShapeProp->gl_o_fill, NULL, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o_count, tempTriangulateReturn->idxCount);
			EM_ASM({console.log("looping 1.1.2 o");});
			EM_ASM({console.log("---------> stats " + $0 + " " + $1 + " " + $2 + " " + $3);}, *(tempTriangulateReturn->vbo + 0), *(tempTriangulateReturn->cbo + 0), *(tempTriangulateReturn->index + 0), tempTriangulateReturn->idxCount);
			delete tempTriangulateReturn;
		}
		*/

		EM_ASM({console.log("tracing 3 ");});
		if (passedPropertiesShapeProp->v != NULL) {
			passedPropertiesShapeProp->buffers_v = newBuffers();
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->v_count);
			EM_ASM({console.log("looping 1.1 v");});
			prepTriangulate(passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v, defaultFill, passedShapesItem->order, passedPropertiesShapeProp);
			EM_ASM({console.log("looping 1.1.0 v");});
			//if (tempTriangulateReturn == NULL) {return 0;}
			
			//passedPropertiesShapeProp->gl_v = tempTriangulateReturn->vbo;
			//passedPropertiesShapeProp->gl_v_fill = tempTriangulateReturn->cbo;
			//passedPropertiesShapeProp->gl_v_idx = tempTriangulateReturn->index;
			EM_ASM({console.log("looping 1.1.1 v");});
			//prepVAO(passedPropertiesShapeProp);
			prepVAO(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->gl_v_idx, passedPropertiesShapeProp->gl_v_fill, NULL, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v->idxCount);
			EM_ASM({console.log("looping 1.1.2 v " + $0);}, passedPropertiesShapeProp->gl_v.size());
			//delete tempTriangulateReturn;
		}

		//bezierNode = passedPropertiesShapeProp->gl_v;

			
		//if (elementCount == 1 || passedPropertiesShapeProp->next == NULL) {
//			EM_ASM({console.log("---------> stats " + $0 + " " + $1 + " " + $2 + " " + $3);}, *(tempTriangulateReturn->vbo + 0), *(tempTriangulateReturn->cbo + 0), *(tempTriangulateReturn->index + 0), tempTriangulateReturn->idxCount);
		//}
		//delete tempTriangulateReturn->vbo;
		//delete tempTriangulateReturn->cbo;
		//delete tempTriangulateReturn->index;
		EM_ASM({console.log("looping 1.4");});

		EM_ASM({console.log("tracing 4 ");});
		if (passedPropertiesShapeProp->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp = passedPropertiesShapeProp->next;
		}
	}
	delete defaultFill;
	EM_ASM({console.log("all prep done");});
	
	return 1;
}

int prepPropertiesShape(struct PropertiesShape* passedPropertiesShape, struct ShapesItem* passedShapesItem) {
	if (passedPropertiesShape == NULL) {
		return 0;
	}
	bool exhausted = false;
	passedPropertiesShape = passedPropertiesShape->start;
	while (! exhausted) {
		if (passedPropertiesShape->isKeyframe) {
			EM_ASM({console.log("SHAPEPROPKEYFRAME found");});
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->s, passedShapesItem);
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->e, passedShapesItem);
		} else {
			EM_ASM({console.log("SHAPEPROP found");});
			prepPropertiesShapeProp(passedPropertiesShape->k, passedShapesItem);
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
			prepPropertiesShape(passedShapesItem->ks, passedShapesItem);
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
	EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- LAYERS found pre 1.0");});
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
	EM_ASM({console.log("ASSETS found pre 1.1");});
	bool exhausted = false;
	while (! exhausted) {
		EM_ASM({console.log("PRECOMP found");});
		if (passedAssets->precomps != NULL) {
			prepLayers(passedAssets->precomps->start);
		}
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

