#ifndef __SERIALARRAY_HPP__
#define __SERIALARRAY_HPP__

#include <entityx/entityx.h>
#include <vector>

struct SerialArray
{
	std::vector<entityx::Entity::Id> entityIds;
};

#endif