#pragma once

//-------------------

namespace txu
{

//-------------------

class Timer;

class Time
{
public:
	typedef double time_t;

	Time (time_t milliseconds);
	Time (const Time& that);
	Time ();

	time_t getMicroseconds ();
	time_t getMilliseconds ();
	time_t getSeconds      ();
	time_t getMinutes      ();
	time_t getHours        ();

	static Time microseoconds (time_t microseconds);
	static Time milliseconds  (time_t milliseconds);
	static Time seconds       (time_t seconds);
	static Time minutes       (time_t minutes);
	static Time hours         (time_t hours);

	operator double ();

private:
	double milliseconds_;

	friend class Timer;
};

//-------------------

Time::Time (time_t milliseconds) :
	milliseconds_ (milliseconds)
{}

Time::Time (const Time& that) :
	milliseconds_ (that.milliseconds_)
{}

Time::Time () :
	milliseconds_ (0)
{}

//-------------------

Time::time_t Time::getMicroseconds ()
{
	return milliseconds_ * 1000;
}

Time::time_t Time::getMilliseconds ()
{
	return milliseconds_;
}

Time::time_t Time::getSeconds ()
{
	return milliseconds_ / 1000;
}

Time::time_t Time::getMinutes ()
{
	return milliseconds_ / 1000 / 60;
}

Time::time_t Time::getHours ()
{
	return milliseconds_ / 1000 / 60 / 60;
}

//-------------------

Time Time::microseoconds (Time::time_t microseconds)
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

Time::operator double ()
{
	return static_cast <double> (milliseconds_);
}

//-------------------

}