#ifndef __ARRAYSYSTEM_HPP__
#define __ARRAYSYSTEM_HPP__

#include "serialarray.hpp"
#include <entityx/entityx.h>

class CapArraySystem 
	: public entityx::System<CapArraySystem> 
{
private:
	entityx::Entity *_arrayEnt;

	void updateCapArray();

public:
	explicit CapArraySystem(entityx::Entity& arrayEnt);
	void update(entityx::EntityManager& es, 
		entityx::EventManager& events, 
		entityx::TimeDelta dt) override;
};

#endif