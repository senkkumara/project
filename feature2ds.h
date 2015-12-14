#ifndef FEATURE2DS_H
#define FEATURE2DS_H

/**
 *	feature2ds.h
 *	---------------------------------------------------------------------------
 *	A Feature2Ds object is container for one or more Feature objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "collection.h"
#include "feature2d.h"

class Feature2Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature2Ds> Feature2Ds_ptr;

/**
 *	Collection of Feature2D.
 */
class Feature2Ds : public Collection<Feature2D_ptr, Feature2Ds_ptr>
{
private:
	// Constructors
	Feature2Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature2Ds &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature2Ds_ptr &f);

public:
	// Factories
	static Feature2Ds_ptr create();
};

#endif