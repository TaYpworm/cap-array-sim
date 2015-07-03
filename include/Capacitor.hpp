#ifndef __CAPACITOR_HPP__
#define __CAPACITOR_HPP__

#include <cmath>
#include <entityx/entityx.h>
#include "Types.hpp"

struct Capacitor 
{
	// Capacitance
	capacitance curCapacitance;
	capacitance minCapacitance;
	
	// Current
	current maxCurrent;
	current leakageCurrent;

	// Voltage
	voltage curVoltage;
	// TODO: Max voltage could be statistically modeled
	voltage maxVoltage;
	voltage ratedVoltage;
	
	// Resistance
	resistance esr;	
	
	// Coefficient that adds non-linear effects due to diffused layer
	double diffusedEffectsCoef;

	// Energy
	energy curEnergy;

	// Methods
	void update(const current current, const entityx::TimeDelta dt);
};

struct MaxwellK23400F 
	: public Capacitor
{
	MaxwellK23400F(voltage startingVoltage = 0);
};

// power < 0 = charge
// power > 0 = discharge
// return < 0 = charge
// return > 0 = discharge
inline double calcCurrentFromPower(const Capacitor &cap, const power inPower, const entityx::TimeDelta dt)
{
	return -(inPower / cap.curVoltage) * sqrt(cap.minCapacitance * cap.curVoltage * cap.curVoltage) / \
		(cap.minCapacitance * cap.curVoltage * cap.curVoltage - 2 * inPower * dt);
}

// current < 0 = charge
// current > 0 = discharge
inline double calcVoltageDelta(const Capacitor &cap, const current inCurrent, const entityx::TimeDelta dt)
{
	return sqrt((cap.minCapacitance * cap.minCapacitance) / \
		(4 * cap.diffusedEffectsCoef * cap.diffusedEffectsCoef) + \
		(1 / cap.diffusedEffectsCoef) * \
		(cap.curVoltage * cap.minCapacitance + \
		cap.curVoltage * cap.curVoltage * cap.diffusedEffectsCoef - inCurrent * dt)) - \
		cap.minCapacitance / (2 * cap.diffusedEffectsCoef); // Volts

	// Capacitor voltage can become negative, but should not be done for safety.
}

inline double calcCapacitance(const Capacitor &cap)
{
	// C(u_c) = C_0 + k_c * u_c
	// where k_c = diffused effects coefficient
	return cap.minCapacitance + cap.diffusedEffectsCoef * cap.curVoltage; // Farads
}

inline double calcEnergy(const Capacitor &cap)
{
	// "Energetic" capacitance = C_e(u_c) = C_0 + 4/3 * k_c * u_c
	return 0.5 * (cap.minCapacitance + 4 / 3 * cap.diffusedEffectsCoef * cap.curVoltage) * \
		cap.curVoltage * cap.curVoltage; // Joules
}

#endif