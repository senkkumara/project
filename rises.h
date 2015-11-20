#ifndef RISES_H
#define RISES_H

/**
 *	rises.h
 *	-----------------------------------------------------------------------
 *	A Rises object is container for one or more Rise objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "collection.h"
#include "rise.h"

class Rises;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Rises> Rises_ptr;

class Rises : public Collection<Rise_ptr>
{
private:
	// Constructors
	Rises();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Rises &rs);
	friend std::ostream &operator<<(std::ostream &strm,
		const Rises_ptr &rs);

public:
	// Factories
	static Rises_ptr create();

};

#endif