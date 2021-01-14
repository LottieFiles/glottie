/////////////////////////////////////////////////////////
/////////                                       /////////
/////////  ******            *****************  /////////
/////////   ****              ***************   /////////
/////////    ***               ***         **   /////////
/////////    ***               ***              /////////
/////////    ***               ***     **       /////////
/////////    ***               **********       /////////
/////////    ***               **********       /////////
/////////    ***               ***     **       /////////
/////////    ***               ***              /////////
/////////    ***       **      ***              /////////
/////////   **************    *****             /////////
/////////  ****************  *******            /////////
/////////                                       /////////
/////////////////////////////////////////////////////////
///////  Created by: https://github.com/shaafiee  ///////
///////      Copyright 2020, lottiefiles.com      ///////
/////////////////////////////////////////////////////////

void debugNestedArray(struct ValuesVector* passedArray, int nestLevel) {
	bool exhausted = false;
	
	if (passedArray == NULL) {
		return;
	}

	passedArray = passedArray->start;
	
	cout << "[";

	while (! exhausted) {
		
		if (passedArray->child != NULL && passedArray->child->vector != NULL) {
			nestLevel++;
			debugNestedArray(passedArray->child->vector, (nestLevel));
		}
		else {
			cout << passedArray->value;
		}

		if (passedArray->next == NULL) {
			exhausted = true;
		}
		else {
			passedArray = passedArray->next;
			cout << ", ";
		}
	}

	cout << "]";
}
