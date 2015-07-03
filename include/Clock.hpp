#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include "Types.hpp"

struct Clock
{
	// Fields
	tick currentTick;
	elapsedSeconds elapsedTime;

	// Constructors
	Clock()
		: currentTick(0),
		elapsedTime(0.0)
	{
		
	}
};

#endif