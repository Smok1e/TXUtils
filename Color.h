#pragma once

namespace txu
{

//-------------------

struct Color;

template <typename TypeValue, typename TypeMin, typename TypeMax>
TypeValue Clamp (TypeValue value, TypeMin min, TypeMax max);

Color Blend        (Color a, Color b);
Color operator <<= (Color a, Color b);

bool operator == (const Color& a, const Color& b);
bool operator != (const Color& a, const Color& b);

//-------------------

#pragma pack (push, 1)

struct Color
{
	union
	{
		struct { unsigned char b, g, r, a; };

		RGBQUAD       rgbquad;
		unsigned char data[4];
	};

	Color (int r, int g, int b, int a);
	Color (int r, int g, int b       );
	Color (const Color& that    );
	Color (RGBQUAD      rgbquad );
	Color (COLORREF     colorref);
	Color ();

	static Color Interpolate (Color a, Color b, double t);
	static Color Interpolate (const std::initializer_list <Color>& list, double t);

	static Color Random ();
	static Color Choose ();

	operator RGBQUAD  () const;
	operator COLORREF () const;

	Color& operator = (const Color& that);

	Color operator ! ();

	static Color HSV (int hue, int saturation, int value);
	int hue        ();
	int saturation ();
	int value      ();

	int average ();

	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Pink;
	static const Color DarkPink;
	static const Color Cyan;
	static const Color Magneta;
	static const Color DarkCyan;
	static const Color DarkMagneta;
	static const Color Gray;
	static const Color Orange;
	static const Color DarkGreen;

	static const Color Transparent;
};

//-------------------

const Color Color::Black       (0,   0,   0    );
const Color Color::White       (255, 255, 255  );
const Color Color::Red         (255, 0,   0    );
const Color Color::Green       (0,   255, 0    );
const Color Color::Blue        (0,   0,   255  );
const Color Color::Yellow      (255, 255, 0    );
const Color Color::Pink        (255, 54,  200  );
const Color Color::DarkPink	   (255, 0,   89   );
const Color Color::Cyan        (0,   255, 255  );
const Color Color::Magneta     (255, 0,   255  );
const Color Color::DarkCyan    (0,   140, 255  );
const Color Color::DarkMagneta (135, 0,   135  );
const Color Color::Gray        (100, 100, 100  );
const Color Color::Orange      (255, 135, 0    );
const Color Color::DarkGreen   (0,   128, 0    );

const Color Color::Transparent (0,   0,   0,  0);

//-------------------

#pragma pack (pop)

//-------------------

Color::Color (int r_, int g_, int b_, int a_) :
	r (static_cast <unsigned char> (Clamp (r_, 0, 255))),
	g (static_cast <unsigned char> (Clamp (g_, 0, 255))),
	b (static_cast <unsigned char> (Clamp (b_, 0, 255))),
	a (static_cast <unsigned char> (Clamp (a_, 0, 255)))
{}

Color::Color (int r_, int g_, int b_) :
	r (static_cast <unsigned char> (Clamp (r_, 0, 255))),
	g (static_cast <unsigned char> (Clamp (g_, 0, 255))),
	b (static_cast <unsigned char> (Clamp (b_, 0, 255))),
	a (255)
{}

Color::Color (const Color& that) :
	r (that.r),
	g (that.g),
	b (that.b),
	a (that.a)
{}

Color::Color (RGBQUAD rgbquad_) :
	rgbquad (rgbquad_)
{}

Color::Color (COLORREF colorref) :
	r (static_cast <unsigned char> ( colorref        & 0x000000FF)),
	g (static_cast <unsigned char> ((colorref >>  8) & 0x000000FF)),
	b (static_cast <unsigned char> ((colorref >> 16) & 0x000000FF)),
	a (255) //(static_cast <unsigned char> ((colorref >> 24) & 0x000000FF))	???
{}

Color::Color () :
	r (0),
	g (0),
	b (0),
	a (255)
{}

//-------------------

Color Color::Interpolate (Color a, Color b, double t)
{
	t = Clamp (t, 0.0, 1.0);

	return Color (static_cast <int> (a.r + t * (b.r - a.r)),
				  static_cast <int> (a.g + t * (b.g - a.g)),
				  static_cast <int> (a.b + t * (b.b - a.b)),
				  static_cast <int> (a.a + t * (b.a - a.a)));
}

Color Color::Interpolate (const std::initializer_list <Color>& list, double t)
{
	t = Clamp (t, 0.0, 1.0);

	size_t size = list.size ()-1;

	size_t a_index = static_cast <size_t> (floor (t*size));
	size_t b_index = static_cast <size_t> (ceil  (t*size));

	Color a = *(list.begin () + a_index);
	Color b = *(list.begin () + b_index);

	return Interpolate (a, b, t*size - floor (t*size));
}

//-------------------

Color Color::Random ()
{
	return Color (rand () % 255, rand () % 255, rand () % 255);
}

//-------------------

Color Color::Choose ()
{
	static COLORREF data[16] = {};	
	
	CHOOSECOLORA cc = {};
	cc.hwndOwner      = txWindow ();
	cc.hInstance      = nullptr;
	cc.lpCustColors   = data;
	cc.Flags          = CC_RGBINIT | CC_ANYCOLOR | CC_FULLOPEN;
	cc.lCustData      = {};
	cc.lpfnHook       = nullptr;
	cc.lpTemplateName = nullptr;
	cc.lStructSize    = sizeof (cc);

	if (ChooseColorA (&cc)) return cc.rgbResult;
	else                    return Black;
}

//-------------------

Color::operator RGBQUAD () const
{
	return rgbquad;
}

Color::operator COLORREF () const
{
	if (a == 0) return TX_TRANSPARENT;
	return r | (g << 8) | (b << 16); // | (a << 24); ???
}

//-------------------

Color Color::operator ! ()
{
	return Color (255-r, 255-g, 255-b, a);
}

//-------------------

Color& Color::operator = (const Color& that)
{
	if (this == &that) return *this;

	r = that.r;
	g = that.g;
	b = that.b;
	a = that.a;

	return *this;
}

//-------------------

Color Color::HSV (int h, int s, int v)
{
	Color rgb;
	h = Clamp (h, 0, 255);
	s = Clamp (s, 0, 255);
	v = Clamp (v, 0, 255);

    if (s == 0)
    {
        rgb.r = static_cast <unsigned char> (v);
        rgb.g = static_cast <unsigned char> (v);
        rgb.b = static_cast <unsigned char> (v);

        return rgb;
    }

    int region = h / 43;
    int remainder = (h - (region * 43)) * 6;

    int p = (v * (255 - s)) >> 8;
    int q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    int t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = static_cast <unsigned char> (v); 
			rgb.g = static_cast <unsigned char> (t); 
			rgb.b = static_cast <unsigned char> (p);
            break;

        case 1:
            rgb.r = static_cast <unsigned char> (q); 
			rgb.g = static_cast <unsigned char> (v); 
			rgb.b = static_cast <unsigned char> (p);
            break;

        case 2:
			rgb.r = static_cast <unsigned char> (p); 
			rgb.g = static_cast <unsigned char> (v); 
			rgb.b = static_cast <unsigned char> (t);
            break;

        case 3:
            rgb.r = static_cast <unsigned char> (p); 
			rgb.g = static_cast <unsigned char> (q); 
			rgb.b = static_cast <unsigned char> (v);
            break;

        case 4:
            rgb.r = static_cast <unsigned char> (t); 
			rgb.g = static_cast <unsigned char> (p); 
			rgb.b = static_cast <unsigned char> (v);
            break;

        default:
            rgb.r = static_cast <unsigned char> (v); 
			rgb.g = static_cast <unsigned char> (p); 
			rgb.b = static_cast <unsigned char> (q);
            break;

    }

