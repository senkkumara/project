using namespace std;

#include "plan.h"
#include <iostream>

Plan::Plan(Application_ptr &app)
{
	_app = app;

	_buildPath();
	_checkPath();
	_buildRise();
	_smoothRise();
	_checkRise();
}

void Plan::_buildPath()
{
	cout << "Building..." << endl;
}

void Plan::_checkPath()
{

}

void Plan::_buildRise()
{

}

void Plan::_smoothRise()
{

}

void Plan::_checkRise()
{

}

Plan_ptr Plan::create(Application_ptr &app)
{
	return Plan_ptr(new Plan(app));
}