#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <entityx/entityx.h>
#include <map>
#include "PowerLink.hpp"

struct Node
{
	std::map<entityx::Entity, PowerLink> inputs;
	std::map<entityx::Entity, PowerLink> outputs;
};

#endif