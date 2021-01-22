## Naming conventions in Glottie

The naming conventions in the [lottie_json_map.pdf](../doc/lottie_json_map.pdf) has been followed throughout the source code. For instance, the *properties/offsetKeyframe.json* leaf object in the top-right corner of the schema map is named `PropertiesOffsetKeyframe` in Glottie code. This is shown in the following snippet from [properties.h](../deserializer/properties.h) [line 60]):

```c++
#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesOffsetKeyframe {
#else
struct PropertiesOffsetKeyframe {
#endif
	struct PropertiesOffsetKeyframe* start = NULL;
	struct PropertiesOffsetKeyframe* next = NULL;
	struct PropertiesOffsetKeyframe* prev = NULL;

	struct BezierCurve* i = NULL;
	struct BezierCurve* o = NULL;
	float* s; // start value
	int s_count;
	float t = 0; // start time 
	float* ti;
	int ti_count;
	float* to;
	int to_count;
} *currentPropertiesOffsetKeyframe;
```

The corresponding functions for *properties/offsetKeyframe.json* uses the naming convention &lt;purpose&gt;PropertiesOffsetKeyframe (with the function name beginning with a lowercase letter). A function is illustrated in the following snippet ([properties.cpp](../deserializer/properties.cpp) [line 80]):

```c++
struct PropertiesOffsetKeyframe* newPropertiesOffsetKeyframe() {
	if (currentPropertiesOffsetKeyframe == NULL) {
		currentPropertiesOffsetKeyframe = new PropertiesOffsetKeyframe;
		currentPropertiesOffsetKeyframe->start = currentPropertiesOffsetKeyframe;
	}
	else {
		currentPropertiesOffsetKeyframe->next = new PropertiesOffsetKeyframe;
		currentPropertiesOffsetKeyframe->next->start = currentPropertiesOffsetKeyframe->start;
		currentPropertiesOffsetKeyframe->next->prev = currentPropertiesOffsetKeyframe;
		currentPropertiesOffsetKeyframe = currentPropertiesOffsetKeyframe->next;
	}
	return currentPropertiesOffsetKeyframe;
}
```