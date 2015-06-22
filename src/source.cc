#include "source.hpp"

double Source::calcPower()
{
	return voltage * current;
}