using namespace std;

#include "rise.h"

Rise::Rise()
{
	_init();
}

Rise::Rise(Facet_ptr &facet)
{
	_init();
	_maxHeight = facet->getMaxZ() + _tol;
	_minHeight = facet->getMinZ() - _tol;

	add(facet);
}

void Rise::_init()
{
	_tol = 35.0;
	_geometry = Geometry::create();
	_left = Edges::create();
	_right = Edges::create();

	recalculateIfcAngle();
}

Rise_ptr Rise::create()
{
	return Rise_ptr(new Rise());
}

Rise_ptr Rise::create(Facet_ptr &facet)
{
	return Rise_ptr(new Rise(facet));
}