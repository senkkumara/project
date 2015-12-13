#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <string>

/**
 *	specification.h
 *	---------------------------------------------------------------------------
 *	Contains enumerations and struct definition for details input by the
 *	salesperson - e.g. rail side.
 */

typedef enum Mode
{
	MODE_CLEAN,			// No application, use text file
	MODE_ITERATE		// Solution started, use CAD
};

typedef enum Side
{
	SIDE_RIGHT,			// Build right only
	SIDE_LEFT,			// Build left only
	SIDE_UNDEFINED		// Try both sides - will not necessarily return both
};

typedef enum Rules
{
	RULES_UK,
	RULES_GERMANY,
	RULES_ROW
};

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