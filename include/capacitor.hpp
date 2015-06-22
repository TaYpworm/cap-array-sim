#ifndef __CAPACITOR_HPP__
#define __CAPACITOR_HPP__

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

	// current < 0 = charge
	// current > 0 = discharge
	virtual void update(const double current, const double time) = 0;

private:
	virtual void calcVoltage(const double current, const double time) = 0;
	virtual void calcCapacitance() = 0;
	virtual void calcEnergy() = 0;
};

struct MaxwellK23400F 
	: public Capacitor
{
	MaxwellK23400F(double startingVoltage = 0);
	void update(const double current, const double time);

private:
	void calcVoltage(const double current, const double time);
	void calcCapacitance();
	void calcEnergy();
};


#endif