#ifndef ENTITY_H
#define ENTITY_H

/**
 *	entity.h
 *	---------------------------------------------------------------------------
 *	A Entity object is container for one or more Rail objects.
 */

using namespace std;

#include <memory>
#include "edge.h"
#include "edges.h"
#include "point.h"
#include "points.h"

class Entity;			// Pre-declare class for shared pointer typedef
typedef shared_ptr<Entity> Entity_ptr;

class Entity2D;			// Pre-declare class for shared pointer typedef
typedef shared_ptr<Entity2D> Entity2D_ptr;

class LineEntity2D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<LineEntity2D> LineEntity2D_ptr;

class RadEntity2D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<RadEntity2D> RadEntity2D_ptr;

class Entity3D;			// Pre-declare class for shared pointer typedef
typedef shared_ptr<Entity3D> Entity3D_ptr;

class LineEntity3D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<LineEntity3D> LineEntity3D_ptr;

class ArcEntity3D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<ArcEntity3D> ArcEntity3D_ptr;

class HelixEntity3D;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<HelixEntity3D> HelixEntity3D_ptr;

class Entity
{
public:
	class TransformationFunction;
	typedef shared_ptr<TransformationFunction> TransformationFunction_ptr;

	class TransformationMatrix;
	typedef shared_ptr<TransformationMatrix> TransformationMatrix_ptr;

	class Transformation;
	typedef shared_ptr<Transformation> Transformation_ptr;

protected:
	// Destructors
	virtual ~Entity();	// Abstract base class

	// Fields (protected)
	double				_cfs[3][2];
	double				_range[2];
	Point_ptr			_ends[2];
	Transformation_ptr	_t;

public:
	// Function pointers
	typedef double(*Fn)(Entity_ptr, vector<double>);

	class TransformationFunction
	{
	private:
		// Constructors
		TransformationFunction(Entity_ptr &e,Fn fn, double p);
		TransformationFunction(Entity_ptr &e, Fn fn, vector<double> p);

		// Fields (private)
		Entity_ptr		_entity;
		Fn				_fn;
		vector<double>	_inputs;

	public:
		// Factories
		TransformationFunction_ptr create(Entity_ptr &e, Fn fn, double p);
		TransformationFunction_ptr create(Entity_ptr &e, Fn fn, vector<double> p);

		// Methods (public)
		Fn				getFn();
		vector<double>	getInputs();
		double			calculate();
	};

	class TransformationMatrix
	{
	private:
		// Constructors
		TransformationMatrix();

	public:
		// Factories
		static TransformationMatrix_ptr create();
		static TransformationMatrix_ptr createParallel();
		static TransformationMatrix_ptr createNormal(LineEntity2D_ptr &l, Point_ptr &p);
	};

	class Transformation
	{
	private:
		Point_ptr _origin;
		TransformationMatrix_ptr _t;
		bool _empty;

	public:
		Point_ptr getOrigin();
		TransformationMatrix_ptr getMatrix();
		bool isEmpty();
	};

	// Methods (public)
	double*				getRange();
	double				minT();
	double				maxT();
	Point_ptr*			getEnds();
	Point_ptr			left();
	Point_ptr			right();
	double*				getXCoefficients();
	double*				getYCoefficients();
	double*				getZCoefficients();
	Transformation_ptr	getTransformation();
	bool				isTransformed();
	void				setRange(double min, double max);
	void				setMinT(double min);
	void				setMaxT(double max);
	virtual void		update() = 0;
	virtual void		updateDeps() = 0;
	virtual void		transform(Transformation_ptr &t) = 0;
	virtual Point_ptr	posAt(double pc) = 0;

private:
	virtual void		_applyTransform() = 0;
};

class Entity2D : public Entity
{
protected:
	// Destructor
	virtual ~Entity2D();

	// Fields (protected)
	Side _side;

public:
	// Methods (public)
	Side				getSide();
	virtual double		x(double t) = 0;
	virtual double		y(double t) = 0;
	Point_ptr			posAt(double pc);
};

class LineEntity2D : public Entity2D, Collection<Point_ptr, Points_ptr>
{
private:
	// Constructors
	LineEntity2D(Point_ptr &p1, Point_ptr &p2);
	LineEntity2D(Point_ptr &p1, Point_ptr &p2, Side s);
	LineEntity2D(Points_ptr &p);
	LineEntity2D(Points_ptr &p, Side s);
	LineEntity2D(Edge_ptr &e);
	LineEntity2D(Edge_ptr &e, Side s);
	LineEntity2D(LineEntity2D_ptr &l, Transformation_ptr &t);

	// Fields (private)
	vector<Entity2D_ptr> _deps;

	// Methods (private)
	void	_init(Points_ptr &p, Side s);
	void	_calculate();
	bool	_increment(Point_ptr &p);
	void	_applyTransform();

public:
	// Factories
	static LineEntity2D_ptr clone(LineEntity2D_ptr &l);
	static LineEntity2D_ptr create(Point_ptr &point, Point_ptr &point2);
	static LineEntity2D_ptr create(Point_ptr &point, Point_ptr &point2, Side f);
	static LineEntity2D_ptr create(Points_ptr &points);
	static LineEntity2D_ptr create(Points_ptr &points, Side s);
	static LineEntity2D_ptr create(Edge_ptr &e);
	static LineEntity2D_ptr create(Edge_ptr &e, Side s);
	static LineEntity2D_ptr create(LineEntity2D_ptr &l, Transformation_ptr &t);
	static LineEntity2D_ptr createParallel(LineEntity2D_ptr &l,
		double d, bool link);

