#ifndef __TXUTILS_H_INCLUDED
	#if (not defined (__MINGW32__) and not defined (_MSC_VER)) and not defined (_TXU_COMPILER_NO_WARNINGS)
		#error TXUtils: This compiler is not supported by TXUtils. Define _TXU_COMPILER_NO_WARNINGS before including TXUtils to disable this deprecation
	#endif

	#ifdef __TXLIB_H_INCLUDED
		#ifdef __MINGW32__
			#pragma GCC diagnostic push
		#else
			#pragma warning (push)
		#endif

	    #include "Compatibility.h"
		#include "Filesystem.h"
		#include "Utilits.h"
		#include "Time.h"
		#include "Timer.h"
		#include "Color.h"
		#include "Coord.h"
		#include "Font.h"
		#include "Context.h"
		#include "Sound.h"
		#include "Ini.h"

		#ifdef __MINGW32__
			#pragma GCC diagnostic pop
		#else
			#pragma warning (pop)
		#endif

		#define __TXUTILS_H_INCLUDED

	#else
		#error TXUtils: TXLib must be included
	#endif
#endif