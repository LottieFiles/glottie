
struct BuffersList* newBuffersList(struct BuffersList* passedBuffersList, struct Buffers* passedBuffers) {
	if (passedBuffersList == NULL) {
		passedBuffersList = new BuffersList;
		passedBuffersList->start = passedBuffersList;
	} else {
		passedBuffersList->next = new BuffersList;
		passedBuffersList->next->prev = passedBuffersList;
		passedBuffersList->next->start = passedBuffersList->start;
		passedBuffersList = passedBuffersList->next;
	}
	passedBuffersList->buffers_v = passedBuffers;
	passedBuffersList->buffers_v->addedToComposition = true;

	return passedBuffersList;
}

struct TransformAOV* createSegmentR(struct PropertiesValueKeyframe* passedKeyframe, struct BoundingBox* currentBB, int type, bool layers) {
	bool exhausted = false;
	struct TransformAOV* tempAOV = NULL;
	tempAOV = new TransformAOV;
	float previousTime = 0;
	tempAOV->frames = new float[passedKeyframe->s_count];
	tempAOV->segSize = new float[passedKeyframe->s_count];
	tempAOV->startTime = passedKeyframe->t * theAnimation->lengthMultiplier;
	//EM_ASM_({console.log("1---> " + $0 + " " + $1);}, passedKeyframe->t, passedKeyframe->s_count);
	float w, h, z;
	w = theAnimation->w;
	h = theAnimation->h;
	if (theAnimation->z != 0) {
		z = theAnimation->z;
	} else {
		z = 1;
	}
	struct ReturnPosition* tempPos = getRelativePosition(currentBB, NULL, false);
	float tempX, tempY, tempZ;
	if (layers) {
		tempX = tempPos->layers->x;
		tempY = tempPos->layers->y;
		tempZ = tempPos->layers->z;
	} else {
		tempX = tempPos->shapes->x;
		tempY = tempPos->shapes->y;
		tempZ = tempPos->shapes->z;
	}
	float _1, _2, _3, _4;
	while (! exhausted) {
		_4 = 1.0f;
		if (passedKeyframe->s_count == 1) {
			if (type == 1) {
				_1 = *(passedKeyframe->s + 0);
				_2 = 0.0f;
				_3 = 0.0f;
			} else if (type == 2) {
				_1 = *(passedKeyframe->s + 0) / 100;
				_2 = 1.0f;
				_3 = 1.0f;
			}
		} else if (passedKeyframe->s_count == 2) {
			if (type == 1) {
				_1 = *(passedKeyframe->s + 0);
				_2 = *(passedKeyframe->s + 1);
				_3 = 0.0f;
			} else if (type == 2) {
				_1 = *(passedKeyframe->s + 0) / 100;
				_2 = *(passedKeyframe->s + 1) / 100;
				_3 = 1.0f;
			}
		} else if (passedKeyframe->s_count == 3) {
			if (type == 1) {
				_1 = *(passedKeyframe->s + 0);
				_2 = *(passedKeyframe->s + 1);
				_3 = *(passedKeyframe->s + 2);
			} else if (type == 2) {
				_1 = *(passedKeyframe->s + 0) / 100;
				_2 = *(passedKeyframe->s + 1) / 100;
				_3 = *(passedKeyframe->s + 2) / 100;
			}
			//EM_ASM_({console.log("4---> " + $0 + " " + $1 + " " + $2);}, *(passedKeyframe->s + 0), passedKeyframe->s_count, type);
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
			*(tempAOV->frames + (tempAOV->v_count - 1)) = (passedKeyframe->t * theAnimation->lengthMultiplier) - previousTime;
			if (*(tempAOV->frames + (tempAOV->v_count - 1)) >= 2) {
				*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / (*(tempAOV->frames + (tempAOV->v_count - 1)) - 1);
			} else {
				*(tempAOV->segSize + (tempAOV->v_count - 1)) = 0;
			}
			/*
			*(tempAOV->frames + (tempAOV->v_count - 1)) = (passedKeyframe->t * theAnimation->lengthMultiplier) - previousTime;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / (*(tempAOV->frames + (tempAOV->v_count - 1)) - 1);
			*/
		} else {
			*(tempAOV->frames + (tempAOV->v_count - 1)) = 1;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 0;
		}
		//EM_ASM_({console.log("----> v: " + $0 + "/" + $1 + " -- frames: " + $2 + ", segsize: " + $3 + " -- start " + $4 + " vcount: " + $5 + "  i: " + $6 + "/" + $7 + "  o: " + $8 + "/" + $9);}, tempAOV->v->vertex->x, tempAOV->v->vertex->y, *(tempAOV->frames + (tempAOV->v_count - 1)), *(tempAOV->segSize + (tempAOV->v_count - 1)), tempAOV->startTime, tempAOV->v_count, tempAOV->i->vertex->x, tempAOV->i->vertex->y, tempAOV->o->vertex->x, tempAOV->o->vertex->y);
		previousTime = passedKeyframe->t * theAnimation->lengthMultiplier;

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
	//EM_ASM_({console.log("1----------------> " + $0 + " " + $1);}, passedKeyframe->t * theAnimation->lengthMultiplier, passedKeyframe->s_count);

	if (tempAOV->startTime > previousTime || tempAOV->v_count == 1) {
		tempAOV->endTime = tempAOV->startTime;
	} else {
		tempAOV->endTime = previousTime;
	}
	return tempAOV;
}


struct TransformAOV* createSegmentP(struct PropertiesOffsetKeyframe* passedKeyframe, struct BoundingBox* currentBB, int type, bool layers) {
	bool exhausted = false;
	struct TransformAOV* tempAOV = NULL;
	tempAOV = new TransformAOV;
	float previousTime = 0;
	tempAOV->frames = new float[passedKeyframe->s_count];
	tempAOV->segSize = new float[passedKeyframe->s_count];
	tempAOV->startTime = passedKeyframe->t * theAnimation->lengthMultiplier;
	//EM_ASM_({console.log("1---> " + $0 + " " + $1);}, passedKeyframe->t, passedKeyframe->s_count);
	float w, h, z;
	w = theAnimation->w;
	h = theAnimation->h;
	if (theAnimation->z != 0) {
		z = theAnimation->z;
	} else {
		z = 1;
	}
	struct ReturnPosition* tempPos = getRelativePosition(currentBB, NULL, false);
	float tempX, tempY, tempZ;
	if (layers) {
		tempX = tempPos->layers->x;
		tempY = tempPos->layers->y;
		tempZ = tempPos->layers->z;
	} else {
		tempX = tempPos->shapes->x;
		tempY = tempPos->shapes->y;
		tempZ = tempPos->shapes->z;
	}
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
				_2 = *(passedKeyframe->s + 0) / 100;
				_3 = *(passedKeyframe->s + 0) / 100;
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
			//EM_ASM_({console.log("4---> " + $0 + " " + $1 + " " + $2);}, *(passedKeyframe->s + 0), passedKeyframe->s_count, type);
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
			*(tempAOV->frames + (tempAOV->v_count - 1)) = (passedKeyframe->t * theAnimation->lengthMultiplier) - previousTime;
			if (*(tempAOV->frames + (tempAOV->v_count - 1)) >= 2) {
				*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / (*(tempAOV->frames + (tempAOV->v_count - 1)) - 1);
			} else {
				*(tempAOV->segSize + (tempAOV->v_count - 1)) = 0;
			}
			/*
			*(tempAOV->frames + (tempAOV->v_count - 1)) = (passedKeyframe->t * theAnimation->lengthMultiplier) - previousTime;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / (*(tempAOV->frames + (tempAOV->v_count - 1)) - 1);
			*/
		} else {
			*(tempAOV->frames + (tempAOV->v_count - 1)) = 1;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 0;
		}
		//EM_ASM_({console.log("----> v: " + $0 + "/" + $1 + " -- frames: " + $2 + ", segsize: " + $3 + " -- start " + $4 + " vcount: " + $5 + "  i: " + $6 + "/" + $7 + "  o: " + $8 + "/" + $9);}, tempAOV->v->vertex->x, tempAOV->v->vertex->y, *(tempAOV->frames + (tempAOV->v_count - 1)), *(tempAOV->segSize + (tempAOV->v_count - 1)), tempAOV->startTime, tempAOV->v_count, tempAOV->i->vertex->x, tempAOV->i->vertex->y, tempAOV->o->vertex->x, tempAOV->o->vertex->y);
		previousTime = passedKeyframe->t * theAnimation->lengthMultiplier;

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
	//EM_ASM_({console.log("1----------------> " + $0 + " " + $1);}, (passedKeyframe->t * theAnimation->lengthMultiplier), passedKeyframe->s_count);

