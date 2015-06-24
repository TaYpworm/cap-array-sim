#include "arraysystem.hpp"
#include "caparray.hpp"
#include "capacitor.hpp"
#include "serialarray.hpp"
#include <stdexcept>
#include <cassert>

CapArraySystem::CapArraySystem(entityx::Entity& arrayEnt) 
{
	assert(arrayEnt);
	assert(arrayEnt.has_component<CapArray>() && arrayEnt.has_component<SerialArray>());
	assert(hasCap(arrayEnt.component<SerialArray>()));
}

void CapArraySystem::update(entityx::EntityManager &es,
	entityx::EventManager &events,
	entityx::TimeDelta dt) 
{

}

bool hasCap(const entityx::ComponentHandle<SerialArray>& array)
{
	bool retval = false;
	for (auto ent : array->entities)
	{
		if (ent.has_component<Capacitor>())
			retval = true;
	}

	return retval;
}
