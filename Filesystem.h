#pragma once

//-------------------

namespace txu
{

//-------------------

size_t fsize (FILE* file);

template <typename obj_t>
size_t freadobj (FILE* file, obj_t* obj);

template <typename obj_t>
size_t fwriteobj (FILE* file, obj_t* obj);

//-------------------

size_t fsize (FILE* file)
{
	size_t position = ftell (file);
	
	fseek (file, 0, SEEK_END);
	size_t size = ftell (file);
	
	fseek (file, position, SEEK_SET);
	return size;
}

//-------------------

template <typename obj_t>
size_t freadobj (FILE* file, obj_t* obj)
{
	return fread (obj, sizeof (obj_t), 1, file);
}

template <typename obj_t>
size_t fwriteobj (FILE* file, obj_t* obj)
{
	return fwrite (obj, sizeof (obj_t), 1, file);
}

//-------------------

} // namespace txu