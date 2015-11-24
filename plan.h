#ifndef PLAN_H
#define PLAN_H

using namespace std;

#include <memory>
#include "collection.h"
#include "application.h"
#include "block.h"

class Plan;
typedef shared_ptr<Plan> Plan_ptr;

class Plan : public Collection<Block_ptr, Plan_ptr>
{
private:
	// Constructors
	Plan(Application_ptr &app);

	// Fields (private)
	Application_ptr _app;

	// Methods (private)
	void _buildPath();
	void _checkPath();
	void _buildRise();
	void _smoothRise();
	void _checkRise();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Plan &p);
	friend std::ostream &operator<<(std::ostream &strm,
		const Plan_ptr &p);

public:
	// Factories
	static Plan_ptr create(Application_ptr &app);


};

#endif