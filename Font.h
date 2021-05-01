#pragma once

namespace txu
{

//-------------------

#define txuSelectFont(dc, font) { _txBuffer_Select ((HFONT) font, (HDC) dc); }

//-------------------

class Font
{
public :
	Font ();
	Font (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false);
	Font (const Font& that);

	bool create ();
	bool create (const char* name, int size_x, int size_y, int weight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false);
	bool create (const Font& that);

	void setSize (int size_x, int size_y);

	int getSizeX ();
	int getSizeY ();

	void setWeight (int weight);
	int  getWeight ();

	void setItalicEnabled (bool enable);
	bool getItalicEnabled ();

	void setUnderlineEnabled (bool enable);
	bool getUnderlineEnabled ();

	void setStrikeoutEnabled (bool enable);
	bool getStrikeoutEnabled ();

	void        setName (const char* name);
	const char* getName ();

	HFONT getSystemHandle ();

	operator HFONT ();

private :
	const char* name_;

	int size_x_;
	int size_y_;

	int weight_;

	bool italic_;
	bool underline_;
	bool strikeout_;

	HFONT handle_;

	bool update ();
};

//-------------------

Font::Font () :
	name_ (nullptr),

	size_x_    (0),
	size_y_    (0),
	weight_    (0),

	italic_    (false),
	underline_ (false),
	strikeout_ (false)
{ 
	create (); 
}

Font::Font (const char* name, int size_x, int size_y, int weight /*= FW_DONTCARE*/, bool italic /*= false*/, bool underline /*= false*/, bool strikeout /*= false*/) :
	name_ (nullptr),

	size_x_    (0),
	size_y_    (0),
	weight_    (0),

	italic_    (false),
	underline_ (false),
	strikeout_ (false)
{ 
	create (name, size_x, size_y, weight, italic, underline, strikeout); 
}

Font::Font (const Font& that) :
	name_ (nullptr),

	size_x_    (0),
	size_y_    (0),
	weight_    (0),

	italic_    (false),
	underline_ (false),
	strikeout_ (false)
{
	create (that);
}

//-------------------

bool Font::create ()
{
	name_ = "arial";
	
	size_x_ = 30;
	size_y_ = 10;
	
	weight_ = FW_DONTCARE;

	italic_    = false;
	underline_ = false;
	strikeout_ = false;

	handle_ = nullptr;

	return update ();
}

//-------------------

bool Font::create (const char* name, int size_x, int size_y, int weight /*= FW_DONTCARE*/, bool italic /*= false*/, bool underline /*= false*/, bool strikeout /*= false*/)
{
	name_ = name;
	
	size_x_ = size_x;
	size_y_ = size_y;
	
	weight_ = weight;

	italic_    = italic;
	underline_ = underline;
	strikeout_ = strikeout;

	handle_ = nullptr;

	return update ();
}

//-------------------

bool Font::create (const Font& that)
{
	name_ = that.name_;
	
	size_x_ = that.size_x_;
	size_y_ = that.size_y_;
	
	weight_ = that.weight_;

	italic_    = that.italic_;
	underline_ = that.underline_;
	strikeout_ = that.strikeout_;

	handle_ = nullptr;

	return update ();
}

//-------------------

void Font::setSize (int size_x, int size_y)
{
	size_x_ = size_x;
	size_y_ = size_y;

	update ();
}

int Font::getSizeX ()
{
	return size_x_;
}

int Font::getSizeY ()
{
	return size_y_;
}

//-------------------

void Font::setWeight (int weight)
{
	weight_ = weight;
	update ();
}

int Font::getWeight ()
{
	return weight_;
}

//-------------------

void Font::setItalicEnabled (bool enabled)
{
	italic_ = enabled;
	update ();
}

bool Font::getItalicEnabled ()
{
	return italic_;
}

//-------------------

void Font::setUnderlineEnabled (bool enabled)
{
	underline_ = enabled;
	update ();
}

bool Font::getUnderlineEnabled ()
{
	return underline_;
}

//-------------------

void Font::setStrikeoutEnabled (bool enable)
{
	strikeout_ = enable;
}

bool Font::getStrikeoutEnabled ()
{
	return strikeout_;
}

//-------------------

void Font::setName (const char* name)
{
	name_ = name;
	update ();
}

const char* Font::getName ()
{
	return name_;
}

//-------------------

HFONT Font::getSystemHandle ()
{
	return handle_;
}

Font::operator HFONT ()
{
	return getSystemHandle ();
}

//-------------------

bool Font::update ()
{
	handle_ = CreateFontA (size_y_, size_x_, 0, 0, weight_, italic_, underline_, strikeout_, RUSSIAN_CHARSET, 0, 0, 0, 0, name_);
	return handle_ != 0;
}

//-------------------

}
