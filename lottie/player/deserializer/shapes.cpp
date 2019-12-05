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
	if (passedTy == shape) {
		passedShapesItem->item = new ShapesShape;
		passedShapesItem->ty = passedTy;
		currentShapesShape = passedShapesItem->item;
	} else if (passedTy == group) {
	} else if (passedTy == ellipse) {
	} else if (passedTy == rect) {
	} else if (passedTy == star) {
	} else if (passedTy == fill) {
	} else if (passedTy == gFill) {
	} else if (passedTy == gStroke) {
	} else if (passedTy == stroke) {
	} else if (passedTy == merge) {
	} else if (passedTy == trim) {
		passedShapesItem->item = new ShapesGroup;
		passedShapesItem->ty = passedTy;
		currentShapesGroup = passedShapesItem->item;
	} else if (passedTy == roundedCorners) {
	} else if (passedTy == repeater) {
	} else if (passedTy == transform) {
	} 
        return passedShapesItem;
}


//////////// assign values

