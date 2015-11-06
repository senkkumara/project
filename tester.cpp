using namespace std;

#include <iostream>
#include <map>
#include "tester.h"
#include "tests.h"

Tester::Tester(Layer_ptr &layer)
{
	_layer = layer;
}

void Tester::_init()
{
	
}

Tester_ptr Tester::create(Layer_ptr &layer)
{
	return Tester_ptr(new Tester(layer));
}

void Tester::run()
{
	
	_layer->setType(LT_STRAIGHT);
}

Layer_ptr Tester::getLayer()
{
	return _layer;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Tester &t)
{
	return strm;
}