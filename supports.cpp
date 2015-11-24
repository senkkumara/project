using namespace std;

#include "supports.h"

Supports::Supports(Plan_ptr &plan)
{
	_plan = plan;
}

Supports_ptr Supports::create(Plan_ptr &plan)
{
	return Supports_ptr(new Supports(plan));
}

Plan_ptr Supports::getPlan()
{
	return _plan;
}