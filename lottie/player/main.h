int globalObjCount;

string jsonString = "{'v':'5.5.7','fr':60,'ip':0,'op':480,'w':110,'h':110,'nm':'','ddd':0,'assets':[{'id':'comp_0','layers':[{'ddd':0,'ind':2,'ty':4,'nm':'2','td':1,'sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'r':{'a':0,'k':0,'ix':10},'p':{'a':0,'k':[375,667,0],'ix':2},'a':{'a':0,'k':[375,210,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'shapes':[{'ty':'gr','it':[{'ind':0,'ty':'sh','ix':1,'ks':{'a':0,'k':{'i':[[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0]],'o':[[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0]],'v':[[-10.589,-56],[33.176,-56],[4.47,-16.941],[29.882,-16.941],[-30.824,56],[-10.589,4.639],[-33.177,4.639]],'c':true},'ix':2},'nm':' 1','hmn':'ADBE Vector Shape - Group','hd':false},{'ty':'fl','c':{'a':0,'k':[0,0,0,1],'ix':4},'o':{'a':0,'k':100,'ix':5},'r':1,'bm':0,'nm':' 1','mn':'ADBE Vector Graphic - Fill','hd':false},{'ty':'tr','p':{'a':0,'k':[390.668,212.29],'ix':2},'a':{'a':0,'k':[0,0],'ix':1},'s':{'a':0,'k':[100,100],'ix':3},'r':{'a':0,'k':0,'ix':6},'o':{'a':0,'k':100,'ix':7},'sk':{'a':0,'k':0,'ix':4},'sa':{'a':0,'k':0,'ix':5},'nm':''}],'nm':' 1','np':2,'cix':2,'bm':0,'ix':1,'mn':'ADBE Vector Group','hd':false}],'ip':0,'op':478,'st':0,'bm':0},{'ddd':0,'ind':3,'ty':0,'nm':' 1  1','tt':1,'refId':'comp_1','sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'r':{'a':0,'k':0,'ix':10},'p':{'a':1,'k':[{'i':{'x':0.833,'y':0.833},'o':{'x':0.167,'y':0.167},'t':0,'s':[875,737,0],'to':[-180.333,0,0],'ti':[180.333,0,0]},{'t':478,'s':[-207,737,0]}],'ix':2},'a':{'a':0,'k':[750,667,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'w':1500,'h':1334,'ip':0,'op':480,'st':0,'bm':0}]},{'id':'comp_1','layers':[{'ddd':0,'ind':1,'ty':0,'nm':' 1','refId':'comp_2','sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'r':{'a':0,'k':0,'ix':10},'p':{'a':1,'k':[{'i':{'x':0.667,'y':1},'o':{'x':0.333,'y':0},'t':0,'s':[751,628.5,0],'to':[2.5,-25.833,0],'ti':[-2.5,25.833,0]},{'i':{'x':0.667,'y':0.667},'o':{'x':0.333,'y':0.333},'t':120,'s':[766,473.5,0],'to':[0,0,0],'ti':[0,0,0]},{'i':{'x':0.667,'y':1},'o':{'x':0.333,'y':0},'t':240,'s':[766,473.5,0],'to':[-1.5,8,0],'ti':[1,-1.667,0]},{'i':{'x':0.667,'y':1},'o':{'x':0.333,'y':0},'t':300,'s':[757,521.5,0],'to':[-1,1.667,0],'ti':[-0.5,6.333,0]},{'i':{'x':0.667,'y':0.667},'o':{'x':0.333,'y':0.333},'t':360,'s':[760,483.5,0],'to':[0,0,0],'ti':[0,0,0]},{'i':{'x':0.667,'y':1},'o':{'x':0.333,'y':0},'t':420,'s':[760,483.5,0],'to':[-4.5,25.667,0],'ti':[4.5,-25.667,0]},{'t':476,'s':[733,637.5,0]}],'ix':2},'a':{'a':0,'k':[750,667,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'w':1500,'h':1334,'ip':0,'op':480,'st':0,'bm':0}]},{'id':'comp_2','layers':[{'ddd':0,'ind':1,'ty':4,'nm':' 2','sr':1,'ks':{'o':{'a':0,'k':70,'ix':11},'r':{'a':0,'k':0,'ix':10},'p':{'a':0,'k':[753,660,0],'ix':2},'a':{'a':0,'k':[0,0,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'shapes':[{'ty':'gr','it':[{'ind':0,'ty':'sh','ix':1,'ks':{'a':0,'k':{'i':[[57,24],[16,13],[54,-4],[50,59],[65,9],[45,45],[74,47],[19,-23],[63,25],[0,0],[0,0],[0,0],[0,0],[0,0],[25,58],[29,-8]],'o':[[-57,-24],[-16,-13],[-54,4],[-50,-59],[-65,-9],[-45,-45],[-74,-47],[-19,23],[-63,-25],[0,0],[0,0],[0,0],[0,0],[0,0],[-25,-58],[-29,8]],'v':[[425,56],[339,111],[240,83],[155,127],[-2,73],[-84,109],[-192,126],[-358,123],[-462,117],[-574,129],[-559,264],[164,280],[524,263],[569,232],[572,103],[492,100]],'c':true},'ix':2},'nm':' 1','mn':'ADBE Vector Shape - Group','hd':false},{'ty':'fl','c':{'a':0,'k':[0.03529400171,0.705881993911,0.580391977348,1],'ix':4},'o':{'a':0,'k':100,'ix':5},'r':1,'bm':0,'nm':' 1','mn':'ADBE Vector Graphic - Fill','hd':false},{'ty':'tr','p':{'a':0,'k':[0,0],'ix':2},'a':{'a':0,'k':[0,0],'ix':1},'s':{'a':0,'k':[100,100],'ix':3},'r':{'a':0,'k':0,'ix':6},'o':{'a':0,'k':100,'ix':7},'sk':{'a':0,'k':0,'ix':4},'sa':{'a':0,'k':0,'ix':5},'nm':''}],'nm':' 1','np':3,'cix':2,'bm':0,'ix':1,'mn':'ADBE Vector Group','hd':false}],'ip':0,'op':480,'st':0,'bm':0},{'ddd':0,'ind':2,'ty':4,'nm':' 1','sr':1,'ks':{'o':{'a':0,'k':70,'ix':11},'r':{'a':0,'k':0,'ix':10},'p':{'a':0,'k':[816,631,0],'ix':2},'a':{'a':0,'k':[0,0,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'shapes':[{'ty':'gr','it':[{'ind':0,'ty':'sh','ix':1,'ks':{'a':0,'k':{'i':[[112,50],[28,0],[62,0],[48,68],[48,-18],[18,48],[34,-24],[18,50],[10,-2],[76,96],[0,0],[0,0],[0,0],[32,32],[52,-30]],'o':[[-60.295,-26.917],[-28,0],[-62,0],[-48,-68],[-48,18],[-18,-48],[-34,24],[-18,-50],[-10,2],[-76,-96],[0,0],[0,0],[0,0],[-32,-32],[-52,30]],'v':[[265,87],[187,125],[93,105],[7,93],[-109,145],[-191,137],[-315,129],[-365,119],[-421,101],[-483,119],[-601,155],[-603,239],[633,235],[617,115],[461,109]],'c':true},'ix':2},'nm':' 1','mn':'ADBE Vector Shape - Group','hd':false},{'ty':'fl','c':{'a':0,'k':[0.03529400171,0.705881993911,0.580391977348,1],'ix':4},'o':{'a':0,'k':100,'ix':5},'r':1,'bm':0,'nm':' 1','mn':'ADBE Vector Graphic - Fill','hd':false},{'ty':'tr','p':{'a':0,'k':[-2,30],'ix':2},'a':{'a':0,'k':[0,0],'ix':1},'s':{'a':0,'k':[100,100],'ix':3},'r':{'a':0,'k':0,'ix':6},'o':{'a':0,'k':100,'ix':7},'sk':{'a':0,'k':0,'ix':4},'sa':{'a':0,'k':0,'ix':5},'nm':''}],'nm':' 1','np':3,'cix':2,'bm':0,'ix':1,'mn':'ADBE Vector Group','hd':false}],'ip':0,'op':480,'st':0,'bm':0}]}],'layers':[{'ddd':0,'ind':1,'ty':0,'nm':' ','refId':'comp_0','sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'r':{'a':0,'k':0,'ix':10},'p':{'a':0,'k':[55,55,0],'ix':2},'a':{'a':0,'k':[375,667,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'w':750,'h':1334,'ip':0,'op':480,'st':0,'bm':0}],'markers':[]}";

