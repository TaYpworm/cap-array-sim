#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <entityx/entityx.h>

struct Connection 
{
	entityx::Entity *next;

	Connection(entityx::Entity *nextEnt);
};

#endif