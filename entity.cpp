using namespace std;

#include "entity.h"

/**
 *	Virtual deconstructor, forcing Entity to be polymorphic.
 */
Entity::~Entity()
{
	// do nothing...
}

Points_ptr Entity::getPoints()
{
	return _ps;
}

double* Entity::getRange()
{
	return _range;
}

Entity::Fit Entity::getFit()
{
	return _fit;
}

double Entity::minT()
{
	return _range[0];
}

double Entity::maxT()
{
	return _range[1];
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

Entity::Transformation::Transformation(Fn fn, double p)
{
	_fn = fn;
	_inputs.push_back(p);
}

Entity::Transformation::Transformation(Fn fn, vector<double> p)
{
	_fn = fn;
	_inputs = p;
}

Entity::Transformation_ptr Entity::Transformation::create(Fn fn,
		double p)
{
	return Entity::Transformation_ptr(new Entity::Transformation(
		fn, p));
}

Entity::Transformation_ptr Entity::Transformation::create(Fn fn,
		vector<double> p)
{
	return Entity::Transformation_ptr(new Entity::Transformation(
		fn, p));
}

Entity::Fn Entity::Transformation::getFn()
{
	return _fn;
}

vector<double> Entity::Transformation::getInputs()
{
	return _inputs;
}

Entity::Transformed2D::Transformed2D(LineEntity2D_ptr &eq,
									   Entity::TransformationMatrix_ptr &t)
{
	_line = eq;
	_transform = t;
}

Entity::Transformed2D_ptr Entity::Transformed2D::create(
	LineEntity2D_ptr &eq, Entity::TransformationMatrix_ptr &t)
{
	return Entity::Transformed2D_ptr(new Entity::Transformed2D(eq, t));
}

Entity::Transformed3D::Transformed3D(LineEntity3D_ptr &eq,
									   Entity::TransformationMatrix_ptr &t)
{
	_line = eq;
	_transform = t;
}

Entity::Transformed3D_ptr Entity::Transformed3D::create(
	LineEntity3D_ptr &eq, Entity::TransformationMatrix_ptr &t)
{
	return Entity::Transformed3D_ptr(new Entity::Transformed3D(eq, t));
}

Entity::TransformedArc::TransformedArc(RadEntity2D_ptr &eq,
									   Entity::TransformationMatrix_ptr &t)
{
	_line = eq;
	_transform = t;
}

Entity::TransformedArc_ptr Entity::TransformedArc::create(
	RadEntity2D_ptr &eq, Entity::TransformationMatrix_ptr &t)
{
	return Entity::TransformedArc_ptr(
		new Entity::TransformedArc(eq, t));
}

Entity::TransformedHelix::TransformedHelix(HelixEntity3D_ptr &eq,
									   Entity::TransformationMatrix_ptr &t)
{
	_line = eq;
	_transform = t;
}

Entity::TransformedHelix_ptr Entity::TransformedHelix::create(
	HelixEntity3D_ptr &eq, Entity::TransformationMatrix_ptr &t)
{
	return Entity::TransformedHelix_ptr(
		new Entity::TransformedHelix(eq, t));
}

LineEntity2D::LineEntity2D(Point_ptr &p1, Point_ptr &p2)
{
	Points_ptr p = Points::create();
	p->add(p1);
	p->add(p2);

	_init(p, Entity::FIT_BEST);
}

LineEntity2D::LineEntity2D(Point_ptr &p1, Point_ptr &p2, Entity::Fit f)
{
	Points_ptr p = Points::create();
	p->add(p1);
	p->add(p2);

	_init(p, f);
}

LineEntity2D::LineEntity2D(Points_ptr &p)
{
	_init(p, Entity::FIT_BEST);
}

LineEntity2D::LineEntity2D(Points_ptr &p, Entity::Fit f)
{
	_init(p, f);
}

void LineEntity2D::_init(Points_ptr &p, Entity::Fit f)
{
	
}

LineEntity2D_ptr LineEntity2D::clone(LineEntity2D_ptr &eq)
{
	return LineEntity2D::create(eq->getPoints());
	//TODO: implement method
}

LineEntity2D_ptr LineEntity2D::create(Point_ptr &p1, Point_ptr &p2)
{
	return LineEntity2D_ptr(new LineEntity2D(p1, p2));
}

LineEntity2D_ptr LineEntity2D::create(Points_ptr &p)
{
	return LineEntity2D_ptr(new LineEntity2D(p));
}

double LineEntity2D::x(double t)
{
	//TODO: implement method
	return 0;
}

double LineEntity2D::y(double t)
{
	//TODO: implement method
	return 0;
}

double LineEntity2D::z(double t)
{
	//TODO: implement method
	return 0;
}

void LineEntity2D::transform(double m[4][4])
{
	//TODO: implement method
}

void LineEntity2D::update()
{
	//TODO: implement method
}

void LineEntity2D::updateDeps()
{
	//TODO: implement method
}

void LineEntity2D::add(Point_ptr &p)
{
	//TODO: implement method
}

bool LineEntity2D::intercept(LineEntity2D_ptr &e, Entity::Plane p)
{
	//TODO: implement method
	return false;
}

bool LineEntity2D::intercept(vector<LineEntity2D_ptr> e, Entity::Plane p)
{
	//TODO: implement method
	return false;
}

Point_ptr LineEntity2D::posAt(double pc)
{
	//TODO: implement method
	return Point::create(0.0, 0.0, 0.0);
}

/*
LineEntity2D_ptr LineEntity2D::createParallel(LineEntity2D_ptr &eq,
		double d, bool link)
{
	LineEntity2D_ptr peq = LineEntity2D::clone(eq);
	if (link)
	{
		
	}
}
*/