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

class RadEntity3D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<RadEntity3D> RadEntity3D_ptr;

class SurfaceEntity;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceEntity> SurfaceEntity_ptr;

class VolumeEntity;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<VolumeEntity> VolumeEntity_ptr;

class Entity
{
public:
	// Methods (public)
	virtual double		x(double t) = 0;
	virtual double		y(double t) = 0;
	virtual double		z(double t) = 0;
	double*				getRange();
	double				minT();
	double				maxT();
	Point_ptr*			getEnds();
	Point_ptr			start();
	Point_ptr			end();
	double*				getXCoefficients();
	double*				getYCoefficients();
	double*				getZCoefficients();
	virtual void		setRange(double min, double max) = 0;
	virtual void		setMinT(double min) = 0;
	virtual void		setMaxT(double max) = 0;
	virtual Point_ptr	posAt(double t) = 0;
	virtual Point_ptr	posAtDist(double pc) = 0;

protected:
	// Destructors
	virtual ~Entity();	// Abstract base class

	// Fields (protected)
	double				_cfs[3][2];
	double				_range[2];
	Point_ptr			_ends[2];
};

class Entity2D
{
public:
	// Enumerations (public)
	enum Fit2D
	{
		// Fits relative to someone 'standing' on the start & looking at
		// the end of the entity.
		FIT2D_BEST,		// Do not adjust LOBF
		FIT2D_LEFT,		// Adjust LOBF so is left of all points
		FIT2D_RIGHT		// Adjust LOBF so is right of all points
	};

	// Methods (public)
	Fit2D	getFit();

protected:
	// Destructor
	virtual ~Entity2D();	// Abstract base class

	// Fields (protected)
	Fit2D _fit;
};

class LineEntity2D : public Entity, public Entity2D,
	public Collection<Point_ptr, Points_ptr>
{
public:
	// Factories
	static LineEntity2D_ptr clone(LineEntity2D_ptr &l);
	static LineEntity2D_ptr create(Point_ptr &p1, Point_ptr &p2);
	static LineEntity2D_ptr create(Point_ptr &p1, Point_ptr &p2, Fit2D fit);
	static LineEntity2D_ptr create(Points_ptr &ps);
	static LineEntity2D_ptr create(Points_ptr &ps, Fit2D fit);
	static LineEntity2D_ptr create(Edge_ptr &e);
	static LineEntity2D_ptr create(Edge_ptr &e, Fit2D fit);
	static LineEntity2D_ptr create(Edges_ptr &es);
	static LineEntity2D_ptr create(Edges_ptr &es, Fit2D fit);
	static LineEntity2D_ptr createParallel(LineEntity2D_ptr &l, double d);
	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &l, Point_ptr &p);
	static LineEntity2D_ptr createNormal(LineEntity2D_ptr &l, double t);
	static LineEntity2D_ptr convertTo2D(LineEntity3D_ptr &l);
	static LineEntity2D_ptr split(double t);

	// Methods (public)
	double				x(double t);
	double				y(double t);
	double				z(double t);
	void				setRange(double min, double max);
	void				setMinT(double min);
	void				setMaxT(double max);
	Point_ptr			posAt(double t);
	Point_ptr			posAtDist(double pc);
	void				add(Point_ptr &p);						// Override
	void				add(Points_ptr &p);						// Override
	void				insert(Point_ptr &p, int i);			// Override
	void				remove(Point_ptr &p);					// Override
	void				merge(LineEntity2D_ptr &l);
	LineEntity2D_ptr	cast(Entity2D_ptr &e);
	bool				intersects(LineEntity2D_ptr &e);
	bool				intersects(vector<LineEntity2D_ptr> e);
	bool				intersects(Edge_ptr &e);
	bool				intersects(Edges_ptr &e);
	bool				intersects(RadEntity2D_ptr &e);
	bool				intersects(vector<RadEntity2D_ptr> &es);
	Point_ptr			getIntersect(LineEntity2D_ptr &l);

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

	// Methods (private)
	void	_init(Fit2D fit);
	void	_calculate();
	void	_increment(Point_ptr &p);
	void	_increment(Points_ptr &ps);
	void	_decrement(Point_ptr &p);
	void	_decrement(Points_ptr &ps);
};

class RadEntity2D : public Entity, public Entity2D
{
public:
	// Factories
	static RadEntity2D_ptr clone(RadEntity2D_ptr &l);
	static RadEntity2D_ptr create(LineEntity2D_ptr &l1, LineEntity2D_ptr &l2);
	static RadEntity2D_ptr createRadial(RadEntity2D_ptr &l, double d);
	static vector<LineEntity2D_ptr> createCorner(RadEntity2D_ptr &l, double d);
	static RadEntity2D_ptr convertToArc(HelixEntity3D_ptr &l);
	static RadEntity2D_ptr cast(Entity2D_ptr &e);

