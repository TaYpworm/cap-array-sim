#include "capacitor.hpp"
#include <chrono>
#include <random>
#include <stdexcept>
#include <sstream>

MaxwellK23400F::MaxwellK23400F(double startingVoltage) {
	// Set voltage
	ratedVoltage = 2.85; // Volts
	maxVoltage = 3.0; // Volts
	if (startingVoltage < 0 || startingVoltage > maxVoltage) {
		std::ostringstream message;
		message << "Starting voltage is out of range 0.." << maxVoltage << "V.";
		throw std::out_of_range (message.str());
	}
	voltage = startingVoltage;

	// Set capacitance
	minCapacitance = 3400.0; // Farad
	meanCapacitance = 3550.0; // Farad
	// Difference between mean and min is 150F. Selecting this as 3*sigma.
	// Sigma = 50F.
	// Generate random capacitance value.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::normal_distribution<double> capDist (meanCapacitance, 50);
	capacitance = capDist(generator); // Farad
	// Ensure random capacitance value is bounded by minimum.
	if (capacitance < minCapacitance)
		capacitance = minCapacitance; // Farad

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
	esr = esrDist(generator);
}