	if (tempAOV->startTime > previousTime || tempAOV->v_count == 1) {
		tempAOV->endTime = tempAOV->startTime;
	} else {
		tempAOV->endTime = previousTime;
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
			//return glm::rotate(identity, glm::radians(angle), glm::vec3(X, Y, 1.0f));
			return glm::rotate(identity, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
			break;
	}
}

void fillAnimation(struct TransformAOV* passedAOV, int type, struct BoundingBox* currentBB, bool layers) {
	passedAOV->v = passedAOV->v->start;
	bool exhausted = false;
	int currentIndex = 0;
	/*if (type == 1) {
		passedAOV->transformMatrix->transform = glm::mat4(1.0f);
	}*/
	while (! exhausted) {

		switch (type) {
			case 1: //translate
				if (passedAOV->s_count >= 2) {
					passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
					//passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, passedAOV->v->vertex->x, passedAOV->v->vertex->y, passedAOV->v->vertex->z, 0);
					passedAOV->transformMatrix->vector = glm::vec3(passedAOV->v->vertex->x, passedAOV->v->vertex->y, passedAOV->v->vertex->z);
					//passedAOV->isTranslate = true;
				}
				break;
			case 2: //scale
				if (passedAOV->s_count >= 2) {
					passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
					//passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, passedAOV->v->vertex->x, passedAOV->v->vertex->x, passedAOV->v->vertex->x, 0);
					passedAOV->transformMatrix->vector = glm::vec3(passedAOV->v->vertex->x, passedAOV->v->vertex->y, passedAOV->v->vertex->z);
					passedAOV->transformMatrix->inverseVector = glm::vec3((passedAOV->v->vertex->x * -1), (passedAOV->v->vertex->y * -1), (passedAOV->v->vertex->z * -1));
					//passedAOV->isScale = true;
				}
				break;
			case 3: //rotate
				if (passedAOV->s_count >= 1) {
					passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
					//struct ReturnPosition* tempPos = getRelativePosition(currentBB, NULL, false);
					//passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, currentBB->translatedX, currentBB->translatedY, 0.0f, passedAOV->v->vertex->x);
					passedAOV->transformMatrix->angle = passedAOV->v->vertex->x;
					//passedAOV->isRotate = true;
					/*
					if (layers) {
						passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, (currentBB->initY, tempPos->layers->x), (currentBB->initY + tempPos->layers->y), 1.0f, passedAOV->v->vertex->x);
					} else {
						passedAOV->transformMatrix->transform = generateMatrix(passedAOV->transformMatrix->transform, type, (tempPos->layers->x + tempPos->shapes->x), (tempPos->layers->y + tempPos->shapes->y), 1.0f, passedAOV->v->vertex->x);
					}
					*/
				}

				if (passedAOV->s_count >= 1) {
					passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
					passedAOV->transformMatrix->opacity = passedAOV->v->vertex->x;
					//EM_ASM_({console.log("========> OPACITY " + $0);}, passedAOV->v->vertex->x);

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

		passedCompositeArray->start->prev = passedCompositeArray->next;
		passedCompositeArray->next->next = passedCompositeArray->start;

		passedCompositeArray = passedCompositeArray->next;
	}
	passedCompositeArray->frame = frame;
	return passedCompositeArray;
}

struct VAOList* addCompositeVAO(struct VAOList* passedVAOL, GLuint* passedVAO, int idxSize, int passedFrame) {
	if (passedVAOL == NULL) {
		passedVAOL = new VAOList;
		passedVAOL->start = passedVAOL;
	} else {
		if (passedVAOL->assigned) {
			passedVAOL->next = new VAOList;
			passedVAOL->next->prev = passedVAOL;
			passedVAOL->next->start = passedVAOL->start;

			passedVAOL->start->prev = passedVAOL->next;
			passedVAOL->next->next = passedVAOL->start;

			passedVAOL = passedVAOL->next;
		}
	}
	if (passedVAO != NULL) {
		//EM_ASM({console.log("--- VAO properly added ");});
		passedVAOL->vao = passedVAO;
		passedVAOL->frame = passedFrame;
		passedVAOL->idxSize = idxSize;
		passedVAOL->assigned = true;
	}
	return passedVAOL;
}

struct FrameCompositionRef* addToSequence(struct FrameCompositionRef* passedSequence, int frame) {
	if (passedSequence == NULL) {
		passedSequence = new FrameCompositionRef;
		passedSequence->start = passedSequence;
	} else {
		passedSequence->next = new FrameCompositionRef;
		passedSequence->next->prev = passedSequence;
		passedSequence->next->start = passedSequence->start;
		passedSequence =  passedSequence->next;
	}

	passedSequence->frame = frame;

	return passedSequence;
}

void addToCompositionList(struct FrameCompositionRef* passedSequence, struct CompositeArray* passedArray) {
	if (passedSequence->compositionList == NULL) {
		passedSequence->compositionList = new CompositionList;
		passedSequence->compositionList->start = passedSequence->compositionList;
	} else {
		passedSequence->compositionList->next = new CompositionList;
		passedSequence->compositionList->next->prev = passedSequence->compositionList;
		passedSequence->compositionList->next->start = passedSequence->compositionList->start;

		passedSequence->compositionList->start->prev = passedSequence->compositionList->next;
		passedSequence->compositionList->next->next = passedSequence->compositionList->start;

		passedSequence->compositionList = passedSequence->compositionList->next;
	}

	if (passedArray != NULL) {
		//EM_ASM({console.log("--- new composition added to list");});
		passedSequence->compositionList->composite = passedArray;
	}
}

struct VAOList* iterateK(struct PropertiesShapeProp* passedK, struct VAOList* passedVAOL, int frame) {
	bool exhausted = false;
	while (! exhausted) {
		if (passedK != NULL && passedK->buffers_v != NULL && passedK->buffers_v->vao != NULL) {
			//EM_ASM({console.log("--- VAOL added ");});
			passedVAOL = addCompositeVAO(passedVAOL, passedK->buffers_v->vao, passedK->buffers_v->idx.size(), frame);
			if (passedVAOL->assigned) {
				passedK->buffers_v->addedToComposition = true;
			}
		}
		if (passedK->next == NULL) {
			exhausted = true;
		} else {
			passedK = passedK->next;
		}
	}
	return passedVAOL;
}

struct VAOList* iterateKS(struct PropertiesShape* passedKS, struct VAOList* passedVAOL, int frame) {
	//passedKS = passedKS->start;
	bool exhausted = false;
	while (! exhausted) {
		if (passedKS != NULL && passedKS->k != NULL) {
			//EM_ASM({console.log("--- VAOL iterateKS k found ");});
			passedVAOL = iterateK(passedKS->k->start, passedVAOL, frame);
		}
		if (passedKS->next == NULL) {
			exhausted = true;
		} else {
			passedKS = passedKS->next;
		}
	}
	return passedVAOL;
}

struct VAOList* iterateShapesItem(struct ShapesItem* passedShapesItem, struct VAOList* passedVAOL, int frame) {
	//passedShapesItem = passedShapesItem->start;
	bool exhausted = false;
	while (! exhausted) {
		if (passedShapesItem != NULL && passedShapesItem->it != NULL) {
			//EM_ASM({console.log("--- VAOL iterateShapesItem it found ");});
			passedVAOL = iterateShapesItem(passedShapesItem->it->start, passedVAOL, frame);
		}
		if (passedShapesItem != NULL && passedShapesItem->ks != NULL) {
			//EM_ASM({console.log("--- VAOL iterateShapesItem ks found ");});
			passedVAOL = iterateKS(passedShapesItem->ks->start, passedVAOL, frame);
		}
		if (passedShapesItem->next == NULL) {
			exhausted = true;
		} else {
			passedShapesItem = passedShapesItem->next;
		}
	}
	return passedVAOL;
}

void fillCompositeAnimation(int minTime, int maxTime, struct Transform* passedTransform, struct ShapesItem* passedShapesItem, bool isArray, bool isLayers) {
	bool pFound = false;
	bool sFound = false;
	bool rFound = false;
	bool oFound = false;
	if (passedTransform->p != NULL && passedTransform->p->transformMatrix != NULL) {
		pFound = true;
		passedTransform->p->transformMatrix = passedTransform->p->transformMatrix->start;
	}
	if (passedTransform->s != NULL && passedTransform->s->transformMatrix != NULL) {
		sFound = true;
		passedTransform->s->transformMatrix = passedTransform->s->transformMatrix->start;
	}
	if (passedTransform->r != NULL && passedTransform->r->transformMatrix != NULL) {
		rFound = true;
		passedTransform->r->transformMatrix = passedTransform->r->transformMatrix->start;
	}
	if (passedTransform->o != NULL && passedTransform->o->transformMatrix != NULL) {
		oFound = true;
		passedTransform->o->transformMatrix = passedTransform->o->transformMatrix->start;
	}

	int i = minTime;
	bool exhausted = false;
	bool pExhausted = false;
	bool sExhausted = false;
	bool rExhausted = false;
	bool oExhausted = false;
	bool pEnded = false;
	bool sEnded = false;
	bool rEnded = false;
	bool oEnded = false;
	bool pEndProcessed = false;
	bool sEndProcessed = false;
	bool rEndProcessed = false;
	bool oEndProcessed = false;
	//glm::mat4 tempP = glm::mat4(1.0f);
	//glm::mat4 tempR = glm::mat4(1.0f);
	//glm::mat4 tempS = glm::mat4(1.0f);
	float tempAngle;
	float tempOpacity;
	bool tempAngleFound, tempPFound, tempSFound;;
	//tempP = glm::mat4(1.0f);
	//tempR = glm::mat4(1.0f);
	//tempS = glm::mat4(1.0f);
	glm::vec3 tempPInverse = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 tempP = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 tempS = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 lastTempP = glm::vec3(0.0f);
	glm::mat4 lastTempRMatrix = glm::mat4(0.0f);
	glm::mat4 tempRMatrix = glm::mat4(1.0f);
	glm::mat4 tempSMatrix = glm::mat4(1.0f);
	glm::mat4 tempPMatrix = glm::mat4(1.0f);

	glm::quat rotateQuat;
	/*
	glm::mat4 previousPosition;
	bool previousPositionSet = false;

	glm::mat4 postRotateH;
	glm::vec3 postRotate;
	*/

	glm::mat4 identityMatrix = glm::mat4(1.0f);

	float sinHalfAngle;
	float cosHalfAngle;
	if (layersAnimationSequence != NULL) {
		layersAnimationSequence = layersAnimationSequence->start;
	}
	if (shapesAnimationSequence != NULL) {
		shapesAnimationSequence = shapesAnimationSequence->start;
	}

	bool firstCycleDone = false;
	while (! exhausted) {
		//EM_ASM_({console.log("---- CYCLE in ");});
		//tempAngleFound = false;
		tempPFound = false;
		tempSFound = false;

		if (passedTransform->composite == NULL) {
			passedTransform->composite = newCompositeArray(passedTransform->composite, i);
		} else {
			if (passedTransform->composite != passedTransform->composite->start) {
				while (passedTransform->composite->next != passedTransform->composite->start) {
					passedTransform->composite = passedTransform->composite->next;
				}
			}
			if (passedTransform->composite->frame != i) {
				passedTransform->composite = newCompositeArray(passedTransform->composite, i);
			}
		}

		if (pEnded && sEnded && rEnded && oEnded) {
			exhausted = true;
		}

		if (passedTransform->p != NULL && passedTransform->p->transformMatrix != NULL && passedTransform->p->startTime <= i && ! pEndProcessed) {
		//if (passedTransform->p != NULL && passedTransform->p->isTranslate && passedTransform->p->startTime <= i && ! pEndProcessed) {
			//EM_ASM_({console.log("---------------===================TRANSFORM composite position ");});
			//tempP = passedTransform->p->transformMatrix->transform;
			tempP = passedTransform->p->transformMatrix->vector;
			tempPInverse = passedTransform->p->transformMatrix->inverseVector;
			//passedTransform->composite->positionSet = true;
			pFound = true;
			tempPFound = true;
			if (pEnded) {
				pEndProcessed = true;
			}
			if (passedTransform->p->transformMatrix->next != NULL && passedTransform->p->transformMatrix->next != passedTransform->p->transformMatrix->start) {
				passedTransform->p->transformMatrix = passedTransform->p->transformMatrix->next;
				pEnded = false;
			} else {
				pEnded = true;
			}
		} else {
			if (! pFound) {
				pEnded = true;
			}
			if (i >= maxTime) {
				pExhausted = true;
			}
		}
		if (passedTransform->s != NULL && passedTransform->s->transformMatrix != NULL && passedTransform->s->startTime <= i && ! sEndProcessed) {
		//if (passedTransform->s != NULL && passedTransform->s->isScale && passedTransform->s->startTime <= i && ! sEnded) {
			//EM_ASM_({console.log("---------------===================TRANSFORM composite scale ");});
			//passedTransform->composite->transform = passedTransform->composite->transform * passedTransform->s->transformMatrix->transform;
			tempS = passedTransform->s->transformMatrix->vector;
			//passedTransform->composite->scaleSet = true;
			//passedTransform->composite->transformSet = true;
			//passedTransform->composite->frame = i;
			//tempS = passedTransform->s->transformMatrix->transform;
			sFound = true;
			tempSFound = true;
			if (sEnded) {
				sEndProcessed = true;
			}
			if (passedTransform->s->transformMatrix->next != NULL && passedTransform->s->transformMatrix->next != passedTransform->s->transformMatrix->start) {
				passedTransform->s->transformMatrix = passedTransform->s->transformMatrix->next;
				sEnded = false;
			} else {
				sEnded = true;
			}
		} else {
			if (! sFound) {
				sEnded = true;
			}
			if (i >= maxTime) {
				sExhausted = true;
			}
		}
		if (passedTransform->r != NULL && passedTransform->r->transformMatrix != NULL && passedTransform->r->startTime <= i && ! rEnded) {
		//if (passedTransform->r != NULL && passedTransform->r->isRotate && passedTransform->r->startTime <= i && ! rEnded) {
			//EM_ASM_({console.log("---------------===================TRANSFORM composite rotate ");});
			//passedTransform->composite->transform = passedTransform->composite->transform * passedTransform->r->transformMatrix->transform;
			//passedTransform->composite->rotateSet = true;
			//passedTransform->composite->transformSet = true;
			//passedTransform->composite->frame = i;
			//tempR = passedTransform->r->transformMatrix->transform;
			rFound = true;
			tempAngle = passedTransform->r->transformMatrix->angle;
			tempAngleFound = true;
			if (rEnded) {
				rEndProcessed = true;
			}
			if (passedTransform->r->transformMatrix->next != NULL && passedTransform->r->transformMatrix->next != passedTransform->r->transformMatrix->start) {
				passedTransform->r->transformMatrix = passedTransform->r->transformMatrix->next;
				rEnded = false;
			} else {
				rEnded = true;
			}
		} else {
			if (! rFound) {
				rEnded = true;
			}
			if (i >= maxTime) {
				rExhausted = true;
			}
		}
		if (passedTransform->o != NULL && passedTransform->o->transformMatrix != NULL && passedTransform->o->startTime <= i && ! oEnded) {
		//if (passedTransform->o != NULL && passedTransform->o->isRotate && passedTransform->o->startTime <= i && ! rEnded) {
			//EM_ASM_({console.log("---------------===================TRANSFORM composite rotate ");});
			//passedTransform->composite->transform = passedTransform->composite->transform * passedTransform->o->transformMatrix->transform;
			//passedTransform->composite->opacitySet = true;
			//passedTransform->composite->transformSet = true;
			//passedTransform->composite->frame = i;
			//tempR = passedTransform->o->transformMatrix->transform;
			oFound = true;
			tempOpacity = passedTransform->o->transformMatrix->opacity;
					//EM_ASM_({console.log("--------> OPACITY " + $0);}, tempOpacity);
			//tempAngleFound = true;
			if (oEnded) {
				oEndProcessed = true;
			}
			if (passedTransform->o->transformMatrix->next != NULL && passedTransform->o->transformMatrix->next != passedTransform->o->transformMatrix->start) {
				passedTransform->o->transformMatrix = passedTransform->o->transformMatrix->next;
				oEnded = false;
			} else {
				oEnded = true;
			}
		} else {
			if (! oFound) {
				oEnded = true;
			}
			if (i >= maxTime) {
				oExhausted = true;
			}
		}
			//if (tempAngleFound) {
			//	tempP = glm::rotate(tempP, glm::radians(tempAngle), glm::vec3(0.0f, 0.0f, 1.0f));
			//}
		passedTransform->composite->transform = glm::mat4(1.0f);


		if (rFound) {
			passedTransform->composite->rotateSet = true;

			//rotateQuat = glm::angleAxis(glm::radians(tempAngle), glm::vec3(0.0f, 0.0f, 1.0f));
			/*
			glm::quat rotateQuat(
					0,
					0,
					sin(glm::radians(tempAngle) / 2),
					cos(glm::radians(tempAngle) / 2)
				);
			tempRMatrix = glm::mat4_cast(rotateQuat) * identityMatrix;
			*/
			//tempRMatrix = glm::translate(identityMatrix, -lastTempP);
			tempRMatrix = glm::rotate(identityMatrix, glm::radians(tempAngle), glm::vec3(0.0f, 0.0f, 1.0f));
			//tempRMatrix = glm::translate(tempRMatrix, lastTempP);

			//lastTempP = tempP;

		}
		passedTransform->composite->rotate = tempRMatrix;

		if (sFound) {
			passedTransform->composite->scaleSet = true;
			tempSMatrix = glm::scale(identityMatrix, tempS);
			//passedTransform->composite->transform = glm::scale(passedTransform->composite->transform, tempS);
		}
		passedTransform->composite->scale = tempSMatrix;

		if (pFound) {
			passedTransform->composite->transformSet = true;
			tempPMatrix = glm::translate(identityMatrix, tempP);
			//passedTransform->composite->transform = glm::translate(passedTransform->composite->transform, tempP);
		}
		passedTransform->composite->transform = tempPMatrix;

		if (oFound) {
			passedTransform->composite->opacitySet = true;
		}

		passedTransform->composite->opacity = tempOpacity;
		//passedTransform->composite->transform = tempSMatrix * tempPMatrix;


		if (shapesAnimationSequence == NULL) {
			shapesAnimationSequence = addToSequence(shapesAnimationSequence, i);
		} else if (shapesAnimationSequence != NULL && shapesAnimationSequence->next == NULL) {
			shapesAnimationSequence = addToSequence(shapesAnimationSequence, i);
		} else {
			shapesAnimationSequence = shapesAnimationSequence->next;
		}

		if (layersAnimationSequence == NULL) {
			layersAnimationSequence = addToSequence(layersAnimationSequence, i);
		} else if (layersAnimationSequence != NULL && layersAnimationSequence->next == NULL) {
			layersAnimationSequence = addToSequence(layersAnimationSequence, i);
		} else {
			layersAnimationSequence = layersAnimationSequence->next;
		}

		if (passedTransform->composite->vaol == NULL) {
			passedTransform->composite->vaol = new VAOList;
			passedTransform->composite->vaol->start = passedTransform->composite->vaol;
		}

		if (rFound || sFound || pFound || oFound) {


			if (isArray) {
				iterateShapesItem(passedShapesItem, passedTransform->composite->vaol, i);
			} else {
				iterateKS(passedShapesItem->ks, passedTransform->composite->vaol, i);
			}

		}
		firstCycleDone = true;

		if (isLayers) {
			addToCompositionList(layersAnimationSequence, passedTransform->composite);
		} else {
			addToCompositionList(shapesAnimationSequence, passedTransform->composite);
		}


		/*
		if (tempAngleFound) {
			passedTransform->composite->transform = passedTransform->composite->transform * tempRMatrix;
		}
		*/
		
		//passedTransform->composite->transform = tempRMatrix * tempSMatrix *tempPMatrix;
		//passedTransform->composite->transform = tempRMatrix * tempSMatrix * tempPMatrix;
		//passedTransform->composite->rotateAngle = tempAngle;


			
			/*if (tempSFound) {
				passedTransform->composite->transform = tempS * tempP;
			} else {
				passedTransform->composite->transform = tempP;
			}*/
			//if (tempAngleFound) {
			//	passedTransform->composite->transform = glm::rotate(passedTransform->composite->transform, glm::radians(tempAngle), glm::vec3(0.0f, 0.0f, 1.0f));
			//}
			//passedTransform->composite->transform = tempS * tempP;
		if (pExhausted && sExhausted && rExhausted) {
			exhausted = true;
		}
		i++;

		//EM_ASM_({console.log("---- CYCLE out ");});
	}
	//EM_ASM_({console.log("---- CYCLE end ");});
	passedTransform->startTime = minTime;
	passedTransform->endTime = maxTime;
	
	//EM_ASM_({console.log("---------------===================TRANSFORM composite done ");});

	//buildVAO(passedTransform->composite->buffers, true);
}


/*
GLuint* unboundVAO;

void addBoundVAO(GLuint* passedVAO) {
	if (boundVAO == NULL) {
		boundVAO = new VAOList;
		boundVAO->start = boundVAO;
	} else {
		boundVAO->next = new VAOList;
		boundVAO->next->prev = boundVAO;
		boundVAO->next->start = boundVAO->start;
	}
	boundVAO->vao = passedVAO;
}

void buildVAO(struct Buffers* passedBuffers, bool addedToComposition) {
	passedBuffers = passedBuffers->start;
	bool exhausted = false;
	GLuint* vao;

	glGenVertexArraysOES(1, &vao);
       	glBindVertexArrayOES(vao);

	if (addedToComposition) {
		addBoundVAO(vao);
	} else {
		unboundVAO = vao;
	}

	while (! exhausted) {
		if (addedToComposition) {
			if (! passedBuffers->addedToComposition) {
			}
		} else {
			if (passedBuffers->addedToComposition) {
			}
		}
		
		if (passedBuffers == NULL) {
			exhausted = true;
		} else {
			passedBuffers = passedBuffers->next;
		}
	}

	if (addedToComposition) {
		
	} else {
	}
	glBindVertexArrayOES(0);
}
*/

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
		//EM_ASM_({console.log("---------------===================TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedShapesItem->p->keyframe->start, passedShapesItem->currentBB, 1, false);
		passedShapesItem->transform->p = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================POSITION v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 3);
		}
		fillAnimation(passedShapesItem->transform->p, 1, passedShapesItem->currentBB, false);
		//EM_ASM_({console.log("---------------===================TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (passedShapesItem->s != NULL && passedShapesItem->s->keyframe != NULL) {
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedShapesItem->s->keyframe->start, passedShapesItem->currentBB, 2, false);
		passedShapesItem->transform->s = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 3);
		}
		fillAnimation(passedShapesItem->transform->s, 2, passedShapesItem->currentBB, false);
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (passedShapesItem->r != NULL && passedShapesItem->r->keyframe != NULL && passedShapesItem->currentBB != NULL) {
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentR(passedShapesItem->r->keyframe->start, passedShapesItem->currentBB, 1, false);
		passedShapesItem->transform->r = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 1);
		}
		fillAnimation(passedShapesItem->transform->r, 3, passedShapesItem->currentBB, false);
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (passedShapesItem->o != NULL && passedShapesItem->o->keyframe != NULL && passedShapesItem->currentBB != NULL) {
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentR(passedShapesItem->o->keyframe->start, passedShapesItem->currentBB, 2, false);
		passedShapesItem->transform->o = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 1);
		}
		fillAnimation(passedShapesItem->transform->o, 4, passedShapesItem->currentBB, false);
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}

	if (maxTime > minTime) {
		fillCompositeAnimation(minTime, maxTime, passedShapesItem->transform, passedShapesItem, false, false);
	}
	//EM_ASM_({console.log("---------------===================TRANSFORM done ");});

	return passedShapesItem->transform;
}

