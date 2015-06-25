#ifndef __SOURCE_HPP__
#define __SOURCE_HPP__

#include <entityx/entityx.h>
#include <vector>

// Assume two source terminals +/- per array
struct Source
{
	double voltage;
	double current;
	entityx::Entity::Id connectionId;

	Source(entityx::Entity::Id inConnectionId);
};

inline double calcPower(const Source &source)
{
	return source.voltage * source.current;
}

#endif