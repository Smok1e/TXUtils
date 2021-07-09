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

	Time getTime () const;

private:
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_freq;
};

//-------------------

Timer::Timer (const Timer& that) :
	m_start (that.m_start),
	m_freq  (that.m_freq )
{}

Timer::Timer () :
	m_start (),
	m_freq  ()
{ start (); }

//-------------------

void Timer::start ()
{
	m_start = {};
	QueryPerformanceCounter (&m_start);

	m_freq = {};
	QueryPerformanceFrequency (&m_freq);
}

//-------------------

Time Timer::getTime () const
{
	LARGE_INTEGER stop = {};
	QueryPerformanceCounter (&stop);

	return Time::seconds (
		static_cast <Time::time_t> (stop.QuadPart - m_start.QuadPart) / 
		static_cast <Time::time_t> (m_freq.QuadPart)
	);
}

//-------------------

} // namespace txu