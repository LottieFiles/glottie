
struct PropertiesShape* newPropertiesShape() {
	struct PropertiesShape* tempPropertiesShape;
	tempPropertiesShape = new tempPropertiesShape;
	tempPropertiesShape->keyframe = newPropertiesShapePropKeyframe();
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

int fillPropertiesShapeProp(struct KeyValue* passedKeyValue) {
	
}

