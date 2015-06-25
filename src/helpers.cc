#include "helpers.hpp"
#include "capacitor.hpp"

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