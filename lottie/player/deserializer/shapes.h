//// shapes

enum ShapesTy {
		sh,
		gr
	};

struct ShapesItem {
	struct ShapesItem* start;
	struct ShapesItem* end;
	struct ShapesItem* next;
	struct ShapesItem* prev;

	string ty;
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
} *currentShapesItem;

struct ShapesGroup {
	string mn; // match name
	string nm; // name
	string np; // number of properties

	enum ShapesTy ty = gr;

	struct ShapesItem* it; // item

	struct ShapesGroup* parentGroup;
} *currentShapesGroup;

struct ShapesShape {
	string mn; // match name
	string nm; // name
	int d; // direction

	enum ShapesTy ty = sh;

	struct PropertiesShape* ks;
	struct PropertiesShapeKeyframed* ksKeyframed;

	struct ShapesGroup *parentGroup;
} *currentShapesShape;


