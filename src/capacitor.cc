#include "capacitor.hpp"
#include <chrono>
#include <random>
#include <stdexcept>
#include <sstream>
#include <cmath>

MaxwellK23400F::MaxwellK23400F(double startingVoltage) 
{
	// Set voltage
	ratedVoltage = 2.85; // Volts
	maxVoltage = 3.0; // Volts
	if (startingVoltage < 0 || startingVoltage > maxVoltage) 
	{
		std::ostringstream message;
		message << "Starting voltage is out of range 0.." << maxVoltage << "V.";
		throw std::out_of_range (message.str());
	}
	voltage = startingVoltage;

	// Set diffused coefficient
	// This value should be measured empirically for each capacitor.
	// Using model from "Ultra-Capacitors in power conversion systems" for 3000F/2.5V Boostcap
	diffusedEffectsCoef = 473.0; // Farads/Volt

	// Set capacitance
	// Datasheet min capacitance will be used for calculating a statistical max capacitance.
	// Statistical max will, in turn, be used to calc a new minimum based on diffused effects
	// coefficient.
	minCapacitance = 3400.0; // Farad
	meanCapacitance = 3550.0; // Farad
	// Difference between mean and min is 150F. Selecting this as 3*sigma.
	// Sigma = 50F. Should establish sigma empirically.
	// Generate random capacitance value.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::normal_distribution<double> capDist (meanCapacitance, 
		(meanCapacitance - minCapacitance) / 3.0);
	maxCapacitance = capDist(generator); // Farad
	// Calculate minimum capacitance from diffused effects coefficient and max voltage.
	// C(u_c) = C_0 + k_c * u_c
	// C_0 = C(max_volt) - k_c * max_volt
	// where k_c = diffused effects coefficient
	minCapacitance = maxCapacitance - diffusedEffectsCoef * maxVoltage;
	calcCapacitance();

	// Set current
	maxCurrent = 2000.0; // Amp
	leakageCurrent = 0.018; // Amp

	// Set resistance
	maxEsr = 0.00028; // Ohms
	meanEsr = 0.00022; // Ohms
	// Difference between mean and min is 0.00006 Ohms. Selecting this as
	// sigma.
	// Generate random ESR value.
	std::normal_distribution<double> esrDist (meanEsr, 6e-6);
	esr = esrDist(generator); // Ohms

	// Set energy
	calcEnergy();
}

// Constant current charge/discharge model.
// current < 0 = charge
// current > 0 = discharge
void MaxwellK23400F::update(const double current, const double time) 
{
	calcVoltage(current, time);
	calcCapacitance();
	calcEnergy();
}

// current < 0 = charge
// current > 0 = discharge
void MaxwellK23400F::calcVoltage(const double current, const double time)
{
	voltage = sqrt((minCapacitance * minCapacitance) / \
		(4 * diffusedEffectsCoef * diffusedEffectsCoef) + \
		(1 / diffusedEffectsCoef) * \
		(voltage * minCapacitance + \
		voltage * voltage * diffusedEffectsCoef - current * time)) - \
		minCapacitance / (2 * diffusedEffectsCoef); // Volts

	// Capacitor voltage can become negative, but should not be done for safety.
}

void MaxwellK23400F::calcCapacitance() 
{
	// C(u_c) = C_0 + k_c * u_c
	// where k_c = diffused effects coefficient
	capacitance = minCapacitance + diffusedEffectsCoef * voltage; // Farads
}

void MaxwellK23400F::calcEnergy() 
{
	// "Energetic" capacitance = C_e(u_c) = C_0 + 4/3 * k_c * u_c
	energy = 0.5 * (minCapacitance + 4 / 3 * diffusedEffectsCoef * voltage) * voltage * voltage; // Joules
}