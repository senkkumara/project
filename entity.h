#ifndef ENTITY_H
#define ENTITY_H

using namespace std;

#include <memory>
#include <map>
#include "edge.h"
#include "edges.h"
#include "point.h"
#include "points.h"

class Entity;
typedef shared_ptr<Entity> Entity_ptr;

class Entity2D;
typedef shared_ptr<Entity2D> Entity2D_ptr;

class Entity3D;
typedef shared_ptr<Entity3D> Entity3D_ptr;

class LineEntity2D;
typedef shared_ptr<LineEntity2D> LineEntity2D_ptr;

class RadEntity2D;
typedef shared_ptr<RadEntity2D> RadEntity2D_ptr;

class LineEntity3D;
typedef shared_ptr<LineEntity3D> LineEntity3D_ptr;

class ArcEntity3D;
typedef shared_ptr<ArcEntity3D> ArcEntity3D_ptr;

class HelixEntity3D;
typedef shared_ptr<HelixEntity3D> HelixEntity3D_ptr;

class Entity
{
public:
	/**
	 *	The plane enumeration is used in conjunction with the "intercept"
	 *	methods to determine on which plane an interception is being
	 *	checked for.
	 */
	enum Plane
	{
		PLANE_XY,
		PLANE_YZ,
		PLANE_XZ
	};

	enum Fit
	{
		FIT_BEST,
		FIT_LEFT,
		FIT_LEFT_ABOVE,
		FIT_LEFT_BELOW,
		FIT_RIGHT,
		FIT_RIGHT_ABOVE,
		FIT_RIGHT_BELOW,
		FIT_ABOVE,
		FIT_BELOW
	};

protected:
	// Destructors
	virtual ~Entity();	// Abstract base class

	// Fields (protected)
	Points_ptr	_ps;
	Point_ptr	_ends[2];
	double		_cfs[3][2];
	double		_range[2];
	Fit			_fit;

public:
	// Sub-classes
	/**
	 *	Transformations contain the transformation function that
	 *	was used to create transformation matrix and the inputs
	 *	to it.
	 *
	 *	A transformation can be stored with the resultant line
	 *	to track dependencies.
	 */
	class Transformation;
	typedef shared_ptr<Transformation> Transformation_ptr;
	typedef vector<Transformation_ptr> TransformationMatrixRow;
	typedef shared_ptr<TransformationMatrixRow> TransformationMatrixRow_ptr;
	typedef vector<TransformationMatrixRow_ptr> TransformationMatrix;
	typedef shared_ptr<TransformationMatrix> TransformationMatrix_ptr;

	// Methods (public)
	Points_ptr			getPoints();
	Point_ptr			left();
	Point_ptr			right();
	double*				getRange();
	Fit					getFit();
	double				minT();
	double				maxT();
	void				setRange(double min, double max);
	void				setMinT(double min);
	void				setMaxT(double max);
	virtual double		x(double t) = 0;
	virtual double		y(double t) = 0;
	virtual double		z(double t) = 0;
	virtual void		transform(double m[4][4]) = 0;
	virtual void		update() = 0;
	virtual void		updateDeps() = 0;
	virtual void		add(Point_ptr &p) = 0;
	virtual bool		intercept(LineEntity2D_ptr &e, Entity::Plane p) = 0;
	virtual bool		intercept(vector<LineEntity2D_ptr> e, Entity::Plane p) = 0;
	virtual bool		incercept(Edge_ptr &e, Entity::Plane p) = 0;
	virtual bool		intercept(Edges_ptr &e, Entity::Plane p) = 0;
	virtual Point_ptr	posAt(double pc) = 0;

	// Function pointers
	typedef void(*Fn)(TransformationMatrix_ptr &m,
		Entity_ptr eq, vector<double>);

	class Transformation
	{
	private:
		Transformation(Fn fn, double p);
		Transformation(Fn fn, vector<double> p);

		Fn				_fn;
		vector<double>	_inputs;

	public:
		Transformation_ptr create(Fn fn, double p);
		Transformation_ptr create(Fn fn, vector<double> p);

		Fn				getFn();
		vector<double>	getInputs();
	};

