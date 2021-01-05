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

void associateShaderAttributes(int passedIndex) {
		//assignAttributeNames(passedIndex);
	transformationsCountLoc = glGetUniformLocation(mainShader, "transformationsCount");
	preAnimationLoc = glGetUniformLocation(mainShader, "preAnimation");

	if (passedIndex == 0) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[0]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[0]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[0]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[0]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[0]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[0]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[0]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[0]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[0]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[0]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[0]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[0]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[0]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[0]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[0]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[0]");
	}

	if (passedIndex == 1) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[1]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[1]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[1]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[1]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[1]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[1]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[1]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[1]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[1]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[1]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[1]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[1]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[1]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[1]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[1]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[1]");
	}

	if (passedIndex == 2) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[2]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[2]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[2]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[2]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[2]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[2]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[2]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[2]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[2]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[2]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[2]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[2]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[2]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[2]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[2]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[2]");
	}

	if (passedIndex == 3) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[3]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[3]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[3]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[3]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[3]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[3]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[3]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[3]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[3]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[3]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[3]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[3]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[3]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[3]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[3]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[3]");
	}

	if (passedIndex == 4) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[4]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[4]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[4]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[4]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[4]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[4]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[4]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[4]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[4]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[4]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[4]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[4]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[4]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[4]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[4]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[4]");
	}

	if (passedIndex == 5) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[5]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[5]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[5]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[5]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[5]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[5]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[5]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[5]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[5]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[5]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[5]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[5]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[5]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[5]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[5]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[5]");
	}

	if (passedIndex == 6) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[6]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[6]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[6]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[6]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[6]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[6]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[6]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[6]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[6]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[6]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[6]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[6]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[6]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[6]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[6]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[6]");
	}

	if (passedIndex == 7) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[7]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[7]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[7]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[7]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[7]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[7]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[7]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[7]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[7]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[7]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[7]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[7]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[7]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[7]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[7]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[7]");
	}

	if (passedIndex == 8) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[8]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[8]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[8]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[8]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[8]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[8]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[8]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[8]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[8]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[8]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[8]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[8]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[8]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[8]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[8]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[8]");
	}

	if (passedIndex == 9) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[9]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[9]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[9]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[9]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[9]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[9]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[9]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[9]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[9]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[9]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[9]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[9]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[9]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[9]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[9]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[9]");
	}

	if (passedIndex == 10) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[10]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[10]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[10]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[10]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[10]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[10]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[10]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[10]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[10]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[10]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[10]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[10]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[10]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[10]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[10]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[10]");
	}

	if (passedIndex == 11) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[11]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[11]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[11]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[11]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[11]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[11]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[11]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[11]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[11]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[11]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[11]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[11]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[11]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[11]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[11]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[11]");
	}

	if (passedIndex == 12) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[12]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[12]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[12]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[12]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[12]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[12]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[12]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[12]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[12]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[12]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[12]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[12]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[12]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[12]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[12]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[12]");
	}

	if (passedIndex == 13) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[13]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[13]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[13]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[13]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[13]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[13]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[13]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[13]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[13]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[13]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[13]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[13]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[13]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[13]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[13]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[13]");
	}

	if (passedIndex == 14) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[14]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[14]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[14]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[14]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[14]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[14]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[14]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[14]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[14]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[14]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[14]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[14]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[14]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[14]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[14]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[14]");
	}

	if (passedIndex == 15) {
		layersTransformLoc = glGetUniformLocation(mainShader, "layersTransform[15]");
		shapesTransformLoc = glGetUniformLocation(mainShader, "shapesTransform[15]");
		layersRotateLoc = glGetUniformLocation(mainShader, "layersRotate[15]");
		shapesRotateLoc = glGetUniformLocation(mainShader, "shapesRotate[15]");
		layersScaleLoc = glGetUniformLocation(mainShader, "layersScale[15]");
		shapesScaleLoc = glGetUniformLocation(mainShader, "shapesScale[15]");

		layersPositionSetLoc = glGetUniformLocation(mainShader, "layersPositionSet[15]");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, "shapesPositionSet[15]");

		opacityValueLoc = glGetUniformLocation(mainShader, "objectOpacity[15]");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, "rotateLayersAngle[15]");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, "rotateLayersAngleSet[15]");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateLayersAxisOffset[15]");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, "rotateShapesAngle[15]");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, "rotateShapesAngleSet[15]");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, "rotateShapesAxisOffset[15]");

		instigatedLoc = glGetUniformLocation(mainShader, "instigated[15]");
	}



}
