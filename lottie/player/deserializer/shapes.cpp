// functions

int newShapesShape() {
	if (currentShapesItem->ty == "sh") {
		currentShapesItem->shape = new ShapesShape;
		currentShapesShape = currentShapesItem->shape;
	} else if (currentShapesItem->ty == "el") {
	} else if (currentShapesItem->ty == "rc") {
	} else if (currentShapesItem->ty == "sr") {
	} else if (currentShapesItem->ty == "fl") {
	} else if (currentShapesItem->ty == "gf") {
	} else if (currentShapesItem->ty == "gs") {
	} else if (currentShapesItem->ty == "st") {
	} else if (currentShapesItem->ty == "mm") {
	} else if (currentShapesItem->ty == "tm") {
	} else if (currentShapesItem->ty == "gr") {
	} else if (currentShapesItem->ty == "rd") {
	} else if (currentShapesItem->ty == "rp") {
	} else if (currentShapesItem->ty == "tr") {
	} 
        return 1;
}

//////////// assign values

