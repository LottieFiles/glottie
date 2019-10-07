//// properties

struct PropertiesValueKeyframe {
	int e; //end
	int s; //start
	int t; //time

	struct XY* i; // bezier curve interpolation in value
};

struct PropertiesValue {
	float k;
	string ix; //property index
	int a; // animated
	string x; //expression

	struct PropertiesValueKeyframe* keyframe;
};

struct PropertiesMultiDimensionalKeyframe {
	vector<float> s; //start
	int e; //end
	int t;
	
	struct XY* i; // bezier curve interpolation in value
	struct XY* o; // bezier curve interpolation out value
};

struct PropertiesMultiDimensional {
	vector<float> k;
	string x; // property expression - AE expression that modifies the value
	string ix; // property index - used for expression
	vector<float> ti; // in tangent
	vector<float> to; // out tangent

	struct PropertiesMultiDimensionalKeyframe* keyframe;
};

struct PropertiesShapeKeyframed {
	string x;
	string ix;
	int a; //animated
	vector<float> ti;
	vector<float> to;

	//keyframed
	struct PropertiesShapePropKeyframe* k;	
};

struct PropertiesShapeProp {
	bool c; //closed
	vector<float> i; // in point - array of 2 elements
	vector<float> o; // out point
	vector<float> v; // vertices
};

struct PropertiesShapePropKeyframe {
	struct PropertiesShapeProp* e;
	struct PropertiesShapeProp* s;
};

struct PropertiesShape {
	string x;
	string ix;
	int a; //animated

	struct PropertiesShapeProp* k;
};



