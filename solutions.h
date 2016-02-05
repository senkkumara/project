#ifndef SOLUTIONS_H
#define SOLUTIONS_H

/**
 *	solutions.h
 *	-----------------------------------------------------------------------
 *	A Solutions object is container for one or more Solution objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "application.h"
#include "collection.h"
#include "solution.h"
#include "specification.h"

/**
 *	Collection of Solutions.
 */
class Solutions;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Solutions> Solutions_ptr;

class Solutions : public Collection<Solution_ptr, Solutions_ptr>
{
private:
	// Constructors
	Solutions(Specification &spec, Application_ptr &app);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Solutions &ss);
	friend std::ostream &operator<<(std::ostream &strm,
		const Solutions_ptr &ss);

public:
	// Factories
	static Solutions_ptr create(Specification &spec, Application_ptr &app);
};

#endif