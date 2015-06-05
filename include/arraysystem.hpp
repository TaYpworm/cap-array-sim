#ifndef __ARRAYSYSTEM_HPP__
#define __ARRAYSYSTEM_HPP__

#include <entityx/entityx.h>

class ArraySystem 
	: public entityx::System<ArraySystem> 
{
public:
	explicit ArraySystem(entityx::Entity &start, entityx::Entity &end);
	void update(entityx::EntityManager &es, 
		entityx::EventManager &events, 
		entityx::TimeDelta dt) override;

private:
	entityx::Entity startCap;
	entityx::Entity endCap;
	double capacitance;

	void calcCapacitance();
};

#endif