//string jsonString = "{'v':'5.5.8','fr':24,'ip':0,'op':63,'w':900,'h':900,'nm':'Comp 1','ddd':1,'assets':[],'layers':[{'ddd':1,'ind':1,'ty':4,'nm':'Shape Layer 4','parent':4,'sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'rx':{'a':0,'k':0,'ix':8},'ry':{'a':0,'k':270,'ix':9},'rz':{'a':0,'k':0,'ix':10},'or':{'a':0,'k':[0,0,0],'ix':7},'p':{'a':0,'k':[51,0,0],'ix':2},'a':{'a':0,'k':[51,0,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'shapes':[{'ty':'gr','it':[{'ind':0,'ty':'sh','ix':1,'ks':{'a':0,'k':{'i':[[0,0],[0,0],[0,0]],'o':[[0,0],[0,0],[0,0]],'v':[[51.071,102.142],[-51.071,0],[51.071,-102.142]],'c':true},'ix':2},'nm':'Path 1','mn':'ADBE Vector Shape - Group','hd':false},{'ty':'fl','c':{'a':0,'k':[0.125490196078,0.639215686275,0.619607843137,1],'ix':4},'o':{'a':0,'k':100,'ix':5},'r':1,'bm':0,'nm':'Fill 1','mn':'ADBE Vector Graphic - Fill','hd':false},{'ty':'tr','p':{'a':0,'k':[0,0],'ix':2},'a':{'a':0,'k':[0,0],'ix':1},'s':{'a':0,'k':[100,100],'ix':3},'r':{'a':0,'k':0,'ix':6},'o':{'a':0,'k':100,'ix':7},'sk':{'a':0,'k':0,'ix':4},'sa':{'a':0,'k':0,'ix':5},'nm':'Transform'}],'nm':'Shape 1','np':3,'cix':2,'bm':0,'ix':1,'mn':'ADBE Vector Group','hd':false}],'ip':0,'op':658,'st':0,'bm':0},{'ddd':1,'ind':2,'ty':4,'nm':'Shape Layer 3','parent':4,'sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'rx':{'a':0,'k':0,'ix':8},'ry':{'a':0,'k':180,'ix':9},'rz':{'a':0,'k':0,'ix':10},'or':{'a':0,'k':[0,0,0],'ix':7},'p':{'a':0,'k':[51,0,0],'ix':2},'a':{'a':0,'k':[51,0,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'shapes':[{'ty':'gr','it':[{'ind':0,'ty':'sh','ix':1,'ks':{'a':0,'k':{'i':[[0,0],[0,0],[0,0]],'o':[[0,0],[0,0],[0,0]],'v':[[51.071,102.142],[-51.071,0],[51.071,-102.142]],'c':true},'ix':2},'nm':'Path 1','mn':'ADBE Vector Shape - Group','hd':false},{'ty':'fl','c':{'a':0,'k':[0.882352941176,0.333333333333,0.329411764706,1],'ix':4},'o':{'a':0,'k':100,'ix':5},'r':1,'bm':0,'nm':'Fill 1','mn':'ADBE Vector Graphic - Fill','hd':false},{'ty':'tr','p':{'a':0,'k':[0,0],'ix':2},'a':{'a':0,'k':[0,0],'ix':1},'s':{'a':0,'k':[100,100],'ix':3},'r':{'a':0,'k':0,'ix':6},'o':{'a':0,'k':100,'ix':7},'sk':{'a':0,'k':0,'ix':4},'sa':{'a':0,'k':0,'ix':5},'nm':'Transform'}],'nm':'Shape 1','np':3,'cix':2,'bm':0,'ix':1,'mn':'ADBE Vector Group','hd':false}],'ip':0,'op':658,'st':0,'bm':0},{'ddd':1,'ind':3,'ty':4,'nm':'Shape Layer 2','parent':4,'sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'rx':{'a':0,'k':0,'ix':8},'ry':{'a':0,'k':90,'ix':9},'rz':{'a':0,'k':0,'ix':10},'or':{'a':0,'k':[0,0,0],'ix':7},'p':{'a':0,'k':[51,0,0],'ix':2},'a':{'a':0,'k':[51,0,0],'ix':1},'s':{'a':0,'k':[100,100,100],'ix':6}},'ao':0,'shapes':[{'ty':'gr','it':[{'ind':0,'ty':'sh','ix':1,'ks':{'a':0,'k':{'i':[[0,0],[0,0],[0,0]],'o':[[0,0],[0,0],[0,0]],'v':[[51.071,102.142],[-51.071,0],[51.071,-102.142]],'c':true},'ix':2},'nm':'Path 1','mn':'ADBE Vector Shape - Group','hd':false},{'ty':'fl','c':{'a':0,'k':[0.44099222819,0,1,1],'ix':4},'o':{'a':0,'k':100,'ix':5},'r':1,'bm':0,'nm':'Fill 1','mn':'ADBE Vector Graphic - Fill','hd':false},{'ty':'tr','p':{'a':0,'k':[0,0],'ix':2},'a':{'a':0,'k':[0,0],'ix':1},'s':{'a':0,'k':[100,100],'ix':3},'r':{'a':0,'k':0,'ix':6},'o':{'a':0,'k':100,'ix':7},'sk':{'a':0,'k':0,'ix':4},'sa':{'a':0,'k':0,'ix':5},'nm':'Transform'}],'nm':'Shape 1','np':3,'cix':2,'bm':0,'ix':1,'mn':'ADBE Vector Group','hd':false}],'ip':0,'op':658,'st':0,'bm':0},{'ddd':1,'ind':4,'ty':4,'nm':'Shape Layer 1','sr':1,'ks':{'o':{'a':0,'k':100,'ix':11},'rx':{'a':0,'k':312.125,'ix':8},'ry':{'a':1,'k':[{'i':{'x':[0.833],'y':[0.833]},'o':{'x':[0.167],'y':[0.167]},'t':0,'s':[0]},{'t':62,'s':[360]}],'ix':9},'rz':{'a':0,'k':138.742,'ix':10},'or':{'a':0,'k':[0,0,0],'ix':7},'p':{'a':0,'k':[491,406,0],'ix':2},'a':{'a':0,'k':[51,0,0],'ix':1},'s':{'a':0,'k':[249.792,249.792,249.792],'ix':6}},'ao':0,'shapes':[{'ty':'gr','it':[{'ind':0,'ty':'sh','ix':1,'ks':{'a':0,'k':{'i':[[0,0],[0,0],[0,0]],'o':[[0,0],[0,0],[0,0]],'v':[[51.071,102.142],[-51.071,0],[51.071,-102.142]],'c':true},'ix':2},'nm':'Path 1','mn':'ADBE Vector Shape - Group','hd':false},{'ty':'fl','c':{'a':0,'k':[0.639215686275,0.96862745098,0.709803921569,1],'ix':4},'o':{'a':0,'k':100,'ix':5},'r':1,'bm':0,'nm':'Fill 1','mn':'ADBE Vector Graphic - Fill','hd':false},{'ty':'tr','p':{'a':0,'k':[0,0],'ix':2},'a':{'a':0,'k':[0,0],'ix':1},'s':{'a':0,'k':[100,100],'ix':3},'r':{'a':0,'k':0,'ix':6},'o':{'a':0,'k':100,'ix':7},'sk':{'a':0,'k':0,'ix':4},'sa':{'a':0,'k':0,'ix':5},'nm':'Transform'}],'nm':'Shape 1','np':3,'cix':2,'bm':0,'ix':1,'mn':'ADBE Vector Group','hd':false}],'ip':0,'op':658,'st':0,'bm':0}],'markers':[]}";

//#include "jsonstring.h"

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
	_c = 18
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


