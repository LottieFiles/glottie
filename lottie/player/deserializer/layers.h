//// layers

struct LayersShapes {
        struct ShapesItem* shapesItem;
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

} currentLayersShape;

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

struct Asset {
        string itemType; // any of 'image', 'precomp'
        int id;
        bool isImage;
        bool isPrecomp;
        struct ImageSource* images;
        struct PrecompSource* precomps;
};

struct Layers {
        struct Layers* start;
        struct Layers* end;
        struct Layers* prev;
        struct Layers* next;

	int ty;
        int id;
        string itemType; // any of 'shape', 'solid', 'precomp', 'image', 'null', 'text'
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


