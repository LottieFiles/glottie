// functions

struct HelpersTransform* newHelpersTransform(struct HelpersTransform* passedHelpersTransform) {
	if (passedHelpersTransform == NULL) {
		passedHelpersTransform = new HelpersTransform;
		passedHelpersTransform->start = passedHelpersTransform;
	} else {
		passedHelpersTransform->next = new HelpersTransform;
		passedHelpersTransform->next->start = passedHelpersTransform->start;
		passedHelpersTransform->next->prev = passedHelpersTransform;
		passedHelpersTransform = passedHelpersTransform->next;
	}
	return passedHelpersTransform;
}

int fillHelpersTransform(struct HelpersTransform* passedHelpersTransform) {
	//EM_ASM({console.log("========================> entered");});
	bool exhausted = false;
	struct KeyValue* tempKeyValue;
	tempKeyValue = theScope->currentKeyValueTrail->keyValue->start;
	struct ArrayOfString* tempArrayValue;
	bool foundExternalHandler = false;
	///////// first check whether this is a specialized shapes subobject - and call the appropriate handler
	while (! exhausted) {
		if (tempKeyValue->next == NULL) {
			exhausted = true;
		} else {
			tempKeyValue = tempKeyValue->next;
		}
	}

	if (! foundExternalHandler) {
	}

	return 1;
}


//////////// assign values

