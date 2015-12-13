#ifndef FEATURE3DS_H
#define FEATURE3DS_H

/**
 *	feature3ds.h
 *	-----------------------------------------------------------------------
 *	A Feature3Ds object is container for one or more Feature objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "collection.h"
#include "feature3d.h"

class Feature3Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature3Ds> Feature3Ds_ptr;

class Feature3Ds : public Collection<Feature3D_ptr, Feature3Ds_ptr>
{
private:
	// Constructors
	Feature3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature3Ds &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature3Ds_ptr &fs);

public:
	// Factories
	static Feature3Ds_ptr create();
};

#endif