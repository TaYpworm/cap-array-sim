#include "sourcesystem.hpp"
#include <cassert>

ConstCurrentSourceSystem::ConstCurrentSourceSystem(entityx::Entity::Id sourceId) 
{
	assert(sourceId == entityx::Entity::INVALID);
	_id = sourceId;
}

void ConstCurrentSourceSystem::update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) 
{

}