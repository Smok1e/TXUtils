#ifndef __TXUTILS_H_INCLUDED
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