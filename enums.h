#ifndef ENUMS_H
#define ENUMS_H

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

#endif