	/**
	 *	Transformed Lines (of which there are four varieties) contain a
	 *	line and a 4x4 matrix of transformations that was used to create it.
	 *
	 *	This is used to track dependencies between lines.
	 */
	template<typename L>
	class TransformedLine
	{
	protected:
		L							_line;
		TransformationMatrix_ptr	_transform;
	};

	class Transformed2D;
	typedef shared_ptr<Transformed2D> Transformed2D_ptr;

	class Transformed2D : TransformedLine<LineEntity2D_ptr>
	{
	private:
		Transformed2D(LineEntity2D_ptr &eq,
			TransformationMatrix_ptr &t);
	public:
		Transformed2D_ptr create(LineEntity2D_ptr &eq,
			TransformationMatrix_ptr &t);
	};

	class Transformed3D;
	typedef shared_ptr<Transformed3D> Transformed3D_ptr;

	class Transformed3D : TransformedLine<LineEntity3D_ptr>
	{
	private:
		Transformed3D(LineEntity3D_ptr &eq,
			TransformationMatrix_ptr &t);
	public:
		Transformed3D_ptr create(LineEntity3D_ptr &eq,
			TransformationMatrix_ptr &t);
	};

	class TransformedArc;
	typedef shared_ptr<TransformedArc> TransformedArc_ptr;

	class TransformedArc : TransformedLine<RadEntity2D_ptr>
	{
	private:
		TransformedArc(RadEntity2D_ptr &eq,
			TransformationMatrix_ptr &t);
	public:
		TransformedArc_ptr create(RadEntity2D_ptr &eq,
			TransformationMatrix_ptr &t);
	};

	class TransformedHelix;
	typedef shared_ptr<TransformedHelix> TransformedHelix_ptr;

	class TransformedHelix : TransformedLine<HelixEntity3D_ptr>
	{
	private:
		TransformedHelix(HelixEntity3D_ptr &eq,
			TransformationMatrix_ptr &t);
	public:
		TransformedHelix_ptr create(HelixEntity3D_ptr &eq,
			TransformationMatrix_ptr &t);
	};
};

class Entity2D : public Entity
{

};

class LineEntity2D : public Entity2D, Collection<Point_ptr, LineEntity2D_ptr>
{
private:
	// Constructors
	LineEntity2D(Point_ptr &p1, Point_ptr &p2);
	LineEntity2D(Point_ptr &p1, Point_ptr &p2, Entity::Fit f);
	LineEntity2D(Points_ptr &p);
	LineEntity2D(Points_ptr &p, Entity::Fit f);
	LineEntity2D(Edge_ptr &e);

	// Fields (private)
	vector<Transformed2D_ptr> _deps;

	// Methods (private)
	void	_init(Points_ptr &p, Entity::Fit f);

public:
	// Factories
	static LineEntity2D_ptr clone(LineEntity2D_ptr &eq);
	static LineEntity2D_ptr create(Point_ptr &point, Point_ptr &point2);
	static LineEntity2D_ptr create(Point_ptr &point, Point_ptr &point2, Entity::Fit f);
	static LineEntity2D_ptr create(Points_ptr &points);
	static LineEntity2D_ptr create(Points_ptr &points, Entity::Fit f);
	static LineEntity2D_ptr create(Edge_ptr &e);
	static LineEntity2D_ptr createParallel(LineEntity2D_ptr &eq,
		double d, bool link);

	static LineEntity2D_ptr createParallel(LineEntity2D_ptr &eq,
		double d, Fn t, bool link);

	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &eq,
		Point_ptr &p, bool link);

	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &eq,
		double f, bool link);

	static LineEntity2D_ptr convertTo2D(LineEntity3D_ptr &eq);

	// Methods (public)
	vector<Transformed2D_ptr> getDeps();
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		transform(double m[4][4]);
	void		translate(double x, double y);
	void		rotate(double th);
	void		update();
	void		updateDeps();
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	bool		intercept(LineEntity2D_ptr &e, Entity::Plane p);
	bool		intercept(vector<LineEntity2D_ptr> e, Entity::Plane p);
	bool		incercept(Edge_ptr &e, Entity::Plane p);
	 bool		intercept(Edges_ptr &e, Entity::Plane p);
	Point_ptr	posAt(double pc);
};



