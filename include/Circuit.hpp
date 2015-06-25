#ifndef __CIRCUIT_HPP__
#define __CIRCUIT_HPP__

#include <entityx/entityx.h>

class Circuit : public entityx::Entityx {
public:
	explicit Circuit();
	void update(entityx::TimeDelta dt) override;
};

#endif