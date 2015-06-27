
#ifndef __BALANCERSYSTEM_HPP__
#define __BALANCERSYSTEM_HPP__

#include <entityx/entityx.h>

class BalancerSystem : public entityx::System<BalancerSystem> {
public:
	explicit BalancerSystem();
	void update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) override;
};

#endif