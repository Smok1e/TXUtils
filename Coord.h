#pragma once

namespace txu
{

//-------------------

#ifdef txCoord
	#undef txCoord
#endif

#define txCoord(coord) (coord).x, (coord).y

//-------------------

class Coord2D;

bool operator == (const Coord2D& a, const Coord2D& b);
bool operator != (const Coord2D& a, const Coord2D& b);

double Coord2DSqrDistance (const Coord2D& a, const Coord2D& b);
double Coord2Distance     (const Coord2D& a, const Coord2D& b);

//-------------------

class Coord2D
{
public :
	double x, y;

	Coord2D (double x, double y);
	Coord2D (const Coord2D& that);
	Coord2D (POINT point);
	Coord2D (SIZE  size);
	Coord2D ();

	static Coord2D Screen ();

	operator POINT () const;
	operator SIZE  () const;

	Coord2D operator - ();

	Coord2D& operator += (const Coord2D& that);
	Coord2D& operator -= (const Coord2D& that);
	Coord2D& operator *= (const Coord2D& that);
	Coord2D& operator /= (const Coord2D& that);

	Coord2D& operator += (double scalar);
	Coord2D& operator -= (double scalar);
	Coord2D& operator *= (double scalar);
	Coord2D& operator /= (double scalar);
};

//-------------------

Coord2D::Coord2D (double x, double y) :
	x (x),
	y (y)
{}

Coord2D::Coord2D (const Coord2D& that) :
	x (that.x),
	y (that.y)
{}

Coord2D::Coord2D (POINT point) :
	x (point.x),
	y (point.y)
{}

Coord2D::Coord2D (SIZE size) :
	x (size.cx),
	y (size.cy)
{}

Coord2D::Coord2D () :
	x (0),
	y (0)
{}

//-------------------

Coord2D Coord2D::Screen ()
{
	return Coord2D (GetSystemMetrics (SM_CXSCREEN), GetSystemMetrics (SM_CYSCREEN));
}

//-------------------

Coord2D::operator POINT () const
{
	return POINT {static_cast <int> (x), static_cast <int> (y)};
}

Coord2D::operator SIZE () const
{
	return SIZE {static_cast <int> (x), static_cast <int> (y)};
}

//-------------------

Coord2D Coord2D::operator - ()
{
	return Coord2D (-x, -y);
}

//-------------------

#ifdef __txu_coord_member_operator
	#undef __txu_coord_member_operator
#endif

#define __txu_coord_member_operator(operator_)             \
Coord2D& Coord2D::operator operator_ (const Coord2D& that) \
{														   \
	x operator_ that.x;			    					   \
	y operator_ that.y;			   	 				       \
	return *this;										   \
}

__txu_coord_member_operator (+=);
__txu_coord_member_operator (-=);
__txu_coord_member_operator (*=);
__txu_coord_member_operator (/=);

#undef __txu_coord_member_operator

//-------------------

#ifdef __txu_coord_member_scalar_operator
	#undef __txu_coord_member_scalar_operator
#endif

#define __txu_coord_member_scalar_operator(operator_) \
Coord2D& Coord2D::operator operator_ (double scalar)  \
{													  \
	x operator_ scalar;								  \
	y operator_ scalar;								  \
	return *this;									  \
}													  

__txu_coord_member_scalar_operator (+=);
__txu_coord_member_scalar_operator (-=);
__txu_coord_member_scalar_operator (*=);
__txu_coord_member_scalar_operator (/=);

#undef __txu_coord_member_scalar_operator

//-------------------

#ifdef __txu_coord_operator
	#undef __txu_coord_operator
#endif

#define __txu_coord_operator(operator_) 				    	\
Coord2D operator operator_ (const Coord2D& a, const Coord2D& b)	\
{																\
	return Coord2D (a.x operator_ b.x, a.y operator_ b.y);		\
}																\

__txu_coord_operator (+);
__txu_coord_operator (-);
__txu_coord_operator (*);
__txu_coord_operator (/);

#undef __txu_coord_operator

//-------------------

#ifdef __txu_coord_scalar_operator
	#undef __txu_coord_scalar_operator
#endif

#define __txu_coord_scalar_operator(operator_)							 \
Coord2D operator operator_ (const Coord2D& coord, double scalar)		 \
{																		 \
	return Coord2D (coord.x operator_ scalar, coord.y operator_ scalar); \
}																		 \
																		 \
Coord2D operator operator_ (double scalar, const Coord2D& coord)		 \
{																		 \
	return Coord2D (coord.x operator_ scalar, coord.y operator_ scalar); \
}

__txu_coord_scalar_operator (+);
__txu_coord_scalar_operator (-);
__txu_coord_scalar_operator (*);
__txu_coord_scalar_operator (/);

#undef __txu_coord_scalar_operator

//-------------------

bool operator == (const Coord2D& a, const Coord2D& b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator != (const Coord2D& a, const Coord2D& b)
{
	return a.x != b.x || a.y != b.y;
}

//-------------------

double Coord2DSqrDistance (const Coord2D& a, const Coord2D& b)
{
	double x = b.x - a.x;
	double y = b.y - a.y;

	return x*x + y*y;
}

double Coord2Distance (const Coord2D& a, const Coord2D& b)
{
	return sqrt (Coord2DSqrDistance (a, b));
}

//-------------------

} // namespace txu