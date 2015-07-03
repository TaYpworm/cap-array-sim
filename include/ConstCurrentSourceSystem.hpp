#ifndef __CONSTCURRENTSOURCESYSTEM_HPP__
#define __CONSTCURRENTSOURCESYSTEM_HPP__

#include <entityx/entityx.h>

class ConstCurrentSourceSystem : public entityx::System<ConstCurrentSourceSystem> 
{
public:
	explicit ConstCurrentSourceSystem();
	void update(entityx::EntityManager &es,
		entityx::EventManager &events,
		entityx::TimeDelta dt) override;
};

#endif