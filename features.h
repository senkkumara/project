#ifndef FEATURES_H
#define FEATURES_H

using namespace std;

#include <memory>
#include "collection.h"
#include "surfaces.h"
#include "feature.h"

class Features;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Features> Features_ptr;

class Features : public Collection<Feature_ptr, Features_ptr>
{
private:
	// Constructors
	Features();
	Features(Surfaces_ptr &surfaces);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Features &fs);

	friend std::ostream &operator<<(std::ostream &strm,
		const Features_ptr &fs);

public:
	// Factories
	static Features_ptr create();
	static Features_ptr create(Surfaces_ptr &surfaces);

};

#endif