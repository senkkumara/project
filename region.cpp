using namespace std;

#include "region.h"
#include "entities.h"
#include "entity.h"
#include "exceptions.h"
#include "utils.h"

SurfaceRegion2D_ptr SurfaceRegion2D::create(Edge_ptr &e, Edges_ptr &b,
		Entity2D::Fit2D f)
{
	return SurfaceRegion2D_ptr(new SurfaceRegion2D(e, b, f));
}

bool SurfaceRegion2D::append(Edge_ptr &e)
{
	_active->add(e->right());
	if (_intercept())
	{
		_active->remove(e->right());
		return false;
	}
	return true;
}

Edges_ptr SurfaceRegion2D::getBoundary()
{
	return _boundary;
}

Entity2D::Fit2D SurfaceRegion2D::getFit()
{
	return _fit;
}

SurfaceRegion2D::Type SurfaceRegion2D::getType()
{
	return _type;
}

Edges_ptr SurfaceRegion2D::getEdges()
{
	return _edges;
}

LineEntity2D_ptr SurfaceRegion2D::getActive()
{
	return _active;
}

LineEntity2D_ptr SurfaceRegion2D::getPassive()
{
	return _passive;
}

LineEntity2D_ptr SurfaceRegion2D::entry()
{
	return _entry;
}

LineEntity2D_ptr SurfaceRegion2D::exit()
{
	return _exit;
}

SurfaceRegion2D::SurfaceRegion2D(Edge_ptr &e, Edges_ptr &b, Entity2D::Fit2D f)
{
	//TODO: implement method
}

void SurfaceRegion2D::_init()
{
	//TODO: implement method
}

bool SurfaceRegion2D::_intercept()
{
	//TODO: implement method
	return false;
}

bool SurfaceRegion2D::_intercept(Edges_ptr &e)
{
	//TODO: implement method
	return false;
}

bool SurfaceRegion2D::_intercept(Edge_ptr &e)
{
	//TODO: implement method
	return false;
}

SurfaceTransition2D_ptr SurfaceTransition2D::create(SurfaceRegion2D_ptr &f1,
		SurfaceRegion2D_ptr &f2, Edges_ptr &e)
{
	return SurfaceTransition2D_ptr(new SurfaceTransition2D(f1, f2, e));
}

RadEntity2D_ptr SurfaceTransition2D::getActive()
{
	return _active;
}

LineEntity2D_ptr* SurfaceTransition2D::getPassive()
{
	return _passive;
}

SurfaceTransition2D::SurfaceTransition2D(SurfaceRegion2D_ptr &f1, SurfaceRegion2D_ptr &f2, Edges_ptr &b)
{
	_init();

	_boundary = b;

	LineEntity2D_ptr l[2];
	Point_ptr p[4];

	l[0] = f1->getActive();
	l[1] = f2->getActive();

	_active = RadEntity2D::create(l[0], l[1]);
	//_passive = RadEntity2D::createCorner(_active, 150.0, true);

	if (_intercept())
	{
		// Rail is not possible! (without further work...)
		throw SolutionBuildException();
	}

	p[0] = _active->left();
	p[1] = _active->right();
	//p[2] = _passive.at(0)->left();
	//p[3] = _passive.at(1)->right();

	_entry = LineEntity2D::create(p[0], p[1]);
	_exit = LineEntity2D::create(p[2], p[3]);
}

void SurfaceTransition2D::_init()
{
	//TODO: implement method
}

bool SurfaceTransition2D::_intercept()
{
	//TODO: implement method
	return false;
}

bool SurfaceTransition2D::_intercept(Edges_ptr &e)
{
	//TODO: implement method
	return false;
}

bool SurfaceTransition2D::_intercept(Edge_ptr &e)
{
	//TODO: implement method
	return false;
}

SurfaceRegion3D::Type SurfaceRegion3D::getType()
{
	return _type;
}