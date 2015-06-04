#ifndef __DRAINSYSTEM_HPP__
#define __DRAINSYSTEM_HPP__

#include <entityx/entityx.h>

class DrainSystem : public entityx::System<DrainSystem> {
public:
	explicit DrainSystem();
	void update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) override;
};

#endif