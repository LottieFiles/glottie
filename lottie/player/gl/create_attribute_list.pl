#!/usr/bin/perl


open (FILE, ">attribute_names.cpp") || die "Error opening attributes file!";

for ($i = 0; $i < 16; $i++) {
print FILE "if (passedIndex == $i) {";
print FILE "\t__layersTransform = \"layersTransform[$i]\"\n";
print FILE "\t__shapesTransform = \"shapesTransform[$i]\"\n";
print FILE "\t__layersRotate = \"layersRotate[$i]\"\n";
print FILE "\t__shapesRotate = \"shapesRotate[$i]\"\n";
print FILE "\t__layersScale = \"layersScale[$i]\"\n";
print FILE "\t__shapesScale = \"shapesScale[$i]\"\n";

print FILE "\t__layersPositionSet = \"layersPosition[$i]\"\n";
print FILE "\t__shapesPositionSet = \"shapesPosition[$i]\"\n";

print FILE "\t__rotateLayersAngle = \"rotateLayersAngle[$i]\"\n";
print FILE "\t__rotateLayersAngleSet = \"rotateLayersAngleSet[$i]\"\n";
print FILE "\t__rotateLayersAxisOffset = \"rotateLayersAxisOffset[$i]\"\n";

print FILE "\t__rotateShapesAngle = \"rotateShapesAngle[$i]\"\n";
print FILE "\t__rotateShapesAngleSet = \"rotateShapesAngleSet[$i]\"\n";
print FILE "\t__rotateShapesAxisOffset = \"rotateShapesAxisOffset[$i]\"\n";

print FILE "\t__opacityValue = \"objectOpacity[$i]\"\n";

print FILE "\t__preAnimationLoc = \"preAnimation\"\n";
print FILE "}\n";
}
print FILE "\n\n";

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

