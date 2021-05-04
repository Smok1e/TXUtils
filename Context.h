#pragma once

namespace txu
{

//-------------------

class Context
{
public :
	Context ();
	Context (int size_x, int size_y);
	Context (const Context& that);
	Context (const HDC& dc);
	Context (const char* filename);

	~Context ();

	bool create ();
	bool create (int size_x, int size_y);
	bool create (const Context& that);
	bool create (const HDC& dc);
	bool create (const char* filename);

	bool loadFromFile (const char* filename);
	bool saveToFile   (const char* filename);

	int getSizeX ();
	int getSizeY ();
	void resize  (int new_size_x, int new_size_y);

	void render (HDC dc = txDC (), int x = 0, int y = 0, int width = 0, int height = 0);

	void clear (Color color);

	operator HDC& ();

	RGBQUAD* getBuffer       ();
	size_t   getBufferLength ();

	RGBQUAD* access (size_t index);
	RGBQUAD* access (int x, int y);

	void  setPixel (int x, int y, Color color);
	Color getPixel (int x, int y);

	void setColor     (Color color, int thikness = 0);
	void setFillColor (Color color);

	void setFont (HFONT font);

	void setFont (const char *name, int sx, int sy = -1, int bold = FW_DONTCARE, 
		          bool italic = false, bool underline = false, bool strikeout = false, 
		          double angle = 0);

private :
	RGBQUAD* buffer_;
	HDC      dc_;

	int size_x_;
	int size_y_;

	void destruct ();
};

//-------------------

Context::Context () :
	buffer_ (nullptr),
	dc_     (nullptr),

	size_x_ (0),
	size_y_ (0)
{
	create (); 
}

Context::Context (int size_x, int size_y) :
	buffer_ (nullptr),
	dc_     (nullptr),

	size_x_ (0),
	size_y_ (0)
{
	create (size_x, size_y); 
}

Context::Context (const Context& that) :
	buffer_ (nullptr),
	dc_     (nullptr),

	size_x_ (0),
	size_y_ (0)
{
	create (that); 
}

Context::Context (const HDC& dc) :
	buffer_ (nullptr),
	dc_     (nullptr),

	size_x_ (0),
	size_y_ (0)
{
	create (dc); 
}

Context::Context (const char* filename) :
	buffer_ (nullptr),
	dc_     (nullptr),

	size_x_ (0),
	size_y_ (0)
{
	create (filename); 
}

//-------------------

Context::~Context ()
{
	destruct ();
}

//-------------------

bool Context::create ()
{
	return create (0, 0);
}

bool Context::create (int size_x, int size_y)
{
	destruct ();

	if (size_x == 0) size_x = 1;
	if (size_y == 0) size_y = 1;

	size_x_ = size_x;
	size_y_ = size_y;
	dc_ = txCreateDIBSection (size_x_, size_y_, &buffer_);

	return dc_ != 0;
}

bool Context::create (const Context& that)
{
	create (that.size_x_, that.size_y_);
	txBitBlt (dc_, 0, 0, 0, 0, that.dc_);

	return dc_ != 0;
}

bool Context::create (const HDC& dc)
{
	create (txGetExtentX (dc), txGetExtentY (dc));
	txBitBlt (dc_, 0, 0, 0, 0, dc);

	return dc_ != 0;
}

bool Context::create (const char* filename)
{
	return loadFromFile (filename);
}

//-------------------

void Context::destruct ()
{
	if (!dc_) return;
	txDeleteDC (dc_);

	dc_     = nullptr;
	buffer_ = nullptr;
	size_x_ = 0;
	size_y_ = 0;
}

//-------------------

bool Context::loadFromFile (const char* filename)
{
	HDC dc = txLoadImage (filename);
	if (!dc) return false;
	create (dc);
	txDeleteDC (dc);

	return true;
}

//-------------------

bool Context::saveToFile (const char* filename)
{
	return txSaveImage (filename, dc_);
}

//-------------------

int Context::getSizeX ()
{
	return size_x_;
}

int Context::getSizeY ()
{
	return size_y_;
}

void Context::resize (int new_size_x, int new_size_y)
{
	if (new_size_x == size_x_ && new_size_y == size_y_) return;

	HDC new_dc = txCreateDIBSection (new_size_x, new_size_y, &buffer_);
	if (dc_) txBitBlt (new_dc, 0, 0, 0, 0, dc_);
	
	std::swap (dc_, new_dc);
	
	txDeleteDC (new_dc);

	size_x_ = new_size_x;
	size_y_ = new_size_y;
}

//-------------------

Context::operator HDC& ()
{
	return dc_;
}

//-------------------

RGBQUAD* Context::getBuffer ()
{
	return buffer_;
}

size_t Context::getBufferLength ()
{
	return size_x_*size_y_;
}

RGBQUAD* Context::access (size_t index)
{
	if (index >= size_x_*size_y_) return nullptr;
	return buffer_ + index;
}

RGBQUAD* Context::access (int x, int y)
{
	y = size_y_ - y-1;
	if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_)	return nullptr;
	size_t index = y*size_x_ + x;
	return buffer_ + index;
}

//-------------------

void Context::render (HDC dc /* = txDC () */, int x /* = 0 */, int y /* = 0 */, int width /* = 0 */, int height /* = 0 */)
{
	txBitBlt (dc, x, y, width, height, dc_);
}

//-------------------

void Context::clear (Color color)
{
	Color last_fillcolor = txGetFillColor (dc_);
	setFillColor (color);
	txClear (dc_);
	setFillColor (last_fillcolor);
}

//-------------------

void Context::setPixel (int x, int y, Color color)
{
	y = size_y_ - y-1;

	if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) return;

	int index = x + y*size_x_;
	buffer_[index] = (color.a < 255) ? (buffer_[index] <<= color) : color;
}

//-------------------

Color Context::getPixel (int x, int y)
{
	y = size_y_ - y-1;

	if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) return Color::Black;

	int index = x + y * size_x_;

	return txu::Color (buffer_[index]);
}

//------------------

void Context::setColor (Color color, int thikness /*= 0*/)
{
	txSetColor (color, thikness, dc_);
}

//------------------

void Context::setFillColor (Color color)
{
	txSetFillColor (color, dc_);
}

//------------------

void Context::setFont (HFONT font)
{
	_txBuffer_Select (font, dc_);
}

//------------------

void Context::setFont (const char * name, int sx, int sy /*= -1*/, int bold /*= FW_DONTCARE*/, 
	                          bool italic /*= false*/, bool underline /*= false*/, bool strikeout /*= false*/, 
	                          double angle /*= 0*/)
{
	txSelectFont (name, sx, sy, bold, italic, underline, strikeout, angle, dc_);
}

//------------------

}