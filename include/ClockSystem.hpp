#ifndef __CLOCKSYSTEM_HPP__
#define __CLOCKSYSTEM_HPP__

#include <entityx/entityx.h>
#include "Types.hpp"

class ClockSystem : entityx::System<ClockSystem>
{
public:
 	explicit ClockSystem();
 	void update(entityx::EntityManager &es,
 		entityx::EventManager &events,
 		entityx::TimeDelta dt) override;
};

#endif