using namespace std;

#define _USE_MATH_DEFINES

#include "entity.h"
#include <iostream>
#include <math.h>
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
 *	Set the coefficients for a single direction - not all coefficients.
 */
void Entity::setCoefficients(int dir, double* cfs)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		_cfs[dir][i] = cfs[i];
	}
}

/**
 *	Set the X coefficients of the equation of the entity.
 */
void Entity::setXCoefficients(double* cfs)
{
	setCoefficients(0, cfs);
}

/**
 *	Set the Y coefficients of the equation of the entity.
 */
void Entity::setYCoefficients(double* cfs)
{
	setCoefficients(1, cfs);
}

/**
 *	Set the Z coefficients of the equation of the entity.
 */
void Entity::setZCoefficients(double* cfs)
{
	setCoefficients(2, cfs);
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
 *	Factory method using the default constructor.
 */
LineEntity2D_ptr LineEntity2D::create()
{
	return LineEntity2D_ptr(new LineEntity2D());
}

/**
 *	Factory method using the constructor that takes a vector of points -
 *	least squares regression on the coordinates is used to determine the line.
 *
 *	Note that a "Best Fit" is used - there are no adjustments made.
 */
LineEntity2D_ptr LineEntity2D::create(vector<Point_ptr> &ps)
{
	return LineEntity2D_ptr(new LineEntity2D(ps));
}

/**
 *	Factory method using the constructor that takes a vector of points -
 *	least squares regression on the coordinates is used to determine the line
 *	- along with a fit.
 *
 *	The specified fit specified ensures all the points are on one side of the
 *	line.
 */
LineEntity2D_ptr LineEntity2D::create(vector<Point_ptr> &ps, Fit2D fit)
{
	return LineEntity2D_ptr(new LineEntity2D(ps));
}

/**
 *	Factory method using the constructor that takes two points.
 */
LineEntity2D_ptr LineEntity2D::create(Point_ptr &p1, Point_ptr &p2)
{
	return LineEntity2D_ptr(new LineEntity2D(p1, p2));
}

/**
 *	Factory method using the constructor that takes two points and a fit.
 *
 *	The specified fit specified ensures all the points are on one side of the
 *	line.
 */
LineEntity2D_ptr LineEntity2D::create(Point_ptr &p1, Point_ptr &p2, Fit2D fit)
{
	return LineEntity2D_ptr(new LineEntity2D(p1, p2, fit));
}

/**
 *	Factory method using a Points collection.
 */
LineEntity2D_ptr LineEntity2D::create(Points_ptr &ps)
{
	return LineEntity2D_ptr(new LineEntity2D(ps));
}

/**
 *	Factory method using a Points collection and a fit.
 *
 *	The specified fit specified ensures all the points are on one side of the
 *	line.
 */
LineEntity2D_ptr LineEntity2D::create(Points_ptr &ps, Fit2D fit)
{
	return LineEntity2D_ptr(new LineEntity2D(ps, fit));
}

/**
 *	Factory method using an edge.
 */
LineEntity2D_ptr LineEntity2D::create(Edge_ptr &e)
{
	return LineEntity2D_ptr(new LineEntity2D(e));
}

/**
 *	Factory method using an edge and a fit.
 *
 *	The specified fit specified ensures all the points are on one side of the
 *	line.
 */
LineEntity2D_ptr LineEntity2D::create(Edge_ptr &e, Fit2D fit)
{
	return LineEntity2D_ptr(new LineEntity2D(e, fit));
}

/**
 *	Factory method using an edge collection.
 */
LineEntity2D_ptr LineEntity2D::create(Edges_ptr &es)
{
	return LineEntity2D_ptr(new LineEntity2D(es));
}

/**
 *	Factory method using an edge collection and a fit.
 *
 *	The specified fit specified ensures all the points are on one side of the
 *	line.
 */
LineEntity2D_ptr LineEntity2D::create(Edges_ptr &es, Fit2D fit)
{
	return LineEntity2D_ptr(new LineEntity2D(es, fit));
}

/**
 *	Factory method that creates a new line that is parallel to an existing
 *	line and at a given distance. The direction is determined by the sign
 *	of the distance (-ive = left, +ive = right).
 */
LineEntity2D_ptr LineEntity2D::createParallel(LineEntity2D_ptr &l, double d)
{
	LineEntity2D_ptr lp = LineEntity2D::create();
	
	double cfs[3][2];
	double* donor[2];
	double ang = 0.0;

	for (int i = 0; i < 3; i++)	// Zero-fill array
	{
		for (int j = 0; j < 2; j++)
		{
			cfs[i][j] = 0.0;
		}
	}

	// Get donor coefficients
	donor[0] = l->getXCoefficients();
	donor[1] = l->getYCoefficients();

	// Get angle of donor line
	ang = atan2(donor[1][0], donor[0][0]);

	// Create new coefficients
	cfs[0][0] = donor[0][0];
	cfs[1][0] = donor[1][0];

	cfs[0][1] = (d * sin(ang)) + donor[0][1];
	cfs[1][1] = (-1 * d * cos(ang)) + donor[1][1];

	// Populate new line's coefficients
	for (int i = 0; i < 3; i++)
	{
		lp->setCoefficients(i, cfs[i]);
	}

	return lp;
}

/**
 *	Factory method that creates a new line that is parallel to an existing
 *	line, at a given distance and in a given direction.
 *
 *	Note that the distance should always be positive regardless of direction
 *	since the directionality is achieved by multiplying the direction and the
 *	distance. Therefore, in this case two lefts would definitely make a right..
 */
LineEntity2D_ptr LineEntity2D::createParallel(LineEntity2D_ptr &l, double d,
											  Entity::EntitySide s)
{
	d *= s;
	return LineEntity2D::createParallel(l, d);
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l,
											Entity::EntityDir dir, double t1)
{
	LineEntity2D_ptr ln = LineEntity2D::create();

	double cfs[3][2];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cfs[i][j] = 0.0;
		}
	}

	double t[2] = {t1, 0.0};

	double* donor[2];
	donor[0] = l->getXCoefficients();
	donor[1] = l->getYCoefficients();

	double ang = dir * M_PI / 2;

	double coords[2];
	coords[0] = l->x(t[0]);
	coords[1] = l->y(t[0]);

	cfs[0][0] = (donor[0][0] * cos(ang)) - (donor[1][0] * sin(ang));
	cfs[1][0] = (donor[0][0] * sin(ang)) + (donor[1][0] * cos(ang));

	cfs[0][1] = coords[0] - (cfs[0][0] * t[1]);
	cfs[1][1] = coords[1] - (cfs[1][0] * t[1]);

	for (int i = 0; i < 3; i++)
	{
		ln->setCoefficients(i, cfs[i]);
	}

	return ln;
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l,
											Entity::EntityDir dir,
											Entity::EntityLoc loc)
{
	double t = 0.0;

	switch (loc)
	{
	case ENTITYLOC_START:
		t = l->minT();
		break;

	case ENTITYLOC_END:
		t = l->maxT();
		break;

	case ENTITYLOC_MID:
		t = (l->minT() + l->maxT()) / 2;
		break;

	}

	return LineEntity2D::createNormal(l, dir, t);
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::join(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2,
									double t1, double t2)
{
	LineEntity2D_ptr l = LineEntity2D::create(l1->posAt(t1),
		l2->posAt(t2));

	double r[2];
	Point_ptr p[2];
	p[0] = l1->posAt(t1);
	p[1] = l2->posAt(t2);

	double* lx = l->getXCoefficients();
	double* ly = l->getYCoefficients();

	if (lx[0] != 0)
	{
		r[0] = (p[0]->getX() - lx[1]) / lx[0];
		r[1] = (p[1]->getX() - lx[1]) / lx[0];
	}
	else
	{
		r[0] = (p[0]->getY() - ly[1]) / ly[0];
		r[1] = (p[1]->getY() - ly[1]) / ly[0];
	}

	l->setRange(r[0], r[1]);

	return l;
}

/**
 *	
 */
LineEntity2D_ptr LineEntity2D::join(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2,
									Entity::EntityLoc loc1,
									Entity::EntityLoc loc2)
{
	double t1 = 0.0, t2 = 0.0;

	switch (loc1)
	{
	case ENTITYLOC_START:
		t1 = l1->minT();
		break;

	case ENTITYLOC_END:
		t1 = l1->maxT();
		break;

	case ENTITYLOC_MID:
		t1 = (l1->minT() + l1->maxT()) / 2;
		break;

	}

	switch (loc2)
	{
	case ENTITYLOC_START:
		t2 = l2->minT();
		break;

	case ENTITYLOC_END:
		t2 = l2->maxT();
		break;

	case ENTITYLOC_MID:
		t2 = (l2->minT() + l2->maxT()) / 2;
		break;

	}

	return LineEntity2D::join(l1, l2, t1, t2);
}

/**
 *	Factory method that creates a 2D equivalent of the 3D argument.
 */
LineEntity2D_ptr LineEntity2D::convertTo2D(LineEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
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

	xP = x(t);
	yP = y(t);

	return Point::create(xP, yP, zP);
}

/**
 *	Get the Point a given percentage along the entity.
 */
Point_ptr LineEntity2D::posAtDist(double pc)
{
	double t = 0.0;

	t = ((_range[1] + _range[0]) * pc) + _range[0];
	return posAt(t);
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
 *	
 */
LineEntity2D_ptr LineEntity2D::split(double t)
{
	//TODO: implement method
	return 0;
}

/**
 *	
 */
void LineEntity2D::merge(LineEntity2D_ptr &l)
{
	//TODO: implement method
}

/**
 *	Returns a boolean depending on whether an argument entity intersects
 *	this entity.
 */
bool LineEntity2D::intersects(LineEntity2D_ptr &l, bool incRange)
{
	if (getIntersect(l, incRange))
	{
		return true;
	}

	return false;
}

/**
 *	Returns a boolean depending on whether one or more argument entities
 *	intersect this entity.
 */
bool LineEntity2D::intersects(vector<LineEntity2D_ptr> e, bool incRange)
{
	for (unsigned int i = 0; i < e.size(); i++)
	{
		if (intersects(e.at(i), incRange)) return true;
	}

	return false;
}

/**
 *	Returns a boolean depending on whether an argument edge intersects
 *	this entity.
 */
bool LineEntity2D::intersects(Edge_ptr &e, bool incRange)
{
	return intersects(LineEntity2D::create(e), incRange);
}

/**
 *	Returns a boolean depending on whether one or more of the argument
 *	edges intersects this entity.
 */
bool LineEntity2D::intersects(Edges_ptr &e, bool incRange)
{
	for (int i = 0; i < e->size(); i++)
	{
		if (intersects(e->get(i), incRange)) return true;
	}

	return false;
}

bool LineEntity2D::intersects(RadEntity2D_ptr &e, bool incRange)
{
	//TODO: implement method
	return false;
}

bool LineEntity2D::intersects(vector<RadEntity2D_ptr> &es, bool incRange)
{
	for (unsigned int i = 0; i < es.size(); i++)
	{
		if (intersects(es.at(i), incRange)) return true;
	}

	return false;
}

/**
 *	Gets the point where this entity intersects an argument entity.
 */
Point_ptr LineEntity2D::getIntersect(LineEntity2D_ptr &l, bool incRange)
{
	double c[2][2][2];	// coefficients [line][coordinate][coefficient]
	double r[2][2];		// ranges [line][min / max]
	double g[2];		// gradient [line]
	double I[2];		// coordinates of intercept [coordinate]

	// Matrices used to solve simultaneous equations
	double frac = 0.0, tmp = 0.0;
	double A[2][2];
	double X[2];
	double B[2];

	c[0][0][0] = _cfs[0][0];
	c[0][0][1] = _cfs[0][1];
	c[0][1][0] = _cfs[1][0];
	c[0][1][1] = _cfs[1][1];
	c[1][0][0] = l->getXCoefficients()[0];
	c[1][0][1] = l->getXCoefficients()[1];
	c[1][1][0] = l->getYCoefficients()[0];
	c[1][1][1] = l->getYCoefficients()[1];

	if (c[0][0][0] == 0.0 && c[1][0][0] == 0.0)
	{
		// Lines are colinear (vertical)
		return 0;
	}

	if (c[0][1][0] == 0.0 && c[1][1][0] == 0.0)
	{
		// Lines are colinear (horizontal)
		return 0;
	}

	g[0] = c[0][1][0] / c[0][0][0];
	g[1] = c[1][1][0] / c[1][0][0];

	if (g[0] == g[1])
	{
		// Lines are colinear
		return 0;
	}

	if (incRange)
	{
		r[0][0] = _range[0];
		r[0][1] = _range[1];
		r[1][0] = l->getRange()[0];
		r[1][1] = l->getRange()[1];
	}

	A[0][0] = c[0][0][0];
	A[0][1] = c[1][0][0] * -1;
	A[1][0] = c[0][1][0];
	A[1][1] = c[1][1][0] * -1;

	B[0] = c[1][0][1] - c[0][0][1];
	B[1] = c[1][1][1] - c[0][1][1];

	// Invert A
	frac = 1 / ((A[0][0] * A[1][1]) - (A[0][1] * A[1][0]));
	tmp = A[0][0];
	A[0][0] = A[1][1];
	A[1][1] = tmp;
	A[0][1] *= -1;
	A[1][0] *= -1;

	// Calculate X = (A-1)*B
	X[0] = ((A[0][0] * B[0]) + (A[0][1] * B[1])) * frac;
	X[1] = ((A[1][0] * B[0]) + (A[1][1] * B[1])) * frac;

	// Check if is finite - if not, they do not intersect!
	if (!(_finite(X[0]) && _finite(X[1])))
	{
		return 0;
	}

	// Do we want to only check in range for intercept?
	if (incRange)
	{
		// Has to be in range for BOTH lines!
		if (! ((X[0] > r[0][0]) && (X[0] < r[0][1]) &&
			(X[1] > r[1][0]) && (X[1] > r[1][1])))
		{
			return 0;
		}
	}

	I[0] = this->x(X[0]);
	I[1] = this->y(X[0]);

	return Point::create(I[0], I[1], 0.0);
}

/**
 *	Default constructor.
 */
LineEntity2D::LineEntity2D()
{
	_init(Entity2D::FIT2D_BEST);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(vector<Point_ptr> &ps)
{
	_items = ps;
	_init(Entity2D::FIT2D_BEST);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(vector<Point_ptr> &ps, Fit2D f)
{
	_items = ps;
	_init(f);
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
 *	
 */
LineEntity2D::LineEntity2D(Edges_ptr &es)
{
	Edge_ptr e = es->get(0);
	__super::add(e->left());

	for (unsigned int i = 0; i < size(); i++)
	{
		e = es->get(i);
		__super::add(e->right());
	}

	_init(Entity2D::FIT2D_BEST);
}

/**
 *	
 */
LineEntity2D::LineEntity2D(Edges_ptr &es, Entity2D::Fit2D f)
{
	Edge_ptr e = es->get(0);
	__super::add(e->left());

	for (unsigned int i = 0; i < size(); i++)
	{
		e = es->get(i);
		__super::add(e->right());
	}

	_init(f);
}

/**
 *	Initialise the fields.
 */
void LineEntity2D::_init(Entity2D::Fit2D f)
{
	_fit = f;
	_range[0] = 0.0;
	_range[1] = 0.0;
	_ends[0] = Point::create(0.0, 0.0, 0.0);
	_ends[1] = Point::create(0.0, 0.0, 0.0);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_cfs[i][j] = 0.0;
		}
	}

	_avgs[0] = 0.0;
	_avgs[1] = 0.0;
	_ss[0] = 0.0;
	_ss[1] = 0.0;
	_ss[2] = 0.0;

	// Initial calculation
	_calculate();
}

/**
 *	Full recalculate the coefficients of the equation.
 */
void LineEntity2D::_calculate()
{
	if (this->size() == 0) return;

	vector<vector<double>> v;
	double m = 0.0, c = 0.0, tmp = 0.0, of = 0.0;

	// Set up array
	v.resize(this->size());
	for (int i = 0; i < this->size(); i++)
	{
		v[i].resize(12);
	}

	// Populate X and Y
	_avgs[0] = 0.0;
	_avgs[1] = 0.0;

	for (int i = 0; i < this->size(); i++)
	{
		v[i][0] = get(i)->getX();	// X
		v[i][1] = get(i)->getY();	// Y
		v[i][2] = pow(v[i][0], 2);	// X^2
		v[i][3] = pow(v[i][1], 2);	// Y^2

		// Keep running total for means
		_avgs[0] += v[i][0];
		_avgs[1] += v[i][1];
	}

	// Calculate means
	_avgs[0] /= size();
	_avgs[1] /= size();

	// Calculate remaining fields
	_ss[0] = 0.0;
	_ss[1] = 0.0;
	_ss[2] = 0.0;

	for (int i = 0; i < size(); i++)
	{
		v[i].at(4) = v[i][0] - _avgs[0];		// (X - Xb)
		v[i].at(5) = v[i][1] - _avgs[1];		// (Y - Yb)
		v[i].at(6) = pow(v[i][4], 2);			// (X - Xb) ^ 2
		v[i].at(7) = pow(v[i][5], 2);			// (Y - Yb) ^ 2
		v[i].at(8) = v[i][4] * v[i][5];			// (X - Xb) * (Y - Yb)

		_ss[0] += v[i][6];						// SSxx
		_ss[1] += v[i][7];						// SSyy
		_ss[2] += v[i][8];						// SSxy
	}

	// jic by some miracle SSxx = 0
	if (_ss[0] != 0.0)
	{
		// y = mx + c
		m = _ss[2] / _ss[0];
		c = _avgs[1] - (m * _avgs[0]);

		// set x = t
		_cfs[0][0] = 1.0;
		_cfs[0][1] = 0.0;

		_cfs[1][0] = m;
		_cfs[1][1] = c;

		// Find point furthest away from line (use fit)
		// NB. due to coefficients potentially being 0, this differs from below
		if (_fit == FIT2D_BEST) return;
		for (int i = 0; i < size(); i++)
		{
			// Get the equivalent t values
			v[i][9] = (v[i][0] - _cfs[0][1]) / _cfs[0][0];

			// Calculate actual values at equivalent t
			v[i][10] = (v[i][9] * _cfs[1][0]) + _cfs[1][1];

			// Calculate cartesian distances
			v[i][11] = v[i][10] - v[i].at(1);

			// Calculate distance (-ive = left, +ive = right)
			tmp = v[i][11] * cos(atan2(_cfs[1][0],_cfs[0][0]));

			// Find largest on side of interest
			switch (_fit)
			{
			case FIT2D_LEFT:
				if (tmp < of) of = tmp;
				break;

			case FIT2D_RIGHT:
				if (tmp > of) of = tmp;
				break;
			}
		}

	}
	else
	{
		// x = my + c
		m = _ss[2] / _ss[1];
		c = _avgs[0] - (m * _avgs[1]);

		// set y = t;
		_cfs[1][0] = 1.0;
		_cfs[1][1] = 0.0;

		_cfs[0][0] = m;
		_cfs[0][1] = c;

		// Find point furthest away from line (use fit)
		// NB. due to coefficients potentially being 0, this differs from above
		if (_fit == FIT2D_BEST) return;
		for (int i = 0; i < size(); i++)
		{
			// Get the equivalent t values
			v[i][9] = (v[i][1] - _cfs[1][1]) / _cfs[1][0];

			// Calculate actual values at equivalent t
			v[i][10] = (v[i][9] * _cfs[0][0]) + _cfs[0][1];

			// Calculate cartesian distances
			v[i][11] = v[i][10] - v[i][0];

			// Calculate distance (-ive = left, +ive = right - need minus to correct
			// this direction)
			tmp = v[i][11] * sin(atan2(_cfs[1][0],_cfs[0][0])) * -1;

			// Find largest on side of interest
			switch (_fit)
			{
			case FIT2D_LEFT:
				if (tmp < of) of = tmp;
				break;

			case FIT2D_RIGHT:
				if (tmp > of) of = tmp;
				break;
			}
		}
	}

	// Move line
	_cfs[0][1] += of * sin(atan2(_cfs[1][0], _cfs[0][0]));
	_cfs[1][1] -= of * cos(atan2(_cfs[1][0], _cfs[0][0]));

	v.clear();
}

/**
 *	
 */
void LineEntity2D::_calculateOffset()
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
	__super::add(p);
	_incrementCFS(p);
}

/**
 *	Update the coefficients of the equation to include the additional points.
 *
 *	This equation does not recalculate the whole equation, it merely
 *	incorporates the partial contribution of the points.
 */
void LineEntity2D::_increment(Points_ptr &ps)
{
	__super::add(ps);

	for (int i = 0; i < ps->size(); i++)
	{
		_incrementCFS(ps->get(i));
	}
}

/**
 *	(Private) Update the coefficients to include argument point.
 *	
 *	This method DOES NOT add the part to the collection.
 */
void LineEntity2D::_incrementCFS(Point_ptr &p)
{
	//TODO: implement method
	_calculate();
}

/**
 *	Update the coefficients of the equation to exclude the argument point.
 *
 *	This equation does not recalculate the whole equation, it merely
 *	removes the partial contribution of the point.
 */
void LineEntity2D::_decrement(Point_ptr &p)
{
	__super::remove(p);
	_decrementCFS(p);
}

/**
 *	Update the coefficients of the equation to exclude the argument points.
 *
 *	This equation does not recalculate the whole equation, it merely
 *	removes the partial contribution of the point.
 */
void LineEntity2D::_decrement(Points_ptr &ps)
{
	for (int i = 0; i < ps->size(); i++)
	{
		Point_ptr p = ps->get(i);
		__super::remove(p);
		_decrementCFS(p);
	}
}

/**
 *	(Private) Update the coefficients to exclude argument point.
 *	
 *	This method DOES NOT remove the point to the collection.
 */
void LineEntity2D::_decrementCFS(Point_ptr &p)
{
	//TODO: implement method
	_calculate();
}

double LineEntity2D::_findIntersect(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0.0;
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
 *	Get the range of "t" value for the entity.
 */
void LineEntity3D::setRange(double min, double max)
{
	//TODO: implement method
}

/**
 *	Get the minimum "t" value for the entity.
 */
void LineEntity3D::setMinT(double min)
{
	//TODO: implement method
}

/**
 *	Get the maximum "t" value for the entity.
 */
void LineEntity3D::setMaxT(double max)
{
	//TODO: implement method
}

/**
 *
 */
Point_ptr LineEntity3D::posAt(double t)
{
	//TODO: implement method
	return 0;
}

/**
 *
 */
Point_ptr LineEntity3D::posAtDist(double pc)
{
	//TODO: implement method
	return 0;
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