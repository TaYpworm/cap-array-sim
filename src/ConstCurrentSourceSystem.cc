#include <cassert>
#include <vector>
#include "Capacitor.hpp"
#include "ConstCurrentSourceSystem.hpp"
#include "Node.hpp"
#include "Sources.hpp"
#include "Types.hpp"

void ConstCurrentSourceSystem::update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) 
{
	entityx::ComponentHandle<ConstCurrentSource> constSource;
	entityx::ComponentHandle<Node> node;
	// Distribute power equally to all connected nodes.
	// This will result in sub-optimal distribution, but cannot be currently
	// optimized because nodes deeper in the network have not been updated yet 
	// -- maximum power for this time delta has not been calculated.
	// 
	// Nodes will emit backprop events if the allocated power exceeds the system's
	// capabilities.
	//
	// TODO: add link resistance so power will flow asymmetrically.
	for (entityx::Entity entity : es.entities_with_components(constSource, node))
	{
		current sharedCur = constSource->cur / node->outputs.size() * dt;
		for (std::map<entityx::Entity, PowerLink>::iterator it = node->outputs.begin(); 
			it != node->outputs.end(); 
			++it)
		{
			it->second.cur = sharedCur;
			it->second.volt = constSource->volt;
		}
	}
}