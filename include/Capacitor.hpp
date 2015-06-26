#ifndef __CAPACITOR_HPP__
#define __CAPACITOR_HPP__

#include <cmath>

// TODO: Capacitor has invariants, should implement as class to enforce.
class Capacitor 
{
public: 
	struct CapacitorData
	{
		// Capacitance constants
		double minCapacitance;
		
		// Current constants
		double maxCurrent;
		double leakageCurrent;

		// Voltage constants
		double ratedVoltage;
		// TODO: Max voltage could be statistically modeled
		double maxVoltage;
				
		// Variables
		double esr;
		// Capacitance varies non-linearly with voltage
		double capacitance;
		double maxCapacitance;
		double voltage;
		// Coefficient that adds non-linear effects due to diffused layer
		double diffusedEffectsCoef;
		double energy;

		CapacitorData();
	};

private:
	// Members
	CapacitorData _data;

protected:
	// Methods
	virtual void setMinCapacitance(double minCapacitance);
	virtual void setMaxCurrent(double maxCurrent);
	virtual void setLeakageCurrent(double leakageCurrent);
	virtual void setRatedVoltage(double ratedVoltage);
	virtual void setMaxVoltage(double maxVoltage);
	virtual void setCapacitance(double capacitance);
	virtual void setMaxCapacitance(double maxCapacitance);
	virtual void setVoltage(double voltage);
	virtual void setDiffusedEffectsCoef(double diffusedEffectsCoef);
	virtual void setEnergy(double energy);
	virtual void setEsr(double esr);

public:
	// Constructors
	Capacitor();
	Capacitor(const CapacitorData &capData);

	// Methods
	virtual double getMinCapacitance() const;
	virtual double getMaxCurrent() const;
	virtual double getLeakageCurrent() const;
	virtual double getRatedVoltage() const;
	virtual double getMaxVoltage() const;
	virtual double getCapacitance() const;
	virtual double getMaxCapacitance() const;
	virtual double getVoltage() const;
	virtual double getDiffusedEffectsCoef() const;
	virtual double getEnergy() const;
	virtual double getEsr() const;
	virtual void update(const double current, const double time);
};

class MaxwellK23400F 
	: public Capacitor
{
	MaxwellK23400F(double startingVoltage = 0);
};

// power < 0 = charge
// power > 0 = discharge
// return < 0 = charge
// return > 0 = discharge
inline double calcCurrentFromPower(const Capacitor &cap, const double power, const double time)
{
	double voltage = cap.getVoltage();
	double minCapacitance = cap.getMinCapacitance();
	return -(power / voltage * sqrt(minCapacitance * voltage * voltage)) / \
		(minCapacitance * voltage * voltage - 2 * power * time);
}

// current < 0 = charge
// current > 0 = discharge
inline double calcVoltageDelta(const Capacitor &cap, const double current, const double time)
{
	double minCapacitance = cap.getMinCapacitance();
	double diffusedCoef = cap.getDiffusedEffectsCoef();
	double voltage = cap.getVoltage();
	return sqrt((minCapacitance * minCapacitance) / \
		(4 * diffusedCoef * diffusedCoef) + \
		(1 / diffusedCoef) * \
		(voltage * minCapacitance + \
		voltage * voltage * diffusedCoef - current * time)) - \
		minCapacitance / (2 * diffusedCoef); // Volts

	// Capacitor voltage can become negative, but should not be done for safety.
}

inline double calcCapacitance(const Capacitor &cap)
{
	// C(u_c) = C_0 + k_c * u_c
	// where k_c = diffused effects coefficient
	return cap.getMinCapacitance() + cap.getDiffusedEffectsCoef() * cap.getVoltage(); // Farads
}

inline double calcEnergy(const Capacitor &cap)
{
	// "Energetic" capacitance = C_e(u_c) = C_0 + 4/3 * k_c * u_c
	double voltage = cap.getVoltage();
	return 0.5 * (cap.getMinCapacitance() + 4 / 3 * cap.getDiffusedEffectsCoef() * voltage) * \
		voltage * voltage; // Joules
}

#endif