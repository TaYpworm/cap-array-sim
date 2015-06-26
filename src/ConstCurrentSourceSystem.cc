#include <cassert>
#include "Capacitor.hpp"
#include "ConstCurrentSourceSystem.hpp"
#include "SerialArray.hpp"

ConstCurrentSourceSystem::ConstCurrentSourceSystem(entityx::Entity::Id sourceId) 
{
	assert(sourceId == entityx::Entity::INVALID);
	_id = sourceId;
}

void ConstCurrentSourceSystem::update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) 
{
	entityx::Entity arrayEnt = es.get(_id);
	entityx::ComponentHandle<SerialArray> array = arrayEnt.component<SerialArray>();

	entityx::ComponentHandle<Capacitor> cap;
	for (entityx::Entity::Id id : array->entityIds)
	{
		cap = es.get(id).component<Capacitor>();
		if (cap)
		{

		}
	}
}