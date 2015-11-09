#ifndef PLAN_H
#define PLAN_H

using namespace std;

#include <memory>
#include <vector>
#include "features.h"
#include "block.h"

class Plan;
typedef shared_ptr<Plan> Plan_ptr;

class Plan
{
private:
	// Constructors
	Plan(Features_ptr &features);

	// Member variables (private)
	vector<Feature_ptr> _features;
	vector<Block_ptr>	_items;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Plan &p);

public:
	// Factories
	static Plan_ptr create(Features_ptr &features);


};

#endif