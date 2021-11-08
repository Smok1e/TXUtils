#pragma once

//-------------------

namespace txu
{

//-------------------

size_t fsize (FILE* file);

template <typename obj_t>
void freadobj (FILE* file, obj_t* obj);

template <typename obj_t>
void mreadobj (obj_t* obj, const char* data);

template <typename obj_t>
void fwriteobj (FILE* file, obj_t* obj);

template <typename obj_t>
void mwriteobj (const char* data, obj_t* obj);

//-------------------

size_t fsize (FILE* file)
{
	long position = ftell (file);
	
	fseek (file, 0, SEEK_END);
	size_t size = ftell (file);
	
	fseek (file, position, SEEK_SET);
	return size;
}

//-------------------

template <typename obj_t>
void freadobj (FILE* file, obj_t* obj)
{
	fread (obj, sizeof (obj_t), 1, file);
}

template <typename obj_t>
void mreadobj (obj_t* obj, const char* data)
{
	__txu_memcpy (obj, data, sizeof (obj_t));
}

//-------------------

template <typename obj_t>
void fwriteobj (FILE* file, obj_t* obj)
{
	fwrite (obj, sizeof (obj_t), 1, file);
}

template <typename obj_t>
void mwriteobj (const char* data, obj_t* obj)
{
	__txu_memcpy (data, obj, sizeof (obj_t));
}

//-------------------

} // namespace txu