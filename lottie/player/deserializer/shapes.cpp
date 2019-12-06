// functions

struct ShapesItem* newShapesItem(struct ShapesItem* passedShapesItem) {
	if (passedShapesItem == NULL) {
		passedShapesItem = new ShapesItem;
		passedShapesItem->start = passedShapesItem;
	} else {
		passedShapesItem->next = new ShapesItem;
		passedShapesItem->next->start = passedShapesItem->start;
		passedShapesItem->next->prev = passedShapesItem;
		passedShapesItem = passedShapesItem->next;
	}
	currentShapesItem = passedShapesItem;
	return passedShapesItem;
}

	

int updateShapesItemType(enum ShapesTy passedTy, struct ShapesItem* passedShapesItem) {
	if (passedTy == _shape) {
	} else if (passedTy == _group) {
	} else if (passedTy == _ellipse) {
	} else if (passedTy == _rect) {
	} else if (passedTy == _star) {
	} else if (passedTy == _fill) {
	} else if (passedTy == _gFill) {
	} else if (passedTy == _gStroke) {
	} else if (passedTy == _stroke) {
	} else if (passedTy == _merge) {
	} else if (passedTy == _trim) {
	} else if (passedTy == _roundedCorners) {
	} else if (passedTy == _repeater) {
	} else if (passedTy == _transform) {
	} 
        return 1;
}


//////////// assign values

