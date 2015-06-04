#ifndef __ARRAYSYSTEM_HPP__
#define __ARRAYSYSTEM_HPP__

#include <entityx/entityx.h>

class ArraySystem : public entityx::System<ArraySystem> {
public:
	explicit ArraySystem();
	void update(entityx::EntityManager &es, 
		entityx::EventManager &events, 
		entityx::TimeDelta dt) override;
};

#endif