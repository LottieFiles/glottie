#ifndef _libglottie_DLLRELATED_H_
#define _libglottie_DLLRELATED_H_

/* Cmake will define MyLibrary_EXPORTS on Windows when it
configures to build a shared library. If you are going to use
another build system on windows or create the visual studio
projects by hand you need to define MyLibrary_EXPORTS when
building a DLL on windows.
*/
// We are using the Visual Studio Compiler and building Shared libraries

#if defined (_WIN32)
	#if defined(libglottie_EXPORTS)
		#define  MYLIB_EXPORT __declspec(dllexport)
	#else
		#define  MYLIB_IMPORT __declspec(dllimport)
	#endif /* MyLibrary_EXPORTS */
#else /* defined (_WIN32) */
	#define MYLIB_EXPORT
#endif

#endif /* _MyLibrary_DLLDEFINES_H_ */
