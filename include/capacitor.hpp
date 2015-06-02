#ifndef __CAPACITOR_HPP__
#define __CAPACITOR_HPP__

struct Capacitor {
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
	double capacitance;
	double voltage;
};

struct MaxwellK23400F : public Capacitor{
	MaxwellK23400F(double startingVoltage = 0);
};

#endif