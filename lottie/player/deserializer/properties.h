//// properties

struct alignas(ALIGNSIZE) PropertiesValueKeyframe {
	float e; //end
	float s; //start
	float t; //time

	struct Vertex* i; // bezier curve interpolation in value
} *currentPropertiesValueKeyframe;

struct alignas(ALIGNSIZE) PropertiesValue {
	float k;
	int k_count;
	//string ix; //property index
	int a; // animated
	//string x; //expression
	struct textBlock* ix;
	struct textBlock* x;

	struct PropertiesValueKeyframe* keyframe;
} *currentPropertiesValue;

struct alignas(ALIGNSIZE) PropertiesMultiDimensionalKeyframe {
	float* e; // end - array of numbers
	int e_count;
	float* s;
	int s_count;
} *currentPropertiesMultiDimensionalKeyframe;

struct alignas(ALIGNSIZE) PropertiesMultiDimensional {
	float* k;
	int k_count;
	string x; // property expression - AE expression that modifies the value
	string ix; // property index - used for expression
	float* ti; // in tangent
	int ti_count; // in tangent
	float* to; // out tangent
	int to_count; // out tangent
	int a;

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

	//struct Buffers* buffers_i = NULL;
	//struct Buffers* buffers_o = NULL;
	struct Buffers* buffers_v = NULL;

	//GLfloat* gl_i;
	//GLfloat* gl_o;
	//GLfloat* gl_v;
	//struct Vertex* gl_i;
	//struct Vertex* gl_o;
	//struct Vertex* gl_v;
	std::vector<GLfloat> gl_v;

	/*
	GLfloat* gl_i_fill;
	GLfloat* gl_o_fill;
	GLfloat* gl_v_fill;
	*/
	//struct Vertex* gl_i_fill;
	//struct Vertex* gl_o_fill;
	//struct Vertex* gl_v_fill;
	std::vector<GLfloat> gl_v_fill;

	/*
	unsigned int* gl_i_idx;
	unsigned int* gl_o_idx;
	unsigned int* gl_v_idx;
	*/
	//struct IndexArray* gl_i_idx;
	//struct IndexArray* gl_o_idx;
	//struct IndexArray* gl_v_idx;
	std::vector<unsigned int> gl_v_idx;

	int i_count = 0;	
	int o_count = 0;	
	int v_count = 0;
	int bezier_count = 0;

	int lowestX;
	int lowestY;

	//int refIndex_i = 0;
	//int refIndex_o = 0;
	//int refIndex_v = 0;

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
	struct PropertiesShape* start=NULL;
	struct PropertiesShape* next=NULL;
	struct PropertiesShape* prev=NULL;

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



