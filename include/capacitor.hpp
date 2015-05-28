#ifndef __capacitor_hpp__
#define __capacitor_hpp__

struct Capacitor {
	// Capacitance constants
	double minCapacitance;
	double meanCapacitance;
	
	// Current constants
	double maxCurrent;
	double leakageCurrent;

	// Voltage constants
	double ratedVoltage;
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