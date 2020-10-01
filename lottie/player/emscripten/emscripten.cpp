#include <string>

using namespace std;

string ems_getString (string varName) {
    
	int length = //EM_ASM_INT ({
		return eval(
			'Module.lengthBytesUTF8(' + Module.Pointer_stringify($0) + ')'
		)}, varName.c_str()
	);
    
	string s;
	s.reserve (length+1);
	s.resize (length);
    
	//EM_ASM_ ({
		eval('Module.stringToUTF8 ('
			+ Module.Pointer_stringify($0) + ', $1, $2)'
		)}, varName.c_str(),
			s.c_str(), s.size()
	);

	return s;
}

int ems_sendString (string varName) {
	return 1;
}

