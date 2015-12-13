#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <string>

enum Mode
{
	MODE_CLEAN,			// No application, use text file
	MODE_ITERATE		// Solution started, use CAD
};

enum Side
{
	RAIL_RIGHT,
	RAIL_LEFT,
	RAIL_UNDEFINED
};

struct Specification
{
	Mode		RunMode;
	std::string Project;
	std::string Filename;
	Side		RailSide;
};

#endif