#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <string>
#include "enums.h"

/**
 *	specification.h
 *	---------------------------------------------------------------------------
 *	Contains the definition for details input by the
 *	salesperson - e.g. rail side.
 */

/**
 *	Structure containing details input by the salesperson.
 */
struct Specification
{
public:
	Mode		Mode;
	std::string Project;
	std::string Filename;
	Side		Side;
	Rules		Rules;
};

#endif