#ifdef __TXLIB_H_INCLUDED
	#ifdef __MINGW32__
		#pragma GCC diagnostic push
	#else
		#pragma warning (push)
	#endif

    #include "Compatibility.h"
	#include "Utilits.h"
	#include "Time.h"
	#include "Timer.h"
	#include "Color.h"
	#include "Font.h"
	#include "Coord.h"
	#include "Context.h"

	#ifdef __MINGW32__
		#pragma GCC diagnostic pop
	#else
		#pragma warning (pop)
	#endif

	#define _TXUTILS_INCLUDED
#else
	#error TXUtils: TXLib must be included
#endif