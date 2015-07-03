#include <cassert>
#include <stdexcept>
#include "Capacitor.hpp"
#include "CapArray.hpp"
#include "CapArraySystem.hpp"

// Updates capacitor array component variables
// Cap array voltage and capacitance change during charge/discharge
void CapArraySystem::update(entityx::EntityManager &es,
	entityx::EventManager &events,
	entityx::TimeDelta dt) 
{
	// entityx::Entity arrayEnt = es.get(_id);
	// entityx::ComponentHandle<CapArray> capArray = arrayEnt.component<CapArray>();

	// // Calc cap array components
	// int numCaps = 0;
	// resistance esr = 0.0;
	// capacitance eCapacitance = 0.0;
	// voltage totVoltage = 0.0;
	// entityx::ComponentHandle<Capacitor> cap;
	// // Entities of SerialArray may not contain capacitors
	// for (auto entId : serialArray->entityIds)
	// {
	// 	cap = es.get(entId).component<Capacitor>();
	// 	if (cap)
	// 	{
	// 		numCaps++;
	// 		esr += cap->esr;
	// 		// Equivalent capacitance of series-connected capacitors
	// 		eCapacitance += 1 / cap->capacitance; 
	// 		totVoltage += cap->voltage;
	// 	}
	// }

	// // Update CapArray component variables
	// capArray->numCaps = numCaps;
	// capArray->esr = esr;
	// capArray->eCapacitance = 1 / eCapacitance;
	// capArray->totVoltage = voltage;
}