
struct PropertiesShape* newPropertiesShape(struct PropertiesShape* passedPropertiesShape) {
	if (passedPropertiesShape == NULL) {
		passedPropertiesShape = new PropertiesShape;
		passedPropertiesShape->start = passedPropertiesShape;
	} else {
		passedPropertiesShape->next = new PropertiesShape;
		passedPropertiesShape->next->start = passedPropertiesShape->start;
		passedPropertiesShape->next->prev = passedPropertiesShape;
		passedPropertiesShape = passedPropertiesShape->next;
	}
	passedPropertiesShape->keyframe = new PropertiesShapePropKeyframe;
	
	return passedPropertiesShape;
}

struct PropertiesShapeProp* newPropertiesShapeProp(struct PropertiesShape* passedPropertiesShape, struct PropertiesShapeProp* passedPropertiesShapeProp, bool isKeyframe) {
	if (passedPropertiesShapeProp == NULL) {
		passedPropertiesShapeProp = new PropertiesShapeProp;
		passedPropertiesShapeProp->start = passedPropertiesShapeProp;
	} else {
		passedPropertiesShapeProp->next = new PropertiesShapeProp;
		passedPropertiesShapeProp->next->start = passedPropertiesShapeProp->start;
		passedPropertiesShapeProp->next->prev = passedPropertiesShapeProp;
		passedPropertiesShapeProp = passedPropertiesShapeProp->next;
	}
	if (isKeyframe) {
		passedPropertiesShape->isKeyframe = true;
	}

	return passedPropertiesShapeProp;
}

struct PropertiesShapePropKeyframe* newPropertiesShapePropKeyframe() {
	struct PropertiesShapePropKeyframe* tempPropertiesShapePropKeyframe;
	tempPropertiesShapePropKeyframe = new PropertiesShapePropKeyframe;
	currentPropertiesShapePropKeyframe = tempPropertiesShapePropKeyframe;

	return tempPropertiesShapePropKeyframe;
}

//////////////////// assign values


struct ArrayOfVertex* populatePropertiesShapePropVertices(struct ArrayOfString* traceArrayValue, struct ArrayOfVertex* targetVertex, struct PropertiesShapeProp* passedPropertiesShapeProp) {
	struct ValuesVector* baseVector;
	if (traceArrayValue == NULL) {
		return 0;
	}
	/*if (targetVertex == NULL) {
		targetVertex = new ArrayOfVertex;
		targetVertex->start = targetVertex;
	}*/

	baseVector = traceArrayValue->vector->start;

	bool exhausted = false;
	currentUniversalCount = 0;
	while (! exhausted) {
		if (baseVector->child == NULL) {
			break;
		}
		currentUniversalCount = currentUniversalCount + 1;

		string xvals(baseVector->child->vector->start->value);
		//for (char& somechar : xvals) {
		//	//EM_ASM({console.log("========================> xval 1 " + String.fromCharCode($0));}, somechar);
		//}	
		float xval = 0;
		if (xvals[0] == '0' || xvals.length() < 1) {
			xval = 0;
		} else {
			if (! xvals.empty()) {
				xval = stof(xvals);
			} else {
				xval = 0;
			}
		}
		//EM_ASM({console.log("========================> xval " + $0);}, xval);
		string yvals(baseVector->child->vector->start->next->value);
		//EM_ASM({console.log("========================> yval 1 " + $0);}, yvals[0]);
		float yval = 0;
		if (yvals[0] == '0' || yvals.length() < 1) {
			yval = 0;
		} else {
			if (! yvals.empty()) {
				yval = stof(yvals);
			} else {
				yval = 0;
			}
		}
		/*if (targetVertex != NULL && targetVertex->vertex != NULL) {
			//EM_ASM({console.log("========================> xval / yval " + $0 + " : " + $1 + " --> " + $2);}, xval, yval, (int)targetVertex->vertex->position[0]);
		} else {
			//EM_ASM({console.log("========================> xval / yval " + $0 + " : " + $1);}, xval, yval);
		}*/
		float vertex[4] = {xval, yval, 0.0f, 1.0f};
		targetVertex = pushVertex(targetVertex, vertex);

		//EM_ASM_({console.log("vector " + $0 + " - " + $1);}, xval, yval);

		if (baseVector->next == NULL) {	
			exhausted = true;
		} else {
			baseVector = baseVector->next;
		}
	}
	if (targetVertex != NULL) {
		return targetVertex->start;
	} else {
		return NULL;
	}
}

int fillPropertiesShapeProp(struct PropertiesShapeProp* passedPropertiesShapeProp) {
	//EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue; 
	while (! exhausted) {
		if (tempKeyValue) {
			//EM_ASM({console.log("========================> iteration");});
		}
		if (strlen(tempKeyValue->key) == 0) {
			//EM_ASM({console.log("========================> empty");});
			if (tempKeyValue->next == NULL) {
				exhausted = true;
			} else {
				tempKeyValue = tempKeyValue->next;
			}
			continue;
		}
		if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "c") == 0) {
			//EM_ASM({console.log("========================> fill 80.1");});
				if (strcmp(tempKeyValue->value, "true") == 0) {
					passedPropertiesShapeProp->c = true;
				} else {
					passedPropertiesShapeProp->c = false;
				}
				//EM_ASM({console.log("========================> fill 80.1.1");});
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "i") == 0) {
			//EM_ASM({console.log("========================> fill 80.2 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->i = 
				populatePropertiesShapePropVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->i, passedPropertiesShapeProp);
			passedPropertiesShapeProp->i_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_i = vertexToGLfloat(passedPropertiesShapeProp->i, passedPropertiesShapeProp->count);

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "o") == 0) {
			//EM_ASM({console.log("========================> fill 80.3 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->o = 
				populatePropertiesShapePropVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->o, passedPropertiesShapeProp);
			passedPropertiesShapeProp->o_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_o = vertexToGLfloat(passedPropertiesShapeProp->o, passedPropertiesShapeProp->count);

		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "v") == 0) {
			//EM_ASM({console.log("========================> fill 80.4 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			passedPropertiesShapeProp->v = 
				populatePropertiesShapePropVertices(tempKeyValue->arrayValue, passedPropertiesShapeProp->v, passedPropertiesShapeProp);
			passedPropertiesShapeProp->v_count = currentUniversalCount;
			//passedPropertiesShapeProp->gl_v = vertexToGLfloat(passedPropertiesShapeProp->v, passedPropertiesShapeProp->count);

		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}
	//deleteKeyValues(theScope->currentKeyValueTrail);

	return 1;
}

