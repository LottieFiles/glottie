## Animation

Once [geometries are created](../doc/geometry.md), the transformations that are applied to them during the sequence of the animation are sequenced.

This is firstly done by calling *fillTransformShapes()* ([transform.cpp](../animate/transform.cpp)) from within [prep.cpp](../gl/prep.cpp), which happens right after each call to *prepShapesItem()*.

#### Transformations for shapes

To begin with, *fillTransformShapes()* builds eases bezier curves used for various transformations. Next this eased transformation data is converted into matrices. These matrices are then added to the respective frames of the animation ([transform.cpp](../animate/transform.cpp)).

#### Transformations for layers

Layers transformations are done after all the [geometry](geometry.md) data has been built. The function called to compose the layer transformations is *prepTransformShapes()* ([prep_transform.cpp](../animate/prep_transform.cpp)), which finds all the layers with transformations.

In any are found, then *composeTransformLayers()* ([transform.cpp](../animate/transform.cpp)) is called. This function goes through the almost the exact same process as *fillTransformShapes()* ([transform.cpp](../animate/transform.cpp) to compose layer transformations.

At the end of this stage, all the transformation matrices will have been added to the global linked list *animationSequence*, with each transformation matrix slotted into its relevant frame.