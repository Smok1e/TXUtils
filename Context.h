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
public:
	class Iterator
	{
	public:
		class PixelReference
		{
		public:
			PixelReference (RGBQUAD* reference_pixel);
			PixelReference (const PixelReference& copy);

			operator Color    ();
			operator RGBQUAD  ();
			operator COLORREF ();

			PixelReference& operator = (const Color& color);

		private:
			RGBQUAD* m_reference_pixel;

		};

		Iterator (txu::Context* reference_context, int reference_x);
		Iterator (const Iterator& copy);

		txu::Context* getReferenceContext ();
		int           getReferenceX       () const;

		PixelReference operator [] (int y);			

	private:
		txu::Context* m_reference_context;
		int           m_reference_x;

	};

	Context ();
	Context (int size_x, int size_y);
	Context (Coord2D size);
	Context (const Context& that);
	Context (const HDC& dc);
	Context (const char* filename);

	~Context ();

	bool create ();
	bool create (int size_x, int size_y);
	bool create (Coord2D size);
	bool create (const Context& that);
	bool create (const HDC& dc);
	bool create (const char* filename);

	bool loadFromFile (const char* filename);
	bool saveToFile   (const char* filename) const;

	Coord2D getSize  () const;
	int     getSizeX () const;
	int     getSizeY () const;
	void    resize   (int new_size_x, int new_size_y);

	void render (HDC dc = txDC (), int dst_x = 0, int dst_y = 0, int width = 0, int height = 0,
		         int src_x = 0, int src_y = 0, unsigned operation = SRCCOPY) const;

	void clear ();
	void clear (Color color);

	void capture (HWND wnd = nullptr);

	HCURSOR makeCursor (txu::Color alpha, int x_hot_spot = -1, int y_hot_spot = -1);

	Iterator                 operator [] (int x);
	Iterator::PixelReference operator [] (const Coord2D& coord);

	operator HDC& ();

	RGBQUAD* getBuffer       ();
	size_t   getBufferLength ();

	RGBQUAD* access (size_t index);
	RGBQUAD* access (int x, int y);

	void  setPixel (int x, int y, Color color, bool blend = true);
	Color getPixel (int x, int y) const;

	void setColor     (Color color, int thikness = 0);
	void setFillColor (Color color);

	void setFont (HFONT font);

	void setFont (const char *name, int sy, int sx = -1, int bold = FW_DONTCARE,
		          bool italic = false, bool underline = false, bool strikeout = false,
		          double angle = 0);

private:
	RGBQUAD* m_buffer;
	HDC      m_dc;

	int m_size_x;
	int m_size_y;

	void destruct ();
};

//-------------------

Context::Iterator::PixelReference::PixelReference (RGBQUAD* reference_pixel):
	m_reference_pixel (reference_pixel)
{}

Context::Iterator::PixelReference::PixelReference (const PixelReference& copy):
	m_reference_pixel (copy.m_reference_pixel)
{}

//-------------------

Context::Iterator::PixelReference::operator Color ()
{
	return Color (*m_reference_pixel);
}

Context::Iterator::PixelReference::operator RGBQUAD ()
{
	return Color (*m_reference_pixel).operator RGBQUAD ();
}

Context::Iterator::PixelReference::operator COLORREF ()
{
	return Color (*m_reference_pixel).operator COLORREF ();
}

//-------------------

Context::Iterator::PixelReference& Context::Iterator::PixelReference::operator = (const Color& color)
{
	*m_reference_pixel = (color.a < 255) ? (*m_reference_pixel <<= color) : color;
	return *this;
}

//-------------------

Context::Iterator::Iterator (Context* reference_context, int reference_x):
	m_reference_context (reference_context),
	m_reference_x       (reference_x      )
{}

Context::Iterator::Iterator (const Context::Iterator& copy):
	m_reference_context (copy.m_reference_context),
	m_reference_x       (copy.m_reference_x      )
{}

//-------------------

Context* Context::Iterator::getReferenceContext ()
{
	return m_reference_context;
}

