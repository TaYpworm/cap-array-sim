#ifndef __POWERLINK_HPP__
#define __POWERLINK_HPP__

#include "Types.hpp"

struct PowerLink
{
	resistance res;
	current cur;
	voltage volt;
};

double calcPower(const PowerLink& link)
{
	return link.cur * link.volt;
}

#endif