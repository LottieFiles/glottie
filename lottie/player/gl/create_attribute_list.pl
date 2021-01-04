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


open (FILE, ">assignAttributeNames.cpp") || die "Error opening attributes file!";


print FILE "\tconst char* __layersTransform;\n";
print FILE "\tconst char* __shapesTransform;\n";
print FILE "\tconst char* __layersRotate;\n";
print FILE "\tconst char* __shapesRotate;\n";
print FILE "\tconst char* __layersScale;\n";
print FILE "\tconst char* __shapesScale;\n";

print FILE "\tconst char* __layersPositionSet;\n";
print FILE "\tconst char* __shapesPositionSet;\n";

print FILE "\tconst char* __rotateLayersAngle;\n";
print FILE "\tconst char* __rotateLayersAngleSet;\n";
print FILE "\tconst char* __rotateLayersAxisOffset;\n";

print FILE "\tconst char* __rotateShapesAngle;\n";
print FILE "\tconst char* __rotateShapesAngleSet;\n";
print FILE "\tconst char* __rotateShapesAxisOffset;\n";

print FILE "\tconst char* __opacityValue;\n";

print FILE "\n";
print FILE "\n";

	
print FILE "void assignAttributeNames(int passedIndex) {\n";
for ($i = 0; $i < 16; $i++) {
	print FILE "\tif (passedIndex == $i) {\n";
	print FILE "\t\t__layersTransform = \"layersTransform[$i]\";\n";
	print FILE "\t\t__shapesTransform = \"shapesTransform[$i]\";\n";
	print FILE "\t\t__layersRotate = \"layersRotate[$i]\";\n";
	print FILE "\t\t__shapesRotate = \"shapesRotate[$i]\";\n";
	print FILE "\t\t__layersScale = \"layersScale[$i]\";\n";
	print FILE "\t\t__shapesScale = \"shapesScale[$i]\";\n";
	
	print FILE "\t\t__layersPositionSet = \"layersPosition[$i]\";\n";
	print FILE "\t\t__shapesPositionSet = \"shapesPosition[$i]\";\n";
	
	print FILE "\t\t__rotateLayersAngle = \"rotateLayersAngle[$i]\";\n";
	print FILE "\t\t__rotateLayersAngleSet = \"rotateLayersAngleSet[$i]\";\n";
	print FILE "\t\t__rotateLayersAxisOffset = \"rotateLayersAxisOffset[$i]\";\n";
	
	print FILE "\t\t__rotateShapesAngle = \"rotateShapesAngle[$i]\";\n";
	print FILE "\t\t__rotateShapesAngleSet = \"rotateShapesAngleSet[$i]\";\n";
	print FILE "\t\t__rotateShapesAxisOffset = \"rotateShapesAxisOffset[$i]\";\n";
	
	print FILE "\t\t__opacityValue = \"objectOpacity[$i]\";\n";
	
	print FILE "\t}\n";
	print FILE "\n";
}
print FILE "}\n";

close (FILE);

#		layersTransformLoc = glGetUniformLocation(mainShader, getCString("layersTransform[" + std::to_string(passedIndex) + "]"));
#		shapesTransformLoc = glGetUniformLocation(mainShader, getCString("shapesTransform[" + std::to_string(passedIndex) + "]"));
#		layersRotateLoc = glGetUniformLocation(mainShader, getCString("layersRotate[" + std::to_string(passedIndex) + "]"));
#		shapesRotateLoc = glGetUniformLocation(mainShader, getCString("shapesRotate[" + std::to_string(passedIndex) + "]"));
#		layersScaleLoc = glGetUniformLocation(mainShader, getCString("layersScale[" + std::to_string(passedIndex) + "]"));
#		shapesScaleLoc = glGetUniformLocation(mainShader, getCString("shapesScale[" + std::to_string(passedIndex) + "]"));
#
#		layersPositionSetLoc = glGetUniformLocation(mainShader, getCString("layersPositionSet[" + std::to_string(passedIndex) + "]"));
#		shapesPositionSetLoc = glGetUniformLocation(mainShader, getCString("shapesPositionSet[" + std::to_string(passedIndex) + "]"));
#
#
#		rotateLayersAngleLoc = glGetUniformLocation(mainShader, getCString("rotateLayersAngle[" + std::to_string(passedIndex) + "]"));
#		rotateLayersAngleSetLoc = glGetUniformLocation(mainShader, getCString("rotateLayersAngleSet[" + std::to_string(passedIndex) + "]"));
#		rotateLayersAxisOffsetLoc = glGetUniformLocation(mainShader, getCString("rotateLayersAxisOffset[" + std::to_string(passedIndex) + "]"));
#
#		rotateShapesAngleLoc = glGetUniformLocation(mainShader, getCString("rotateShapesAngle[" + std::to_string(passedIndex) + "]"));
#		rotateShapesAngleSetLoc = glGetUniformLocation(mainShader, getCString("rotateShapesAngleSet[" + std::to_string(passedIndex) + "]"));
#		rotateShapesAxisOffsetLoc = glGetUniformLocation(mainShader, getCString("rotateShapesAxisOffset[" + std::to_string(passedIndex) + "]"));
#
#		opacityValue = glGetUniformLocation(mainShader, getCString("objectOpacity[" + std::to_string(passedIndex) + "]"));
#
#		preAnimationLoc = glGetUniformLocation(mainShader, "preAnimation");

