using namespace std;

#include "entity.h"
#include "utils.h"

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
 *	Virtual deconstructor, forcing Entity to be polymorphic.
 */
Entity::~Entity()
{
	// do nothing...
}

/** 
 *	Get the fit used to create the entity.
 */
Entity2D::Fit2D Entity2D::getFit()
{
	return _fit;
}

/**
 *	Virtual deconstructor, forcing Entity to be polymorphic.
 */
Entity2D::~Entity2D()
{
	// do nothing...
}

/**
 *	Factory method that creates a new entity from another.
 *	
 *	Note that it will reuse the same Points as the donor.
 */
LineEntity2D_ptr LineEntity2D::clone(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::createParallel(LineEntity2D_ptr &l, double d)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l, Point_ptr &p)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l, double t)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::convertTo2D(LineEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::cast(Entity2D_ptr &e)
{
	return utils::cast<Entity2D_ptr, LineEntity2D_ptr, LineEntity2D>(e);
}

/**
 *	Calculate the x-coordinate at a given value of t.
 */
double LineEntity2D::x(double t)
{
	return (_cfs[0][0]*t + _cfs[0][1]);
}

/**
 *	Calculate the y-coordinate at a given value of t.
 */
double LineEntity2D::y(double t)
{
	return (_cfs[1][0]*t + _cfs[1][1]);
}

/**
 *	Calculate the z-coordinate at a given value of t.
 */
double LineEntity2D::z(double t)
{
	return 0.0;
}

/**
 *	Get the range of "t" value for the entity.
 */
void LineEntity2D::setRange(double min, double max)
{
	_range[0] = min;
	_range[1] = max;

	_ends[0] = posAt(min);
	_ends[1] = posAt(max);
}

/**
 *	Get the minimum "t" value for the entity.
 */
void LineEntity2D::setMinT(double min)
{
	_range[0] = min;
	_ends[0] = posAt(min);
}

/**
 *	Get the maximum "t" value for the entity.
 */
void LineEntity2D::setMaxT(double max)
{
	_range[1] = max;
	_ends[1] = posAt(max);
}

/**
 *	Get the point at a given "t" value.
 */
Point_ptr LineEntity2D::posAt(double t)
{
	double xP = 0.0, yP = 0.0, zP = 0.0;

	if (_range[0] != 0 || _range[1] != 0)
	{
		xP = x(t);
		yP = y(t);
		zP = z(t);
	}

	return Point::create(xP, yP, zP);
}

/**
 *	Get the Point a given percentage along the entity.
 */
Point_ptr LineEntity2D::posAtDist(double pc)
{
	double t = 0.0;

	if (_range[0] != 0 || _range[1] != 0)
	{
		t = ((_range[1] + _range[0]) * pc) + _range[0];
		return posAt(t);
	}

	return Point::create(0.0, 0.0, 0.0);
}

/**
 *	Add a point to the entity and recalculate the equation.
 */
void LineEntity2D::add(Point_ptr &p)
{
	__super::add(p);
	_increment(p);
}

/**
 *	Add the points to the entity and recalculate the equation.
 */
void LineEntity2D::add(Points_ptr &ps)
{
	__super::add(ps);
	_increment(ps);
}

/**
 *	Inserts a point and recalculates the equation.
 */
void LineEntity2D::insert(Point_ptr &p, int index)
{
	__super::insert(p, index);
	_increment(p);
}

/**
 *	Remove a point and recalculate the equation.
 */
void LineEntity2D::remove(Point_ptr &p)
{
	__super::remove(p);
	_decrement(p);
}

/**
 *	Returns a boolean depending on whether an argument entity intersects
 *	this entity.
 */
bool LineEntity2D::intersects(LineEntity2D_ptr &l)
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

/**
 *	Returns a boolean depending on whether one or more argument entities
 *	intersect this entity.
 */
bool LineEntity2D::intersects(vector<LineEntity2D_ptr> e)
{
	for (unsigned int i = 0; i < e.size(); i++)
	{
		if (intersects(e.at(i))) return true;
	}

	return false;
}

/**
 *	Returns a boolean depending on whether an argument edge intersects
 *	this entity.
 */
bool LineEntity2D::intersects(Edge_ptr &e)
{
	return intersects(LineEntity2D::create(e));
}

/**
 *	Returns a boolean depending on whether one or more of the argument
 *	edges intersects this entity.
 */
bool LineEntity2D::intersects(Edges_ptr &e)
{
	for (int i = 0; i < e->size(); i++)
	{
		if (intersects(e->get(i))) return true;
	}

	return false;
}

bool LineEntity2D::intersects(RadEntity2D_ptr &e)
{
	//TODO: implement method
	return false;
}

bool LineEntity2D::intersects(vector<RadEntity2D_ptr> &es)
{
	for (unsigned int i = 0; i < es.size(); i++)
	{
		if (intersects(es.at(i))) return true;
	}

	return false;
}

/**
 *	Gets the point where this entity intersects an argument entity.
 */
Point_ptr LineEntity2D::getIntersect(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity2D::LineEntity2D(Point_ptr &p1, Point_ptr &p2)
{
	__super::add(p1);
	__super::add(p2);

	_init(Entity2D::FIT2D_BEST);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(Point_ptr &p1, Point_ptr &p2, Entity2D::Fit2D f)
{
	__super::add(p1);
	__super::add(p2);

	_init(f);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(Points_ptr &ps)
{
	__super::add(ps);

	_init(Entity2D::FIT2D_BEST);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(Points_ptr &ps, Entity2D::Fit2D f)
{
	__super::add(ps);

	_init(f);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(Edge_ptr &e)
{
	__super::add(e->left());
	__super::add(e->right());

	_init(Entity2D::FIT2D_BEST);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(Edge_ptr &e, Entity2D::Fit2D f)
{
	__super::add(e->left());
	__super::add(e->right());

	_init(f);
}

/**
 *	Initialise the fields.
 */
void LineEntity2D::_init(Entity2D::Fit2D f)
{
	_fit = f;
	_calculate();
}

/**
 *	Full recalculate the coefficients of the equation.
 */
void LineEntity2D::_calculate()
{
	//TODO: implement method
}

/**
 *	Update the coefficients of the equation to include the additional point.
 *
 *	This equation does not recalculate the whole equation, it merely
 *	incorporates the partial contribution of the point.
 */
void LineEntity2D::_increment(Point_ptr &p)
{
	//TODO: implement method
}

/**
 *	Update the coefficients of the equation to include the additional points.
 *
 *	This equation does not recalculate the whole equation, it merely
 *	incorporates the partial contribution of the points.
 */
void LineEntity2D::_increment(Points_ptr &ps)
{
	//TODO: implement method
}

/**
 *	Update the coefficients of the equation to exclude the argument point.
 *
 *	This equation does not recalculate the whole equation, it merely
 *	removes the partial contribution of the point.
 */
void LineEntity2D::_decrement(Point_ptr &p)
{
	//TODO: implement method
}

/**
 *	Update the coefficients of the equation to exclude the argument points.
 *
 *	This equation does not recalculate the whole equation, it merely
 *	removes the partial contribution of the point.
 */
void LineEntity2D::_decrement(Points_ptr &ps)
{
	//TODO: implement method
}

/**
 *	
 */
RadEntity2D_ptr RadEntity2D::clone(RadEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
RadEntity2D_ptr RadEntity2D::create(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2)
{
	return RadEntity2D_ptr(new RadEntity2D(l1, l2));
}

/**
 *	
 */
RadEntity2D_ptr RadEntity2D::createRadial(RadEntity2D_ptr &l, double d)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
vector<LineEntity2D_ptr> RadEntity2D::createCorner(RadEntity2D_ptr &l, double d)
{
	//TODO: implement method
	vector<LineEntity2D_ptr> v;
	return v;
}

/**
 *	
 */
RadEntity2D_ptr RadEntity2D::convertToArc(HelixEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
RadEntity2D_ptr RadEntity2D::cast(Entity2D_ptr &e)
{
	return utils::cast<Entity2D_ptr, RadEntity2D_ptr, RadEntity2D>(e);
}

/**
 *	Calculate the x-coordinate at a given value of t.
 */
double RadEntity2D::x(double t)
{
	return (_cfs[0][0] * cos(t)) + _cfs[0][1];
}

/**
 *	Calculate the y-coordinate at a given value of t.
 */
double RadEntity2D::y(double t)
{
	return (_cfs[1][0] * sin(t)) + _cfs[1][1];
}

/**
 *	Calculate the z-coordinate at a given value of t.
 */
double RadEntity2D::z(double t)
{
	return 0.0;
}

/**
 *	Get the range of "t" value for the entity.
 */
void RadEntity2D::setRange(double min, double max)
{
	_range[0] = min;
	_range[1] = max;

	_ends[0] = posAt(min);
	_ends[1] = posAt(max);
}

/**
 *	Get the minimum "t" value for the entity.
 */
void RadEntity2D::setMinT(double min)
{
	_range[0] = min;
	_ends[0] = posAt(min);
}

/**
 *	Get the maximum "t" value for the entity.
 */
void RadEntity2D::setMaxT(double max)
{
	_range[1] = max;
	_ends[1] = posAt(max);
}

/**
 *	Get the point at a given "t" value.
 */
Point_ptr RadEntity2D::posAt(double t)
{
	double xP = 0.0, yP = 0.0, zP = 0.0;

	if (_range[0] != 0 || _range[1] != 0)
	{
		xP = x(t);
		yP = y(t);
		zP = z(t);
	}

	return Point::create(xP, yP, zP);
}

/**
 *	Get the Point a given percentage along the entity.
 */
Point_ptr RadEntity2D::posAtDist(double pc)
{
	double t = 0.0;

	if (_range[0] != 0 || _range[1] != 0)
	{
		t = ((_range[1] + _range[0]) * pc) + _range[0];
		return posAt(t);
	}

	return Point::create(0.0, 0.0, 0.0);
}

/**
 *	
 */
bool RadEntity2D::intersects(LineEntity2D_ptr &e)
{
	//TODO: implement method
	return false;
}

/**
 *	
 */
bool RadEntity2D::intersects(vector<LineEntity2D_ptr> e)
{
	for (unsigned int i = 0; i < e.size(); i++)
	{
		if (intersects(e.at(i))) return true;
	}

	return false;
}

/**
 *	
 */
bool RadEntity2D::intersects(Edge_ptr &e)
{
	return intersects(LineEntity2D::create(e));
}

/**
 *	
 */
bool RadEntity2D::intersects(Edges_ptr &e)
{
	for (unsigned int i = 0; i < e->size(); i++)
	{
		if (intersects(e->get(i))) return true;
	}

	return false;
}

/**
 *
 */
bool RadEntity2D::intersects(RadEntity2D_ptr &e)
{
	//TODO: implement method
	return false;
}

/**
 *
 */
bool RadEntity2D::intersects(vector<RadEntity2D_ptr> &es)
{
	for (unsigned int i = 0; i < es.size(); i++)
	{
		if (intersects(es.at(i))) return true;
	}

	return false;
}

/**
 *	
 */
RadEntity2D::RadEntity2D(LineEntity2D_ptr &e1, LineEntity2D_ptr &e2)
{
	_adj[0] = e1;
	_adj[1] = e2;

	_calculate();
}

/**
 *	Fully recalculate the coefficients from the adjacent lines.
 */
void RadEntity2D::_calculate()
{
	//TODO: implement method
}

/**
 *	Get the fit used to create the entity.
 */
Entity3D::Fit3D Entity3D::getFit()
{
	return _fit;
}

/**
 *	
 */
Entity3D::~Entity3D()
{
	//TODO: implement method
}

/**
 *	
 */
LineEntity3D_ptr LineEntity3D::clone(LineEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity3D_ptr LineEntity3D::createParallel(LineEntity3D_ptr &l, double d)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity3D_ptr LineEntity3D::createNormal(LineEntity3D_ptr &l, Point_ptr &p)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity3D_ptr LineEntity3D::convertTo3D(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
LineEntity3D_ptr LineEntity3D::cast(Entity3D_ptr &e)
{
	return utils::cast<Entity3D_ptr, LineEntity3D_ptr, LineEntity3D>(e);
}

/**
 *	
 */
double LineEntity3D::x(double t)
{
	//TODO: implement method
	return 0.0;
}

/**
 *	
 */
double LineEntity3D::y(double t)
{
	//TODO: implement method
	return 0.0;
}

/**
 *	
 */
double LineEntity3D::z(double t)
{
	//TODO: implement method
	return 0.0;
}

/**
 *	
 */
void LineEntity3D::add(Point_ptr &p)
{
	//TODO: implement method
}

/**
 *	
 */
void LineEntity3D::add(Points_ptr &p)
{
	//TODO: implement method
}

/**
 *	
 */
void LineEntity3D::insert(Point_ptr &p, int i)
{
	//TODO: implement method
}

/**
 *	
 */
void LineEntity3D::remove(Point_ptr &p)
{
	//TODO: implement method
}

/**
 *	
 */
LineEntity3D::LineEntity3D(Point_ptr &point1, Point_ptr &point2)
{
	//TODO: implement method
}

/**
 *	
 */
LineEntity3D::LineEntity3D(Points_ptr &points)
{
	//TODO: implement method
}