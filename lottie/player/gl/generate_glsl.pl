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

open(FILE, ">vertexShader.cpp") || die "Error opening vertex shader\n";

print FILE 'const GLchar* vertexSource = '."\n";

for ($i = 0; $i < 16; $i++) {
	print FILE '    "#define counter_'.$i.'  '.$i.'\n"'."\n";
}

#print FILE '    "#version 100\n"
#    "attribute vec4 position; \n"
#print FILE '    "#version 150\n"
print FILE '    "attribute vec4 position; \n"
    "attribute vec4 color; \n"
    "varying vec4 vcolors; \n"
    "uniform int transformationsCount; \n"
    "uniform int preAnimation; \n"
    "uniform int layersPositionSet[16]; \n"
    "uniform int shapesPositionSet[16]; \n"
    "uniform int layersPositionIncluded[16]; \n"
    "uniform int shapesPositionIncluded[16]; \n"
    "uniform mat4 layersRotate[16]; \n"
    "uniform mat4 shapesRotate[16]; \n"
    "uniform mat4 layersScale[16]; \n"
    "uniform mat4 shapesScale[16]; \n"
    "uniform mat4 layersTransform[16]; \n"
    "uniform mat4 shapesTransform[16]; \n"
    "uniform vec3 layersPosition[16]; \n"
    "uniform vec3 shapesPosition[16]; \n"
    "uniform float objectOpacity[16]; \n"
    "uniform float rotateLayersAngle[16]; \n"
    "uniform vec3 rotateLayersAxisOffset[16]; \n"
    "uniform int rotateLayersAngleSet[16]; \n"
    "uniform float rotateShapesAngle[16]; \n"
    "uniform vec3 rotateShapesAxisOffset[16]; \n"
    "uniform int rotateShapesAngleSet[16]; \n"
    "uniform int instigated[16]; \n"
    "vec4 quat_from_axis_angle(vec3 axis, float angle) \n"
    "{ \n"
    "  vec4 qr; \n"
    "  float half_angle = (angle * 0.5) * 3.14159 / 180.0; \n"
    "  qr.x = axis.x * sin(half_angle); \n"
    "  qr.y = axis.y * sin(half_angle); \n"
    "  qr.z = axis.z * sin(half_angle); \n"
    "  qr.w = cos(half_angle); \n"
    "  return qr; \n"
    "} \n"
    "vec3 rotate_vertex_position(vec3 passedPosition, vec3 axis, float angle) \n"
    "{ \n"
    "  vec4 q = quat_from_axis_angle(axis, angle); \n"
    "  vec3 v = passedPosition.xyz; \n"
    "  return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v); \n"
    "} \n"
    "void main() \n"
    "{ \n"
    "  vec4 glpre; \n"
    "  vec4 gltemp; \n"
    "  float tempOpValue = 1.0; \n"
    "  if (preAnimation == 1) { \n"
    "    gl_Position = position; \n"
    "  } else { \n"
    "    gltemp = position; \n"
';




#print FILE '    "    for (int cntr = 0; cntr < transformationsCount; cntr++) { \n"
#';

#for ($i = 0; $i < 16; $i++) {
#    print FILE '    "      if (transformationsCount > counter_'.$i.') { \n"
#    "        if (shapesPositionSet[counter_'.$i.'] == 1 && layersPositionSet[counter_'.$i.'] == 1) { \n"
#    "          gltemp = ((layersRotate[counter_'.$i.'] * shapesRotate[counter_'.$i.']) * (layersScale[counter_'.$i.'] * shapesScale[counter_'.$i.']) * (layersTransform[counter_'.$i.'] * shapesTransform[counter_'.$i.'])) * gltemp; \n"
#    "        } else if (layersPositionSet[counter_'.$i.'] == 1) {\n"
#    "          gltemp = layersRotate[counter_'.$i.'] * ((layersScale[counter_'.$i.'] * layersTransform[counter_'.$i.']) * gltemp); \n"
#    "        } else if (shapesPositionSet[counter_'.$i.'] == 1) {\n"
#    "          gltemp = (shapesRotate[counter_'.$i.'] * shapesScale[counter_'.$i.'] * shapesTransform[counter_'.$i.']) * gltemp; \n"
#    "        } \n"
#    "      } \n"
#';
#}

for ($i = 0; $i < 16; $i++) {
    print FILE '    "      if (transformationsCount > '.$i.') { \n"
    "        if (instigated['.$i.'] == 0) { \n"
    "          if (shapesPositionSet['.$i.'] == 1 && layersPositionSet['.$i.'] == 1) { \n"
    "            gltemp = shapesRotate['.$i.'] * (shapesScale['.$i.'] * (shapesTransform['.$i.'] * gltemp)); \n"
    "            gltemp = layersRotate['.$i.'] * (layersScale['.$i.'] * (layersTransform['.$i.'] * gltemp)); \n"
    "          } else if (layersPositionSet['.$i.'] == 1) {\n"
    "            gltemp = layersRotate['.$i.'] * (layersScale['.$i.'] * (layersTransform['.$i.'] * gltemp)); \n"
    "          } else if (shapesPositionSet['.$i.'] == 1) {\n"
    "            gltemp = shapesRotate['.$i.'] * (shapesScale['.$i.'] * (shapesTransform['.$i.'] * gltemp)); \n"
    "          } \n"
    "          tempOpValue = objectOpacity['.$i.']; \n"
    "        } \n"
    "      } \n"
';
}

#    "          gltemp = layersRotate['.$i.'] * ((layersScale['.$i.'] * layersTransform['.$i.']) * gltemp); \n"
#    "          gltemp = (layersTransform['.$i.'] * layersScale['.$i.'] * layersRotate['.$i.']) * gltemp; \n"

#for ($i = 0; $i < 16; $i++) {
#    print FILE '    "      if (transformationsCount > '.$i.') { \n"
#    "        if (shapesPositionSet['.$i.'] == 1 && layersPositionSet['.$i.'] == 1) { \n"
#    "          gltemp = ((layersRotate['.$i.'] * shapesRotate['.$i.']) * (layersScale['.$i.'] * shapesScale['.$i.']) * (layersTransform['.$i.'] * shapesTransform['.$i.'])) * gltemp; \n"
#    "        } else if (layersPositionSet['.$i.'] == 1) {\n"
#    "          gltemp = layersRotate['.$i.'] * ((layersTransform['.$i.']) * gltemp); \n"
#    "        } else if (shapesPositionSet['.$i.'] == 1) {\n"
#    "          gltemp = (shapesRotate['.$i.'] * shapesScale['.$i.'] * shapesTransform['.$i.']) * gltemp; \n"
#    "        } \n"
#    "      } \n"
#';
#}

#    "      gltemp = glpre; \n"
#print FILE '    "    } \n"
#';


#print FILE '    "    gl_Position = position; \n"
print FILE '    "    gl_Position = gltemp; \n"
    "  } \n"
    "    if (tempOpValue > 1.0) { \n"
    "      tempOpValue = 1.0; \n"
    "    } \n"
    "    vcolors = vec4(color.xyz, tempOpValue); \n"
    "} \n";';
