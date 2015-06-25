#ifndef __CAPARRAYSYSTEM_HPP__
#define __CAPARRAYSYSTEM_HPP__

#include <entityx/entityx.h>
#include "SerialArray.hpp"

class CapArraySystem 
	: public entityx::System<CapArraySystem> 
{
private:
	entityx::Entity::Id _id;

public:
	explicit CapArraySystem(entityx::Entity::Id arrayEntId);
	void update(entityx::EntityManager& es, 
		entityx::EventManager& events, 
		entityx::TimeDelta dt) override;
};

#endif