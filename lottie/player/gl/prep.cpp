#include <array>
#include "../external/earcut.hpp"

	struct alignas(ALIGNSIZE) IntPoint {
		int64_t X, Y;
	};
namespace mapbox {
namespace util {

template <>
struct alignas(ALIGNSIZE) nth<0, IntPoint> {
    inline static auto get(const IntPoint &t) {
        return t.X;
    };
};
template <>
struct alignas(ALIGNSIZE) nth<1, IntPoint> {
    inline static auto get(const IntPoint &t) {
        return t.Y;
    };
};

} // namespace util
} // namespace mapbox

struct TriangulateReturn* prepTriangulate(int count, struct Buffers* passedBuffers, struct ArrayOfVertex* passedArray, float* defaultFill, int order) {
	struct TriangulateReturn* tempTriangulate;
	tempTriangulate = new TriangulateReturn;
	using Coord = double;
	using N = uint32_t;
	using Point = std::array<Coord, 2>;


	
	EM_ASM({console.log("attempting to add tempPoint 0.1");});
	std::vector<std::vector<IntPoint>> polygon;
	//alignas(ALIGNSIZE) std::vector<std::vector<IntPoint>> polygon;
	EM_ASM({console.log("attempting to add tempPoint 0.2");});
	//alignas(ALIGNSIZE) std::array<Coord, 2> tempPoint;
	struct IntPoint* tempPoint = new IntPoint();
	
	EM_ASM({console.log("attempting to add tempPoint 0.3");});
	polygon.reserve(1);
	polygon[0].reserve(count + 2);

	EM_ASM({console.log("attempting to add tempPoint 0.4");});
	bool exhausted = false;
	passedArray = passedArray->start;
	GLfloat* tempVBO = new GLfloat[count * 4];
	GLfloat* tempCBO = new GLfloat[count * 4];
	EM_ASM({console.log("attempting to add tempPoint 1");});
	unsigned int* tempIndex = new unsigned int[count * 3];
	EM_ASM({console.log("attempting to add tempPoint 2");});
	int Bcounter = 0;
	tempPoint->X = (double)passedArray->vertex->position[0]*10000;
	tempPoint->Y = (double)passedArray->vertex->position[1]*10000;
	while (! exhausted) {

		EM_ASM({console.log("attempting to add tempPoint 1.1 " + $0);}, Bcounter);
		//tempPoint.X = (double)passedArray->vertex->position[0]*10000;
		//tempPoint.Y = (double)passedArray->vertex->position[1]*10000;
		tempPoint->X = (double)passedArray->vertex->position[0]*10000;
		tempPoint->Y = (double)passedArray->vertex->position[1]*10000;
		//tempPoint.at(0) = (double)passedArray->vertex->position[0]*10000;
		//tempPoint.at(1) = (double)passedArray->vertex->position[1]*10000;
		
		//polygon.at(Bcounter).push_back({(uint32_t)(passedArray->vertex->position[0]*10000), (uint32_t)(passedArray->vertex->position[0]*10000)});
	
		//polygon[0][Bcounter].reserve(1);	
		polygon[0].push_back(*tempPoint);
		EM_ASM({console.log("attempting to add tempPoint 1.3 " + $0);}, Bcounter);
		if (passedArray->vertex->position[2] == 0) {
			*(tempVBO + ((Bcounter * 4) + 2)) = 1 - ((float)order / 100000);
		} else {
			*(tempVBO + ((Bcounter * 4) + 2)) = passedArray->vertex->position[2];
		}
		*(tempVBO + ((Bcounter * 4) + 3)) = 1;

		*(tempCBO + ((Bcounter * 4) + 0)) = *(defaultFill + 0);
		*(tempCBO + ((Bcounter * 4) + 1)) = *(defaultFill + 1);
		*(tempCBO + ((Bcounter * 4) + 2)) = *(defaultFill + 2);
		*(tempCBO + ((Bcounter * 4) + 3)) = *(defaultFill + 3);
		Bcounter++;
		if (passedArray->next == passedArray->start) {
			exhausted = true;
		} else {
			passedArray = passedArray->next;
		}
	}
	EM_ASM({console.log("attempting to add tempPoint 1.4");});
	std::vector<N> indices;
	indices.reserve(count * 3);
	indices = mapbox::earcut<N>(polygon);
	EM_ASM({console.log("attempting to add tempPoint 1.5");});
	for (int i = 0; i < Bcounter; i++) {
		EM_ASM({console.log("attempting to add tempPoint 3 " + $0);}, i);
		*(tempVBO + ((Bcounter * 4) + 0)) = (2 * ((float)(polygon[0][i]).X / 10000)) / theAnimation->w;
		*(tempVBO + ((Bcounter * 4) + 1)) = (2 * ((float)(polygon[0][i]).Y / 10000)) / theAnimation->h;
		//*(tempVBO + ((Bcounter * 4) + 0)) = (2 * ((float)(polygon[0][i])[0] / 10000)) / theAnimation->w;
		//*(tempVBO + ((Bcounter * 4) + 1)) = (2 * ((float)(polygon[0][i])[1] / 10000)) / theAnimation->h;
	}
	
