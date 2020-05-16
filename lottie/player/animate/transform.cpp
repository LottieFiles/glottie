
struct alignas(ALIGNSIZE) TransformAOV {
	struct ArrayOfVertex* v = NULL;
	struct ArrayOfVertex* i = NULL;
	struct ArrayOfVertex* o = NULL;
	float startTime;
	float endTime;
	float* frames;
	float* segSize;
	int v_count = 0;
	int bezier_count = 0;
};

struct TransformAOV* createSegment() {
}

struct TransformAOV* createSegmentValue(struct PropertiesValueKeyframe* passedKeyframe) {
}

struct TransformAOV* createSegmentMultiDimensional(struct PropertiesOffsetKeyframe* passedKeyframe) {
	bool exhausted = false;
	struct TransformAOV* tempAOV = NULL;
	tempAOV = new TransformAOV;
	float previousTime = 0;
	tempAOV->frames = new float[passedKeyframe->s_count];
	tempAOV->segSize = new float[passedKeyframe->s_count];
	tempAOV->startTime = passedKeyframe->t;
	while (! exhausted) {
		if (passedKeyframe->s_count == 1) {
			float currentList[4] = {*(passedKeyframe->s + 0), 0, 0, 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			EM_ASM_({console.log("1---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		} else if (passedKeyframe->s_count == 2) {
			float currentList[4] = {*(passedKeyframe->s + 0), *(passedKeyframe->s + 1), 0, 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			EM_ASM_({console.log("2---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		} else if (passedKeyframe->s_count == 3) {
			float currentList[4] = {*(passedKeyframe->s + 0), *(passedKeyframe->s + 1), *(passedKeyframe->s + 2), 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			EM_ASM_({console.log("3---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		} else {
			float currentList[4] = {0, 0, 0, 1};
			tempAOV->v = pushVertex(tempAOV->v, currentList);
			EM_ASM_({console.log("4---> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);
		}

		tempAOV->v_count++;
		EM_ASM_({console.log("----> " + $0 + " " + $1);}, *(passedKeyframe->s + 0), passedKeyframe->s_count);

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
			*(tempAOV->frames + (tempAOV->v_count - 1)) = (passedKeyframe->t - previousTime) / theAnimation->frameTime;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / *(tempAOV->frames + (tempAOV->v_count - 1));
		} else {
			*(tempAOV->frames + (tempAOV->v_count - 1)) = 1;
			*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1;
		}
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

	tempAOV->endTime = previousTime;
	return tempAOV;
}

void fillTransformShapes(struct ShapesItem* passedShapesItem) {
	struct TransformAOV* tempAOV = NULL;
	if (passedShapesItem->transform == NULL) {
		passedShapesItem->transform = new Transform;
	}
	if (passedShapesItem->p != NULL && passedShapesItem->p->keyframe != NULL) {
		EM_ASM_({console.log("=================================TRANSFORM BEGINS ");});
		tempAOV = createSegmentMultiDimensional(passedShapesItem->p->keyframe->start);
		bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize);
		passedShapesItem->transform->p = tempAOV;
	}
	EM_ASM_({console.log("=================================TRANSFORM ENDS ");});
}

void fillTransformLayers(struct Layers* passedLayers) {
	struct TransformAOV* tempAOV = NULL;
	if (passedLayers->transform == NULL) {
		passedLayers->transform = new Transform;
	}
	if (passedLayers->ks != NULL && passedLayers->ks->p != NULL && passedLayers->ks->p->keyframe != NULL) {
		EM_ASM_({console.log("=================================LAYERS TRANSFORM BEGINS ");});
		tempAOV = createSegmentMultiDimensional(passedLayers->ks->p->keyframe->start);
		bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize);
		passedLayers->transform->p = tempAOV;
	}
	EM_ASM_({console.log("=================================LAYERS TRANSFORM ENDS ");});
}

