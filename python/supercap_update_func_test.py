#!/usr/bin/python

import sys
import numpy as np
import pylab as pl

class Maxwellk23400F(object):
	def __init__(self):
		# Model parameters
		self.diffused_effects_coef = 473.0	# Farads / Volt
		self.energy = 0.0					# Joules

		# Voltage
		self.rated_voltage = 2.85 			# Volts
		self.max_voltage = 3.0 				# Volts
		self.voltage = 0.0					# Volts

		# Capacitance
		self.rated_capacitance = 3400.0 	# Farads
		self.min_capacitance = self.rated_capacitance - self.diffused_effects_coef * self.max_voltage
		self.capacitance = self.min_capacitance
		self.calc_capacitance()

		# Resistance
		self.esr = 0.00028


	# power < 0 = charge
	# power > 0 = discharge
	def current_from_power(self, power, time):
		return -(power / self.voltage) * np.sqrt((self.min_capacitance * self.voltage * self.voltage) / (self.min_capacitance * self.voltage * self.voltage - 2 * power * time))

	# current < 0 = charge
	# current > 0 = discharge
	def update(self, current, time):
		self.calc_voltage(current, time)
		self.calc_capacitance()
		self.calc_energy()

	def calc_capacitance(self):
		self.capacitance = self.min_capacitance + self.diffused_effects_coef * self.voltage # Farads
	
	def calc_voltage(self, current, time):
		self.voltage = np.sqrt((self.min_capacitance * self.min_capacitance) / (4 * self.diffused_effects_coef * self.diffused_effects_coef) + (self.voltage * self.min_capacitance + self.voltage * self.voltage * self.diffused_effects_coef - current * time) / self.diffused_effects_coef) - self.min_capacitance / (2 * self.diffused_effects_coef) # Volts

	def calc_energy(self):
		self.energy = 0.5 * (self.min_capacitance + 4 / 3 * self.diffused_effects_coef * self.voltage) * self.voltage * self.voltage

def main(args):
	cap = Maxwellk23400F()
	cap.voltage = 1
	sec = 0.0
	# Current passed as float in command line args
	# Negative current charges capacitor
	# Constant current
	current = -float(args[1])
	time_delta = 0.01
	values = []
	current_values = []
	while cap.voltage < cap.rated_voltage:
		sec += time_delta
		current = cap.current_from_power(-500, time_delta)
		cap.update(-current, time_delta)
		print current, cap.voltage
		#cap.update(current, time_delta)
		values.append((sec, cap.voltage, cap.capacitance, cap.energy))
		#current_values.append(cap.current_from_power(-2500, time_delta))
	
	#c_m = np.matrix(current_values)
	#print c_m
	#print np.max(c_m)
	m = np.matrix(values)

	# Print max values
	print 'max sec = ', np.max(m[:, 0])
	print 'max voltage = ', np.max(m[:, 1])
	print 'max capacitance = ', np.max(m[:, 2])
	print 'max energy = ', np.max(m[:, 3])

	# Plot voltage
	#pl.plot(m[:, 0], c_m.transpose())
	pl.plot(m[:, 0], m[:, 1])
	pl.show()

if __name__ == '__main__':
	# Pass current as single float on command line.
	main(sys.argv)