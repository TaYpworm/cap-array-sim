#include <chrono>
#include <cmath>
#include <random>
#include <sstream>
#include <stdexcept>
#include "Capacitor.hpp"

void Capacitor::update(const current current, const entityx::TimeDelta dt)
{
	curVoltage = calcVoltageDelta(*this, current, dt);
	curCapacitance = calcCapacitance(*this);
	curEnergy = calcEnergy(*this);
}

MaxwellK23400F::MaxwellK23400F(voltage startingVoltage) 
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
	curVoltage = startingVoltage;

	// Set diffused coefficient
	// This value should be measured empirically for each capacitor.
	// Using model from "Ultra-Capacitors in power conversion systems" for 3000F/2.5V Boostcap
	diffusedEffectsCoef = 473.0; // Farads/Volt

	// Set capacitance
	// Datasheet min capacitance will be used for calculating a statistical max capacitance.
	// Statistical max will, in turn, be used to calc a new minimum based on diffused effects
	// coefficient.
	minCapacitance = 3400.0; // Farad
	double meanCapacitance = 3550.0; // Farad
	// Difference between mean and min is 150F. Selecting this as 3*sigma.
	// Sigma = 50F. Should establish sigma empirically.
	// Generate random capacitance value.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::normal_distribution<double> capDist (meanCapacitance, 
		(meanCapacitance - minCapacitance) / 3.0);
	double maxCapacitance = capDist(generator); // Farad
	// Calculate minimum capacitance from diffused effects coefficient and max voltage.
	// C(u_c) = C_0 + k_c * u_c
	// C_0 = C(max_volt) - k_c * max_volt
	// where k_c = diffused effects coefficient
	minCapacitance = maxCapacitance - diffusedEffectsCoef * maxVoltage;
	calcCapacitance(*this);

	// Set current
	maxCurrent = 2000.0; // Amp
	leakageCurrent = 0.018; // Amp

	// Set resistance
	double maxEsr = 0.00028; // Ohms
	double meanEsr = 0.00022; // Ohms
	// Difference between mean and min is 0.00006 Ohms. Selecting this as
	// sigma.
	// Generate random ESR value.
	std::normal_distribution<double> esrDist (meanEsr, maxEsr - meanEsr);
	esr = esrDist(generator); // Ohms

	// Set energy
	calcEnergy(*this);
}