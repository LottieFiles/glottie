#/////////////////////////////////////////////////////////
#/////////                                       /////////
#/////////  ******            *****************  /////////
#/////////   ****              ***************   /////////
#/////////    ***               ***         **   /////////
#/////////    ***               ***              /////////
#/////////    ***               ***     **       /////////
#/////////    ***               **********       /////////
#/////////    ***               **********       /////////
#/////////    ***               ***     **       /////////
#/////////    ***               ***              /////////
#/////////    ***       **      ***              /////////
#/////////   **************    *****             /////////
#/////////  ****************  *******            /////////
#/////////                                       /////////
#/////////////////////////////////////////////////////////
#///////  Created by: https://github.com/shaafiee  ///////
#///////      Copyright 2020, lottiefiles.com      ///////
#/////////////////////////////////////////////////////////

#!/usr/bin/perl

open(FILE, ">associateShaderAttributes.cpp") || die "Error opening file";

print FILE "
void associateShaderAttributes(int passedIndex) {
		//assignAttributeNames(passedIndex);
	transformationsCountLoc = glGetUniformLocation(mainShader, \"transformationsCount\");
	preAnimationLoc = glGetUniformLocation(mainShader, \"preAnimation\");
";


for ($i = 0; $i < 16; $i++) {
print FILE "
	if (passedIndex == $i) {
		layersTransformLoc = glGetUniformLocation(mainShader, \"layersTransform[$i]\");
		shapesTransformLoc = glGetUniformLocation(mainShader, \"shapesTransform[$i]\");
		layersRotateLoc = glGetUniformLocation(mainShader, \"layersRotate[$i]\");
		shapesRotateLoc = glGetUniformLocation(mainShader, \"shapesRotate[$i]\");
		layersScaleLoc = glGetUniformLocation(mainShader, \"layersScale[$i]\");
		shapesScaleLoc = glGetUniformLocation(mainShader, \"shapesScale[$i]\");

		layersPositionSetLoc = glGetUniformLocation(mainShader, \"layersPositionSet[$i]\");
		shapesPositionSetLoc = glGetUniformLocation(mainShader, \"shapesPositionSet[$i]\");

		opacityValueLoc = glGetUniformLocation(mainShader, \"objectOpacity[$i]\");

		rotateLayersAngleLoc = glGetUniformLocation(mainShader, \"rotateLayersAngle[$i]\");
		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, \"rotateLayersAngleSet[$i]\");
		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, \"rotateLayersAxisOffset[$i]\");

		rotateShapesAngleLoc = glGetUniformLocation(mainShader, \"rotateShapesAngle[$i]\");
		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, \"rotateShapesAngleSet[$i]\");
		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, \"rotateShapesAxisOffset[$i]\");

		instigatedLoc = glGetUniformLocation(mainShader, \"instigated[$i]\");
	}
";

}

print FILE "


}
";

close(FILE);
