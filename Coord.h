#pragma once

namespace txu
{

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
	Coord2D ();

	operator POINT ();

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

Coord2D::Coord2D (double x_, double y_) :
	x (x_),
	y (y_)
{}

Coord2D::Coord2D (const Coord2D& that) :
	x (that.x),
	y (that.y)
{}

Coord2D::Coord2D (POINT point) :
	x (point.x),
	y (point.y)
{}

Coord2D::Coord2D () :
	x (0),
	y (0)
{}

//-------------------

Coord2D::operator POINT ()
{
	return POINT {(int) x, (int) y};
}

//-------------------

Coord2D Coord2D::operator - ()
{
	return Coord2D (-x, -y);
}

//-------------------

#define _coord_member_operator(operator_)                  \
Coord2D& Coord2D::operator operator_ (const Coord2D& that) \
{														   \
	x operator_ that.x;			    					   \
	y operator_ that.y;			   	 				       \
	return *this;										   \
}

_coord_member_operator (+=);
_coord_member_operator (-=);
_coord_member_operator (*=);
_coord_member_operator (/=);

#undef _coord_member_operator

//-------------------

#define _coord_member_scalar_operator(operator_)	 \
Coord2D& Coord2D::operator operator_ (double scalar) \
{													 \
	x operator_ scalar;								 \
	y operator_ scalar;								 \
	return *this;									 \
}													 

_coord_member_scalar_operator (+=);
_coord_member_scalar_operator (-=);
_coord_member_scalar_operator (*=);
_coord_member_scalar_operator (/=);

#undef _coord_member_scalar_operator

//-------------------

#define _coord_operator(operator_) 							    \
Coord2D operator operator_ (const Coord2D& a, const Coord2D& b)	\
{																\
	return Coord2D (a.x operator_ b.x, a.y operator_ b.y);		\
}																\

_coord_operator (+);
_coord_operator (-);
_coord_operator (*);
_coord_operator (/);

#undef _coord_operator

//-------------------

#define _coord_operator_scalar(operator_)								 \
Coord2D operator operator_ (const Coord2D& coord, double scalar)		 \
{																		 \
	return Coord2D (coord.x operator_ scalar, coord.y operator_ scalar); \
}																		 \
																		 \
Coord2D operator operator_ (double scalar, const Coord2D coord)			 \
{																		 \
	return Coord2D (coord.x operator_ scalar, coord.y operator_ scalar); \
}

_coord_operator_scalar (+);
_coord_operator_scalar (-);
_coord_operator_scalar (*);
_coord_operator_scalar (/);

#undef _coord_operator_scalar

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

#define txCoord(coord) (coord).x, (coord).y

//-------------------

}