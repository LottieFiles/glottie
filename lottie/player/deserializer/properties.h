//// properties

struct alignas(ALIGNSIZE) PropertiesValueKeyframe {
	int e; //end
	int s; //start
	int t; //time

	struct XY* i; // bezier curve interpolation in value
} *currentPropertiesValueKeyframe;

struct alignas(ALIGNSIZE) PropertiesValue {
	float k;
	//string ix; //property index
	int a; // animated
	//string x; //expression
	struct textBlock* ix;
	struct textBlock* x;

	struct PropertiesValueKeyframe* keyframe;
} *currentPropertiesValue;

struct alignas(ALIGNSIZE) PropertiesMultiDimensionalKeyframe {
	vector<float> s; //start
	int e; //end
	int t;
	
	struct XY* i; // bezier curve interpolation in value
	struct XY* o; // bezier curve interpolation out value
} *currentPropertiesMultiDimensionalKeyframe;

struct alignas(ALIGNSIZE) PropertiesMultiDimensional {
	vector<float> k;
	string x; // property expression - AE expression that modifies the value
	string ix; // property index - used for expression
	vector<float> ti; // in tangent
	vector<float> to; // out tangent

	struct PropertiesMultiDimensionalKeyframe* keyframe=NULL;
} *currentPropertiesMultiDimensional;

struct alignas(ALIGNSIZE) PropertiesShapeKeyframed {
	string x;
	string ix;
	int a; //animated
	vector<float> ti;
	vector<float> to;

	//keyframed
	struct PropertiesShapePropKeyframe* k;	
} *currentPropertiesShapeKeyframed;

struct alignas(ALIGNSIZE) PropertiesShapeProp {
//struct PropertiesShapeProp {
	struct PropertiesShapeProp* start=NULL;
	struct PropertiesShapeProp* next=NULL;
	struct PropertiesShapeProp* prev=NULL;

	struct ArrayOfVertex* i = NULL;
	struct ArrayOfVertex* o = NULL;
	struct ArrayOfVertex* v = NULL;
	
	bool c; //closed
	/*
	vector<float> i; // in point - array of 2 elements
	vector<float> o; // out point
	vector<float> v; // vertices
	*/
} *currentPropertiesShapeProp;

struct alignas(ALIGNSIZE) PropertiesShapePropKeyframe {
	struct PropertiesShapeProp* e=NULL;
	struct PropertiesShapeProp* s=NULL;
} *currentPropertiesShapePropKeyframe;

struct alignas(ALIGNSIZE) PropertiesShape {
//struct PropertiesShape {
	//string x;
	//string ix;
	struct textBlock* x;
	struct textBlock* ix;

	int a; //animated

	struct PropertiesShapeProp* k;
	struct PropertiesShapePropKeyframe* keyframe=NULL;
	bool isKeyframe = false;
	int PropertiesShapePropCount = 0;
} *currentPropertiesShape;