	// Methods (public)
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		setRange(double min, double max);
	void		setMinT(double min);
	void		setMaxT(double max);
	Point_ptr	posAt(double t);
	Point_ptr	posAtDist(double pc);
	bool		intersects(LineEntity2D_ptr &e);
	bool		intersects(vector<LineEntity2D_ptr> e);
	bool		intersects(Edge_ptr &e);
	bool		intersects(Edges_ptr &e);
	bool		intersects(RadEntity2D_ptr &e);
	bool		intersects(vector<RadEntity2D_ptr> &es);

private:
	// Constructors
	RadEntity2D(LineEntity2D_ptr &e1, LineEntity2D_ptr &e2);

	// Fields (private)
	LineEntity2D_ptr		_adj[2];

	// Methods (private)
	void _calculate();
};

class Entity3D
{
public:
	// Enumerations (public)
	enum InterceptPlane
	{
		// Used when determining if two entities intersect.
		PLANE_XY,
		PLANE_YZ,
		PLANE_XZ,
		PLANE_OTHER
	};

	enum Fit3D
	{
		// Fits relative to someone 'standing' on the start & looking at
		// the end of the entity.
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
	Fit3D getFit();

protected:
	// Destructor
	virtual ~Entity3D();

	// Fields (protected)
	Fit3D _fit;
};

class LineEntity3D : public Entity, public Entity3D,
	public Collection<Point_ptr, Points_ptr>
{
public:
	// Factories
	static LineEntity3D_ptr clone(LineEntity3D_ptr &e);
	static LineEntity3D_ptr create(LineEntity2D_ptr &e);
	static LineEntity3D_ptr createParallel(LineEntity3D_ptr &e, double d);
	static LineEntity3D_ptr createNormal(LineEntity3D_ptr &e, Point_ptr &p);
	static LineEntity3D_ptr convertTo3D(LineEntity2D_ptr &e);
	static LineEntity3D_ptr cast(Entity3D_ptr &e);

	// Methods (public)
	double				x(double t);
	double				y(double t);
	double				z(double t);
	void				setRange(double min, double max);
	void				setMinT(double min);
	void				setMaxT(double max);
	Point_ptr			posAt(double t);
	Point_ptr			posAtDist(double pc);
	void				add(Point_ptr &p);						// Override
	void				add(Points_ptr &p);						// Override
	void				insert(Point_ptr &p, int i);			// Override
	void				remove(Point_ptr &p);					// Override
	bool				remove(Point_ptr &p, bool dry);
	LineEntity3D_ptr	split(double t);
	void				merge(LineEntity3D_ptr &l);

private:
	// Constructors
	LineEntity3D(Point_ptr &p1, Point_ptr &p2);
	LineEntity3D(Points_ptr &ps);

	// Methods (private)
	void _increment(Point_ptr &p);
	void _increment(Points_ptr &ps);
	void _decrement(Point_ptr &p);
	void _decrement(Points_ptr &ps);
};

class ArcEntity3D : public Entity, public Entity3D,
	public Collection<Point_ptr, Points_ptr>
{
public:
	// Factories
	static ArcEntity3D_ptr create(RadEntity2D_ptr &r, double h);
	static ArcEntity3D_ptr cast(Entity3D_ptr &e);

	// Method (public)
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		setRange(double min, double max);
	void		setMinT(double min);
	void		setMaxT(double max);
	Point_ptr	posAt(double t);
	Point_ptr	posAtDist(double pc);

private:
	// Constructors
	ArcEntity3D(RadEntity2D_ptr &r, double h);
};

class HelixEntity3D : public Entity, public Entity3D,
	public Collection<Point_ptr, Points_ptr>
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
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		setRange(double min, double max);
	void		setMinT(double min);
	void		setMaxT(double max);
	Point_ptr	posAt(double t);
	Point_ptr	posAtDist(double pc);
	void		add(Point_ptr &p);				// Override
	void		add(Points_ptr &p);				// Override
	void		insert(Point_ptr &p, int i);	// Override
	void		remove(Point_ptr &p);			// Override

private:
	// Constructors
	HelixEntity3D(LineEntity3D_ptr &e1, LineEntity3D_ptr &e2);

	// Fields (private)
	RadEntity2D_ptr	_rad;

	// Methods (private)
	void _calculate();
	void _increment(Point_ptr &p);
	void _decrement(Point_ptr &p);
};

class RadEntity3D: public Entity, public Entity3D
{
public:
// Factories
	static RadEntity3D_ptr clone(RadEntity3D_ptr &e);
	static RadEntity3D_ptr create(Entity3D_ptr &e1, Entity3D_ptr &e2);
	static RadEntity2D_ptr cast(Entity3D_ptr &e);

	// Methods (public)
	double		x(double t);
	double		y(double t);
	double		z(double t);
	void		setRange(double min, double max);
	void		setMinT(double min);
	void		setMaxT(double max);
	Point_ptr	posAt(double t);
	Point_ptr	posAtDist(double pc);
	bool		intersects(LineEntity3D_ptr &e, InterceptPlane p);
	bool		intersects(vector<LineEntity3D_ptr> e, InterceptPlane p);
	bool		intersects(Edge_ptr &e, InterceptPlane p);
	bool		intersects(Edges_ptr &e, InterceptPlane p);

private:
	// Constructors
	RadEntity3D(Entity3D_ptr &e1, Entity3D_ptr &e2);

	// Fields (private)
	Entity3D_ptr		_adj[2];

	// Methods (private)
	void _calculate();
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