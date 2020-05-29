struct alignas(ALIGNSIZE) TransformMatrix {
	struct TransformMatrix* start = NULL;
	struct TransformMatrix* prev = NULL;
	struct TransformMatrix* next = NULL; 
	
	glm::mat4 transform = glm::mat4(1.0f);
} *defaultTransformMatrix = NULL;

struct alignas(ALIGNSIZE) CompositeArray {
	struct CompositeArray* start = NULL;
	struct CompositeArray* prev = NULL;
	struct CompositeArray* next = NULL;

	//struct TransformMatrix* position = NULL;
	//struct TransformMatrix* scale = NULL;
	glm::mat4 position = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	float opacity;

	int frame = -1;
};

struct alignas(ALIGNSIZE) Transform {
	struct TransformAOV* p = NULL;
	struct TransformAOV* r = NULL;
	struct TransformAOV* s = NULL;
	struct TransformAOV* o = NULL;

	struct CompositeArray* composite = NULL;

	int startTime = -1;
	int endTime = -1;
};

struct alignas(ALIGNSIZE) TransformAOV {
	struct ArrayOfVertex* v = NULL;
	struct ArrayOfVertex* i = NULL;
	struct ArrayOfVertex* o = NULL;

	struct TransformMatrix* transformMatrix = NULL;

	int startTime = -1;
	int endTime = -1;
	float* frames;
	float* segSize;
	int v_count = 0;
	int bezier_count = 0;
	int s_count;
};

struct TransformAOV* createSegment() {
}

struct TransformAOV* createSegmentValue(struct PropertiesValueKeyframe* passedKeyframe) {
}

