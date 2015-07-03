#ifndef __SOURCES_HPP__
#define __SOURCES_HPP__

#include <entityx/entityx.h>
#include <vector>
#include "Types.hpp"

struct Source
{
	current cur;
	voltage volt;
};

struct ConstCurrentSource 
	: public Source
{

};

inline double calcPower(const Source &source)
{
	return source.volt * source.cur;
}

#endif