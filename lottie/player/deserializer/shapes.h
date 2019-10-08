//// shapes

struct ShapesItem {
	struct ShapesItem* start;
	struct ShapesItem* end;
	struct ShapesItem* next;
	struct ShapesItem* prev;

	string ty;
	struct ShapesShape* shape;
	struct ShapesEllipse* ellipse;
	struct ShapesRect* rect;
	struct ShapesStar* star;
	struct ShapesFill* fill;
	struct ShapesGFill* gFill;
	struct ShapesGStroke* gStroke;
	struct ShapesStroke* stroke;
	struct ShapesMerge* merge;
	struct ShapesTrim* trim;
	struct ShapesGroup* group;
	struct ShapesRoundedCorners* rd;
	struct ShapesRepeater* rp;
	struct ShapesTransform* tr;
} *currentShapesItem;

struct ShapesGroup {
	string mn; // match name
	string nm; // name
	string np; // number of properties

	struct ShapesItem* it; // item
} *currentShapesGroup;

struct ShapesShape {
	string mn; // match name
	string nm; // name
	int d; // direction
	
	struct PropertiesShape* ks;
	struct PropertiesShapeKeyframed* ksKeyframed;
} *currentShapesShape;


