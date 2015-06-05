#include "arraysystem.hpp"
#include "helper.hpp"
#include <stdexcept>

ArraySystem::ArraySystem(entityx::Entity &start, entityx::Entity &end) 
{
	if (!entitiesConnected(start, end)) 
	{
		throw new std::invalid_argument("Start and end entities must be connected.");
	}

	startCap = start;
	endCap = end;
}

void ArraySystem::update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) 
{

}

// Array capacitance varies with voltage
void ArraySystem::calcCapacitance() 
{

}