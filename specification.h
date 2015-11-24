#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <string>

enum Mode
{
	MODE_CLEAN,			// No application, use text file
	MODE_ITERATE		// Solution started, use CAD
};

struct Specification
{
	Mode		RunMode;
	std::string Project;
	std::string Filename;
	std::string RailSide;
};

#endif