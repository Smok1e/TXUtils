#pragma once

//-------------------

#ifdef __MINGW32__
	#pragma GCC diagnostic ignored "-Wunused-parameter"
	#pragma GCC diagnostic ignored "-Wunused-value"
	#pragma GCC diagnostic ignored "-Wshadow"
	#pragma GCC diagnostic ignored "-Wfloat-equal"
	#pragma GCC diagnostic ignored "-Wreorder"
	#pragma GCC diagnostic ignored "-Weffc++"
	#pragma GCC diagnostic ignored "-Wmissing-declarations"
#else
	#pragma warning (disable: 4100 )
	#pragma warning (disable: 4838 )
	#pragma warning (disable: 26439)
#endif

//-------------------

#ifdef __txu_memcpy
	#undef __txu_memcpy
#endif

#ifdef __MINGW32__
	#define __txu_memcpy memcpy
#else
	#define __txu_memcpy std::memcpy
#endif

//-------------------

char* __txu_strncpy (char* dst, const char* src, size_t len);
FILE* __txu_fopen   (const char* filename, const char* flags);

unsigned __int16 __txu_byteswap_16 (unsigned __int16 x);
unsigned __int32 __txu_byteswap_32 (unsigned __int32 x);

//-------------------

char* __txu_strncpy (char* dst, const char* src, size_t len)
{
	size_t i = 0;
	for (i; i < len && src[i]; i++)
		dst[i] = src[i];

	dst[i] = '\0';

	return dst;
}

//-------------------

FILE* __txu_fopen (const char* filename, const char* mode)
{
	FILE* file = nullptr;

#ifdef __MINGW32__
	file = fopen (filename, mode);
#else
	errno_t err = fopen_s (&file, filename, mode);
	if (err) file = nullptr;
#endif

	return file;
}

//-------------------

unsigned __int16 __txu_byteswap_16 (unsigned __int16 x)
{
#ifdef __MINGW32__
	return ((unsigned __int16) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)));
#else
	return _byteswap_ushort (x);
#endif
}

unsigned __int32  __txu_byteswap_32 (unsigned __int32 x)
{
#ifdef __MINGW32__
	return ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8 ) |
	       (( (x) & 0x0000ff00u) << 8 ) | (((x) & 0x000000ffu) << 24));
#else
	return _byteswap_ulong (x);
#endif
}

//-------------------
