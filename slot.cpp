using namespace std;

#include "slot.h"

Slot::Slot(double val)
{
	_type = Slot::SLOT_TYPE_POINT;
	_range[0] = val;
	_range[1] = val;
}

Slot::Slot(double min, double max)
{
	_type = Slot::SLOT_TYPE_RANGE;
	_range[0] = min;
	_range[1] = max;
}

Slot_ptr Slot::create(double val)
{
	return Slot_ptr(new Slot(val));
}

Slot_ptr Slot::create(double min, double max)
{
	return Slot_ptr(new Slot(min, max));
}

Slot::Type Slot::getType()
{
	return _type;
}

double* Slot::getRange()
{
	return _range;
}