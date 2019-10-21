
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
	tempPropertiesShapeProp = tempPropertiesShapeProp->start;
	currentPropertiesShapeProp = tempPropertiesShapeProp;
	
	return tempPropertiesShapeProp;
}

struct PropertiesShapePropKeyframe* newPropertiesShapePropKeyframe() {
	struct PropertiesShapePropKeyframe* tempPropertiesShapePropKeyframe;
	tempPropertiesShapePropKeyframe = new PropertiesShapePropKeyframe;
	currentPropertiesShapePropKeyframe = tempPropertiesShapePropKeyframe;

	return tempPropertiesShapePropKeyframe;
}

//////////////////// assign values

int fillPropertiesShapeProp() {
	EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = currentKeyValue->start;
	while (! exhausted) {
		if (tempKeyValue) {
			EM_ASM({console.log("========================> iteration");});
		}
		if (tempKeyValue->key.empty()) {
			continue;
		}
		if (!tempKeyValue->key.empty() && tempKeyValue->key == "c") {
			EM_ASM({console.log("========================> fill 80.1");});
				if (tempKeyValue->value == "true") {
					currentPropertiesShapeProp->c = true;
				} else {
					currentPropertiesShapeProp->c = false;
				}
				EM_ASM({console.log("========================> fill 80.1.1");});
		} else if (!tempKeyValue->key.empty() && tempKeyValue->key == "i") {
				float xval = stof(tempKeyValue->arrayValue->child->vector->start->value);
				float yval = stof(tempKeyValue->arrayValue->child->vector->start->next->value);
				float vertex[4] = {xval, yval, 0.0f, 1.0f};
				//currentPropertiesShapeProp->i.emplace_back({xval, yval, 0.0f, 1.0f});
				//currentPropertiesShapeProp->i.push_back(Vertex());
				/*
				currentPropertiesShapeProp->i[currentPropertiesShapeProp->i.back()].position[0] = xval;
				currentPropertiesShapeProp->i[currentPropertiesShapeProp->i.back()].position[1] = xval;
				currentPropertiesShapeProp->i[currentPropertiesShapeProp->i.back()].position[2] = 0.0f;
				currentPropertiesShapeProp->i[currentPropertiesShapeProp->i.back()].position[3] = 1.0f;
				*/
				//currentPropertiesShapeProp->i.at(currentPropertiesShapeProp->i.back()).position = {xval, yval, 0.0f, 1.0f};
				pushVertex(currentPropertiesShapeProp->i, vertex);
				EM_ASM({console.log("========================> fill 80.2");});
		} else if (!tempKeyValue->key.empty() && tempKeyValue->key == "o") {
				float xval = stof(tempKeyValue->arrayValue->child->vector->start->value);
				float yval = stof(tempKeyValue->arrayValue->child->vector->start->next->value);
				//float xval = stof(tempKeyValue->arrayValue->child->value[0]);
				//float yval = stof(tempKeyValue->arrayValue->child->value[1]);
				float vertex[4] = {xval, yval, 0.0f, 1.0f};
				//EM_ASM_({console.log('traced '.$0);},xval);
				//currentPropertiesShapeProp->o.emplace_back({xval, yval, 0.0f, 1.0f});
				pushVertex(currentPropertiesShapeProp->o, vertex);
				EM_ASM({console.log("========================> fill 80.3");});
		} else if (!tempKeyValue->key.empty() && tempKeyValue->key == "v") {
				float xval = stof(tempKeyValue->arrayValue->child->vector->start->value);
				float yval = stof(tempKeyValue->arrayValue->child->vector->start->next->value);
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
				//////////////////////// DEND */
		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
		exhausted = true;
	}

	return 1;
}

