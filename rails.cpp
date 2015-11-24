using namespace std;

#include "rails.h"

Rails::Rails(Plan_ptr &plan)
{
	_plan = plan;
}

Rails_ptr Rails::create(Plan_ptr &plan)
{
	return Rails_ptr(new Rails(plan));
}

Plan_ptr Rails::getPlan()
{
	return _plan;
}