
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * passedBuffers->idxCount, indices, GL_STATIC_DRAW);
	EM_ASM({console.log("VAO 1.1.3.2");});
	passedBuffers->posAttrib = &tempPosAttrib;
	EM_ASM({console.log("VAO 1.2");});

	passedBuffers->vao = &tvao;
	passedBuffers->vbo = &tvbo;
	passedBuffers->ibo = &tibo;
	passedBuffers->idx = indices; 
	glBindVertexArrayOES(0);
		EM_ASM({console.log("done prepping");});

	return refIndex;
}

struct Dimensions* findDimensions(GLfloat *passedVertices, int count) {
	bool exhausted = false;
	struct Dimensions* passedDimensions;
	passedDimensions = new Dimensions;

	for (int i=0; i < count; i++) {
		EM_ASM({console.log("finddim 1.1");});
		GLfloat currX = *(passedVertices + (i * 4));
		GLfloat currY = *(passedVertices + ((i * 4) + 1));
		EM_ASM({console.log("finddim 1.2");});
		if (currX > passedDimensions->maxXval) {
			passedDimensions->maxXval = currX;
			passedDimensions->maxXord = i;
		}
		if (currX < passedDimensions->minXval) {
			passedDimensions->minXval = currX;
			passedDimensions->minXord = i;
		}
		EM_ASM({console.log("finddim 1.4");});
		if (currY > passedDimensions->maxYval) {
			passedDimensions->maxYval = currY;
			passedDimensions->maxYord = i;
		}
		EM_ASM({console.log("finddim 1.5");});
		if (currY < passedDimensions->minYval) {
			EM_ASM({console.log("finddim 1.5.1");});
			passedDimensions->minYval = currY;
			EM_ASM({console.log("finddim 1.5.2");});
			passedDimensions->minYord = i;
			EM_ASM({console.log("finddim 1.5.3");});
		}
		//EM_ASM_({console.log("finddim 1.3 " + $0 + " " + $1);}, passedDimensions->maxXval, passedDimensions->maxXord);
	}
	EM_ASM({console.log("finddim 2");});
	return passedDimensions;
}

unsigned int* prepTriangulate(GLfloat* passedVertices, int count, struct Buffers* passedBuffers) {
	struct Dimensions* dimensions;
	
	EM_ASM({console.log("pretri 1.1");});
	if (passedBuffers->changed || passedBuffers->dimensions == NULL) {
		EM_ASM({console.log("pretri 1.2");});
		dimensions = findDimensions(passedVertices, count);
		EM_ASM({console.log("pretri 1.3");});
		EM_ASM({console.log("pretri 1.4");});
		passedBuffers->dimensions = dimensions;
		EM_ASM({console.log("pretri 1.5");});
		passedBuffers->changed = false;
	} else {
		dimensions = passedBuffers->dimensions;
	}

	int idxCount = 6; // to be replaced with actual count

	EM_ASM({console.log("pretri 2.1");});
	unsigned int* tempIndex;
	tempIndex = new unsigned int[6];
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

	passedBuffers->idxCount = idxCount;

	return tempIndex;
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

	while (! exhausted) {
		if (passedPropertiesShapeProp->i != NULL) {
			if (passedPropertiesShapeProp->buffers_i == NULL) {
				passedPropertiesShapeProp->buffers_i = newBuffers();
			}
			passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->i_count);
			EM_ASM({console.log("looping 1.1");});
			passedPropertiesShapeProp->gl_i_idx = prepTriangulate(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->i_count, passedPropertiesShapeProp->buffers_i);
			EM_ASM({console.log("looping 1.1.1");});
			prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, NULL, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i_count);
			EM_ASM({console.log("looping 1.1.2");});
		}

		if (passedPropertiesShapeProp->o != NULL) {
			if (passedPropertiesShapeProp->buffers_o == NULL) {
				passedPropertiesShapeProp->buffers_o = newBuffers();
			}
			passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->o_count);
			EM_ASM({console.log("looping 1.1");});
			passedPropertiesShapeProp->gl_o_idx = prepTriangulate(passedPropertiesShapeProp->gl_o, passedPropertiesShapeProp->o_count, passedPropertiesShapeProp->buffers_o);
			EM_ASM({console.log("looping 1.1.1");});
			prepVAO(passedPropertiesShapeProp->gl_o, passedPropertiesShapeProp->gl_o_idx, NULL, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o_count);
			EM_ASM({console.log("looping 1.1.2");});
		}

		if (passedPropertiesShapeProp->v != NULL) {
			if (passedPropertiesShapeProp->buffers_v == NULL) {
				passedPropertiesShapeProp->buffers_v = newBuffers();
			}
			passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->v_count);
			EM_ASM({console.log("looping 1.1");});
			passedPropertiesShapeProp->gl_v_idx = prepTriangulate(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v);
			EM_ASM({console.log("looping 1.1.1");});
			prepVAO(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->gl_v_idx, NULL, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v_count);
			EM_ASM({console.log("looping 1.1.2");});
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

