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
#include "enums.h"
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

class SurfaceEntity;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceEntity> SurfaceEntity_ptr;

class VolumeEntity;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<VolumeEntity> VolumeEntity_ptr;

class Entity
{
public:
	// Methods (public)
	double*				getRange();
	double				minT();
	double				maxT();
	Point_ptr*			getEnds();
	Point_ptr			start();
	Point_ptr			end();
	double*				getXCoefficients();
	double*				getYCoefficients();
	double*				getZCoefficients();
	bool				isTransformed();
	void				setRange(double min, double max);
	void				setMinT(double min);
	void				setMaxT(double max);
	virtual Point_ptr	posAt(double t) = 0;

protected:
	// Destructors
	virtual ~Entity();	// Abstract base class

	// Fields (protected)
	double				_cfs[3][2];
	double				_range[2];
	Point_ptr			_ends[2];
};

class Entity2D : public Entity
{
public:
	// Enumerations (public)
	enum Fit2D
	{
		FIT2D_BEST,
		FIT2D_LEFT,
		FIT2D_RIGHT
	};

	// Methods (public)
	Fit2D				getFit();
	virtual double		x(double t) = 0;
	virtual double		y(double t) = 0;
	virtual Point_ptr	posAt(double t) = 0;

protected:
	// Destructor
	virtual ~Entity2D();

	// Fields (protected)
	Fit2D _fit;
};

class LineEntity2D : public Entity2D, Collection<Point_ptr, Points_ptr>
{
public:
	// Factories
	static LineEntity2D_ptr clone(LineEntity2D_ptr &l);
	static LineEntity2D_ptr create(Point_ptr &point, Point_ptr &point2);
	static LineEntity2D_ptr create(Point_ptr &point, Point_ptr &point2, Fit2D fit);
	static LineEntity2D_ptr create(Points_ptr &points);
	static LineEntity2D_ptr create(Points_ptr &points, Fit2D fit);
	static LineEntity2D_ptr create(Edge_ptr &e);
	static LineEntity2D_ptr create(Edge_ptr &e, Fit2D fit);
	static LineEntity2D_ptr create(Edges_ptr &es);
	static LineEntity2D_ptr create(Edges_ptr &es, Fit2D fit);
	static LineEntity2D_ptr createParallel(LineEntity2D_ptr &l,
		double d, bool link);

	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &l,
		Point_ptr &p, bool link);

	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &l,
		double t, bool link);

	static LineEntity2D_ptr convertTo2D(LineEntity3D_ptr &l);
	static LineEntity2D_ptr cast(Entity2D_ptr &e);

	// Methods (public)
	double		x(double t);
	double		y(double t);
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	Point_ptr	posAt(double t);
	bool		intercept(LineEntity2D_ptr &e);
	bool		intercept(vector<LineEntity2D_ptr> e);
	bool		intercept(Edge_ptr &e);
	bool		intercept(Edges_ptr &e);
	bool		intercept(RadEntity2D_ptr &e);
	bool		intercept(vector<RadEntity2D_ptr> &es);
	Point_ptr	getIntersect(LineEntity2D_ptr &l);

private:
	// Constructors
	LineEntity2D(Point_ptr &p1, Point_ptr &p2);
	LineEntity2D(Point_ptr &p1, Point_ptr &p2, Fit2D fit);
	LineEntity2D(Points_ptr &p);
	LineEntity2D(Points_ptr &p, Fit2D fit);
	LineEntity2D(Edge_ptr &e);
	LineEntity2D(Edge_ptr &e, Fit2D fit);
	LineEntity2D(Edges_ptr &es);
	LineEntity2D(Edges_ptr &es, Fit2D fit);

	// Fields (private)
	vector<Entity2D_ptr> _deps;

	// Methods (private)
	void	_init(Points_ptr &p, Fit2D fit);
	void	_calculate();
	bool	_increment(Point_ptr &p);
	bool	_decrement(Point_ptr &p);
};

class RadEntity2D : public Entity2D
{
public:
	// Factories
	static RadEntity2D_ptr clone(RadEntity2D_ptr &l);
	static RadEntity2D_ptr create(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2);
	static RadEntity2D_ptr createRadial(RadEntity2D_ptr &l, double d, bool link);
	static vector<LineEntity2D_ptr> createCorner(RadEntity2D_ptr &l, double d, bool link);
	static RadEntity2D_ptr convertToArc(HelixEntity3D_ptr &l);
	static RadEntity2D_ptr cast(Entity2D_ptr &e);

