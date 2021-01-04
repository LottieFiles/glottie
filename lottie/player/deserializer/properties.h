/////////////////////////////////////////////////////////
/////////                                       /////////
/////////  ******            *****************  /////////
/////////   ****              ***************   /////////
/////////    ***               ***         **   /////////
/////////    ***               ***              /////////
/////////    ***               ***     **       /////////
/////////    ***               **********       /////////
/////////    ***               **********       /////////
/////////    ***               ***     **       /////////
/////////    ***               ***              /////////
/////////    ***       **      ***              /////////
/////////   **************    *****             /////////
/////////  ****************  *******            /////////
/////////                                       /////////
/////////////////////////////////////////////////////////
///////  Created by: https://github.com/shaafiee  ///////
///////      Copyright 2020, lottiefiles.com      ///////
/////////////////////////////////////////////////////////

//// properties

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesValueKeyframe {
#else
struct PropertiesValueKeyframe {
#endif
	struct PropertiesValueKeyframe* start = NULL;
	struct PropertiesValueKeyframe* next = NULL;
	struct PropertiesValueKeyframe* prev = NULL;

	struct BezierCurve* i = NULL;
	struct BezierCurve* o = NULL;
	float* s; // start value
	int s_count;
	float t = 0; // start time 
	float* ti;
	int ti_count;
	float* to;
	int to_count;
} *currentPropertiesValueKeyframe;

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesValue {
#else
struct PropertiesValue {
#endif
	struct PropertiesValueKeyframe* keyframe = NULL;

	struct textBlock* ix;
	struct textBlock* x;

	float k;
	int k_count;
	//string ix; //property index
	int a; // animated
	//string x; //expression
} *currentPropertiesValue;

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

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesMultiDimensionalKeyframe {
#else
struct PropertiesMultiDimensionalKeyframe {
#endif
	float* e; // end - array of numbers
	int e_count;
	float* s;
	int s_count;
} *currentPropertiesMultiDimensionalKeyframe;

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesMultiDimensional {
#else
struct PropertiesMultiDimensional {
#endif
	struct PropertiesOffsetKeyframe* keyframe = NULL;

	float* k = NULL;
	int k_count;
	string x; // property expression - AE expression that modifies the value
	string ix; // property index - used for expression
	float* ti; // in tangent
	int ti_count; // in tangent
	float* to; // out tangent
	int to_count; // out tangent
	int a;

	//struct PropertiesMultiDimensionalKeyframe* keyframe=NULL;
} *currentPropertiesMultiDimensional;

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesShapeKeyframed {
#else
struct PropertiesShapeKeyframed {
#endif
	string x;
	string ix;
	int a; //animated
	vector<float> ti;
	vector<float> to;

	//keyframed
	struct PropertiesShapePropKeyframe* k;	
} *currentPropertiesShapeKeyframed;

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesShapeProp {
#else
struct PropertiesShapeProp {
#endif
	struct PropertiesShapeProp* start = NULL;
	struct PropertiesShapeProp* next = NULL;
	struct PropertiesShapeProp* prev = NULL;

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

	int order;

	//int refIndex_i = 0;
	//int refIndex_o = 0;
	//int refIndex_v = 0;

	bool c; //closed
	bool prepped = false;
	bool vaoAdded = false;

	/*
	vector<float> i; // in point - array of 2 elements
	vector<float> o; // out point
	vector<float> v; // vertices
	*/
} *currentPropertiesShapeProp;

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesShapePropKeyframe {
#else
struct PropertiesShapePropKeyframe {
#endif
	struct PropertiesShapeProp* e=NULL;
	struct PropertiesShapeProp* s=NULL;
} *currentPropertiesShapePropKeyframe;

#ifdef EMT
struct alignas(ALIGNSIZE) PropertiesShape {
#else
struct PropertiesShape {
#endif
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



