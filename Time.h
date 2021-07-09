#pragma once

//-------------------

namespace txu
{
	class Time;
	class Timer;
}

//-------------------

txu::Time operator "" _mcsec (long long unsigned microseconds); // Returns time from microseconds integer
txu::Time operator "" _msec  (long long unsigned milliseconds); // Returns time from milliseconds integer
txu::Time operator "" _sec   (long long unsigned seconds     ); // Returns time from seconds integer
txu::Time operator "" _min   (long long unsigned minutes     ); // Returns time from minutes integer
txu::Time operator "" _hours (long long unsigned hours       ); // Returns time from hours integer

txu::Time operator "" _mcsec (long double microseconds); // Returns time from microseconds double
txu::Time operator "" _msec  (long double milliseconds); // Returns time from milliseconds double
txu::Time operator "" _sec   (long double seconds     ); // Returns time from seconds double
txu::Time operator "" _min   (long double minutes     ); // Returns time from minutes double
txu::Time operator "" _hours (long double hours       ); // Returns time from hours double

//-------------------

namespace txu
{

//-------------------

Time operator + (const Time& a, const Time& b);
Time operator - (const Time& a, const Time& b);

bool operator == (const Time& a, const Time& b);
bool operator != (const Time& a, const Time& b);

//-------------------

class Time
{
public:
	typedef double time_t;

	Time (time_t milliseconds);
	Time (const Time& that);
	Time ();

	time_t getMicroseconds () const;
	time_t getMilliseconds () const;
	time_t getSeconds      () const;
	time_t getMinutes      () const;
	time_t getHours        () const;

	static Time microseconds (time_t microseconds);
	static Time milliseconds (time_t milliseconds);
	static Time seconds      (time_t seconds);
	static Time minutes      (time_t minutes);
	static Time hours        (time_t hours);

	operator double () const;

	Time& operator = (const Time& that);

	Time operator - ();

	Time& operator += (const Time& that);
	Time& operator -= (const Time& that);

private:
	double m_milliseconds;

	friend class Timer;

	friend Time operator + (const Time& a, const Time& b);
	friend Time operator - (const Time& a, const Time& b);

	friend bool operator == (const Time& a, const Time& b);
	friend bool operator != (const Time& a, const Time& b);
};

//-------------------

Time::Time (time_t milliseconds) :
	m_milliseconds (milliseconds)
{}

Time::Time (const Time& that) :
	m_milliseconds (that.m_milliseconds)
{}

Time::Time () :
	m_milliseconds (0)
{}

//-------------------

Time::time_t Time::getMicroseconds () const
{
	return m_milliseconds * 1000;
}

Time::time_t Time::getMilliseconds () const
{
	return m_milliseconds;
}

Time::time_t Time::getSeconds () const
{
	return m_milliseconds / 1000;
}

Time::time_t Time::getMinutes () const
{
	return m_milliseconds / 1000 / 60;
}

Time::time_t Time::getHours () const
{
	return m_milliseconds / 1000 / 60 / 60;
}

//-------------------

Time Time::microseconds (Time::time_t microseconds)
{
	return Time (microseconds / 1000);
}

Time Time::milliseconds (Time::time_t milliseconds)
{
	return Time (milliseconds);
}

Time Time::seconds (Time::time_t seconds)
{
	return Time (seconds * 1000);
}

Time Time::minutes (Time::time_t minutes)
{
	return Time (minutes * 60 * 1000);
}

Time Time::hours (Time::time_t hours)
{
	return Time (hours * 60 * 60 * 1000);
}

//-------------------

Time::operator double () const
{
	return static_cast <double> (m_milliseconds);
}

//-------------------

Time& Time::operator = (const Time& that)
{
	if (this == &that) 
		return *this;

	m_milliseconds = that.m_milliseconds;
	return *this;
}

//-------------------

Time Time::operator - ()
{
	return Time (-m_milliseconds);
}

//-------------------

Time& Time::operator += (const Time& that)
{
	m_milliseconds += that.m_milliseconds;
	return *this;
}

Time& Time::operator -= (const Time& that)
{
	m_milliseconds -= that.m_milliseconds;
	return *this;
}

//-------------------

Time operator + (const Time& a, const Time& b)
{
	return Time (a.m_milliseconds + b.m_milliseconds);
}

Time operator - (const Time& a, const Time& b)
{
	return Time (a.m_milliseconds - b.m_milliseconds);
}

//-------------------

bool operator == (const Time& a, const Time& b)
{
	return a.m_milliseconds == b.m_milliseconds;
}

bool operator != (const Time& a, const Time& b)
{
	return a.m_milliseconds != b.m_milliseconds;
}

//-------------------

} // namespace txu

//-------------------

txu::Time operator "" _mcsec (long long unsigned microseconds) { return txu::Time::microseconds (static_cast <txu::Time::time_t> (microseconds)); }
txu::Time operator "" _msec  (long long unsigned milliseconds) { return txu::Time::milliseconds (static_cast <txu::Time::time_t> (milliseconds)); }
txu::Time operator "" _sec   (long long unsigned seconds     ) { return txu::Time::seconds      (static_cast <txu::Time::time_t> (seconds     )); }
txu::Time operator "" _min   (long long unsigned minutes     ) { return txu::Time::minutes      (static_cast <txu::Time::time_t> (minutes     )); }
txu::Time operator "" _hours (long long unsigned hours       ) { return txu::Time::hours        (static_cast <txu::Time::time_t> (hours       )); }

txu::Time operator "" _mcsec (long double microseconds) { return txu::Time::microseconds (static_cast <txu::Time::time_t> (microseconds)); }
txu::Time operator "" _msec  (long double milliseconds) { return txu::Time::milliseconds (static_cast <txu::Time::time_t> (milliseconds)); }
txu::Time operator "" _sec   (long double seconds     ) { return txu::Time::seconds      (static_cast <txu::Time::time_t> (seconds     )); }
txu::Time operator "" _min   (long double minutes     ) { return txu::Time::minutes      (static_cast <txu::Time::time_t> (minutes     )); }
txu::Time operator "" _hours (long double hours       ) { return txu::Time::hours        (static_cast <txu::Time::time_t> (hours       )); }

//-------------------