	// Methods (public)
	vector<Entity2D_ptr> getDeps();
	double		x(double t);
	double		y(double t);
	Point_ptr	posAt(double t);
	bool		intercept(LineEntity2D_ptr &e);
	bool		intercept(vector<LineEntity2D_ptr> e);
	bool		intercept(Edge_ptr &e);
	bool		intercept(Edges_ptr &e);

private:
	// Constructors
	RadEntity2D(LineEntity2D_ptr &e1, LineEntity2D_ptr &e2);

	// Fields (private)
	LineEntity2D_ptr		_adj[2];

	// Methods (private)
	void _calculate();
};

class Entity3D : public Entity
{
public:
	// Enumerations (public)
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

	// Methods (public)
	Fit3D				getFit();
	virtual double		x(double t) = 0;
	virtual double		y(double t) = 0;
	virtual double		z(double t) = 0;
	virtual Point_ptr	posAt(double pc) = 0;

protected:
	// Destructor
	virtual ~Entity3D();

	// Fields (protected)
	Fit3D _fit;
};

class LineEntity3D : public Entity3D, Collection<Point_ptr, Points_ptr>
{
public:
	// Factories
	static LineEntity3D_ptr clone(LineEntity3D_ptr &l);
	static LineEntity3D_ptr createParallel(LineEntity3D_ptr &l, double d, bool link);
	static LineEntity3D_ptr createNormal(LineEntity3D_ptr &l, Point_ptr &p, bool link);
	static LineEntity3D_ptr convertTo3D(LineEntity2D_ptr &l);
	static LineEntity3D_ptr cast(Entity3D_ptr &e);

	// Methods (public)
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	Point_ptr	posAt(double t);

private:
	// Constructors
	LineEntity3D(Point_ptr &p1, Point_ptr &p2);
	LineEntity3D(Points_ptr &ps);
};

class ArcEntity3D : public Entity3D, public RadEntity2D, Collection<Point_ptr, Points_ptr>
{
public:
	// Factories
	static ArcEntity3D_ptr create(RadEntity2D_ptr &r, double h);
	static ArcEntity3D_ptr cast(Entity3D_ptr &e);

private:
	// Constructors
	ArcEntity3D(RadEntity2D_ptr &r, double h);
};

class HelixEntity3D : public Entity3D, public RadEntity2D, Collection<Point_ptr, Points_ptr>
{
public:
	// Factories
	static HelixEntity3D_ptr clone(HelixEntity3D_ptr &l);
	static HelixEntity3D_ptr create(LineEntity3D_ptr &e1, LineEntity3D_ptr &e2);
	static HelixEntity3D_ptr createOffset(HelixEntity3D_ptr &l, double d, bool link);
	static HelixEntity3D_ptr createRadial(HelixEntity3D_ptr &l, double d, bool link);
	static HelixEntity3D_ptr convertToHelix(RadEntity2D_ptr &l);
	static HelixEntity3D_ptr cast(Entity3D_ptr &e);

	// Methods (public)
	vector<Entity3D_ptr> getDeps();
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		add(Point_ptr &p);
	void		add(Points_ptr &p);
	void		insert(Point_ptr &p, int i);
	void		remove(Point_ptr &p);
	Point_ptr	posAt(double t);

private:
	// Constructors
	HelixEntity3D(LineEntity3D_ptr &e1, LineEntity3D_ptr &e2);

	// Fields (private)
	LineEntity3D_ptr		_adj[2];
	vector<Entity3D_ptr>	_deps;
};

/**
 *	A 2D planar surface used for collision detection.
 */
class SurfaceEntity
{
public:
	// Factories
	static SurfaceEntity_ptr create();

	// Methods (public)
	bool intercept(Edge_ptr &e);

private:
	// Constructors
	SurfaceEntity();

	// Fields (private)
	vector<Entity_ptr>	_edges;
};

/**
 *	A 3D volume used for collision detection.
 */
class VolumeEntity
{
public:
	// Factories
	static VolumeEntity_ptr create();

private:
	// Constructors
	VolumeEntity();

	// Fields (private)
	SurfaceEntity_ptr			_base;
	SurfaceEntity_ptr			_ceiling;
	vector<SurfaceEntity_ptr>	_sides;
};

#endif