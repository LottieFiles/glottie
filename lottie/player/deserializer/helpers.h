struct HelpersLineCap { // usually only one of
	struct HelpersLineCap* start = NULL;
	struct HelpersLineCap* prev = NULL;
	struct HelpersLineCap* next = NULL;

};

struct HelpersLineJoin { // usually only one of
	struct HelpersLineJoin* start = NULL;
	struct HelpersLineJoin* prev = NULL;
	struct HelpersLineJoin* next = NULL;

};

struct HelpersTransform { // usually only one of
	struct HelpersTransform* start = NULL;
	struct HelpersTransform* prev = NULL;
	struct HelpersTransform* next = NULL;

	struct PropertiesMultiDimensional* a = NULL; // anchor point
	struct PropertiesMultiDimensional* p = NULL; // position
	struct PropertiesMultiDimensional* s = NULL; // scale
	struct PropertiesValue* r = NULL; // rotation
	struct PropertiesValue* o = NULL; // opacity
	struct PropertiesValue* px = NULL; // position x
	struct PropertiesValue* py = NULL; // position y
	struct PropertiesValue* pz = NULL; // position z
	struct PropertiesValue* sk = NULL; // skew
	struct PropertiesValue* sa = NULL; // skew axis
};

