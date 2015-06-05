#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#include "connection.hpp"
#include <entityx/entityx.h>
#include <assert.h>

inline bool entitiesConnected(entityx::Entity &first, 
								entityx::Entity &second) 
{
	// First and second are the same entity
	if (first == second)
		return true;

	// First must have a connection component
	// Second may not have a connection component
	if (!first.has_component<Connection>())
		return false;
	
	// Walk the connected capacitor list to see if first and second are connected
	bool connected = false;
	entityx::Entity *entPtr = first.component<Connection>()->next;
	while (!connected) {
		// Reached the end of the connected list, break the loop
		if (entPtr == NULL)
			break;

		// Found the second entity. Entities are connected. Short circuit search.
		if (*entPtr == second) {
			connected = true;
			break;
		}

		// Move to the next entity.
		if (!entPtr->has_component<Connection>()) {
			break;
		}
		else {
			entPtr = entPtr->component<Connection>()->next;
		}
	}
	return connected;
}

#endif