#pragma once

//-------------------

#ifdef TXU_USE_PNG
	#include "PngLoader.h"
#endif

//-------------------

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

	void clear ();
	void clear (Color color);

	void capture (HWND wnd = nullptr);

	operator HDC& ();

	RGBQUAD* getBuffer       ();
	size_t   getBufferLength ();

	RGBQUAD* access (size_t index);
	RGBQUAD* access (int x, int y);

	void  setPixel (int x, int y, Color color, bool blend = true);
	Color getPixel (int x, int y);

	void setColor     (Color color, int thikness = 0);
	void setFillColor (Color color);

	void setFont (HFONT font);

	void setFont (const char *name, int sx, int sy = -1, int bold = FW_DONTCARE, 
		          bool italic = false, bool underline = false, bool strikeout = false, 
		          double angle = 0);

private :
	RGBQUAD* m_buffer;
	HDC      m_dc;

	int m_size_x;
	int m_size_y;

	void destruct ();
};

//-------------------

Context::Context () :
	m_buffer (nullptr),
	m_dc     (nullptr),

	m_size_x (0),
	m_size_y (0)
{
	create (); 
}

Context::Context (int size_x, int size_y) :
	m_buffer (nullptr),
	m_dc     (nullptr),

	m_size_x (0),
	m_size_y (0)
{
	create (size_x, size_y); 
}

Context::Context (const Context& that) :
	m_buffer (nullptr),
	m_dc     (nullptr),

	m_size_x (0),
	m_size_y (0)
{
	create (that); 
}

Context::Context (const HDC& dc) :
	m_buffer (nullptr),
	m_dc     (nullptr),

	m_size_x (0),
	m_size_y (0)
{
	create (dc); 
}

Context::Context (const char* filename) :
	m_buffer (nullptr),
	m_dc     (nullptr),

	m_size_x (0),
	m_size_y (0)
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

	m_size_x = size_x;
	m_size_y = size_y;
	m_dc = txCreateDIBSection (m_size_x, m_size_y, &m_buffer);

	return m_dc != 0;
}

bool Context::create (const Context& that)
{
	create (that.m_size_x, that.m_size_y);
	txBitBlt (m_dc, 0, 0, 0, 0, that.m_dc);

	return m_dc != 0;
}

bool Context::create (const HDC& dc)
{
	create (txGetExtentX (dc), txGetExtentY (dc));
	txBitBlt (m_dc, 0, 0, 0, 0, dc);

	return m_dc != 0;
}

bool Context::create (const char* filename)
{
	return loadFromFile (filename);
}

//-------------------

void Context::destruct ()
{
	if (!m_dc) return;
	txDeleteDC (m_dc);

	m_dc     = nullptr;
	m_buffer = nullptr;
	m_size_x = 0;
	m_size_y = 0;
}

//-------------------

bool Context::loadFromFile (const char* filename)
{
#ifdef TXU_USE_PNG
	if (!png_loader::check_signature (filename))
	{
		RGBQUAD* buffer = nullptr;
		int      sx     = 0;
		int      sy     = 0;

		if (png_loader::load_png (&buffer, &sx, &sy, filename))
			return false;
		
		resize (sx, sy);

		for (size_t i = 0; i < static_cast <size_t> (sx*sy); i++)
			m_buffer[i] = buffer[i];

		delete[] (buffer);

		return true;
	}
#endif

	HDC dc = txLoadImage (filename);
	if (!dc) return false;
	create (dc);
	txDeleteDC (dc);

	return true;
}

//-------------------

bool Context::saveToFile (const char* filename)
{
#ifdef TXU_USE_PNG
	const char* extention = txu::shellapi::PathFindExtensionA (filename);

	if (!strcmp (extention, ".png"))
		return !txu::png_loader::write_png (m_buffer, m_size_x, m_size_y, filename);
#endif

	return txSaveImage (filename, m_dc);
}

//-------------------

int Context::getSizeX ()
{
	return m_size_x;
}

int Context::getSizeY ()
{
	return m_size_y;
}

void Context::resize (int new_size_x, int new_size_y)
{
	if (new_size_x == m_size_x && new_size_y == m_size_y) return;

	HDC new_dc = txCreateDIBSection (new_size_x, new_size_y, &m_buffer);
	if (m_dc) txBitBlt (new_dc, 0, 0, 0, 0, m_dc);
	
	std::swap (m_dc, new_dc);
	
	txDeleteDC (new_dc);

	m_size_x = new_size_x;
	m_size_y = new_size_y;
}

//-------------------

Context::operator HDC& ()
{
	return m_dc;
}

//-------------------

RGBQUAD* Context::getBuffer ()
{
	return m_buffer;
}

size_t Context::getBufferLength ()
{
	return m_size_x*m_size_y;
}

RGBQUAD* Context::access (size_t index)
{
#ifdef _DEBUG
	if (static_cast <int> (index) >= m_size_x*m_size_y) return nullptr;
#endif

	return m_buffer + index;
}

RGBQUAD* Context::access (int x, int y)
{
	y = m_size_y - y-1;

#ifdef _DEBUG
	if (x < 0 || x >= m_size_x || y < 0 || y >= m_size_y) return nullptr;
#endif

	return m_buffer + y*m_size_x + x;
}

//-------------------

void Context::render (HDC dc /*= txDC ()*/, int x /*= 0*/, int y /*= 0*/, int width /*= 0*/, int height /*= 0*/)
{
	txBitBlt (dc, x, y, width, height, m_dc);
}

//-------------------

void Context::clear ()
{
	txClear (m_dc);
}

void Context::clear (Color color)
{
	Color last_fillcolor = txGetFillColor (m_dc);
	setFillColor (color);
	txClear (m_dc);
	setFillColor (last_fillcolor);
}

//-------------------

void Context::capture (HWND wnd /*= nullptr*/)
{
	HDC capture = GetDC (wnd);
	create (capture);
	txDeleteDC (capture);
}

//-------------------

void Context::setPixel (int x, int y, Color color, bool blend /*= true*/)
{
	y = m_size_y - y-1;
	if (x < 0 || x >= m_size_x || y < 0 || y >= m_size_y) return;

	int index = x + y*m_size_x;
	m_buffer[index] = (blend && color.a < 255) ? (m_buffer[index] <<= color) : color;
}

//-------------------

Color Context::getPixel (int x, int y)
{
	y = m_size_y - y-1;
	if (x < 0 || x >= m_size_x || y < 0 || y >= m_size_y) return Color::Black;

	int index = x + y * m_size_x;
	return txu::Color (m_buffer[index]);
}

//------------------

void Context::setColor (Color color, int thikness /*= 0*/)
{
	txSetColor (color, thikness, m_dc);
}

//------------------

void Context::setFillColor (Color color)
{
	txSetFillColor (color, m_dc);
}

//------------------

void Context::setFont (HFONT font)
{
	_txBuffer_Select (font, m_dc);
}

//------------------

void Context::setFont (const char * name, int sx, int sy /*= -1*/, int bold /*= FW_DONTCARE*/, 
	                   bool italic /*= false*/, bool underline /*= false*/, bool strikeout /*= false*/, 
	                   double angle /*= 0*/)
{
	txSelectFont (name, sx, sy, bold, italic, underline, strikeout, angle, m_dc);
}

//------------------

} // namespace txu