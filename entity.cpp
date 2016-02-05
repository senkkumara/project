using namespace std;

#include "entity.h"

/**
 *	Virtual deconstructor, forcing Entity to be polymorphic.
 */
Entity::~Entity()
{
	// do nothing...
}

double* Entity::getRange()
{
	return _range;
}

double Entity::minT()
{
	return _range[0];
}

double Entity::maxT()
{
	return _range[1];
}

Point_ptr* Entity::getEnds()
{
	return _ends;
}

Point_ptr Entity::left()
{
	return _ends[0];
}

Point_ptr Entity::right()
{
	return _ends[1];
}

double*	Entity::getXCoefficients()
{
	return _cfs[0];
}

double* Entity::getYCoefficients()
{
	return _cfs[1];
}

double* Entity::getZCoefficients()
{
	return _cfs[2];
}

Entity::Transformation_ptr Entity::getTransformation()
{
	return _t;
}

bool Entity::isTransformed()
{
	return _t->isEmpty();
}

void Entity::setRange(double min, double max)
{
	setMinT(min);
	setMaxT(max);
}

void Entity::setMinT(double min)
{
	_range[0] = min;
}

void Entity::setMaxT(double max)
{
	_range[1] = max;
}

Entity::TransformationFunction::TransformationFunction(Entity_ptr &e, Fn fn, double p)
{
	_entity = e;
	_fn = fn;
	_inputs.push_back(p);
}

Entity::TransformationFunction::TransformationFunction(Entity_ptr &e, Fn fn, vector<double> p)
{
	_entity = e;
	_fn = fn;
	_inputs = p;
}

Entity::TransformationFunction_ptr Entity::TransformationFunction::create(Entity_ptr &e, Fn fn,
		double p)
{
	return Entity::TransformationFunction_ptr(new Entity::TransformationFunction(
		e, fn, p));
}

Entity::TransformationFunction_ptr Entity::TransformationFunction::create(Entity_ptr &e, Fn fn,
		vector<double> p)
{
	return Entity::TransformationFunction_ptr(new Entity::TransformationFunction(
		e, fn, p));
}

Entity::Fn Entity::TransformationFunction::getFn()
{
	return _fn;
}

vector<double> Entity::TransformationFunction::getInputs()
{
	return _inputs;
}

double Entity::TransformationFunction::calculate()
{
	return _fn(_entity, _inputs);
}

Point_ptr Entity::Transformation::getOrigin()
{
	return _origin;
}

Entity::TransformationMatrix_ptr Entity::Transformation::getMatrix()
{
	return _t;
}

bool Entity::Transformation::isEmpty()
{
	return _empty;
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

LineEntity2D::LineEntity2D(LineEntity2D_ptr &l, Transformation_ptr &t)
{
	//TODO: implement method
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

void LineEntity2D::_applyTransform()
{
	//TODO: implement method
}

LineEntity2D_ptr LineEntity2D::clone(LineEntity2D_ptr &l)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::create(Point_ptr &p1, Point_ptr &p2)
{
	return LineEntity2D_ptr(new LineEntity2D(p1, p2));
}

LineEntity2D_ptr LineEntity2D::create(Point_ptr &p1, Point_ptr &p2,
									  Entity2D::Fit2D f)
{
	return LineEntity2D_ptr(new LineEntity2D(p1, p2, f));
}

LineEntity2D_ptr LineEntity2D::create(Points_ptr &p)
{
	return LineEntity2D_ptr(new LineEntity2D(p));
}

LineEntity2D_ptr LineEntity2D::create(Points_ptr &p, Entity2D::Fit2D f)
{
	return LineEntity2D_ptr(new LineEntity2D(p, f));
}

LineEntity2D_ptr LineEntity2D::create(Edge_ptr &e)
{
	return LineEntity2D_ptr(new LineEntity2D(e));
}

LineEntity2D_ptr LineEntity2D::create(Edge_ptr &e, Entity2D::Fit2D f)
{
	return LineEntity2D_ptr(new LineEntity2D(e, f));
}

LineEntity2D_ptr LineEntity2D::create(LineEntity2D_ptr &l,
									  Entity::Transformation_ptr &t)
{
	return LineEntity2D_ptr(new LineEntity2D(l, t));
}

LineEntity2D_ptr LineEntity2D::createParallel(LineEntity2D_ptr &l, double d, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::createParallel(LineEntity2D_ptr &l, double d, Entity::Fn f, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l, Point_ptr &p, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::createNormal(LineEntity2D_ptr &l, double f, bool link)
{
	//TODO: implement method
	return 0;
}

LineEntity2D_ptr LineEntity2D::convertTo2D(LineEntity3D_ptr &l)
{
	//TODO: implement method
	return 0;
}

vector<Entity2D_ptr> LineEntity2D::getDeps()
{
	return _deps;
}

double LineEntity2D::x(double t)
{
	return (_cfs[0][0]*t + _cfs[0][1]);
}

double LineEntity2D::y(double t)
{
	return (_cfs[1][0]*t + _cfs[1][1]);
}

void LineEntity2D::update()
{
	//TODO: implement method
}

void LineEntity2D::updateDeps()
{
	for (unsigned int i = 0; i < _deps.size(); i++)
	{
		_deps.at(i)->update();
	}
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

void LineEntity2D::transform(Transformation_ptr &t)
{
	//TODO: implement method
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

void RadEntity2D::_applyTransform()
{
	//TODO: implement method
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

RadEntity2D_ptr RadEntity2D::createRadial(RadEntity2D_ptr &l, Fn t, bool link)
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

vector<Entity2D_ptr> RadEntity2D::getDeps()
{
	return _deps;
}

double RadEntity2D::x(double t)
{
	return (_range[0] * cos(t)) + _range[1];
}

double RadEntity2D::y(double t)
{
	return (_range[0] * sin(t)) + _range[1];
}

void RadEntity2D::update()
{
	//TODO: implement method
}

void RadEntity2D:: updateDeps()
{
	for (unsigned int i = 0; i < _deps.size(); i++)
	{
		_deps.at(i)->update();
	}
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

void RadEntity2D::transform(Transformation_ptr &t)
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
	return nullptr;
}

LineEntity3D::LineEntity3D(Point_ptr &point1, Point_ptr &point2)
{
	//TODO: implement method
}

LineEntity3D::LineEntity3D(Points_ptr &points)
{
	//TODO: implement method
}

void LineEntity3D::_applyTransform()
{
	//TODO: implement method
}

LineEntity3D_ptr LineEntity3D::clone(LineEntity3D_ptr &l)
{
	//TODO: implement method
}

LineEntity3D_ptr LineEntity3D::createParallel(LineEntity3D_ptr &l, double d, bool link)
{
	//TODO: implement method
}

LineEntity3D_ptr LineEntity3D::createNormal(LineEntity3D_ptr &l, Point_ptr &p, bool link)
{
	//TODO: implement method
}

LineEntity3D_ptr LineEntity3D::convertTo3D(LineEntity2D_ptr &l)
{
	//TODO: implement method
}