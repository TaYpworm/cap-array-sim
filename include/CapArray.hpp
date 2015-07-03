#ifndef __CAPARRAY_HPP__
#define __CAPARRAY_HPP__

#include <entityx/entityx.h>
#include <vector>
#include "Types.hpp"

struct CapArray
{
	capacitance eCapacitance;
	resistance esr;
	voltage totVoltage;
	int numCaps;
	std::vector<entityx::Entity> capacitors;
};

#endif