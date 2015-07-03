#include "Clock.hpp"
#include "ClockSystem.hpp"

ClockSystem::ClockSystem()
{

}

void ClockSystem::update(entityx::EntityManager &es,
	entityx::EventManager &events,
	entityx::TimeDelta dt)
{
	// Increment ticks and elapsed time of each clock.
	entityx::ComponentHandle<Clock> clock;
	for (entityx::Entity entity : es.entities_with_components(clock))
	{
		clock->currentTick++;
		clock->elapsedTime += dt;
	}
}