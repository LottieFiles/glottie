
int prepVAO(GLfloat* vertices, unsigned int* indices, int shaderRef) {
	int refIndex = lastRefIndex + 1;

	GLuint tvao, tvbo, tibo;
	glGenVertexArraysOES(1, &tvao);
	glBindVertexArrayOES(tvao);

	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &tibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tibo);

	GLuint tempShaderProgram;
	if (shaderRef == 0) {
		tempShaderProgram = mainShader;
	} else {
		tempShaderProgram = *shaderProgram[shaderRef];
	}
	GLint tempPosAttrib = glGetAttribLocation(tempShaderProgram, "position");
	glEnableVertexAttribArray(tempPosAttrib);
	glVertexAttribPointer(tempPosAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	*(posAttrib + refIndex) = &tempPosAttrib;

	*(vao + refIndex) = &tvao;
	*(vbo + refIndex) = &tvbo;
	*(ibo + refIndex) = &tibo;
	glBindVertexArrayOES(0);

	return refIndex;
}

unsigned int* prepTriangulate(GLfloat* passedVertices, int count) {
	unsigned int* tempIndex = new unsigned int[count];
	for (int i = 0; i < count; i++) {
		*(tempIndex + i) = i;
	}
	return tempIndex;
}

int prepPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp) {
	if (passedPropertiesShapeProp == NULL) {
		return 0;
	}
	passedPropertiesShapeProp = passedPropertiesShapeProp->start;
	bool exhausted = false;
	while (! exhausted) {
		passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->i_count);
		passedPropertiesShapeProp->gl_i_idx = prepTriangulate(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->i_count);
		passedPropertiesShapeProp->refIndex_i = prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, 0);

		passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->o_count);
		passedPropertiesShapeProp->gl_o_idx = prepTriangulate(passedPropertiesShapeProp->gl_o, passedPropertiesShapeProp->o_count);
		passedPropertiesShapeProp->refIndex_o = prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, 0);

		passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->v_count);
		passedPropertiesShapeProp->gl_v_idx = prepTriangulate(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->v_count);
		passedPropertiesShapeProp->refIndex_v = prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, 0);

		if (passedPropertiesShapeProp->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp = passedPropertiesShapeProp->next;
		}
	}
	return 1;
}

int prepShapesItem(struct ShapesItem* passedShapesItem) {
	if (passedShapesItem->ks != NULL) {
		if (passedShapesItem->ks->isKeyframe) {
			prepPropertiesShapeProp(passedShapesItem->ks->keyframe->s);
			prepPropertiesShapeProp(passedShapesItem->ks->keyframe->e);
		} else {
			prepPropertiesShapeProp(passedShapesItem->ks->k);
		}
	}

	return 1;
}

int prepLayers(struct Layers* passedLayers) {
	if (passedLayers->shapes == NULL) {
		return 0;
	}
	passedLayers = passedLayers->start;
	bool exhausted = false;
	while (! exhausted) {
		prepShapesItem(passedLayers->shapes);
		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			passedLayers = passedLayers->next;
		}
	}

	return 1;
}

int prepAssets(struct Assets* passedAssets) {
	if (passedAssets == NULL) {
		return 0;
	}
	passedAssets = passedAssets->start;
	bool exhausted = false;
	while (! exhausted) {
		prepLayers(passedAssets->precomps);
		if (passedAssets->next == NULL) {
			exhausted = true;
		} else {
			passedAssets = passedAssets->next;
		}
	}
}

int prepShapes() {

	if (theAnimation->assets != NULL) {
		prepAssets(theAnimation->assets);
	}
	if (theAnimation->layers != NULL) {
		prepLayers(theAnimation->layers);
	}

	return 1;
}

