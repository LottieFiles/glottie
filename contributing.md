## Contributing

At LottieFiles, we are working hard to incorporate all features of lottie into Glottie. You are welcome to contribute to this work.

There are no hard rules for contributions, except that code should be easily readable and commit messages sensible. Other than that, we prefer to let contributors express themselves.

#### Lottie JSON schema

A visual map of the JSON schema for lottie animations can be found in [lottie_json_map.pdf](doc/lottie_json_map.pdf). This schema has been created based on the JSON schema found at https://github.com/airbnb/lottie-web/tree/master/docs/json.

Naming conventions used in Glottie, that conform to this schema, are [detailed here](doc/naming_convention.md).

#### Glottie innards

The following are some basic documentation on the inner workings of Glottie.

The first of these explains the [execution sequence](doc/executionsequence.md), by presenting the call sequence to the main functions, starting with the entry point *main()*.

The next important primer explains how [Glottie's state machine](doc/statemachine.md) works.

Once Glottie's state-machine builds a scene graph, the shape data is used to [compute geometries and transformations](doc/geometry.md).

Next, the [transformations are sequenced](doc/animation.md).

Finally, the [geometries are rendered](doc/render.md) as per the transformation sequences.

