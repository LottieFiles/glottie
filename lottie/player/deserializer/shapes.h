//// shapes

enum ShapesTy {
		_group = 0, //gr
		_shape = 1, //sh
		_ellipse = 2, //el
		_rect = 3, //rc
		_star = 4, //sr
		_fill = 5, //fl
		_gFill = 6, //gf
		_gStroke = 7, //gs
		_stroke = 8, //st
		_merge = 9, //mm
		_trim = 10, //tm
		_roundedCorners = 11, //rd
		_repeater = 12, // rp
		_transform = 13, // tr
		_noshape = 20
	};

struct alignas(ALIGNSIZE) ShapesItem {
	char mn[KVLEN]; // match name
	char nm[KVLEN]; // name

	struct ShapesItem* start = NULL;
	struct ShapesItem* next = NULL;
	struct ShapesItem* prev = NULL;

	/*
	struct ShapesShape* shape; // sh
	struct ShapesEllipse* ellipse; // el
	struct ShapesRect* rect; // rc
	struct ShapesStar* star; // sr
	struct ShapesFill* fill; // fl
	struct ShapesGFill* gFill; // gf
	struct ShapesGStroke* gStroke; // gs
	struct ShapesStroke* stroke; // st
	struct ShapesMerge* merge; // mm
	struct ShapesTrim* trim; // tm
	struct ShapesGroup* group; // gr
	struct ShapesRoundedCorners* roundedCorners; // rd
	struct ShapesRepeater* repeater; // rp
	struct ShapesTransform* transform; // tr
	*/

	struct PropertiesShape* ks = NULL;

	struct PropertiesValue* r = NULL; // rotation (radius for roundedCorners[rd])
	struct PropertiesMultiDimensional* s = NULL; // size (scale for transform[tr], start point for gFill[gf])
	struct PropertiesMultiDimensional* p = NULL; // position
	struct PropertiesValue* o = NULL; // opacity [offset for repeater[rp]
	struct PropertiesMultiDimensional* c = NULL; // color (number of copies for repeater[rp])
	struct PropertiesMultiDimensional* e = NULL; // end point
	struct PropertiesValue* h = NULL; // highlight length
	struct PropertiesMultiDimensional* a = NULL; // anchor point (highlight angle for gFill[gf] and gStroke[gs])
	struct PropertiesValue* sk = NULL; // skew
	struct PropertiesValue* sa = NULL; // skew axis


	struct PropertiesValue* w = NULL; // stroke width
	struct HelpersLineCap* lc = NULL; // line cap
	struct HelpersLineJoin* lj = NULL; // line join

	//struct HelpersTransform* tr = NULL; // transform
	
	struct ShapesItem* it = NULL;
	struct ShapesItem* parent = NULL;

	struct ShapesItem* baseTransform = NULL;

	void* item;

	enum ShapesTy ty;

	void* g = NULL; // gradient colors - to be researched further

	int d; // direction
	int np; // number of properties
	int t; // type [1 for linear, 2 for radial]
	int ml; // miter limit
	int mm; // merge mode

	int order = 0;

	bool isKeyframed = false;
	bool basicShapeGenerated = false;
	
} *currentShapesItem;

/*
struct alignas(ALIGNSIZE) ShapesGroup {
	string mn; // match name
	string nm; // name
	string np; // number of properties

	enum ShapesTy ty = gr;

	struct ShapesItem* it; // item

	struct ShapesGroup* parentGroup;
} *currentShapesGroup;

struct alignas(ALIGNSIZE) ShapesShape {
	string mn; // match name
	string nm; // name
	int d; // direction

	enum ShapesTy ty = sh;

	struct PropertiesShape* ks;
	struct PropertiesShapeKeyframed* ksKeyframed;

	struct ShapesGroup *parentGroup;
} *currentShapesShape;
*/

