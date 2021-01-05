## Glottie State-Machine

Glottie implements a dual-stage state-machine to extract animation data from a JSON string into a scene graph. The entry point for the state machine is in the function [deserializer.cpp](../deserializer/deserializer.cpp):deserializeChar().

In the first stage of the state-machine, the state-machine's states are dictated by JSON syntax. For instance, **{** changes the machine's state to *object opened*. When **"** follows immediately after that, then the state changes to *key opened*, and the very next **"** indicates *key closed* - meaning, all the characters that came in-between these two states constitute the key name.

The next **:** changes the state to *reading a value* and, making the state-machine interpret the string enclosed by the next double-quotes as the value corresponding to the last key found. Once a key-value pair is discovered, the state-machine adds it to the linked list *theScope->currentKeyValueTrail->keyValue* ([deserializer.cpp](..deserializer/deserializer.cpp)).

#### Filling the scene graph

As mentioned before, the Glottie state-machine has dual stages, the first for extracting the data in the source JSON and the second for filling the scene graph. This second stage is triggered on two conditions: when either **{** or **}** are encountered.

When **{** is encountered, the state-machine calls *prepareContainer()* ([associate.cpp](../deserializer/associate.cpp)) to create a new container in the scene graph for storing all the key-values in the current object. What type of container to create, and therefore, which parent node to attach this newly created container, is determined by the global linked list *theScope*.

When the corresponding **}** is encountered, the state-machine calls *associateKeyValues()* ([associate.cpp](../deserializer/associate.cpp)) to finally store all the key-values in the newly created container. Once again, the global linked list *theScope* is used to determine what key-value storage function to call. For instance, if the enums stored in the last 3 elements of *theScope* linked list were **_p**, **_ks** and **_layers**, then the storage function called is *fillPropertiesMultiDimensional()* ([properties.cpp](../deserializer/properties.cpp)).