struct alignas(ALIGNSIZE) TransformMatrix {
	struct TransformMatrix* start = NULL;
	struct TransformMatrix* prev = NULL;
	struct TransformMatrix* next = NULL; 
	
	glm::mat4 transform;
};

struct alignas(ALIGNSIZE) Transform {
	struct TransformAOV* p = NULL;
	struct TransformAOV* r = NULL;
	struct TransformAOV* s = NULL;

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
};

struct TransformAOV* createSegment() {
}

struct TransformAOV* createSegmentValue(struct PropertiesValueKeyframe* passedKeyframe) {
}

struct TransformAOV* createSegmentP(struct PropertiesOffsetKeyframe* passedKeyframe) {
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
	while (! exhausted) {
		
		if (passedKeyframe->s_count == 1) {
			float _1 = ((*(passedKeyframe->s + 0) / w) - 0.5);
			//float currentList[4] = {((*(passedKeyframe->s + 0) / w) - 0.5), 0, 0, 1};
			float currentList[4] = {_1, 0, 0, 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			//EM_ASM_({console.log("1---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		} else if (passedKeyframe->s_count == 2) {
			float _1 = ((*(passedKeyframe->s + 0) / w) - 0.5);
			float _2 = ((*(passedKeyframe->s + 1) / h) - 0.5) * -1;
			float currentList[4] = {_1, _2, 0, 1};
			//float currentList[4] = {((*(passedKeyframe->s + 0) / w) - 0.5), (((*(passedKeyframe->s + 1) / h) - 0.5) * -1), 0, 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			//EM_ASM_({console.log("2---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		} else if (passedKeyframe->s_count == 3) {
			float _1 = ((*(passedKeyframe->s + 0) / w) - 0.5);
			float _2 = ((*(passedKeyframe->s + 1) / h) - 0.5) * -1;
			float _3 = (*(passedKeyframe->s + 3) / z);
			float currentList[4] = {_1, _2, _3, 1};
			//float currentList[4] = {((*(passedKeyframe->s + 0) / w) - 0.5), (((*(passedKeyframe->s + 1) / h) - 0.5) * -1), ((*(passedKeyframe->s + 2) / z) - 0.5), 0, 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			//EM_ASM_({console.log("3---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		} else {
			float currentList[4] = {0, 0, 0, 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			//EM_ASM_({console.log("4---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		}

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
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / *(tempAOV->frames + (tempAOV->v_count - 1));
		} else {
			*(tempAOV->frames + (tempAOV->v_count - 1)) = 1;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 0;
		}
		EM_ASM_({console.log("----> " + $0 + " " + $1 + " -- frames: " + $2 + ", segsize: " + $3 + " -- start " + $4);}, tempAOV->v->vertex->x, tempAOV->v->vertex->y, *(tempAOV->frames + (tempAOV->v_count - 1)), *(tempAOV->segSize + (tempAOV->v_count - 1)), tempAOV->startTime);
		previousTime = passedKeyframe->t;

		if (passedKeyframe->next == NULL) {
			exhausted = true;
		} else {
			passedKeyframe = passedKeyframe->next;
		}
	}
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

void fillAnimationTranslate(struct TransformAOV* passedAOV) {
	passedAOV->v = passedAOV->v->start;
	bool exhausted = false;
	int currentIndex = 0;
	while (! exhausted) {
		passedAOV->transformMatrix = newTransformMatrix(passedAOV->transformMatrix);
		passedAOV->transformMatrix->transform = glm::mat4(1.0f);
		/*if (currentLayersTransform != NULL && currentIndex > 0) {
			currentLayersTransform->p->v = currentLayersTransform->p->v->start;
			for (int i = 1; i <= currentIndex; i++) {
				if (currentLayersTransform->p->v->next != NULL) {
					currentLayersTransform->p->v = currentLayersTransform->p->v->next;
				}
			}
			passedAOV->transformMatrix->transform = glm::translate(passedAOV->transformMatrix->transform, glm::vec3(passedAOV->v->vertex->x + currentLayersTransform->p->v->vertex->x, passedAOV->v->vertex->y + currentLayersTransform->p->v->vertex->y, passedAOV->v->vertex->z + currentLayersTransform->p->v->vertex->z));
		} else {
		}
		*/
		EM_ASM_({console.log("=*******=======transformMatrix ");});
		passedAOV->transformMatrix->transform = glm::translate(passedAOV->transformMatrix->transform, glm::vec3(passedAOV->v->vertex->x, passedAOV->v->vertex->y, passedAOV->v->vertex->z));
		currentIndex++;
		if (passedAOV->v->next == passedAOV->v->start) {
			exhausted = true;
		} else {
			passedAOV->v = passedAOV->v->next;
		}
	}
}

struct Transform* fillTransformShapes(struct ShapesItem* passedShapesItem) {
	struct TransformAOV* tempAOV = NULL;
	if (passedShapesItem->transform == NULL) {
		passedShapesItem->transform = new Transform;
	}
	if (passedShapesItem->p != NULL && passedShapesItem->p->keyframe != NULL) {
		EM_ASM_({console.log("---------------===================TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedShapesItem->p->keyframe->start);
		passedShapesItem->transform->p = tempAOV;
		if (tempAOV->v_count > 1) {
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize);
		}
		fillAnimationTranslate(passedShapesItem->transform->p);
		EM_ASM_({console.log("---------------===================TRANSFORM ENDS ");});
	}

	return passedShapesItem->transform;
}

struct Transform* fillTransformLayers(struct Layers* passedLayers) {
	struct TransformAOV* tempAOV = NULL;
	if (passedLayers->transform == NULL) {
		passedLayers->transform = new Transform;
	}
	if (passedLayers->ks != NULL && passedLayers->ks->p != NULL && passedLayers->ks->p->keyframe != NULL) {
		EM_ASM_({console.log("=================================LAYERS TRANSFORM BEGINS ");});
		tempAOV = createSegmentP(passedLayers->ks->p->keyframe->start);
		passedLayers->transform->p = tempAOV;
		if (tempAOV->v_count > 1) {
			bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize);
		}
		fillAnimationTranslate(passedLayers->transform->p);
		EM_ASM_({console.log("=================================LAYERS TRANSFORM ENDS ");});
	}


	return passedLayers->transform;
}

