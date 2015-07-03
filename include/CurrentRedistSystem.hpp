#ifndef __CURRENTREDISTSYSTEM_HPP__
#define __CURRENTREDISTSYSTEM_HPP__

#include <entityx/entityx.h>

class CurrentRedistSystem
 	: entityx::System<CurrentRedistSystem>
{
public:
	// Constructors
	explicit CurrentRedistSystem();

	// Methods
	void update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) override;
};

#endif