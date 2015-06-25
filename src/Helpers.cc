#include "Capacitor.hpp"
#include "Helpers.hpp"
#include "SerialArray.hpp"

bool hasCap(entityx::EntityManager &es, entityx::Entity::Id id)
{
	entityx::Entity arrayEnt = es.get(id);
	bool retval = false;

	if (arrayEnt.has_component<Capacitor>())
		retval = true;

	if (arrayEnt.has_component<SerialArray>())
	{
		entityx::ComponentHandle<SerialArray> array = arrayEnt.component<SerialArray>();
		for (entityx::Entity::Id id : array->entityIds)
		{
			// Short circuit evaluation if a capacitor is found.
			if (es.get(id).has_component<Capacitor>())
				retval = true;
		}
	}

	return retval;
}