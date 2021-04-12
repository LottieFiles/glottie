# Execution sequence

Glottie's execution sequence is listed in the following table:

File|Purpose
----|-------
[main.cpp](doc/main.cpp)|Program entry point: main()&rightarrow;readFromStdin()&rightarrow;loadJson()
[deserializer/deserializer.cpp](doc/deserializer/deserializer.cpp)|State machine that deserializes the JSON file into a scene graph: deserializeChar()&rightarrow;checkCharacter()&rightarrow;...
[gl/gl.init](doc/gl/gl.init)|Initialize OpenGL system: glInit(), glInitShaders()
[gl/parentage.cpp](doc/gl/parentage.cpp)|Resolve parenting and order scene graph accordingly: parentShapes()&rightarrow;...
[gl/prep.cpp](doc/gl/prep.cpp)|Discover geometric elements, generate their vertex buffers and compute transformations: prepShapes()&rightarrow;prepAssets()&rightarrow;prepLayers()&rightarrow;(findLayersTransform()&rightarrow;[animate/transform.cpp](doc/animate/transform.cpp):fillTransformLayers())&rightarrow;prepShapesItem()&rightarrow;(findShapesTransform()&rightarrow;[animate/transform.cpp](doc/animate/transform.cpp):fillTransformShapes())&rightarrow;prepPropertiesShape()&rightarrow;prepPropertiesShapeProp()&rightarrow;prepTriangulate()&rightarrow;prepVAO()
[animate/prep_transform.cpp](doc/animate/prep_transform.cpp)|Presequence all transformations and add them to the scene graph: prepTransformShapes()&rightarrow;<prepTransformAssets()>&rightarrow;prepTransformLayers()&rightarrow;[animate/transform.cpp](doc/animate/transform.cpp):composeTransformLayers()&rightarrow;[animate/transform.cpp](doc/animate/transform.cpp):fillCompositeAnimation()
[main.cpp](doc/main.cpp)|Setup animation looping: either mainloop() or standaloneLoop()
[gl/gl.cpp](doc/gl/gl.cpp)|Draw loop: glDraw()
