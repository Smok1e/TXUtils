#pragma once

//-------------------

#include <png.h>

//-------------------

namespace txu
{

namespace png_loader
{

//-------------------

bool check_signature (const char* filename);
const char* load_png (RGBQUAD** buffer, int* sx, int* sy, const char* filename);

//-------------------

bool check_signature (const char* filename)
{
	const char png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};

	FILE* file = nullptr;
	errno_t err = fopen_s (&file, filename, "rb");
	if (err || !file)
		return false;

	char header[8] = "";
	fread (header, 1, 8, file);

	fclose (file);

	return !strncmp (header, png_signature, 8);
}

//-------------------

const char* load_png (RGBQUAD** buffer, int* sx, int* sy, const char* filename)
{
	if (!check_signature (filename))
		return "Wrong png file signature";

	FILE* file = nullptr;
	errno_t err = fopen_s (&file, filename, "rb");
	if (err || !file)
		return "Failed to open file";

	png_structp png_ptr  = png_create_read_struct (PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop   info_ptr = png_create_info_struct (png_ptr);

    png_init_io       (png_ptr, file    );
	png_set_sig_bytes (png_ptr, 0       );
    png_read_info     (png_ptr, info_ptr);

    int size_x = png_get_image_width  (png_ptr, info_ptr);
    int size_y = png_get_image_height (png_ptr, info_ptr);

    png_byte cnahhels  = png_get_channels  (png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth (png_ptr, info_ptr);

    int number_of_passes = png_set_interlace_handling (png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    png_byte ** row_pointers = new png_byte * [size_y];

    for (int y = 0; y < size_y; y++)
		row_pointers[y] = new png_byte [png_get_rowbytes (png_ptr, info_ptr)];

    png_read_image (png_ptr, row_pointers);
	fclose (file);

	RGBQUAD* buff = new RGBQUAD [size_x*size_y];
	for (size_t i = 0; i < size_x*size_y; i++)
		buff[i] = {24, 24, 24};

	for (int y = 0; y < size_y; y++)
	{
		png_byte* row = row_pointers[y];

		for (int x = 0; x < size_x; x++)
		{
			png_byte * begin = row + x*cnahhels;
			txu::Color color;

			switch (cnahhels)
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

	*buffer = buff;
	*sx     = size_x;
	*sy     = size_y;

	return nullptr;
}

//-------------------

}

}