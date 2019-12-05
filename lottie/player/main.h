


//// Helpers




//enum States {NoState = 0, Animation = 1, Layers = 2, Assets = 3, Chars = 4, Players = 5, Fonts = 6, ks = 7, ao = 8, bm = 9, ddd = 10, maskProperties = 11, ef = 12, shapes = 13, it = 14, t = 15, a = 16, m = 17, r = 18, p = 19, s = 20, sk = 21, sa = 22, o = 23, sw =  24, sc = 25, fc = 26, fh = 27, fs = 28, fb = 29, maxa = 31, mine = 32, maxe = 33, bo = 34, start  = 35, end = 36, Offset = 37, g = 38};

/*
enum Scopes {
	noscope = 0,
	object = 101,
	animation = 1,
	assets = 2,
	assets_layers = 403,
	assets_layers_shapes = 404,
	assets_layers_shapes_ty = 401,
	assets_layers_shapes_ks = 405,
	assets_layers_shapes_ks_k = 406,
	assets_layers_shapes_ks_k_e = 407,
	assets_layers_shapes_ks_k_s = 408,
	assets_layers_it = 424,
	assets_layers_it_ty = 421,
	assets_layers_it_ks = 425,
	assets_layers_it_ks_k = 426,
	assets_layers_it_ks_k_e = 427,
	assets_layers_it_ks_k_s = 428,
	// 
	layers = 503,
	layers_shapes = 504,
	layers_shapes_ty = 501,
	layers_shapes_ks = 505,
	layers_shapes_ks_k = 506,
	layers_shapes_ks_k_e = 507,
	layers_shapes_ks_k_s = 508,
	layers_it = 520,
	layers_it_ty = 521,
	layers_it_ks = 525,
	layers_it_ks_k = 526,
	layers_it_ks_k_e = 527,
	layers_it_ks_k_s = 528,
	//
	gr = 600,
	gr_it = 620,
	gr_it_ty = 621,
	gr_it_ks = 625,
	gr_it_ks_k = 626,
	gr_it_ks_k_e = 627,
	gr_it_ks_k_s = 628
	};
*/

enum Scopes {
	noscope = 0,
	object = 101,
	animation = 1,
	assets = 2,
	layers = 3,
	gr = 4,
	shapes = 5,
	it = 6,
	ty = 7,
	ks = 8,
	k = 9,
	e = 10,
	s = 11
	/*
	assets_layers = 403,
	assets_layers_shapes = 404,
	assets_layers_shapes_ty = 401,
	assets_layers_shapes_ks = 405,
	assets_layers_shapes_ks_k = 406,
	assets_layers_shapes_ks_k_e = 407,
	assets_layers_shapes_ks_k_s = 408,
	assets_layers_it = 424,
	assets_layers_it_ty = 421,
	assets_layers_it_ks = 425,
	assets_layers_it_ks_k = 426,
	assets_layers_it_ks_k_e = 427,
	assets_layers_it_ks_k_s = 428,
	// 
	layers = 503,
	layers_shapes = 504,
	layers_shapes_ty = 501,
	layers_shapes_ks = 505,
	layers_shapes_ks_k = 506,
	layers_shapes_ks_k_e = 507,
	layers_shapes_ks_k_s = 508,
	layers_it = 520,
	layers_it_ty = 521,
	layers_it_ks = 525,
	layers_it_ks_k = 526,
	layers_it_ks_k_e = 527,
	layers_it_ks_k_s = 528,
	//
	gr = 600,
	gr_it = 620,
	gr_it_ty = 621,
	gr_it_ks = 625,
	gr_it_ks_k = 626,
	gr_it_ks_k_e = 627,
	gr_it_ks_k_s = 628
	*/
	};

enum States {
	NoState = 1,
	Start = 2,
	ScopeOpen = 3,
	ScopeClose = 4,
	ScopeOpenInArray = 5,
	ScopeCloseInArray = 6,
	ArrayOpen = 7,
	ArrayClose = 8,
	KVSwitch = 9,
	KVReadOpen = 10,
	KVReading = 11,
	KVReadClose = 12,
	NewElement = 13,
	ScopeToBeRemoved = 14
	};

enum KeyValueState {Key, Value};

enum KeyValueState kvState = Key;

//struct alignas(alignof(struct StateTrail*)) StateTrail {
struct alignas(ALIGNSIZE) StateTrail {
//struct StateTrail {
	struct StateTrail* start = NULL;
	struct StateTrail* prev = NULL;
	struct StateTrail* next = NULL;
	enum States stateNow;
	bool keyEncountered = false;
} *theState;

//struct alignas(alignof(struct ScopeTrail*)) ScopeTrail {
struct alignas(ALIGNSIZE) ScopeTrail {
//struct ScopeTrail {
	char currentTy[KVLEN];

	struct scopeTrail* start = NULL;
	struct ScopeTrail* prev = NULL;
	struct ScopeTrail* next = NULL;

	struct KeyValueTrail* currentKeyValueTrail;
	struct StateTrail* currentState;
	enum Scopes scope;
} *theScope;

struct alignas(ALIGNSIZE) CurrentValues {
	char currentValue[KVLEN];
	char currentReadKey[KVLEN];
	char currentReadValue[KVLEN];

	char currentTy[KVLEN];

	int currentValueLength = 0;
} *input;

string lastValue;
//string currentValue;
string lastRead;

string currentReadValue;
string currentReadKey;

bool readingArray = false;
bool wasReadingArray = false;
bool previousScopeClosure = false;
bool quoteOpened = false;

struct alignas(ALIGNSIZE) ArrayTrail {
	struct ArrayTrail* start = NULL;
	struct ArrayTrail* prev = NULL;
	struct ArrayTrail* next = NULL;
	bool isRoot;
	struct ScopeTrail scopeHere;
} *arrayNow; 

struct alignas(ALIGNSIZE) scopeBefore {
	enum Scopes scopeNow;
	long objectCount = 0;
};




