using namespace std;

#include "installation.h"

/**
 *	(Private) Constructs an installation from a staircase
 *	argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Installation::Installation(Staircase_ptr &staircase)
{
	_staircase = staircase;
	//TODO:: Implement...
}

/**
 *	Factory method using the constructor with a staircase 
 *	argument.
 */
Installation_ptr Installation::create(Staircase_ptr &staircase)
{
	return Installation_ptr(new Installation(staircase));
}

/**
 *	Gets the staircase that was used to create the installation.
 */
Staircase_ptr Installation::getStaircase()
{
	return _staircase;
}