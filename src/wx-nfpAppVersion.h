#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "26";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.07";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 8;
	static const long BUILD = 771;
	static const long REVISION = 771;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1788;
	#define RC_FILEVERSION 0,8,771,771
	#define RC_FILEVERSION_STRING "0, 8, 771, 771\0"
	static const char FULLVERSION_STRING[] = "0.8.771.771";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;
	

}
#endif //VERSION_H