    return rgb;
}

int Color::hue ()
{
    double min = 0, max = 0, delta = 0;

    min = r   < g ? r   : g;
    min = min < b ? min : b;

    max = r   > g ? r   : g;
    max = max > b ? max : b;

    delta = max - min;

	double h = 0;

	if (delta < 0.00001)
		return static_cast <int> (h);

    if (r >= max)
        h = (g - b) / delta;

    else if (g >= max)
        h = 2.0 + (b - r) / delta;

    else
        h = 4.0 + (r - g) / delta;

    h *= 60.0;

    if (h < 0)
        h += 360.0;

    return static_cast <int> (255.0/360.0 * h);
}

int Color::saturation ()
{
	double min = 0, max = 0, delta = 0;

    min = r   < g ? r   : g;
    min = min < b ? min : b;

    max = r   > g ? r   : g;
    max = max > b ? max : b;

    delta = max - min;

	double s = 0;

	if (delta < 0.00001)
		s = 0;

	else if (max > 0.0)
		s = (double) (delta / max);

	return static_cast <int> (s * 255);
}

int Color::value ()
{
    double min = 0;
	double max = 0;

    min = r   < g ? r   : g;
    min = min < b ? min : b;

    max = r   > g ? r   : g;
    max = max > b ? max : b;

	return static_cast <int> (max);
}

//-------------------

template <typename TypeValue, typename TypeMin, typename TypeMax>
TypeValue Clamp (TypeValue value, TypeMin min, TypeMax max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

//-------------------

int Color::average ()
{
	return (r + g + b) / 3;
}

//-------------------

Color Blend (Color a, Color b)
{
	double alpha = (double) a.a / 255;
	double alpha_inv = 1.0 - alpha;

	return Color (static_cast <int> ((double) b.r * alpha_inv + (double) a.r * alpha),
		          static_cast <int> ((double) b.g * alpha_inv + (double) a.g * alpha),
		          static_cast <int> ((double) b.b * alpha_inv + (double) a.b * alpha), a.a);
}

Color operator <<= (Color a, Color b)
{
	return Blend (b, a);
}

//-------------------

bool operator == (const Color& a, const Color& b)
{
	return a.r == b.r && a.g == b.g && a.b == b.b;
}

bool operator != (const Color& a, const Color& b)
{
	return a.r != b.r || a.g != b.g || a.b != b.b;
}

//-------------------

} // namespace txu