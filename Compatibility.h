#pragma once

//-------------------

#ifdef __txu_empty_string
	#undef __txu_epmty_string
#endif

#ifdef __MINGW32__
	#define __txu_empty_string {}
#else
	#define __txu_empty_string ""
#endif

//-------------------

char* __txu_strncpy (char* dst, const char* src, size_t len);
FILE* __txu_fopen   (const char* filename, const char* flags);

unsigned short __txu_byteswap_16 (unsigned short x);
unsigned long  __txu_byteswap_32  (unsigned long  x);

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

FILE* __txu_fopen (const char* filename, const char* flags)
{
	FILE* file = nullptr;

#ifdef __MINGW32__
	file = fopen (filename, flags);
#else
	errno_t err = fopen_s (&file, filename, flags);
	if (err)
		file = nullptr;
#endif

	return file;
}

//-------------------

unsigned short __txu_byteswap_16 (unsigned short x)
{
#ifdef __MINGW32__
	return ((unsigned short) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)));
#else
	return _byteswap_ushort (x);
#endif
}

unsigned long  __txu_byteswap_32  (unsigned long  x)
{
#ifdef __MINGW32__
	return ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8 ) |
	       (( (x) & 0x0000ff00u) << 8 ) | (((x) & 0x000000ffu) << 24));
#else
	return _byteswap_ulong (x);
#endif
}

//-------------------
