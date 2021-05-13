#pragma once

namespace txu
{

//-------------------

union Color;

template <typename TypeValue, typename TypeMin, typename TypeMax>
TypeValue Clamp (TypeValue value, TypeMin min, TypeMax max);

Color Blend        (Color a, Color b);
Color operator <<= (Color a, Color b);

bool operator == (const Color& a, const Color& b);
bool operator != (const Color& a, const Color& b);

//-------------------

#pragma pack (push, 1)

union Color
{
	struct { unsigned char b, g, r, a; };

	RGBQUAD       rgbquad;
	unsigned char data[4];

	Color (int r, int g, int b, int a);
	Color (int r, int g, int b       );
	Color (const Color& that    );
	Color (RGBQUAD      rgbquad );
	Color (COLORREF     colorref);
	Color ();

	static Color Interpolate (Color a, Color b, double t);
	static Color Interpolate (const std::initializer_list <Color>& list, double t);

	operator RGBQUAD  ();
	operator COLORREF ();

	Color& operator = (const Color& that);

	Color operator ! ();

	static Color HSV (int hue, int saturation, int value);
	int hue        ();
	int saturation ();
	int value      ();

	static Color Black;
	static Color White;
	static Color Red;
	static Color Green;
	static Color Blue;
	static Color Yellow;
	static Color Pink;
	static Color DarkPink;
	static Color Cyan;
	static Color Magneta;
	static Color DarkCyan;
	static Color DarkMagneta;
	static Color Gray;
	static Color Orange;
	static Color DarkGreen;

	static Color Transparent;
};

//-------------------

Color Color::Black       (0,   0,   0    );
Color Color::White       (255, 255, 255  );
Color Color::Red         (255, 0,   0    );
Color Color::Green       (0,   255, 0    );
Color Color::Blue        (0,   0,   255  );
Color Color::Yellow      (255, 255, 0    );
Color Color::Pink        (255, 54,  200  );
Color Color::DarkPink	 (255, 0,   89   );
Color Color::Cyan        (0,   255, 255  );
Color Color::Magneta     (255, 0,   255  );
Color Color::DarkCyan    (0,   140, 255  );
Color Color::DarkMagneta (135, 0,   135  );
Color Color::Gray        (100, 100, 100  );
Color Color::Orange      (255, 135, 0    );
Color Color::DarkGreen   (0,   128, 0    );

Color Color::Transparent (0,   0,   0,  0);

//-------------------

#pragma pack (pop)

//-------------------

Color::Color (int r_, int g_, int b_, int a_) :
	r (Clamp (r_, 0, 255)),
	g (Clamp (g_, 0, 255)),
	b (Clamp (b_, 0, 255)),
	a (Clamp (a_, 0, 255))
{}

Color::Color (int r_, int g_, int b_) :
	r (Clamp (r_, 0, 255)),
	g (Clamp (g_, 0, 255)),
	b (Clamp (b_, 0, 255)),
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
{ 
	a = 255; 
}

Color::Color (COLORREF colorref) :
	r (GetRValue (colorref)),
	g (GetGValue (colorref)),
	b (GetBValue (colorref)),
	a (255)
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

	return Color (a.r + t * (b.r - a.r),
				  a.g + t * (b.g - a.g),
				  a.b + t * (b.b - a.b),
				  a.a + t * (b.a - a.a));
}

Color Color::Interpolate (const std::initializer_list <Color>& list, double t)
{
	t = Clamp (t, 0.0, 1.0);

	size_t size = list.size ()-1;

	int a_index = std::floor (t*size);
	int b_index = std::ceil  (t*size);

	Color a = *(list.begin () + a_index);
	Color b = *(list.begin () + b_index);

	return Interpolate (a, b, t*size - std::floor (t*size));
}

//-------------------

Color::operator RGBQUAD ()
{
	return rgbquad;
}

Color::operator COLORREF ()
{
	if (a == 0)	
		return TX_TRANSPARENT;

	return RGB (r, g, b);
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
        rgb.r = v;
        rgb.g = v;
        rgb.b = v;

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
            rgb.r = v; rgb.g = t; rgb.b = p;
            break;

        case 1:
            rgb.r = q; rgb.g = v; rgb.b = p;
            break;

        case 2:
			rgb.r = p; rgb.g = v; rgb.b = t;
            break;

        case 3:
            rgb.r = p; rgb.g = q; rgb.b = v;
            break;

        case 4:
            rgb.r = t; rgb.g = p; rgb.b = v;
            break;

        default:
            rgb.r = v; rgb.g = p; rgb.b = q;
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
		return h;

    if (r >= max)
        h = (g - b) / delta;

    else if (g >= max)
        h = 2.0 + (b - r) / delta;

    else
        h = 4.0 + (r - g) / delta;

    h *= 60.0;

    if (h < 0)
        h += 360.0;

    return 255.0/360.0*h;
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

	return s * 255;
}

int Color::value ()
{
    double min = 0, max = 0, delta = 0;

    min = r   < g ? r   : g;
    min = min < b ? min : b;

    max = r   > g ? r   : g;
    max = max > b ? max : b;

	return max;
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

Color Blend (Color a, Color b)
{
	double alpha = (double) a.a / 255;
	double alpha_inv = 1.0 - alpha;

	return Color ((double) b.r * alpha_inv + (double) a.r * alpha,
		          (double) b.g * alpha_inv + (double) a.g * alpha,
		          (double) b.b * alpha_inv + (double) a.b * alpha, a.a);
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

}