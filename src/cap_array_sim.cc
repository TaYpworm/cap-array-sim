#include "capacitor.hpp"
#include "config.hpp"
#include "connection.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
	// Print version
	cout << "CapArraySim v" << CapArraySim_VERSION_MAJOR << "." << CapArraySim_VERSION_MINOR << "." << CapArraySim_VERSION_PATCH << endl;

	// Test
	try
	{
		MaxwellK23400F c2;
		cout << c2.minCapacitance << endl;
		cout << c2.meanCapacitance << endl;
		cout << c2.maxCurrent << endl;
		cout << c2.leakageCurrent << endl;
		cout << c2.ratedVoltage << endl;
		cout << c2.maxVoltage << endl;
		cout << c2.maxEsr << endl;
		cout << c2.meanEsr << endl;
		cout << c2.esr << endl;
		cout << c2.capacitance << endl;
		cout << c2.voltage << endl;

		CapConnection conn(static_cast<Capacitor*>(&c2));
		cout << conn.next -> minCapacitance << endl;
		cout << conn.next -> meanCapacitance << endl;
		cout << conn.next -> maxCurrent << endl;
		cout << conn.next -> leakageCurrent << endl;
		cout << conn.next -> ratedVoltage << endl;
		cout << conn.next -> maxVoltage << endl;
		cout << conn.next -> maxEsr << endl;
		cout << conn.next -> meanEsr << endl;
		cout << conn.next -> esr << endl;
		cout << conn.next -> capacitance << endl;
		cout << conn.next -> voltage << endl;
	}
	catch (out_of_range e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}