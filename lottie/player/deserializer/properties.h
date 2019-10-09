//// properties

struct PropertiesValueKeyframe {
	int e; //end
	int s; //start
	int t; //time

	struct XY* i; // bezier curve interpolation in value
} *currentPropertiesValueKeyframe;

struct PropertiesValue {
	float k;
	string ix; //property index
	int a; // animated
	string x; //expression

	struct PropertiesValueKeyframe* keyframe;
} *currentPropertiesValue;

struct PropertiesMultiDimensionalKeyframe {
	vector<float> s; //start
	int e; //end
	int t;
	
	struct XY* i; // bezier curve interpolation in value
	struct XY* o; // bezier curve interpolation out value
} *currentPropertiesMultiDimensionalKeyframe;

struct PropertiesMultiDimensional {
	vector<float> k;
	string x; // property expression - AE expression that modifies the value
	string ix; // property index - used for expression
	vector<float> ti; // in tangent
	vector<float> to; // out tangent

	struct PropertiesMultiDimensionalKeyframe* keyframe;
} *currentPropertiesMultiDimensional;

struct PropertiesShapeKeyframed {
	string x;
	string ix;
	int a; //animated
	vector<float> ti;
	vector<float> to;

	//keyframed
	struct PropertiesShapePropKeyframe* k;	
} *currentPropertiesShapeKeyframed;

struct PropertiesShapeProp {
	struct PropertiesShapeProp* start;
	struct PropertiesShapeProp* next;
	struct PropertiesShapeProp* prev;
	struct PropertiesShapeProp* end;

	bool c; //closed
	vector<float> i; // in point - array of 2 elements
	vector<float> o; // out point
	vector<float> v; // vertices
} *currentPropertiesShapeProp;

struct PropertiesShapePropKeyframe {
	struct PropertiesShapeProp* e;
	struct PropertiesShapeProp* s;
} *currentPropertiesShapePropKeyframe;

struct PropertiesShape {
	string x;
	string ix;
	int a; //animated

	struct PropertiesShapeProp* k;
	struct PropertiesShapePropKeyframe* keyframe;
	bool isKeyframe = false;
	int PropertiesShapePropCount = 0;
} *currentPropertiesShape;



