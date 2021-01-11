## Contributing

At LottieFiles, we are working hard to incorporate all features of lottie into Glottie. You are welcome to contribute to this work.

There are no hard rules for contributions, except that code should be easily readable and commit messages sensible. Other than that, we prefer to let contributors express themselves.

#### Before you begin

We have provided some basic documentation to present the inner workings of Glottie.

The first of these explains the [execution sequence](executionsequence.md), by presenting the call sequence to the main functions, starting with the entry point *main()*.

The next important primer explains how [Glottie's state machine](statemachine.md) works.

Once Glottie's state-machine builds a scene graph, the shape data is used to [compute geometries and transformations](geometry.md).

Next, the [transformations are sequenced](animation.md).

Finally, the [geometries are rendered](render.md) as per the transformation sequences.

