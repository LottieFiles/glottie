## Geometry

Building geometries begins with the function *fillPropertiesShapeProp()* ([properties.cpp](../deserializer/properties.cpp)), which is the function that fills the geometry data into a given shape object in the scene graph. Once the function fills this data for a shape, then from within the same function a call is made to *bezierSegment()* ([misc.cpp](../misc.cpp)), which is an easing function for bezier curves.

The next part of the geometry begins after all data is extracted from the source JSON. Once this is done, the function *prepShapes()* ([prep.cpp](../gl/prep.cpp)) is called. This function finds the relevant data in the scene graph needed to build the geometries in the lottie animation.

All geometry data found is passed to the function *prepTriangulate()* ([triangulate.cpp](../gl/triangulate.cpp)). This function accomplishes two things. Firstly, it cuts away a geometry's ears, yielding a set of simple shapes that together constitute the full geometry. Secondly, each one of these shapes is triangulated. The triangulated shapes are then passed to *prepVAO()* ([prep.cpp](../gl/prep.cpp)), which creates a vertex buffer object (VBO) from the triangulated shapes.
