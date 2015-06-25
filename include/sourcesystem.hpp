#ifndef __SOURCESYSTEM_HPP__
#define __SOURCESYSTEM_HPP__

#include <entityx/entityx.h>

class ConstCurrentSourceSystem : public entityx::System<ConstCurrentSourceSystem> {
private:
	entityx::Entity::Id _id;

public:
	explicit ConstCurrentSourceSystem(entityx::Entity::Id sourceId);
	void update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) override;
};

#endif