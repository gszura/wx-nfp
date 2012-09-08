#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "07";
	static const char  _MONTH[] = "09";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.09";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 9;
	static const long  _BUILD = 1123;
	static const long  _REVISION = 1123;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 2446;
	#define  _RC_FILEVERSION 0,9,1123,1123
	#define  _RC_FILEVERSION_STRING "0, 9, 1123, 1123\0"
	static const char  _FULLVERSION_STRING[] = "0.9.1123.1123";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 0;
	

}
#endif //VERSION_H