	static LineEntity2D_ptr createParallel(LineEntity2D_ptr &l,
		double d, Fn t, bool link);

	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &l,
		Point_ptr &p, bool link);

	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &l,
		double f, bool link);

	static LineEntity2D_ptr convertTo2D(LineEntity3D_ptr &l);

	// Methods (public)
	vector<Entity2D_ptr> getDeps();
	double		x(double t);
	double		y(double t);
	void		update();
	void		updateDeps();
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	bool		intercept(LineEntity2D_ptr &e);
	bool		intercept(vector<LineEntity2D_ptr> e);
	bool		intercept(Edge_ptr &e);
	bool		intercept(Edges_ptr &e);
	Point_ptr	getIntersect(LineEntity2D_ptr &l);
	void		transform(Transformation_ptr &t);
};

class RadEntity2D : public Entity2D
{
private:
	// Constructors
	RadEntity2D(LineEntity2D_ptr &e1, LineEntity2D_ptr &e2);

	// Fields (private)
	LineEntity2D_ptr		_adj[2];
	vector<Entity2D_ptr>	_deps;

	// Methods (private)
	void _calculate();
	void _applyTransform();

public:
	// Factories
	static RadEntity2D_ptr clone(RadEntity2D_ptr &l);
	static RadEntity2D_ptr create(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2);
	static RadEntity2D_ptr createRadial(RadEntity2D_ptr &l, double d, bool link);
	static RadEntity2D_ptr createRadial(RadEntity2D_ptr &l, Fn t, bool link);
	static vector<LineEntity2D_ptr> createCorner(RadEntity2D_ptr &l, double d, bool link);
	static RadEntity2D_ptr convertToArc(HelixEntity3D_ptr &l);

	// Methods (public)
	vector<Entity2D_ptr> getDeps();
	double		x(double t);
	double		y(double t);
	void		update();
	void		updateDeps();
	bool		intercept(LineEntity2D_ptr &e);
	bool		intercept(vector<LineEntity2D_ptr> e);
	bool		intercept(Edge_ptr &e);
	bool		intercept(Edges_ptr &e);
	void		transform(Transformation_ptr &t);
};

class Entity3D : public Entity
{
public:
	/**
	 *	The plane enumeration is used in conjunction with the "intercept"
	 *	methods to determine on which plane an interception is being
	 *	checked for.
	 */
	enum InterceptPlane
	{
		PLANE_XY,
		PLANE_YZ,
		PLANE_XZ,
		PLANE_OTHER
	};

	enum Fit3D
	{
		FIT3D_BEST,
		FIT3D_LEFT,
		FIT3D_LEFT_ABOVE,
		FIT3D_LEFT_BELOW,
		FIT3D_RIGHT,
		FIT3D_RIGHT_ABOVE,
		FIT3D_RIGHT_BELOW,
		FIT3D_ABOVE,
		FIT3D_BELOW
	};

protected:
	// Destructor
	virtual ~Entity3D();

	// Fields (protected)
	Fit3D _fit;

public:
	// Methods (public)
	Fit3D			getFit();
	virtual double	x(double t) = 0;
	virtual double	y(double t) = 0;
	virtual double	z(double t) = 0;
	Point_ptr		posAt(double pc);
};

class LineEntity3D : public Entity3D, Collection<Point_ptr, Points_ptr>
{
private:
	// Constructors
	LineEntity3D(Point_ptr &point1, Point_ptr &point2);
	LineEntity3D(Points_ptr &points);

	// Fields (private)
	vector<Entity3D_ptr> _deps;

	// Methods (private)
	void _applyTransform();

public:
	// Factories
	static LineEntity3D_ptr clone(LineEntity3D_ptr &l);
	static LineEntity3D_ptr createParallel(LineEntity3D_ptr &l, double d, bool link);
	static LineEntity3D_ptr createNormal(LineEntity3D_ptr &l, Point_ptr &p, bool link);
	static LineEntity3D_ptr convertTo3D(LineEntity2D_ptr &l);

	// Methods (public)
	vector<Entity3D_ptr> getDeps();
	void		transform(double m[4][4]);
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		update();
	void		updateDeps();
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	void		transform(Transformation_ptr &t);
};

class ArcEntity3D : public Entity3D, public RadEntity2D, Collection<Point_ptr, Points_ptr>
{
private:
	// Methods (private)
	void _applyTransform();

public:
	// Methods (public)
	void transform(Transformation_ptr &t);
};

class HelixEntity3D : public Entity3D, public RadEntity2D, Collection<Point_ptr, Points_ptr>
{
private:
	// Constructors
	HelixEntity3D(LineEntity3D_ptr &e1, LineEntity3D_ptr &e2);

	// Fields (private)
	LineEntity3D_ptr		_adj[2];
	vector<Entity3D_ptr>	_deps;

	// Methods (private)
	void _applyTransform();

public:
	// Factories
	static HelixEntity3D_ptr clone(HelixEntity3D_ptr &l);
	static HelixEntity3D_ptr create(LineEntity3D_ptr &e1, LineEntity3D_ptr &e2);
	static HelixEntity3D_ptr createOffset(HelixEntity3D_ptr &l, double d, bool link);
	static HelixEntity3D_ptr createOffset(HelixEntity3D_ptr &l, Fn, bool link);
	static HelixEntity3D_ptr createRadial(HelixEntity3D_ptr &l, double d, bool link);
	static HelixEntity3D_ptr createRadial(HelixEntity3D_ptr &l, Fn, bool link);
	static HelixEntity3D_ptr convertToHelix(RadEntity2D_ptr &l);

	// Methods (public)
	vector<Entity3D_ptr> getDeps();
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		update();
	void		updateDeps();
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	void		transform(Transformation_ptr &t);
};

namespace Transformations
{
	double constant(vector<double> p);
};

#endif