
struct alignas(ALIGNSIZE) TransformAOV {
	struct ArrayOfVertex* v = NULL;
	struct ArrayOfVertex* i = NULL;
	struct ArrayOfVertex* o = NULL;
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
	while (! exhausted) {

		if (passedKeyframe->s != NULL) {
			if (passedKeyframe->s_count == 1) {
				float currentList[4] = {*(passedKeyframe->s + 0), 0, 0, 1};
				pushVertex(tempAOV->v, currentList);
			} else if (passedKeyframe->s_count == 2) {
				float currentList[4] = {*(passedKeyframe->s + 0), *(passedKeyframe->s + 1), 0, 1};
				pushVertex(tempAOV->v, currentList);
			} else if (passedKeyframe->s_count == 3) {
				float currentList[4] = {*(passedKeyframe->s + 0), *(passedKeyframe->s + 1), *(passedKeyframe->s + 2), 1};
				pushVertex(tempAOV->v, currentList);
			}
		} else {
			float currentList[4] = {0, 0, 0, 1};
			pushVertex(tempAOV->v, currentList);
		}
		tempAOV->v_count++;

		if (passedKeyframe->i != NULL) {
			float currentList[4] = {*(passedKeyframe->i->x + 0), *(passedKeyframe->i->y + 0), 0, 1};
			pushVertex(tempAOV->i, currentList);
		} else {
			float currentList[4] = {0, 0, 0, 1};
			pushVertex(tempAOV->i, currentList);
		}

		if (passedKeyframe->o != NULL) {
			float currentList[4] = {*(passedKeyframe->o->x + 0), *(passedKeyframe->o->y + 0), 0, 1};
			pushVertex(tempAOV->o, currentList);
		} else {
			float currentList[4] = {0, 0, 0, 1};
			pushVertex(tempAOV->o, currentList);
		}

		*(tempAOV->frames + (tempAOV->v_count - 1)) = (passedKeyframe->t - previousTime) / theAnimation->frameTime;
		*(tempAOV->segSize + (tempAOV->v_count - 1)) = 1 / *(tempAOV->frames + (tempAOV->v_count - 1));
		previousTime = passedKeyframe->t;

		if (passedKeyframe->next == NULL) {
			exhausted = true;
		} else {
			passedKeyframe = passedKeyframe->next;
		}
	}
	return tempAOV;
}

void fillTransform(struct ShapesItem* passedShapesItem) {
	struct TransformAOV* tempAOV = NULL;
	if (passedShapesItem->p != NULL && passedShapesItem->p->keyframe != NULL) {
		tempAOV = createSegmentMultiDimensional(passedShapesItem->p->keyframe->start);
		bezierSegment(tempAOV->v, tempAOV->i, tempAOV->o, &(tempAOV->v_count), &(tempAOV->bezier_count), tempAOV->segSize);
	}
}

