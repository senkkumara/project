using namespace std;

#include "entity.h"
#include "utils.h"

/**
 *	Virtual deconstructor, forcing Entity to be polymorphic.
 */
Entity::~Entity()
{
	// do nothing...
}

/**
 *	Get the valid "t" range for the entity.
 */
double* Entity::getRange()
{
	return _range;
}

/**
 *	Get the minimum "t" value for the entity.
 */
double Entity::minT()
{
	return _range[0];
}

/**
 *	Get the maximum "t" value for the entity.
 */
double Entity::maxT()
{
	return _range[1];
}

/**
 *	Get points representing the ends the entity.
 */
Point_ptr* Entity::getEnds()
{
	return _ends;
}

/**
 *	Get the point representing the start of the entity.
 */
Point_ptr Entity::start()
{
	return _ends[0];
}

/**
 *	Get the point representing the end of the entity.
 */
Point_ptr Entity::end()
{
	return _ends[1];
}

/**
 *	Get the X coefficients of the equation of the entity.
 */
double*	Entity::getXCoefficients()
{
	return _cfs[0];
}

/**
 *	Get the Y coefficients of the equation of the entity.
 */
double* Entity::getYCoefficients()
{
	return _cfs[1];
}

/**
 *	Get the Z coefficients of the equation of the entity.
 */
double* Entity::getZCoefficients()
{
	return _cfs[2];
}

/**
 *	Set the range of "t" value for the entity.
 */
void Entity::setRange(double min, double max)
{
	setMinT(min);
	setMaxT(max);
}

/**
 *	Set the minimum "t" value for the entity.
 */
void Entity::setMinT(double min)
{
	_range[0] = min;
}

/**
 *	Set the maximum "t" value for the entity.
 */
void Entity::setMaxT(double max)
{
	_range[1] = max;
}

Entity2D::~Entity2D()
{
	// do nothing...
}

Entity2D::Fit2D Entity2D::getFit()
{
	return _fit;
}

Point_ptr Entity2D::posAt(double pc)
{
	double t = 0.0, xP = 0.0, yP = 0.0, zP = 0.0;

	if (_range[0] != 0 || _range[1] != 0)
	{
		t = ((_range[1] + _range[0]) * pc) + _range[0];
		xP = x(t);
		yP = y(t);
	}

	return Point::create(xP, yP, zP);
}

