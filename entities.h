#ifndef ENTITIES_H
#define ENTITIES_H

/**
 *	entities.h
 *	-----------------------------------------------------------------------
 *	A Entities object is container for one or more Entity objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "collection.h"
#include "entity.h"

class Entities;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Entities> Entities_ptr;

class Entities : public Collection<Entity_ptr, Entities_ptr>
{
private:
	// Constructors
	Entities();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Entities &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const Entities_ptr &fs);

public:
	// Factories
	static Entities_ptr create();
};

#endif