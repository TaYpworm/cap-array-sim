#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include "capacitor.hpp"

struct CapConnection {
	Capacitor *next;

	CapConnection(Capacitor *nextCap);
};

#endif