int Context::Iterator::getReferenceX () const
{
	return m_reference_x;		
}

//-------------------

Context::Iterator::PixelReference Context::Iterator::operator [] (int y)
{
	return PixelReference (m_reference_context -> access (m_reference_x, y));
}	

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

Context::Context (Coord2D size) :
	m_buffer (nullptr),
	m_dc     (nullptr),

	m_size_x (0),
	m_size_y (0)
{
	create (size);
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

bool Context::create (Coord2D size)
{
	return create (static_cast <int> (size.x), static_cast <int> (size.y));
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

bool Context::saveToFile (const char* filename)	const
{
#ifdef TXU_USE_PNG
	const char* extention = txu::shellapi::PathFindExtensionA (filename);

	if (!strcmp (extention, ".png"))
		return !txu::png_loader::write_png (m_buffer, m_size_x, m_size_y, filename);
#endif

	return txSaveImage (filename, m_dc);
}

//-------------------

Coord2D Context::getSize () const
{
	return txu::Coord2D (m_size_x, m_size_y);
}

int Context::getSizeX () const
{
	return m_size_x;
}

int Context::getSizeY () const
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

Context::Iterator Context::operator [] (int x)
{
	return Iterator (this, x);
}

Context::Iterator::PixelReference Context::operator [] (const Coord2D& coord)
{
	return Iterator::PixelReference (access (txCoordInt (coord)));
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

void Context::render (HDC dc /*= txDC ()*/, int dst_x /*= 0*/, int dst_y /*= 0*/, int width /*= 0*/, int height /*= 0*/,
	                  int src_x /*= 0*/, int src_y /*= 0*/, unsigned operation /*= SRCCOPY*/) const
{
	txBitBlt (dc, dst_x, dst_y, width, height, m_dc, src_x, src_y, operation);
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

HCURSOR Context::makeCursor (txu::Color alpha, int x_hot_spot /*= -1*/, int y_hot_spot /*= -1*/)
{
	return nullptr;

	/* IN DEVELOPMENT

	x_hot_spot = Clamp (x_hot_spot >= 0? x_hot_spot: m_size_x / 2, 0, m_size_x);
	y_hot_spot = Clamp (y_hot_spot >= 0? y_hot_spot: m_size_y / 2, 0, m_size_y);
	
	unsigned char* ANDMask = new unsigned char[m_size_x*m_size_y*3];
	unsigned char* XORMask = new unsigned char[m_size_x*m_size_y*3];

	for (int x = 0; x < m_size_x; x++)
	for (int y = 0; y < m_size_y; y++)
	{
		int index = x + (m_size_y - y-1)*m_size_x;
		txu::Color pixel = getPixel (x, y);

		if (pixel == alpha)
		{
			ANDMask[index*3] = 0x00FFFFFF;
			XORMask[index*3] = 0x00000000;
		}

		else
		{
			*(&ANDMask[index*3]) = 0x00000000;	
			*(&XORMask[index*3]) = pixel;
		}
	}

	HCURSOR cursor = CreateCursor (GetModuleHandleA (nullptr), x_hot_spot, y_hot_spot, m_size_x, m_size_y, ANDMask, XORMask);
	
	delete[] (ANDMask);
	delete[] (XORMask);
	return cursor;

	*/
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

Color Context::getPixel (int x, int y) const
{
	y = m_size_y - y-1;
	if (x < 0 || x >= m_size_x || y < 0 || y >= m_size_y) return Color::Black;

	txu::Color color = m_buffer[x + y * m_size_x];
	color.a = 255;

	return color;
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

void Context::setFont (const char * name, int sy, int sx /*= -1*/, int bold /*= FW_DONTCARE*/,
	                   bool italic /*= false*/, bool underline /*= false*/, bool strikeout /*= false*/,
	                   double angle /*= 0*/)
{
	txSelectFont (name, sy, sx, bold, italic, underline, strikeout, angle, m_dc);
}

//------------------

} // namespace txu
