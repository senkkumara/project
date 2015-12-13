using namespace std;

#include "feature2d.h"
#include "entities.h"
#include "entity.h"
#include "exceptions.h"
#include "utils.h"

Feature2D::~Feature2D()
{
	// do nothing...
}

void Feature2D::_init()
{
	// do nothing...
}

LineEntity2D_ptr Feature2D::entry()
{
	return _entry;
}

LineEntity2D_ptr Feature2D::exit()
{
	return _exit;
}

Feature2DType Feature2D::getType()
{
	return _type;
}

Feature2DLine::Feature2DLine(Edge_ptr &e, Edges_ptr &b, Entity2D::Fit2D f)
{
	_init();

	_fit = f;
	_boundary = b;

	Point_ptr p[4];
	LineEntity2D_ptr l[2];

	p[0] = e->left();
	p[1] = e->right();
	l[0] = LineEntity2D::create(p[0], p[1], _fit);
	l[1] = LineEntity2D::createParallel(l[0], 150.0, true);
	p[2] = l[1]->left();
	p[3] = l[1]->right();

	if (_intercept())
	{
		// Rail is not possible!
		throw SolutionBuildException();
	}

	_active = l[0];
	_passive = l[1];
	_entry = LineEntity2D::create(p[0], p[1]);
	_exit = LineEntity2D::create(p[2], p[3]);
}

void Feature2DLine::_init()
{
	__super::_init();
	_type = F2D_LINE;
}

bool Feature2DLine::_intercept()
{
	//TODO: implement method
	return false;
}

bool Feature2DLine::_intercept(Edge_ptr &e)
{
	//TODO: implement method
	return false;
}

Feature2DLine_ptr Feature2DLine::create(Edge_ptr &e, Edges_ptr &b,
										Entity2D::Fit2D f)
{
	return Feature2DLine_ptr(new Feature2DLine(e, b, f));
}

bool Feature2DLine::append(Edge_ptr &e)
{
	_active->add(e->right());
	if (_intercept())
	{
		_active->remove(e->right());
		return false;
	}
	return true;
}

Entity2D::Fit2D Feature2DLine::getFit()
{
	return _fit;
}

LineEntity2D_ptr Feature2DLine::getActive()
{
	return _active;
}

LineEntity2D_ptr Feature2DLine::getPassive()
{
	return _passive;
}

Feature2DLine_ptr Feature2DLine::cast(Feature2D_ptr &f)
{
	return utils::cast<Feature2D_ptr, Feature2DLine_ptr, Feature2DLine>(f);
}

Feature2DRad::Feature2DRad(Feature2DLine_ptr &f1, Feature2DLine_ptr &f2, Edges_ptr &b)
{
	_init();

	_boundary = b;

	LineEntity2D_ptr l[2];
	Point_ptr p[4];

	l[0] = f1->getActive();
	l[1] = f2->getActive();

	_active = RadEntity2D::create(l[0], l[1]);
	_passive = RadEntity2D::createCorner(_active, 150.0, true);

	if (_intercept())
	{
		// Rail is not possible! (without further work...)
		throw SolutionBuildException();
	}

	p[0] = _active->left();
	p[1] = _active->right();
	p[2] = _passive.at(0)->left();
	p[3] = _passive.at(1)->right();

	_entry = LineEntity2D::create(p[0], p[1]);
	_exit = LineEntity2D::create(p[2], p[3]);
}

void Feature2DRad::_init()
{
	__super::_init();
	_type = F2D_RADIUS;
}

bool Feature2DRad::_intercept()
{
	//TODO: implement method
	return false;
}

bool Feature2DRad::_intercept(Edges_ptr &e)
{
	//TODO: implement method
	return false;
}

bool Feature2DRad::_intercept(Edge_ptr &e)
{
	//TODO: implement method
	return false;
}

Feature2DRad_ptr Feature2DRad::create(Feature2DLine_ptr &f1,
									  Feature2DLine_ptr &f2,
									  Edges_ptr &b)
{
	return Feature2DRad_ptr(new Feature2DRad(f1, f2, b));
}

Feature2DRad_ptr Feature2DRad::cast(Feature2D_ptr &f)
{
	return utils::cast<Feature2D_ptr, Feature2DRad_ptr, Feature2DRad>(f);
}

RadEntity2D_ptr Feature2DRad::getActive()
{
	return _active;
}

vector<LineEntity2D_ptr> Feature2DRad::getPassive()
{
	return _passive;
}