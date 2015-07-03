#ifndef __CAPARRAYSYSTEM_HPP__
#define __CAPARRAYSYSTEM_HPP__

#include <entityx/entityx.h>

class CapArraySystem 
	: public entityx::System<CapArraySystem> 
{
public:
	void update(entityx::EntityManager& es, 
		entityx::EventManager& events, 
		entityx::TimeDelta dt) override;
};

#endif