	for (int i = 0; i < indices.size(); i++) {
		*(tempIndex + i) = indices[i];
	}
	tempTriangulate->vbo = tempVBO;
	tempTriangulate->cbo = tempCBO;
	tempTriangulate->index = tempIndex;
	return tempTriangulate;
}

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

int prepVAO(GLfloat* vertices, unsigned int* indices, GLfloat* colors, struct ShaderProgram* passedShaderProgram, struct Buffers* passedBuffers, int count) {
	//EM_ASM_({console.log("VAO 1.0 " + $0 + " " + $1);}, count, passedBuffers->idxCount);
	int refIndex = lastRefIndex + 1;

	/*
	for (int i = 0; i < count * 4; i++) {
		//EM_ASM_({console.log("VBO " + $0);}, *(vertices + i));
	}
	for (int i = 0; i < passedBuffers->idxCount; i++) {
		//EM_ASM_({console.log("INDEX " + $1);}, *(indices + i));
	}
	*/

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * count * 4, vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexAttribPointer(tempPosAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &tcbo);
	glBindBuffer(GL_ARRAY_BUFFER, tcbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * count * 4, colors, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexAttribPointer(tempColAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	/*
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	*/


	glGenBuffers(1, &tibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * passedBuffers->idxCount, indices, GL_DYNAMIC_DRAW);



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

	//passedBuffers->vao = tvao;
	//passedBuffers->vbo = tvbo;
	//passedBuffers->ibo = tibo;

	passedBuffers->idx = indices; 
		//EM_ASM({console.log("done prepping " + $0 + " " + $1);}, tvao, *(passedBuffers->vao));
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
						*(tempFloat + 3) = *(tempShapesItem->c->k + 3);
					}
				} else {
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
	*(tempFloat + 0) = 1;
	*(tempFloat + 1) = 1;
	*(tempFloat + 2) = 1;
	*(tempFloat + 3) = 1;
	return tempFloat;
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

int prepPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp, struct ShapesItem* passedShapesItem) {
	if (passedPropertiesShapeProp == NULL) {
		return 0;
	}
	passedPropertiesShapeProp = passedPropertiesShapeProp->start;
	bool exhausted = false;
	struct TriangulateReturn* tempTriangulateReturn;


	while (! exhausted) {
		float* defaultFill = getFill(passedShapesItem);

		//EM_ASM({console.log("tracing 1 ");});
		//EM_ASM({console.log("looping 1");});
		if (passedPropertiesShapeProp->i != NULL) {
			passedPropertiesShapeProp->buffers_i = newBuffers();
			//passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->i_count);
			//EM_ASM({console.log("looping 1.1 i");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->i_count, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i, defaultFill, passedShapesItem->order);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_i = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_i_fill = tempTriangulateReturn->cbo;
			passedPropertiesShapeProp->gl_i_idx = tempTriangulateReturn->index;
			//delete tempTriangulateReturn;
			//EM_ASM({console.log("looping 1.1.1 i");});
			prepVAO(passedPropertiesShapeProp->gl_i, passedPropertiesShapeProp->gl_i_idx, passedPropertiesShapeProp->gl_i_fill, NULL, passedPropertiesShapeProp->buffers_i, passedPropertiesShapeProp->i_count);
			//EM_ASM({console.log("looping 1.1.2 i");});
		}

		//EM_ASM({console.log("tracing 2 ");});
		if (passedPropertiesShapeProp->o != NULL) {
			passedPropertiesShapeProp->buffers_o = newBuffers();
			//passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->o_count);
			//EM_ASM({console.log("looping 1.1 o");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->o_count, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o, defaultFill, passedShapesItem->order);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_o = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_o_fill = tempTriangulateReturn->cbo;
			passedPropertiesShapeProp->gl_o_idx = tempTriangulateReturn->index;
			//delete tempTriangulateReturn;
			//EM_ASM({console.log("looping 1.1.1 o");});
			//EM_ASM({console.log("looping 1.2 o");});
			prepVAO(passedPropertiesShapeProp->gl_o, passedPropertiesShapeProp->gl_o_idx, passedPropertiesShapeProp->gl_o_fill, NULL, passedPropertiesShapeProp->buffers_o, passedPropertiesShapeProp->o_count);
			//EM_ASM({console.log("looping 1.1.2 o");});
		}

		//EM_ASM({console.log("tracing 3 ");});
		if (passedPropertiesShapeProp->v != NULL) {
			passedPropertiesShapeProp->buffers_v = newBuffers();
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->v_count);
			//EM_ASM({console.log("looping 1.1 v");});
			tempTriangulateReturn = prepTriangulate(passedPropertiesShapeProp->v_count, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v, defaultFill, passedShapesItem->order);
			if (tempTriangulateReturn == NULL) {return 0;}
			passedPropertiesShapeProp->gl_v = tempTriangulateReturn->vbo;
			passedPropertiesShapeProp->gl_v_fill = tempTriangulateReturn->cbo;
			passedPropertiesShapeProp->gl_v_idx = tempTriangulateReturn->index;
			//delete tempTriangulateReturn;
			//EM_ASM({console.log("looping 1.1.1 v");});
			prepVAO(passedPropertiesShapeProp->gl_v, passedPropertiesShapeProp->gl_v_idx, passedPropertiesShapeProp->gl_v_fill, NULL, passedPropertiesShapeProp->buffers_v, passedPropertiesShapeProp->v_count);
			//EM_ASM({console.log("looping 1.1.2 v");});
		}

		delete tempTriangulateReturn;
		delete defaultFill;
		//EM_ASM({console.log("looping 1.4");});

		//EM_ASM({console.log("tracing 4 ");});
		if (passedPropertiesShapeProp->next == NULL) {
			exhausted = true;
		} else {
			passedPropertiesShapeProp = passedPropertiesShapeProp->next;
		}
	}
	//EM_ASM({console.log("all prep done");});
	
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
			//EM_ASM({console.log("SHAPEPROPKEYFRAME found");});
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->s, passedShapesItem);
			prepPropertiesShapeProp(passedPropertiesShape->keyframe->e, passedShapesItem);
		} else {
			//EM_ASM({console.log("SHAPEPROP found");});
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
	//EM_ASM({console.log("SHAPESITEM found pre 1.0");});
	if (passedShapesItem == NULL) {
		return 0;
	}
	bool exhausted = false;
	passedShapesItem = passedShapesItem->start;
	while (! exhausted) {
		//EM_ASM({console.log("SHAPESITEM found");});
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
	//EM_ASM({console.log("{{{{{{{{{{{{{{----------------------- LAYERS found pre 1.0");});
	if (passedLayers->shapes == NULL || passedLayers == NULL) {
		return 0;
	}
	//EM_ASM({console.log("LAYERS found pre 1.1");});
	passedLayers = passedLayers->start;
	bool exhausted = false;
	while (! exhausted) {
		if (passedLayers->shapes != NULL) {
			//EM_ASM({console.log("LAYERS found 1.0");});
			prepShapesItem(passedLayers->shapes);
		}
		if (passedLayers->next == NULL) {
			exhausted = true;
		} else {
			//EM_ASM({console.log("LAYERS found 1.1");});
			passedLayers = passedLayers->next;
		}
	}
	//EM_ASM({console.log("LAYERS found 1.2");});

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

