#pragma once

//-------------------

#include "FontLoader.h"

//-------------------

namespace txu
{

//-------------------

class Font
{
public :
	Font ();
	Font (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false);
	Font (const Font& that);

	~Font ();

	bool create ();
	bool create (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false);
	bool create (const Font& that);

	bool loadFromFile (const char* filename);

	void setSize (Coord2D size);
	void setSize (int size_x, int size_y);

	Coord2D getSize  () const;
	int     getSizeX () const;
	int     getSizeY () const;

	void setWeight (int weight);
	int  getWeight () const;

	void setItalicEnabled (bool enable);
	bool getItalicEnabled () const;

	void setUnderlineEnabled (bool enable);
	bool getUnderlineEnabled () const;

	void setStrikeoutEnabled (bool enable);
	bool getStrikeoutEnabled () const;

	void        setName (const char* name);
	const char* getName () const;

	HFONT getSystemHandle ();
	operator HFONT ();

	void select (HDC dc = txDC ()) const;

private :
	const char* m_name;

	char m_loaded_name    [MAX_PATH];
	char m_loaded_filename[MAX_PATH];
	bool m_has_loaded;

	int m_size_x;
	int m_size_y;

	int m_weight;

	bool m_italic;
	bool m_underline;
	bool m_strikeout;

	HFONT m_handle;

	bool update ();
	void unload ();
};

//-------------------

Font::Font () :
	m_name        (nullptr),

	m_loaded_name     {},
	m_loaded_filename {},
	m_has_loaded      (false),

	m_size_x    (0),
	m_size_y    (0),
	m_weight    (0),

	m_italic    (false),
	m_underline (false),
	m_strikeout (false),

	m_handle (nullptr)
{
	create ();
}

Font::Font (const char* name, int size_x, int size_y, int weight /*= FW_DONTCARE*/, bool italic /*= false*/, bool underline /*= false*/, bool strikeout /*= false*/) :
	m_name (nullptr),

	m_loaded_name     {},
	m_loaded_filename {},
	m_has_loaded      (false),

	m_size_x    (0),
	m_size_y    (0),
	m_weight    (0),

	m_italic    (false),
	m_underline (false),
	m_strikeout (false),

	m_handle (nullptr)
{
	create (name, size_x, size_y, weight, italic, underline, strikeout);
}

Font::Font (const Font& that) :
	m_name (nullptr),

	m_loaded_name     {},
	m_loaded_filename {},
	m_has_loaded      (false),

	m_size_x    (0),
	m_size_y    (0),
	m_weight    (0),

	m_italic    (false),
	m_underline (false),
	m_strikeout (false),

	m_handle (nullptr)
{
	create (that);
}

//-------------------

Font::~Font ()
{
	unload ();
}

//-------------------

bool Font::create ()
{
	unload ();

	m_name = "arial";

	m_size_x = 30;
	m_size_y = 10;

	m_weight = FW_DONTCARE;

	m_italic    = false;
	m_underline = false;
	m_strikeout = false;

	m_handle = nullptr;

	return update ();
}

//-------------------

bool Font::create (const char* name, int size_x, int size_y, int weight /*= FW_DONTCARE*/, bool italic /*= false*/, bool underline /*= false*/, bool strikeout /*= false*/)
{
	unload ();

	m_name = name;

	m_has_loaded = false;

	m_size_x = size_x;
	m_size_y = size_y;

	m_weight = weight;

	m_italic    = italic;
	m_underline = underline;
	m_strikeout = strikeout;

	m_handle = nullptr;

	return update ();
}

//-------------------

bool Font::create (const Font& that)
{
	unload ();

	m_name = that.m_name;

	m_size_x = that.m_size_x;
	m_size_y = that.m_size_y;

	m_weight = that.m_weight;

	m_italic    = that.m_italic;
	m_underline = that.m_underline;
	m_strikeout = that.m_strikeout;

	m_handle = nullptr;

	return update ();
}

//-------------------

bool Font::loadFromFile (const char* filename)
{
	unload ();

	if (font_loader::load_fucking_font_record_data_228 (filename, NAMEID_FONT_FAMILY_NAME, m_loaded_name, MAX_PATH)) return false;
	if (!gdi::AddFontResourceExA (filename, FR_NOT_ENUM, 0))                                                        return false;

	__txu_strncpy (m_loaded_filename, filename, MAX_PATH);
	m_name = m_loaded_name;

	m_has_loaded = true;

	return update ();
}

//-------------------

void Font::setSize (txu::Coord2D size)
{
	m_size_x = static_cast <int> (size.x);
	m_size_y = static_cast <int> (size.y);

	update ();
}

void Font::setSize (int size_x, int size_y)
{
	m_size_x = size_x;
	m_size_y = size_y;

	update ();
}

//-------------------

Coord2D Font::getSize () const
{
	return Coord2D (m_size_x, m_size_y);
}

int Font::getSizeX () const
{
	return m_size_x;
}

int Font::getSizeY () const
{
	return m_size_y;
}

//-------------------

void Font::setWeight (int weight)
{
	m_weight = weight;
	update ();
}

int Font::getWeight () const
{
	return m_weight;
}

//-------------------

void Font::setItalicEnabled (bool enabled)
{
	m_italic = enabled;
	update ();
}

bool Font::getItalicEnabled () const
{
	return m_italic;
}

//-------------------

void Font::setUnderlineEnabled (bool enabled)
{
	m_underline = enabled;
	update ();
}

bool Font::getUnderlineEnabled () const
{
	return m_underline;
}

//-------------------

void Font::setStrikeoutEnabled (bool enable)
{
	m_strikeout = enable;
}

bool Font::getStrikeoutEnabled () const
{
	return m_strikeout;
}

//-------------------

void Font::setName (const char* name)
{
	m_name = name;
	update ();
}

const char* Font::getName () const
{
	return m_name;
}

//-------------------

HFONT Font::getSystemHandle ()
{
	return m_handle;
}

Font::operator HFONT ()
{
	return getSystemHandle ();
}

//-------------------

void Font::select (HDC dc /*= txDC ()*/) const
{
	_txBuffer_Select (m_handle, dc);
}

//-------------------

bool Font::update ()
{
	m_handle = gdi::CreateFontA (m_size_y, m_size_x, 0, 0, m_weight, m_italic, m_underline, m_strikeout, RUSSIAN_CHARSET, 0, 0, 0, 0, m_name);
	return m_handle != 0;
}

//-------------------

void Font::unload ()
{
	if (!m_has_loaded) return;
	gdi::RemoveFontResourceA (m_loaded_name);
	gdi::RemoveFontResourceA (m_loaded_name);
	m_has_loaded = false;
}

//-------------------

} // namespace txu
