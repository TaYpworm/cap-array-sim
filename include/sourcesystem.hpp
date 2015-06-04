#ifndef __SOURCESYSTEM_HPP__
#define __SOURCESYSTEM_HPP__

#include <entityx/entityx.h>

class SourceSystem : public entityx::System<SourceSystem> {
public:
	explicit SourceSystem();
	void update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) override;
};

#endif