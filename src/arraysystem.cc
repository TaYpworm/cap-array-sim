#include "arraysystem.hpp"
#include "caparray.hpp"
#include "capacitor.hpp"
#include "helpers.hpp"
#include "serialarray.hpp"
#include <stdexcept>
#include <cassert>

CapArraySystem::CapArraySystem(entityx::Entity& arrayEnt) 
{
	assert(arrayEnt);
	assert(arrayEnt.has_component<CapArray>() && arrayEnt.has_component<SerialArray>());
	assert(hasCap(arrayEnt.component<SerialArray>()));

	_arrayEnt = &arrayEnt;
}

void CapArraySystem::update(entityx::EntityManager &es,
	entityx::EventManager &events,
	entityx::TimeDelta dt) 
{

}

// Updates capacitor array component variables
// Cap array voltage and capacitance change during charge/discharge
void CapArraySystem::updateCapArray()
{
	entityx::ComponentHandle<CapArray> capArray = _arrayEnt->component<CapArray>();
	entityx::ComponentHandle<SerialArray> serialArray = _arrayEnt->component<SerialArray>();

	// Calc cap array components
	double eCapacitance = 0.0;
	double voltage = 0.0;
	entityx::ComponentHandle<Capacitor> cap;
	for (auto ent : serialArray->entities)
	{
		cap = ent.component<Capacitor>();
		if (cap)
		{
			// Equivalent capacitance of series-connected capacitors
			eCapacitance += 1 / cap->capacitance; 
			voltage += cap->voltage;
		}
	}

	// Update CapArray component variables
	capArray->eCapacitance = 1 / eCapacitance;
	capArray->voltage = voltage;
}