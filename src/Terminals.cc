#include "Terminals.hpp"

Terminal::Terminal(int inId) 
	: id(inId)
{

}

SourceTerminal::SourceTerminal(int inId)
	: Terminal(inId)
{

}

BalancerTerminal::BalancerTerminal(int inId)
	: Terminal(inId)
{

}

DrainTerminal::DrainTerminal(int inId)
	: Terminal(inId)
{

}