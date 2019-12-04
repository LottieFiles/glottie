//// layers

struct LayersShapes {
	bool created; // internal flag to indicate this object has already been created
        struct ShapesItem* shapes;
	int shapesItemCount = 0; // internal use - amount of shapesItems in this object
        int ind; // index
        string cl; //class
        string ln; //layer html id
        string nm; //name
        int sr = 1; //stretch
        int hasMask; // has masks
        int parent; //parent
        int st; // start time
        int op; // out point
        int ip; // in point

        struct Transform* ks; //transform
        int ao; //auto-orient
        int bm; //blendmode
        int ddd;
        struct Mask* maskProperties;
        struct Index* ef; // effects

} *currentLayersShapes;

struct LayersSolid {
};

struct LayersPrecomp {

};

struct LayersImage {

};

struct LayersNull {

};

struct LayersText {

};

struct Assets {
	struct Assets* start = NULL;
	struct Assets* prev = NULL;
	struct Assets* next = NULL;
	struct Assets* end = NULL;

        string itemType; // any of 'image', 'precomp'
        int id;
        bool isImage;
        bool isPrecomp;
        struct ImageSource* images;
        struct Layers* precomps;
} *currentAssets;

//struct alignas(128) Layers {
struct Layers {
        struct Layers* start = NULL;
        struct Layers* end = NULL;
        struct Layers* prev = NULL;
        struct Layers* next = NULL;

	int ty;
        int id;
        //string itemType; // any of 'shape', 'solid', 'precomp', 'image', 'null', 'text'
        struct LayersShapes* shapes;
        struct LayersSolid* solid;
        struct LayersPrecomp* precomp;
        struct LayersImage* image;
        struct LayersNull* null;
        struct LayersText* text;
} *currentLayers;

struct Animation {
        int ip; // entry frame number
        int op; // exit frame number
        int fr; // frame rate
        int w; // width
        int h; // height
        bool ddd; // is 3D? (1 = yes, 0 = no)
        string v; // Bodymovin (exporter) version
        string nm; // name of animation
        struct Layer* layers;
        struct Asset* assets;
        struct Char* chars;
        struct Player* players;
        struct Font* fonts;
} *theAnimation;


