#ifndef ENTITIES_H
#define ENTITIES_H

/**
 *	entities.h
 *	-----------------------------------------------------------------------
 *	A Entities object is container for one or more Entity objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "collection.h"
#include "entity.h"

class Entities;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Entities> Entities_ptr;

class Entity2Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Entity2Ds> Entity2Ds_ptr;

class LineEntity2Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<LineEntity2Ds> LineEntity2Ds_ptr;

class RadEntity2Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<RadEntity2Ds> RadEntity2Ds_ptr;

class Entity3Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Entity3Ds> Entity3Ds_ptr;

class LineEntity3Ds;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<LineEntity3Ds> LineEntity3Ds_ptr;

class ArcEntity3Ds;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<ArcEntity3Ds> ArcEntity3Ds_ptr;

class HelixEntity3Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<HelixEntity3Ds> HelixEntity3Ds_ptr;

/**
 *	Collection of Entities.
 */
class Entities : public Collection<Entity_ptr, Entities_ptr>
{
private:
	// Constructors
	Entities();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Entities &e);
	friend std::ostream &operator<<(std::ostream &strm,
		const Entities_ptr &e);

public:
	// Factories
	static Entities_ptr create();
};

/**
 *	Collection of Entity2Ds.
 */
class Entity2Ds : public Collection<Entity2D_ptr, Entity2Ds_ptr>
{
private:
	// Constructors
	Entity2Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Entity2Ds &es);
	friend std::ostream &operator<<(std::ostream &strm,
		const Entity2Ds_ptr &es);

public:
	// Factories
	static Entity2Ds_ptr create();
};

/**
 *	Collection of LineEntity2Ds.
 */
class LineEntity2Ds : public Collection<LineEntity2D_ptr, LineEntity2Ds_ptr>
{
private:
	// Constructors
	LineEntity2Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const LineEntity2Ds &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const LineEntity2Ds_ptr &fs);

public:
	// Factories
	static LineEntity2Ds_ptr create();
};

/**
 *	Collection of RadEntity2Ds.
 */
class RadEntity2Ds : public Collection<RadEntity2D_ptr, RadEntity2Ds_ptr>
{
private:
	// Constructors
	RadEntity2Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const RadEntity2Ds &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const RadEntity2Ds_ptr &fs);

public:
	// Factories
	static RadEntity2Ds_ptr create();
};

/**
 *	Collection of Entity3Ds.
 */
class Entity3Ds : public Collection<Entity3D_ptr, Entity3Ds_ptr>
{
private:
	// Constructors
	Entity3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Entity3Ds &es);
	friend std::ostream &operator<<(std::ostream &strm,
		const Entity3Ds_ptr &es);

public:
	// Factories
	static Entity3Ds_ptr create();
};

/**
 *	Collection of LineEntity3Ds.
 */
class LineEntity3Ds : public Collection<LineEntity3D_ptr, LineEntity3Ds_ptr>
{
private:
	// Constructors
	LineEntity3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const LineEntity3Ds &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const LineEntity3Ds_ptr &fs);

public:
	// Factories
	static LineEntity3Ds_ptr create();
};

/**
 *	Collection of ArcEntity3Ds.
 */
class ArcEntity3Ds : public Collection<ArcEntity3D_ptr, ArcEntity3Ds_ptr>
{
private:
	// Constructors
	ArcEntity3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const ArcEntity3Ds &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const ArcEntity3Ds_ptr &fs);

public:
	// Factories
	static ArcEntity3Ds_ptr create();
};

/**
 *	Collection of HelixEntity3Ds.
 */
class HelixEntity3Ds : public Collection<HelixEntity3D_ptr, HelixEntity3Ds_ptr>
{
private:
	// Constructors
	HelixEntity3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const HelixEntity3Ds &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const HelixEntity3Ds_ptr &fs);

public:
	// Factories
	static HelixEntity3Ds_ptr create();
};

#endif