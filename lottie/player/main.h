int globalObjCount;

#include "jsonstring.h"

enum Scopes {
	_noscope = 0,
	_object = 101,
	_animation = 1,
	_assets = 2,
	_layers = 3,
	_gr = 4,
	_shapes = 5,
	_it = 6,
	_ty = 7,
	_ks = 8,
	_k = 9,
	_e = 10,
	_s = 11,
	_a = 12,
	_p = 13,
	_r = 14,
	_o = 15,
	_sk = 16,
	_sa = 17,
	_c = 18,
	_px = 19,
	_py = 20,
	_pz = 21,
	_i = 22,
	_o = 23
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

// forward declarations
struct ScopeTrail* lastScopeBeforeThis(struct ScopeTrail*);
struct ScopeBefore lastScopeBeforeObject();
struct Layers* newLayers(struct Layers*);
struct ShapesItem* newShapesItem(struct ShapesItem*);
struct PropertiesShape* newPropertiesShape();
struct ShaderProgram* newShaderProgram();


enum KeyValueState {Key, Value};

enum KeyValueState kvState = Key;

//struct alignas(alignof(struct StateTrail*)) StateTrail {
struct alignas(ALIGNSIZE) StateTrail {
//struct StateTrail {
	char reservedKey[KVLEN];
	struct StateTrail* start = NULL;
	struct StateTrail* prev = NULL;
	struct StateTrail* next = NULL;
	enum States stateNow;
	bool reservedKeySet = false;
	bool keyEncountered = false;
} *theState;

//struct alignas(alignof(struct ScopeTrail*)) ScopeTrail {
struct alignas(ALIGNSIZE) ScopeTrail {
//struct ScopeTrail {
	char currentTy[KVLEN];

	struct ScopeTrail* start = NULL;
	struct ScopeTrail* prev = NULL;
	struct ScopeTrail* next = NULL;

	struct KeyValueTrail* currentKeyValueTrail = NULL;
	struct StateTrail* currentState = NULL;
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
char lastTypeEncountered[KVLEN];

bool readingArray = false;
bool wasReadingArray = false;
bool previousScopeClosure = false;
bool quoteOpened = false;
bool scopeChanged = false;
bool justStartedArray = false;
bool colonEncountered = false;
bool previousScopeNotArray = false;
int currentOrderIndex = 0;
bool closedArray = false;
int encounteredKeyframe = 0;

enum States lastClosedScope;
int closureCount = 0;

struct alignas(ALIGNSIZE) ArrayTrail {
	struct ArrayTrail* start = NULL;
	struct ArrayTrail* prev = NULL;
	struct ArrayTrail* next = NULL;
	bool isRoot;
	struct ScopeTrail scopeHere;
} *arrayNow; 

struct alignas(ALIGNSIZE) ScopeBefore {
	struct ScopeTrail* scopeNow;
	long objectCount = 0;
};

struct MainOffset {
	float x = 0;
	float y = 0;
} layersPosition, layersAnchor, shapesPosition, shapesAnchor;

