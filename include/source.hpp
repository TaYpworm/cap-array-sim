#ifndef __SOURCE_HPP__
#define __SOURCE_HPP__

struct Source
{
	double voltage;
	double current;
};

inline double calcPower(const Source& source)
{
	return source.voltage * source.current;
}

#endif