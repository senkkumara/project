#ifndef FEATURES_H
#define FEATURES_H

/**
 *	features.h
 *	-----------------------------------------------------------------------
 *	A Features object is container for one or more Feature objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "collection.h"
#include "feature.h"

class Features;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Features> Features_ptr;

class Feature2Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature2Ds> Feature2Ds_ptr;

class Feature3Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature3Ds> Feature3Ds_ptr;

/**
 *	Collection of Features.
 */
class Features : public Collection<Feature_ptr, Features_ptr>
{
private:
	// Constructors
	Features();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Features &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Features_ptr &f);

public:
	// Factories
	static Features_ptr create();
};

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

/**
 *	Collection of Feature3D.
 */
class Feature3Ds : public Collection<Feature3D_ptr, Feature3Ds_ptr>
{
private:
	// Constructors
	Feature3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature3Ds &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature3Ds_ptr &f);

public:
	// Factories
	static Feature3Ds_ptr create();
};

#endif