class RadEntity2D : public Entity2D, Collection<Point_ptr, RadEntity2D_ptr>
{
private:
	// Constructors
	RadEntity2D(LineEntity2D_ptr &e1, LineEntity2D_ptr &e2);

	// Fields (private)
	LineEntity2D_ptr			_adj[2];
	vector<TransformedArc_ptr>	_deps;

public:
	// Factories
	static RadEntity2D_ptr clone(RadEntity2D_ptr &l);
	static RadEntity2D_ptr create(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2);
	static RadEntity2D_ptr createRadial(RadEntity2D_ptr &l, double d, bool link);
	static RadEntity2D_ptr createRadial(RadEntity2D_ptr &l, Fn t, bool link);
	static vector<LineEntity2D_ptr> createCorner(RadEntity2D_ptr &l, double d, bool link);
	static RadEntity2D_ptr convertToArc(HelixEntity3D_ptr &l);

	// Methods (public)
	vector<RadEntity2D_ptr> getDeps();
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		transform(double m[4][4]);
	void		translate(double d);
	void		dilate(double d);
	void		update();
	void		updateDeps();
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	bool		intercept(LineEntity2D_ptr &e, Entity::Plane p);
	bool		intercept(vector<LineEntity2D_ptr> e, Entity::Plane p);
	Point_ptr	posAt(double pc);
};

class Entity3D : public Entity
{

};

class LineEntity3D : public Entity3D, public LineEntity2D, Collection<Point_ptr, LineEntity3D_ptr>
{
private:
	// Constructors
	LineEntity3D(Point_ptr &point1, Point_ptr &point2);
	LineEntity3D(Points_ptr &points);

	// Fields (private)
	vector<Transformed3D_ptr> _deps;

public:
	// Factories
	static LineEntity3D_ptr clone(LineEntity3D_ptr &eq);
	static LineEntity3D_ptr createParallel(LineEntity3D_ptr &eq, double d, bool link);
	static LineEntity3D_ptr createNormal(LineEntity3D_ptr &eq, Point_ptr &p, bool link);
	static LineEntity3D_ptr convertTo3D(LineEntity2D_ptr &eq);

	// Methods (public)
	map<LineEntity3D_ptr, Transformation> getDeps();
	void		transform(double m[4][4]);
	void		update();
	void		updateDeps();
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	Point_ptr	posAt(double pc);
};

class ArcEntity3D : public Entity3D, public RadEntity2D, Collection<Point_ptr, ArcEntity3D_ptr>
{

};

class HelixEntity3D : public Entity3D, public RadEntity2D, Collection<Point_ptr, HelixEntity3D_ptr>
{
private:
	// Constructors
	HelixEntity3D(LineEntity3D_ptr &e1, LineEntity3D_ptr &e2);

	// Fields (private)
	LineEntity3D_ptr				_adj[2];
	vector<TransformedHelix_ptr>	_deps;

public:
	// Factories
	static HelixEntity3D_ptr clone(HelixEntity3D_ptr &eq);
	static HelixEntity3D_ptr create(LineEntity3D_ptr &e1, LineEntity3D_ptr &e2);
	static HelixEntity3D_ptr createOffset(HelixEntity3D_ptr &eq, double d, bool link);
	static HelixEntity3D_ptr createOffset(HelixEntity3D_ptr &eq, Fn, bool link);
	static HelixEntity3D_ptr createRadial(HelixEntity3D_ptr &eq, double d, bool link);
	static HelixEntity3D_ptr createRadial(HelixEntity3D_ptr &eq, Fn, bool link);
	static HelixEntity3D_ptr convertToHelix(RadEntity2D_ptr &eq);

	// Methods (public)
	vector<HelixEntity3D_ptr> getDeps();
	void		offset(double d);
	void		dilate(double d);
	void		update();
	void		updateDeps();
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	Point_ptr	posAt(double pc);
};

namespace Transformations
{
	void constant(Entity::TransformationMatrix_ptr &m, Entity_ptr &eq, vector<double> p);
	void cosine(Entity::TransformationMatrix_ptr &m, Entity_ptr &eq, vector<double> p);
	void sine(Entity::TransformationMatrix_ptr &m, Entity_ptr &eq, vector<double> p);
	void invert(Entity::TransformationMatrix_ptr &m, Entity_ptr &eq, vector<double> p);
};

#endif