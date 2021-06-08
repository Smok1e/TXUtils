#pragma once

//-------------------

namespace txu
{

//-------------------

class Timer
{
public:
	Timer (const Timer& that);
	Timer ();

	void start ();

	Time getTime ();

private:
	LARGE_INTEGER start_;
	LARGE_INTEGER freq_;
};

//-------------------

Timer::Timer (const Timer& that) :
	start_ (that.start_),
	freq_  (that.freq_ )
{}

Timer::Timer () :
	start_ (),
	freq_  ()
{ start (); }

//-------------------

void Timer::start ()
{
	start_ = {};
	QueryPerformanceCounter   (&start_);

	freq_  = {};
	QueryPerformanceFrequency (&freq_);
}

//-------------------

Time Timer::getTime ()
{
	LARGE_INTEGER stop = {};
	QueryPerformanceCounter (&stop);

	return Time::seconds (
		static_cast <Time::time_t> (stop.QuadPart - start_.QuadPart) / 
		static_cast <Time::time_t> (freq_.QuadPart)
	);
}

//-------------------

} // namespace txu