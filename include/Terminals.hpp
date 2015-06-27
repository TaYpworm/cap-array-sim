#ifndef __TERMINALS_HPP__
#define __TERMINALS_HPP__

struct Terminal 
{
	int id;

	Terminal(int inId);
};

struct SourceTerminal : Terminal
{
	SourceTerminal(int inId);
};

struct BalancerTerminal : Terminal
{
	BalancerTerminal(int inId);
};

struct DrainTerminal : Terminal
{
	DrainTerminal(int inId);
};

#endif