struct TransformAOV* createSegmentP(struct PropertiesOffsetKeyframe* passedKeyframe, struct BoundingBox* currentBB, int type) {
	bool exhausted = false;
	struct TransformAOV* tempAOV = NULL;
	tempAOV = new TransformAOV;
	float previousTime = 0;
	tempAOV->frames = new float[passedKeyframe->s_count];
	tempAOV->segSize = new float[passedKeyframe->s_count];
	tempAOV->startTime = passedKeyframe->t * theAnimation->frMultiplier;
	//EM_ASM_({console.log("1---> " + $0 + " " + $1);}, passedKeyframe->t, passedKeyframe->s_count);
	float w, h, z;
	w = theAnimation->w;
	h = theAnimation->h;
	if (theAnimation->z != 0) {
		z = theAnimation->z;
	} else {
		z = 1;
	}
	struct ReturnPosition* tempPos = getRelativePosition(currentBB, NULL);
	float tempX = tempPos->layers->x;
	float tempY = tempPos->layers->y;
	float tempZ = tempPos->layers->z;
	float _1, _2, _3, _4;
	while (! exhausted) {
		_4 = 1.0f;
		if (passedKeyframe->s_count == 1) {
			if (type == 1) {
				_1 = ((((*(passedKeyframe->s + 0) + tempX) * theAnimation->scaleFactorX) / w));
				_2 = 0.0f;
				_3 = 0.0f;
			} else if (type == 2) {
				_1 = *(passedKeyframe->s + 0) / 100;
				_2 = 1.0f;
				_3 = 1.0f;
			}
		} else if (passedKeyframe->s_count == 2) {
			if (type == 1) {
				_1 = ((((*(passedKeyframe->s + 0) + tempX) * theAnimation->scaleFactorX) / w));
				_2 = ((((*(passedKeyframe->s + 1) + tempY) * theAnimation->scaleFactorY) / h)) * -1;
				_3 = 0.0f;
			} else if (type == 2) {
				_1 = *(passedKeyframe->s + 0) / 100;
				_2 = *(passedKeyframe->s + 1) / 100;
				_3 = 1.0f;
			}
		} else if (passedKeyframe->s_count == 3) {
			if (type == 1) {
				_1 = ((((*(passedKeyframe->s + 0) + tempX) * theAnimation->scaleFactorX) / w));
				_2 = ((((*(passedKeyframe->s + 1) + tempY) * theAnimation->scaleFactorY) / h)) * -1;
				_3 = (((*(passedKeyframe->s + 3) + tempZ) * theAnimation->scaleFactorZ) / z);
			} else if (type == 2) {
				_1 = *(passedKeyframe->s + 0) / 100;
				_2 = *(passedKeyframe->s + 1) / 100;
				_3 = *(passedKeyframe->s + 2) / 100;
			}
			EM_ASM_({console.log("4---> " + $0 + " " + $1 + " " + $2);}, *(passedKeyframe->s + 0), passedKeyframe->s_count, type);
		} 
		
		float currentList[4] = {_1, _2, _3, _4};
		tempAOV->v = pushVertex(tempAOV->v, currentList);

		tempAOV->v_count++;

		if (passedKeyframe->i != NULL) {
			float currentList[4] = {*(passedKeyframe->i->x + 0), *(passedKeyframe->i->y + 0), 0, 1};
			tempAOV->i = pushVertex(tempAOV->i, currentList);
		} else {
			float currentList[4] = {0, 0, 0, 0};
			tempAOV->i = pushVertex(tempAOV->i, currentList);
		}

		if (passedKeyframe->o != NULL) {
			float currentList[4] = {*(passedKeyframe->o->x + 0), *(passedKeyframe->o->y + 0), 0, 1};
			tempAOV->o = pushVertex(tempAOV->o, currentList);
		} else {
			float currentList[4] = {0, 0, 0, 0};
			tempAOV->o = pushVertex(tempAOV->o, currentList);
		}

		if (previousTime != 0) {
			*(tempAOV->frames + (tempAOV->v_count - 1)) = (passedKeyframe->t * theAnimation->frMultiplier) - (previousTime * theAnimation->frMultiplier);
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / (*(tempAOV->frames + (tempAOV->v_count - 1)) - 1);
		} else {
			*(tempAOV->frames + (tempAOV->v_count - 1)) = 1;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 0;
		}
		EM_ASM_({console.log("----> v: " + $0 + "/" + $1 + " -- frames: " + $2 + ", segsize: " + $3 + " -- start " + $4 + " vcount: " + $5 + "  i: " + $6 + "/" + $7 + "  o: " + $8 + "/" + $9);}, tempAOV->v->vertex->x, tempAOV->v->vertex->y, *(tempAOV->frames + (tempAOV->v_count - 1)), *(tempAOV->segSize + (tempAOV->v_count - 1)), tempAOV->startTime, tempAOV->v_count, tempAOV->i->vertex->x, tempAOV->i->vertex->y, tempAOV->o->vertex->x, tempAOV->o->vertex->y);
		previousTime = passedKeyframe->t;

		if (passedKeyframe->next == NULL) {
			exhausted = true;
		} else {
			passedKeyframe = passedKeyframe->next;
		}
	}
	tempAOV->s_count = passedKeyframe->s_count;
	tempAOV->v->next = tempAOV->v->start;
	tempAOV->i->next = tempAOV->i->start;
	tempAOV->o->next = tempAOV->o->start;
	tempAOV->v->start->prev = tempAOV->v;
	tempAOV->i->start->prev = tempAOV->i;
	tempAOV->o->start->prev = tempAOV->o;
	EM_ASM_({console.log("1----------------> " + $0 + " " + $1);}, passedKeyframe->t, passedKeyframe->s_count);

	if (tempAOV->startTime > previousTime || tempAOV->v_count == 1) {
		tempAOV->endTime = tempAOV->startTime;
	} else {
		tempAOV->endTime = previousTime * theAnimation->frMultiplier;
	}
	return tempAOV;
}

struct TransformMatrix* newTransformMatrix(struct TransformMatrix* passedTransformMatrix) {
	if (passedTransformMatrix == NULL) {
		passedTransformMatrix = new TransformMatrix;
		passedTransformMatrix->start = passedTransformMatrix;
	} else {
		passedTransformMatrix->next = new TransformMatrix;
		passedTransformMatrix->next->prev = passedTransformMatrix;
		passedTransformMatrix->next->start = passedTransformMatrix->start;
		passedTransformMatrix = passedTransformMatrix->next;
	}
	return passedTransformMatrix;
}

