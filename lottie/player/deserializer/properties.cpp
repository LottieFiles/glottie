
struct PropertiesShape* newPropertiesShape() {
	struct PropertiesShape* tempPropertiesShape;
	tempPropertiesShape = new PropertiesShape;
	tempPropertiesShape->keyframe = new PropertiesShapePropKeyframe;
	currentPropertiesShape = tempPropertiesShape;
	
	return tempPropertiesShape;
}

struct PropertiesShapeProp* newPropertiesShapeProp() {
	struct PropertiesShapeProp* tempPropertiesShapeProp;
	tempPropertiesShapeProp = new PropertiesShapeProp;
	tempPropertiesShapeProp->start = tempPropertiesShapeProp;
	currentPropertiesShapeProp = tempPropertiesShapeProp;
	//currentPropertiesShapeProp->i = new ArrayOfVertex;
	//currentPropertiesShapeProp->o = new ArrayOfVertex;
	//currentPropertiesShapeProp->v = new ArrayOfVertex;
	return currentPropertiesShapeProp;
}

struct PropertiesShapePropKeyframe* newPropertiesShapePropKeyframe() {
	struct PropertiesShapePropKeyframe* tempPropertiesShapePropKeyframe;
	tempPropertiesShapePropKeyframe = new PropertiesShapePropKeyframe;
	currentPropertiesShapePropKeyframe = tempPropertiesShapePropKeyframe;

	return tempPropertiesShapePropKeyframe;
}

//////////////////// assign values


struct ArrayOfVertex* populatePropertiesShapePropVertices(struct ArrayOfString* traceArrayValue, struct ArrayOfVertex* targetVertex) {
	struct ValuesVector* baseVector;
	if (traceArrayValue == NULL) {
		return 0;
	}
	/*if (targetVertex == NULL) {
		targetVertex = new ArrayOfVertex;
		targetVertex->start = targetVertex;
	}*/
	baseVector = traceArrayValue->root->vector->start;

	bool exhausted = false;
	while (! exhausted) {
		string xvals(baseVector->child->vector->start->value);
		//for (char& somechar : xvals) {
		//	EM_ASM({console.log("========================> xval 1 " + String.fromCharCode($0));}, somechar);
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
			EM_ASM({console.log("========================> xval / yval " + $0 + " : " + $1 + " --> " + $2);}, xval, yval, (int)targetVertex->vertex->position[0]);
		} else {
			EM_ASM({console.log("========================> xval / yval " + $0 + " : " + $1);}, xval, yval);
		}*/
		float vertex[4] = {xval, yval, 0.0f, 1.0f};
		targetVertex = pushVertex(targetVertex, vertex);

		if (baseVector->next != NULL) {	
			baseVector = baseVector->next;
		} else {
			exhausted = true;
		}
	}
	return targetVertex->start;
}

int fillPropertiesShapeProp() {
	EM_ASM({console.log("========================> entered");});
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
			EM_ASM({console.log("========================> fill 80.1");});
				if (strcmp(tempKeyValue->value, "true") == 0) {
					currentPropertiesShapeProp->c = true;
				} else {
					currentPropertiesShapeProp->c = false;
				}
				EM_ASM({console.log("========================> fill 80.1.1");});
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "i") == 0) {
			EM_ASM({console.log("========================> fill 80.2 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			currentPropertiesShapeProp->i = 
				populatePropertiesShapePropVertices(tempKeyValue->arrayValue, currentPropertiesShapeProp->i);

			EM_ASM({console.log("========================> fill 80.2 " + $0 + " : " + $1);}, 
				currentPropertiesShapeProp->i->start->vertex->position[0],
				currentPropertiesShapeProp->i->start->vertex->position[1]);
			//tempArrayValue = tempKeyValue->arrayValue->root;

				/*
				//string xvals(tempKeyValue->arrayValue->root->vector->start->value);
				//string yvals(tempKeyValue->arrayValue->root->vector->start->next->value);
				float xval = stof(xvals);
				float yval = stof(yvals);
				float vertex[4] = {xval, yval, 0.0f, 1.0f};
				*/
				//currentPropertiesShapeProp->i.at(currentPropertiesShapeProp->i.back()).position = {xval, yval, 0.0f, 1.0f};
				//pushVertex(currentPropertiesShapeProp->i, vertex);

				//EM_ASM({console.log("========================> fill 80.2");});
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "o") == 0) {
			EM_ASM({console.log("========================> fill 80.3 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			currentPropertiesShapeProp->o = 
				populatePropertiesShapePropVertices(tempKeyValue->arrayValue, currentPropertiesShapeProp->o);

				/*
				string xvals(tempKeyValue->arrayValue->root->vector->start->value);
				string yvals(tempKeyValue->arrayValue->root->vector->start->next->value);
				float xval = stof(xvals);
				float yval = stof(yvals);
				//float xval = stof(tempKeyValue->arrayValue->child->value[0]);
				//float yval = stof(tempKeyValue->arrayValue->child->value[1]);
				float vertex[4] = {xval, yval, 0.0f, 1.0f};
				//EM_ASM_({console.log('traced '.$0);},xval);
				//currentPropertiesShapeProp->o.emplace_back({xval, yval, 0.0f, 1.0f});
				pushVertex(currentPropertiesShapeProp->o, vertex);
				EM_ASM({console.log("========================> fill 80.3");});
				*/
		} else if (strlen(tempKeyValue->key) > 0 && strcmp(tempKeyValue->key, "v") == 0) {
			EM_ASM({console.log("========================> fill 80.4 " + String.fromCharCode($0));}, tempKeyValue->key[0]);
			currentPropertiesShapeProp->v = 
				populatePropertiesShapePropVertices(tempKeyValue->arrayValue, currentPropertiesShapeProp->v);

				/*
				string xvals(tempKeyValue->arrayValue->root->vector->start->value);
				string yvals(tempKeyValue->arrayValue->root->vector->start->next->value);
				float xval = stof(xvals);
				float yval = stof(yvals);
				//float xval = stof(tempKeyValue->arrayValue->child->value[0]);
				//float yval = stof(tempKeyValue->arrayValue->child->value[1]);
				float vertex[4] = {xval, yval, 0.0f, 1.0f};
				//currentPropertiesShapeProp->v.emplace_back({xval, yval, 0.0f, 1.0f});
				pushVertex(currentPropertiesShapeProp->v, vertex);
				//////////////// DEBUG stuff
				EM_ASM_({
					console.log($0);
				}, xval);
				EM_ASM({console.log("========================> fill 80.4");});
				//////////////////////// DEND 
				*/
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

