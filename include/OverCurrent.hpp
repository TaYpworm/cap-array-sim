#ifndef __OVERCURRENT_HPP__
#define __OVERCURRENT_HPP__

#include <entityx/entityx.h>
#include <unordered_map>
#include "Types.hpp"

struct OverCurrent
{
	// Fields
	unordered_map<entityx::Entity, current> redist;
};

#endif