glm::mat4 generateMatrix(glm::mat4 identity, int type, float X, float Y, float Z, float angle) {
	switch (type) {
		case 1:
			return glm::translate(identity, glm::vec3(X, Y, Z));
			break;
		case 2:
			return glm::scale(identity, glm::vec3(X, Y, Z));
			break;
		case 3:
			return glm::translate(identity, glm::vec3(X, Y, Z));
			break;
	}
}

void fillAnimation(struct TransformAOV* passedAOV, int type) {
	passedAOV->v = passedAOV->v->start;
	bool exhausted = false;
	int currentIndex = 0;
	/*if (type == 1) {
		passedAOV->transformMatrix->transform = glm::mat4(1.0f);
	}*/
	while (! exhausted) {

		switch (type) {
			case 1:
				if (passedAOV->s_count >= 2) {
					passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
					passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, passedAOV->v->vertex->x, passedAOV->v->vertex->y, passedAOV->v->vertex->z, 0);
				}
				break;
			case 2:
				if (passedAOV->s_count >= 2) {
					passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
					passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, passedAOV->v->vertex->x, passedAOV->v->vertex->y, passedAOV->v->vertex->z, 0);
				}
			case 3:
				if (passedAOV->s_count >= 1) {
					passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
					passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, passedAOV->v->vertex->x, passedAOV->v->vertex->y, passedAOV->v->vertex->z, 0);
				}
				break;
		}

		currentIndex++;
		if (passedAOV->v->next == passedAOV->v->start) {
			exhausted = true;
		} else {
			passedAOV->v = passedAOV->v->next;
		}
	}
}

/*
	transform type,
		1: position
		2: scale
		3: rotate
		4: opacity
*/

struct CompositeArray* newCompositeArray(struct CompositeArray* passedCompositeArray, int frame) {
	if (passedCompositeArray == NULL) {
		passedCompositeArray = new CompositeArray;
		passedCompositeArray->start = passedCompositeArray;
	} else {
		passedCompositeArray->next = new CompositeArray;
		passedCompositeArray->next->prev = passedCompositeArray;
		passedCompositeArray->next->start = passedCompositeArray->start;
		passedCompositeArray = passedCompositeArray->next;
	}
	passedCompositeArray->frame = frame;
	return passedCompositeArray;
}

void fillCompositeAnimation(int minTime, int maxTime, struct Transform* passedTransform) {
	if (passedTransform->p != NULL && passedTransform->p->transformMatrix != NULL) {
		passedTransform->p->transformMatrix = passedTransform->p->transformMatrix->start;
	}
	if (passedTransform->s != NULL && passedTransform->s->transformMatrix != NULL) {
		passedTransform->s->transformMatrix = passedTransform->s->transformMatrix->start;
	}

	for (int i = minTime; i <= maxTime; i++) {
		if (passedTransform->composite == NULL) {
			passedTransform->composite = newCompositeArray(passedTransform->composite, i);
		} else {
			while (passedTransform->composite->next != NULL) {
				passedTransform->composite = passedTransform->composite->next;
			}
			if (passedTransform->composite->frame != i) {
				passedTransform->composite = newCompositeArray(passedTransform->composite, i);
			}
		}

		if (passedTransform->p != NULL && passedTransform->p->transformMatrix != NULL && passedTransform->p->startTime <= i && passedTransform->p->endTime >= i) {
			EM_ASM_({console.log("---------------===================TRANSFORM composite position ");});
			passedTransform->composite->position = passedTransform->composite->position * passedTransform->p->transformMatrix->transform;
			passedTransform->composite->frame = i;
			if (passedTransform->p->transformMatrix->next != NULL) {
				passedTransform->p->transformMatrix = passedTransform->p->transformMatrix->next;
			}
		}
		if (passedTransform->s != NULL && passedTransform->s->transformMatrix != NULL && passedTransform->s->startTime <= i && passedTransform->s->endTime >= i) {
			EM_ASM_({console.log("---------------===================TRANSFORM composite scale ");});
			passedTransform->composite->scale = passedTransform->composite->scale * passedTransform->s->transformMatrix->transform;
			passedTransform->composite->frame = i;
			//passedTransform->composite->scale = passedTransform->s->transformMatrix;
			if (passedTransform->s->transformMatrix->next != NULL) {
				passedTransform->s->transformMatrix = passedTransform->s->transformMatrix->next;
			}
		}

	}
	passedTransform->startTime = minTime;
	passedTransform->endTime = maxTime;
	
	EM_ASM_({console.log("---------------===================TRANSFORM composite done ");});
}

