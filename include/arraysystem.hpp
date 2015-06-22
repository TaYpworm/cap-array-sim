#ifndef __ARRAYSYSTEM_HPP__
#define __ARRAYSYSTEM_HPP__

#include <entityx/entityx.h>

class CapArraySystem 
	: public entityx::System<CapArraySystem> 
{
public:
	explicit CapArraySystem();
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