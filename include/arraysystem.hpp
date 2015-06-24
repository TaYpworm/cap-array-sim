#ifndef __ARRAYSYSTEM_HPP__
#define __ARRAYSYSTEM_HPP__

#include "serialarray.hpp"
#include <entityx/entityx.h>

class CapArraySystem 
	: public entityx::System<CapArraySystem> 
{
public:
	explicit CapArraySystem(entityx::Entity& serialArray);
	void update(entityx::EntityManager& es, 
		entityx::EventManager& events, 
		entityx::TimeDelta dt) override;
};

bool hasCap(const entityx::ComponentHandle<SerialArray>& serialArray);

#endif