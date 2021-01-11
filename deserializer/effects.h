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

enum EffectsTy {
		_slider = 10,
		_noValue = 1000,
		_customValue = 1010,
		_proLevels = 23,
		_angle = 1,
		_color = 2,
		_checkbox = 7,
		_group = 5,
		_dropDown = 7,
		_point = 2,
		_layer = 0,
		_tint = 20,
		_fill = 21,
		_stroke = 22,
		_tritone = 23
	};

#ifdef EMT
struct alignas(ALIGNSIZE) Effects {
#else
struct Effects {
#endif
	struct Effects* start =  NULL;
	struct Effects* prev = NULL;
	struct Effects* next = NULL;

	int ix;
	enum EffectsTy ty;
	string mn; // match name
	string nm; // name

	struct PropertiesValue* v_value;
	struct PropertiesMultiDimensional* v_multi;

	struct Effects* ef;
	
} currentEffects;



