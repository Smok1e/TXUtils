#pragma once

//-------------------

#include <png.h>

//-------------------

namespace txu
{

namespace png_loader
{

//-------------------

const char* check_signature (const char* filename);
const char* load_png (RGBQUAD** buffer, int* sx, int* sy, const char* filename);

//-------------------

const char* check_signature (const char* filename)
{
	const char png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};

	FILE* file = nullptr;
	errno_t err = fopen_s (&file, filename, "rb");
	if (err || !file)
		return "Failed to open file";

	char header[8] = "";
	fread (header, 1, 8, file);

	fclose (file);

	if (strncmp (header, png_signature, 8))
		return "Wrong png file signature";

	return nullptr;
}

//-------------------

const char* load_png (RGBQUAD** buffer, int* sx, int* sy, const char* filename)
{
	const char* sign_err = check_signature (filename);
	if (sign_err)
		return sign_err;

	png_struct* readstruct = png_create_read_struct (PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!readstruct)
		return "Failed to create read struct";

    png_info* infostruct = png_create_info_struct (readstruct);
	if (!infostruct)
		return "Failed to create info struct";

	FILE* file = nullptr;
	errno_t err = fopen_s (&file, filename, "rb");
	if (err || !file)
		return "Failed to open file";

    png_init_io       (readstruct, file    );
	png_set_sig_bytes (readstruct, 0       );
    png_read_info     (readstruct, infostruct);

    int size_x = png_get_image_width  (readstruct, infostruct);
    int size_y = png_get_image_height (readstruct, infostruct);

    png_byte cnannels = png_get_channels  (readstruct, infostruct);

    png_read_update_info (readstruct, infostruct);

    png_byte** row_pointers = new png_byte* [size_y];
    for (int y = 0; y < size_y; y++)
		row_pointers[y] = new png_byte [png_get_rowbytes (readstruct, infostruct)];

    png_read_image (readstruct, row_pointers);
	fclose (file);

	RGBQUAD* buff = new RGBQUAD [size_x*size_y];
	for (int y = 0; y < size_y; y++)
	{
		png_byte* row = row_pointers[y];

		for (int x = 0; x < size_x; x++)
		{
			png_byte* begin = row + x*cnannels;
			Color color;

			switch (cnannels)
			{				
				case 1:
					color = txu::Color (*(begin+0), *(begin+0), *(begin+0));
					break;

				case 2:
					color = txu::Color (*(begin+0), *(begin+0), *(begin+0), *(begin)+1);
					break;

				case 3:
					color = txu::Color (*(begin+0), *(begin+1), *(begin+2));
					break;

				case 4:
					color = txu::Color (*(begin+0), *(begin+1), *(begin+2), *(begin+3));
					break;

				default:
					color = txu::Color::Red;
			}

			size_t index = (size_y-y-1)*size_x+x;
			buff [index] = color.rgbquad;
		}
	}

	for (int y = 0; y < size_y; y++)
		delete[] (row_pointers[y]);
	
	delete[] (row_pointers);

	*buffer = buff;
	*sx     = size_x;
	*sy     = size_y;

	png_destroy_info_struct ( readstruct, &infostruct             );
	png_destroy_read_struct (&readstruct, &infostruct, &infostruct);

	return nullptr;
}

//-------------------

const char* write_png (RGBQUAD* buffer, int size_x, int size_y, const char* filename)
{
	png_struct* pngstruct = png_create_write_struct (PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!pngstruct)
		return "Failed to create png struct";

	png_info* infostruct = png_create_info_struct (pngstruct);
	if (!infostruct)
		return "Failed to create info struct";

	FILE* file = nullptr;
	errno_t err = fopen_s (&file, filename, "wb");

	if (err && !file)
		return "Failed to open file";

	png_set_IHDR
	(
		pngstruct,
		infostruct,
		size_x, size_y,
		8,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);

	png_byte** row_pointers = new png_byte* [size_y];

	for (int y = 0; y < size_y; y++)
	{
		png_byte* row = new png_byte[size_x*4];
		row_pointers[y] = row;

		for (int x = 0; x < size_x; x++)
		{
			txu::Color color = buffer[(size_y-y-1)*size_x + x];

			row[x*4+0] = color.r;
			row[x*4+1] = color.g;
			row[x*4+2] = color.b;
			row[x*4+3] = color.a;
		}
	}

	png_init_io    (pngstruct, file);
	png_write_info (pngstruct, infostruct);
    png_set_rows   (pngstruct, infostruct, row_pointers);
    png_write_png  (pngstruct, infostruct, PNG_TRANSFORM_IDENTITY, nullptr);

	for (int y = 0; y < size_y; y++)
		delete[] (row_pointers[y]);

	delete[] (row_pointers);

	png_destroy_info_struct  ( pngstruct, &infostruct);
	png_destroy_write_struct (&pngstruct, &infostruct);
	fclose (file);

	return nullptr;
}

//-------------------

}

}