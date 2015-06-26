#include <cassert>
#include <chrono>
#include <cmath>
#include <random>
#include <sstream>
#include <stdexcept>
#include "Capacitor.hpp"

Capacitor::CapacitorData::CapacitorData()
{
	minCapacitance = 0.0;
	maxCurrent = 0.0;
	leakageCurrent = 0.0;
	ratedVoltage = 0.0;
	maxVoltage = 0.0;
	esr = 0.0;
	capacitance = 0.0;
	maxCapacitance = 0.0;
	voltage = 0.0;
	diffusedEffectsCoef = 0.0;
	energy = 0.0;
}

Capacitor::Capacitor()
{
	
}

Capacitor::Capacitor(const CapacitorData &capData)
{
	// Satisify class invariants -- check input capacitor data values.
	setMinCapacitance(capData.minCapacitance);
	setMaxCurrent(capData.maxCurrent);
	setLeakageCurrent(capData.leakageCurrent);
	setRatedVoltage(capData.ratedVoltage);
	setMaxVoltage(capData.maxVoltage);
	setEsr(capData.esr);
	setCapacitance(capData.capacitance);
	setMaxCapacitance(capData.maxCapacitance);
	setVoltage(capData.voltage);
	setDiffusedEffectsCoef(capData.diffusedEffectsCoef);

	// Set capacitance and energy based on initial parameters
	setCapacitance(calcCapacitance(*this));
	setEnergy(calcEnergy(*this));
}

double Capacitor::getMinCapacitance() const
{
	return _data.minCapacitance;
}

void Capacitor::setMinCapacitance(double minCapacitance)
{
	assert(minCapacitance > 0);
	_data.minCapacitance = minCapacitance;
}

double Capacitor::getMaxCurrent() const
{
	return _data.maxCurrent;
}

void Capacitor::setMaxCurrent(double maxCurrent)
{
	assert(maxCurrent > 0);
	_data.maxCurrent = maxCurrent;
}

double Capacitor::getLeakageCurrent() const
{
	return _data.leakageCurrent;
}

void Capacitor::setLeakageCurrent(double leakageCurrent)
{
	assert(leakageCurrent > 0);
	_data.leakageCurrent = leakageCurrent;
}

double Capacitor::getRatedVoltage() const
{
	return _data.ratedVoltage;
}

void Capacitor::setRatedVoltage(double ratedVoltage)
{
	assert(ratedVoltage > 0);
	_data.ratedVoltage = ratedVoltage;
}

double Capacitor::getMaxVoltage() const
{
	return _data.maxVoltage;
}

void Capacitor::setMaxVoltage(double maxVoltage)
{
	assert(maxVoltage > 0);
	_data.maxVoltage = maxVoltage;
}

double Capacitor::getCapacitance() const
{
	return _data.capacitance;
}

void Capacitor::setCapacitance(double capacitance)
{
	assert(capacitance > 0);
	_data.capacitance = capacitance;
}

double Capacitor::getMaxCapacitance() const
{
	return _data.maxCapacitance;
}

void Capacitor::setMaxCapacitance(double maxCapacitance)
{
	assert(maxCapacitance > 0);
	_data.maxCapacitance = maxCapacitance;
}

double Capacitor::getVoltage() const
{
	return _data.voltage;
}

void Capacitor::setVoltage(double voltage)
{
	// Voltage may be negative
	_data.voltage = voltage;
}

double Capacitor::getDiffusedEffectsCoef() const
{
	return _data.diffusedEffectsCoef;
}

void Capacitor::setDiffusedEffectsCoef(double diffusedEffectsCoef)
{
	assert(diffusedEffectsCoef > 0);
	_data.diffusedEffectsCoef = diffusedEffectsCoef;
}

double Capacitor::getEnergy() const
{
	return _data.energy;
}

void Capacitor::setEnergy(double energy)
{
	// Energy could be negative
	_data.energy = energy;
}

double Capacitor::getEsr() const
{
	return _data.esr;
}

void Capacitor::setEsr(double esr)
{
	assert(esr > 0);
	_data.esr = esr;
}

void Capacitor::update(const double current, const double time)
{
	setVoltage(calcVoltageDelta(*this, current, time));
	setCapacitance(calcCapacitance(*this));
	setEnergy(calcEnergy(*this));
}

MaxwellK23400F::MaxwellK23400F(double startingVoltage) 
{
	// Set voltage
	setRatedVoltage(2.85); // Volts
	setMaxVoltage(3.0); // Volts
	// Starting voltage should be between 0..maxVoltage.
	assert(startingVoltage > 0 || startingVoltage < getMaxVoltage());
	// if (startingVoltage < 0 || startingVoltage > maxVoltage) 
	// {
	// 	std::ostringstream message;
	// 	message << "Starting voltage is out of range 0.." << maxVoltage << "V.";
	// 	throw std::out_of_range (message.str());
	// }
	setVoltage(startingVoltage);

	// Set diffused coefficient
	// This value should be measured empirically for each capacitor.
	// Using model from "Ultra-Capacitors in power conversion systems" for 3000F/2.5V Boostcap
	setDiffusedEffectsCoef(473.0); // Farads/Volt

	// Set capacitance
	// Datasheet min capacitance will be used for calculating a statistical max capacitance.
	// Statistical max will, in turn, be used to calc a new minimum based on diffused effects
	// coefficient.
	setMinCapacitance(3400.0); // Farad
	double meanCapacitance = 3550.0; // Farad
	// Difference between mean and min is 150F. Selecting this as 3*sigma.
	// Sigma = 50F. Should establish sigma empirically.
	// Generate random capacitance value.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::normal_distribution<double> capDist (meanCapacitance, 
		(meanCapacitance - getMinCapacitance()) / 3.0);
	double maxCapacitance = capDist(generator); // Farad
	// Calculate minimum capacitance from diffused effects coefficient and max voltage.
	// C(u_c) = C_0 + k_c * u_c
	// C_0 = C(max_volt) - k_c * max_volt
	// where k_c = diffused effects coefficient
	setMinCapacitance(maxCapacitance - getDiffusedEffectsCoef() * getMaxVoltage());
	setCapacitance(calcCapacitance(*this));

	// Set current
	setMaxCurrent(2000.0); // Amp
	setLeakageCurrent(0.018); // Amp

	// Set resistance
	double maxEsr = 0.00028; // Ohms
	double meanEsr = 0.00022; // Ohms
	// Difference between mean and min is 0.00006 Ohms. Selecting this as
	// sigma.
	// Generate random ESR value.
	std::normal_distribution<double> esrDist (meanEsr, maxEsr - meanEsr);
	setEsr(esrDist(generator)); // Ohms

	// Set energy
	calcEnergy(*this);
}