LineEntity2D_ptr LineEntity2D::clone(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::createParallel(LineEntity2D_ptr &l, double d, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l, Point_ptr &p, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l, double t, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::convertTo2D(LineEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::cast(Entity2D_ptr &e)
{
	return utils::cast<Entity2D_ptr, LineEntity2D_ptr, LineEntity2D>(e);
}

double LineEntity2D::x(double t)
{
	return (_cfs[0][0]*t + _cfs[0][1]);
}

double LineEntity2D::y(double t)
{
	return (_cfs[1][0]*t + _cfs[1][1]);
}

void LineEntity2D::add(Point_ptr &p)
{
	Points_ptr ps = Points::create();
	ps->add(p);
	add(ps);
	//TODO: implement method
}

void LineEntity2D::add(Points_ptr &ps)
{
	//TODO: implement method
	__super::add(ps);
}

void LineEntity2D::insert(Point_ptr &p, int index)
{
	//TODO: implement method
	__super::insert(p, index);
}

void LineEntity2D::remove(Point_ptr &p)
{
	//TODO: implement method
}

bool LineEntity2D::intercept(LineEntity2D_ptr &l)
{
	double a, b, c, d, e, f, g, h;
	double r[4];

	a = _cfs[0][0];
	b = _cfs[0][1];
	c = _cfs[1][0];
	d = _cfs[1][1];
	e = l->getXCoefficients()[0];
	f = l->getXCoefficients()[1];
	g = l->getYCoefficients()[0];
	h = l->getYCoefficients()[1];

	r[0] = _range[0];
	r[1] = _range[1];
	r[2] = l->getRange()[0];
	r[3] = l->getRange()[1];

	if (a == 0.0 && e == 0.0)
	{
		// Lines are colinear (vertical)
		return false;
	}

	if (c == 0.0 && g == 0.0)
	{
		// Lines are colinear (horizontal)
		return false;
	}

	return false;
}

bool LineEntity2D::intercept(vector<LineEntity2D_ptr> e)
{
	for (unsigned int i = 0; i < e.size(); i++)
	{
		if (intercept(e.at(i))) return true;
	}

	return false;
}

bool LineEntity2D::intercept(Edge_ptr &e)
{
	return intercept(LineEntity2D::create(e));
}

bool LineEntity2D::intercept(Edges_ptr &e)
{
	for (int i = 0; i < e->size(); i++)
	{
		if (intercept(e->get(i))) return true;
	}

	return false;
}

Point_ptr LineEntity2D::getIntersect(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

LineEntity2D::LineEntity2D(Point_ptr &p1, Point_ptr &p2)
{
	Points_ptr p = Points::create();
	p->add(p1);
	p->add(p2);

	_init(p, Entity2D::FIT2D_BEST);
}

LineEntity2D::LineEntity2D(Point_ptr &p1, Point_ptr &p2, Entity2D::Fit2D f)
{
	Points_ptr p = Points::create();
	p->add(p1);
	p->add(p2);

	_init(p, f);
}

LineEntity2D::LineEntity2D(Points_ptr &p)
{
	_init(p, Entity2D::FIT2D_BEST);
}

LineEntity2D::LineEntity2D(Points_ptr &p, Entity2D::Fit2D f)
{
	_init(p, f);
}

LineEntity2D::LineEntity2D(Edge_ptr &e)
{
	Points_ptr p = Points::create();
	p->add(e->left());
	p->add(e->right());

	_init(p, Entity2D::FIT2D_BEST);
}

LineEntity2D::LineEntity2D(Edge_ptr &e, Entity2D::Fit2D f)
{
	Points_ptr p = Points::create();
	p->add(e->left());
	p->add(e->right());

	_init(p, f);
}

void LineEntity2D::_init(Points_ptr &p, Entity2D::Fit2D f)
{
	//TODO: implement method
}

void LineEntity2D::_calculate()
{
	//TODO: implement method
}

bool LineEntity2D::_increment(Point_ptr &p)
{
	//TODO: implement method
	return false;
}

RadEntity2D_ptr RadEntity2D::clone(RadEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

RadEntity2D_ptr RadEntity2D::create(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2)
{
	return RadEntity2D_ptr(new RadEntity2D(l1, l2));
}

RadEntity2D_ptr RadEntity2D::createRadial(RadEntity2D_ptr &l, double d, bool link)
{
	//TODO: implement method
	return 0;
}

vector<LineEntity2D_ptr> RadEntity2D::createCorner(RadEntity2D_ptr &l, double d, bool link)
{
	//TODO: implement method
	vector<LineEntity2D_ptr> v;
	return v;
}

RadEntity2D_ptr RadEntity2D::convertToArc(HelixEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
}

RadEntity2D_ptr RadEntity2D::cast(Entity2D_ptr &e)
{
	return utils::cast<Entity2D_ptr, RadEntity2D_ptr, RadEntity2D>(e);
}

double RadEntity2D::x(double t)
{
	//TODO: correct(?)
	return (_range[0] * cos(t)) + _range[1];
}

double RadEntity2D::y(double t)
{
	//TODO: correct(?)
	return (_range[0] * sin(t)) + _range[1];
}

bool RadEntity2D::intercept(LineEntity2D_ptr &e)
{
	//TODO: implement method
	return false;
}

bool RadEntity2D::intercept(vector<LineEntity2D_ptr> e)
{
	for (unsigned int i = 0; i < e.size(); i++)
	{
		if (intercept(e.at(i))) return true;
	}

	return false;
}

bool RadEntity2D::intercept(Edge_ptr &e)
{
	return intercept(LineEntity2D::create(e));
}

bool RadEntity2D::intercept(Edges_ptr &e)
{
	for (int i = 0; i < e->size(); i++)
	{
		if (intercept(e->get(i))) return true;
	}

	return false;
}

RadEntity2D::RadEntity2D(LineEntity2D_ptr &e1, LineEntity2D_ptr &e2)
{
	_adj[0] = e1;
	_adj[1] = e2;

	_calculate();
}

void RadEntity2D::_calculate()
{
	//TODO: implement method
}

Entity3D::Fit3D Entity3D::getFit()
{
	return _fit;
}

Point_ptr Entity3D::posAt(double pc)
{
	//TODO: implement method
	return 0;
}

Entity3D::~Entity3D()
{
	//TODO: implement method
}

LineEntity3D_ptr LineEntity3D::clone(LineEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
}

LineEntity3D_ptr LineEntity3D::createParallel(LineEntity3D_ptr &l, double d, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity3D_ptr LineEntity3D::createNormal(LineEntity3D_ptr &l, Point_ptr &p, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity3D_ptr LineEntity3D::convertTo3D(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

LineEntity3D_ptr LineEntity3D::cast(Entity3D_ptr &e)
{
	return utils::cast<Entity3D_ptr, LineEntity3D_ptr, LineEntity3D>(e);
}

double LineEntity3D::x(double t)
{
	//TODO: implement method
	return 0.0;
}

double LineEntity3D::y(double t)
{
	//TODO: implement method
	return 0.0;
}

double LineEntity3D::z(double t)
{
	//TODO: implement method
	return 0.0;
}

void LineEntity3D::add(Point_ptr &p)
{
	//TODO: implement method
}

void LineEntity3D::add(Points_ptr &p)
{
	//TODO: implement method
}

void LineEntity3D::insert(Point_ptr &p, int i)
{
	//TODO: implement method
}

void LineEntity3D::remove(Point_ptr &p)
{
	//TODO: implement method
}

LineEntity3D::LineEntity3D(Point_ptr &point1, Point_ptr &point2)
{
	//TODO: implement method
}

LineEntity3D::LineEntity3D(Points_ptr &points)
{
	//TODO: implement method
}