struct Transform* fillTransformShapes(struct ShapesItem* passedShapesItem, struct BoundingBox* currentBB) {
	if (defaultTransformMatrix == NULL) {
		defaultTransformMatrix = new TransformMatrix;
	}
	int minTime = -1;
	int maxTime = -1;
	struct TransformAOV* tempAOV = NULL;
	if (passedShapesItem->transform == NULL) {
		passedShapesItem->transform = new Transform;
	}
	if (passedShapesItem->p != NULL && passedShapesItem->p->keyframe != NULL) {
		EM_ASM_({console.log("---------------===================TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedShapesItem->p->keyframe->start, currentBB, 1);
		passedShapesItem->transform->p = tempAOV;
		if (tempAOV->v_count > 1) {
			EM_ASM_({console.log("=================================POSITION v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false);
		}
		fillAnimation(passedShapesItem->transform->p, 1);
		EM_ASM_({console.log("---------------===================TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (passedShapesItem->s != NULL && passedShapesItem->s->keyframe != NULL) {
		EM_ASM_({console.log("---------------===================SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedShapesItem->s->keyframe->start, currentBB, 2);
		passedShapesItem->transform->s = tempAOV;
		if (tempAOV->v_count > 1) {
			EM_ASM_({console.log("=================================SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false);
		}
		fillAnimation(passedShapesItem->transform->s, 2);
		EM_ASM_({console.log("---------------===================SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (maxTime > minTime) {
		fillCompositeAnimation(minTime, maxTime, passedShapesItem->transform);
	}
	EM_ASM_({console.log("---------------===================TRANSFORM done ");});

	return passedShapesItem->transform;
}

struct Transform* fillTransformLayers(struct Layers* passedLayers, struct BoundingBox* currentBB) {
	if (defaultTransformMatrix == NULL) {
		defaultTransformMatrix = new TransformMatrix;
	}
	int minTime = -1;
	int maxTime = -1;
	struct TransformAOV* tempAOV = NULL;
	if (passedLayers->transform == NULL) {
		passedLayers->transform = new Transform;
	}
	if (passedLayers->ks != NULL && passedLayers->ks->p != NULL && passedLayers->ks->p->keyframe != NULL) {
		EM_ASM_({console.log("=================================LAYERS TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedLayers->ks->p->keyframe->start, currentBB, 1);
		passedLayers->transform->p = tempAOV;
		if (tempAOV->v_count > 1) {
			EM_ASM_({console.log("=================================LAYERS POSITION v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false);
		}
		fillAnimation(passedLayers->transform->p, 1);
		EM_ASM_({console.log("=================================LAYERS TRANSFORM ENDS ");});
		minTime = tempAOV->startTime;
		maxTime = tempAOV->endTime;
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (passedLayers->ks != NULL && passedLayers->ks->s != NULL && passedLayers->ks->s->keyframe != NULL) {
		EM_ASM_({console.log("=================================LAYERS SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedLayers->ks->s->keyframe->start, currentBB, 2);
		passedLayers->transform->s = tempAOV;
		if (tempAOV->v_count > 1) {
			EM_ASM_({console.log("=================================LAYERS SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false);
		}
		fillAnimation(passedLayers->transform->s, 2);
		EM_ASM_({console.log("=================================LAYERS SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (maxTime > minTime) {
		fillCompositeAnimation(minTime, maxTime, passedLayers->transform);
	}
	EM_ASM_({console.log("---------------===================TRANSFORM done ");});

	return passedLayers->transform;
}