struct FillTransformReturn* fillTransformLayers(struct Layers* passedLayers, struct BoundingBox* currentBB) {
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
		//EM_ASM_({console.log("=================================LAYERS TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedLayers->ks->p->keyframe->start, passedLayers->currentBB, 1, true);
		passedLayers->transform->p = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================LAYERS POSITION v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 3);
		}
		fillAnimation(passedLayers->transform->p, 1, passedLayers->currentBB, true);
		//EM_ASM_({console.log("=================================LAYERS TRANSFORM ENDS ");});
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
		//EM_ASM_({console.log("=================================LAYERS SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedLayers->ks->s->keyframe->start, passedLayers->currentBB, 2, true);
		passedLayers->transform->s = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================LAYERS SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 3);
		}
		fillAnimation(passedLayers->transform->s, 2, passedLayers->currentBB, true);
		//EM_ASM_({console.log("=================================LAYERS SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (passedLayers->ks != NULL && passedLayers->ks->r != NULL && passedLayers->ks->r->keyframe != NULL && passedLayers->currentBB != NULL) {
		//EM_ASM_({console.log("=================================LAYERS SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentR(passedLayers->ks->r->keyframe->start, passedLayers->currentBB, 1, true);
		passedLayers->transform->r = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================LAYERS SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 1);
		}
		fillAnimation(passedLayers->transform->r, 3, passedLayers->currentBB, true);
		//EM_ASM_({console.log("=================================LAYERS SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}
	if (passedLayers->ks != NULL && passedLayers->ks->o != NULL && passedLayers->ks->o->keyframe && passedLayers->currentBB != NULL) {
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM BEGINS ");});
		tempAOV = createSegmentR(passedLayers->ks->o->keyframe->start, passedLayers->currentBB, 2, true);
		passedLayers->transform->o = tempAOV;
		if (tempAOV->v_count > 1) {
			//EM_ASM_({console.log("=================================SCALE v_count ");});
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize, true, false, false, 1);
		}
		fillAnimation(passedLayers->transform->o, 4, passedLayers->currentBB, true);
		//EM_ASM_({console.log("---------------===================SCALE TRANSFORM ENDS ");});
		if (tempAOV->startTime < minTime || minTime == -1) {
			minTime = tempAOV->startTime;
		}
		if (tempAOV->endTime > maxTime || maxTime == -1) {
			maxTime = tempAOV->endTime;
		}
	}

	currentLayersTransformReturn->transform = passedLayers->transform;
	currentLayersTransformReturn->minTime = minTime;
	currentLayersTransformReturn->maxTime = maxTime;

	return currentLayersTransformReturn;
}

void composeTransformLayers(struct Layers* passedLayers, int minTime, int maxTime) {
	if (maxTime > minTime) {
		fillCompositeAnimation(minTime, maxTime, passedLayers->transform, passedLayers->shapes->start, true, true);
	}
	//EM_ASM_({console.log("---------------===================TRANSFORM done ");});
}

