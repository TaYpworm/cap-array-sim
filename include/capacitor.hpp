#ifndef __CAPACITOR_HPP__
#define __CAPACITOR_HPP__

#include <cmath>

struct Capacitor 
{
	// Capacitance constants
	double minCapacitance;
	double meanCapacitance;
	
	// Current constants
	double maxCurrent;
	double leakageCurrent;

	// Voltage constants
	double ratedVoltage;
	// Max voltage could be statistically modeled
	double maxVoltage;
	
	// Resistance constants
	double maxEsr;
	double meanEsr;
	
	// Variables
	double esr;
	// Capacitance varies non-linearly with voltage
	double capacitance;
	double maxCapacitance;
	double voltage;
	// Coefficient that adds non-linear effects due to diffused layer
	double diffusedEffectsCoef;
	double energy;
};

struct MaxwellK23400F 
	: public Capacitor
{
	MaxwellK23400F(double startingVoltage = 0);
};

// power < 0 = charge
// power > 0 = discharge
// return < 0 = charge
// return > 0 = discharge
inline double calcCurrentFromPower(const Capacitor& cap, const double power, const double time)
{
	return -(power / cap.voltage) * sqrt(cap.minCapacitance * cap.voltage * cap.voltage) / \
		(cap.minCapacitance * cap.voltage * cap.voltage - 2 * power * time);
}

// current < 0 = charge
// current > 0 = discharge
inline double calcVoltageDelta(const Capacitor& cap, const double current, const double time)
{
	return sqrt((cap.minCapacitance * cap.minCapacitance) / \
		(4 * cap.diffusedEffectsCoef * cap.diffusedEffectsCoef) + \
		(1 / cap.diffusedEffectsCoef) * \
		(cap.voltage * cap.minCapacitance + \
		cap.voltage * cap.voltage * cap.diffusedEffectsCoef - current * time)) - \
		cap.minCapacitance / (2 * cap.diffusedEffectsCoef); // Volts

	// Capacitor voltage can become negative, but should not be done for safety.
}

inline double calcCapacitance(const Capacitor& cap)
{
	// C(u_c) = C_0 + k_c * u_c
	// where k_c = diffused effects coefficient
	return cap.minCapacitance + cap.diffusedEffectsCoef * cap.voltage; // Farads
}

inline double calcEnergy(const Capacitor& cap)
{
	// "Energetic" capacitance = C_e(u_c) = C_0 + 4/3 * k_c * u_c
	return 0.5 * (cap.minCapacitance + 4 / 3 * cap.diffusedEffectsCoef * cap.voltage) * \
		cap.voltage * cap.voltage; // Joules
}

#endif