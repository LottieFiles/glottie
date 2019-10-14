
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
				EM_ASM_({
					console.log("entered");
				});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = currentKeyValueTrail->keyValue->start;
	while (! exhausted) {
		if (tempKeyValue->key == "c") {
				if (tempKeyValue->value == "true") {
					currentPropertiesShapeProp->c = true;
				} else {
					currentPropertiesShapeProp->c = false;
				}
		} else if (tempKeyValue->key == "i") {
				float xval = stof(tempKeyValue->arrayValue->child->value[0]);
				float yval = stof(tempKeyValue->arrayValue->child->value[1]);
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
				break;
		} else if (tempKeyValue->key == "o") {
				float xval = stof(tempKeyValue->arrayValue->child->value[0]);
				float yval = stof(tempKeyValue->arrayValue->child->value[1]);
				float vertex[4] = {xval, yval, 0.0f, 1.0f};
				//currentPropertiesShapeProp->o.emplace_back({xval, yval, 0.0f, 1.0f});
				pushVertex(currentPropertiesShapeProp->o, vertex);
		} else if (tempKeyValue->key == "v") {
				float xval = stof(tempKeyValue->arrayValue->child->value[0]);
				float yval = stof(tempKeyValue->arrayValue->child->value[1]);
				float vertex[4] = {xval, yval, 0.0f, 1.0f};
				//currentPropertiesShapeProp->v.emplace_back({xval, yval, 0.0f, 1.0f});
				pushVertex(currentPropertiesShapeProp->v, vertex);
				//////////////// DEBUG stuff
				EM_ASM_({
					console.log(String.$0);
				}, xval);
				//////////////////////// DEND */
		}



		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}

	return 1;
}

