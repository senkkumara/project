#ifndef FEATURES_H
#define FEATURES_H

using namespace std;

#include <memory>
#include <vector>
#include "surface.h"
#include "feature.h"

class Features;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Features> Features_ptr;

class Features
{
private:
	// Constructors
	Features();
	Features(Surface_ptr &surface);

	// Member variables (private)
	vector<Feature_ptr> _items;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Features &fs);

public:
	// Factories
	static Features_ptr create();
	static Features_ptr create(Surface_ptr &surface);
	
	// Member functions (public)
	void			add(Feature_ptr &feature);
	void			remove (Feature_ptr &feature);
	Feature_ptr		get(int index);
	Feature_ptr		first();
	Feature_ptr		last();
	int				size();

	// Getters
	vector<Feature_ptr> getItems();
};

#endif