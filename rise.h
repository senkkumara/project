#ifndef RISE_H
#define RISE_H

/**
 *	rise.h
 *	-----------------------------------------------------------------------
 *	A rise corresponds to a section of the geometry that is near vertical.
 *	Generally this connects one layer to another.
 */

using namespace std;

#include <memory>
#include "surface.h"
#include "facet.h"

class Rise;
typedef shared_ptr<Rise> Rise_ptr;

class Rise : public Surface
{
private:
	// Constructors
	Rise();
	Rise(Facet_ptr &facet);

	// Member functions (private)
	void _init();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Rise &rise);

	friend std::ostream &operator<<(std::ostream &strm,
		const Rise_ptr &rise);

	friend bool operator==(Rise &rise1, Rise &rise2);
	friend bool operator!=(Rise &rise1, Rise &rise2);
	friend bool operator==(Rise_ptr &rise1, Rise_ptr &rise2);
	friend bool operator!=(Rise_ptr &rise1, Rise_ptr &rise2);

public:
	// Factories
	static Rise_ptr create();
	static Rise_ptr create(Facet_ptr &facet);

};

#endif