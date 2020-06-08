//// layers

struct alignas(ALIGNSIZE) Layers {
        struct Layers* start = NULL;
        struct Layers* prev = NULL;
        struct Layers* next = NULL;
      
	struct Mask* maskProperties = NULL;
        //struct Index* ef = NULL; // effects
        struct Effects* ef = NULL; // effects

        struct ShapesItem* shapes = NULL;

        struct LayersText* text;

        struct HelpersTransform* ks = NULL; //transform

	struct BoundingBox* currentBB = NULL;

	struct Transform* transform = NULL;

        string cl; //class
        string ln; //layer html id
        string nm; //name

	int shapesItemCount = 0; // internal use - amount of shapesItems in this object
        int ind; // index

        int sr = 1; //stretch
        int hasMask; // has masks
        int parent; //parent
        int st; // start time
        int op; // out point
        int ip; // in point

        int ao; //auto-orient
        int bm; //blendmode
        int ddd;

      
	int id;


	bool created; // internal flag to indicate this object has already been created
} *currentLayers;

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

struct alignas(ALIGNSIZE) Assets {
	struct Assets* start = NULL;
	struct Assets* prev = NULL;
	struct Assets* next = NULL;

        string itemType; // any of 'image', 'precomp'
        int id;
        bool isImage;
        bool isPrecomp;
        struct ImageSource* images = NULL;
        struct Layers* precomps = NULL;
} *currentAssets;

//struct alignas(128) Layers {
struct alignas(ALIGNSIZE) Layers_old {
        struct Layers* start = NULL;
        struct Layers* prev = NULL;
        struct Layers* next = NULL;

	int ty;
        int id;
        //string itemType; // any of 'shape', 'solid', 'precomp', 'image', 'null', 'text'
        struct LayersShapes* shapes = NULL;
        struct LayersSolid* solid = NULL;
        struct LayersPrecomp* precomp = NULL;
        struct LayersImage* image = NULL;
        struct LayersNull* null = NULL;
        struct LayersText* text = NULL;
} *currentLayers_old;

struct alignas(ALIGNSIZE) Animation {
        string v; // Bodymovin (exporter) version
        string nm; // name of animation
        struct Layers* layers = NULL;
        struct Assets* assets = NULL;
        struct Char* chars = NULL;
        struct Player* players = NULL;
        struct Font* fonts = NULL;
        float ip; // entry frame number
        float op; // exit frame number
        float fr; // frame rate
        float w; // width
        float h; // height
	float z; // depth

	float halfW;
	float halfH;

	float scaleFactorX = 2;
	float scaleFactorY = 2;
	float scaleFactorZ = 2;

	float customWidth = 0;
	float customHeight = 0;

	float frMultiplier = 1;
	float lengthMultiplier = 2;
	float frameTime; // in seconds
	float totalTime; // in seconds
	float frameTimeMS;

        bool ddd = false; // is 3D? (1 = yes, 0 = no)

} *theAnimation;


