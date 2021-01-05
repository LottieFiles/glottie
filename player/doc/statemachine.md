## Glottie State Machine

Glottie implements a dual-stage state-machine to extract animation data from a JSON string into a scene graph. The entry point for the state machine is in the function [deserializer.cpp](../deserializer/deserializer.cpp):deserializeChar().

In the first stage of the state-machine, the state-machine's states are dictated by JSON syntax. For instance, **{** changes the machine's state to *object opened*. When **"** immediately after that, then the state changes to *key opened*, and the very next **"** indicates *key closed* - meaning, all the characters that came in-between these two states constitute the key name. The next **:** changes the state to *reading value* and, which state allows the machine to interpret the string enclosed by the next double-quotes as the value corresponding to the last key found.

Once a 
