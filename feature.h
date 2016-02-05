#ifndef FEATURE_H
#define FEATURE_H

using namespace std;

#include <memory>
#include <vector>
#include "entities.h"
#include "entity.h"
#include "edges.h"
#include "edge.h"
#include "region.h"
#include "utils.h"

class Feature;
typedef shared_ptr<Feature> Feature_ptr;

class Feature2D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature2D> Feature2D_ptr;

class Feature2DLine;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature2DLine> Feature2DLine_ptr;

class Feature2DRad;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature2DRad> Feature2DRad_ptr;

class Feature
{

};

/**
 *	Generic 2D feature.
 */
class Feature2D
{
public:
	// Enumerations
	typedef enum Type
	{
		FEATURE2D_TYPE_LINE,
		FEATURE2D_TYPE_RADIUS
	};

protected:
	// Deconstructor
	virtual ~Feature2D();

	// Fields (private)
	Edges_ptr			_boundary;
	LineEntity2D_ptr	_entry;
	LineEntity2D_ptr	_exit;
	Type				_type;	

	// Methods (private)
	void			_init();
	virtual bool	_intercept() = 0;
	virtual bool	_intercept(Edge_ptr &e) = 0;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature2D &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature2D_ptr &f);

public:
	// Methods (public)
	LineEntity2D_ptr	entry();
	LineEntity2D_ptr	exit();
	Type				getType();

};

/**
 *	A 2D straight line.
 */
class Feature2DLine : public Feature2D
{
private:
	// Constructors
	Feature2DLine(Edge_ptr &e, Edges_ptr &b, Entity2D::Fit2D f);

	// Fields (private)
	Entity2D::Fit2D		_fit;
	Edges_ptr			_edges;
	LineEntity2D_ptr	_active;
	LineEntity2D_ptr	_passive;

	// Methods (private)
	void _init();
	bool _intercept();
	bool _intercept(Edge_ptr &e);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature2DLine &f);

	friend std::ostream &operator<<(std::ostream &strm,
		const Feature2DLine_ptr &f);

public:
	// Factories
	static Feature2DLine_ptr create(Edge_ptr &e, Edges_ptr &b, Entity2D::Fit2D f);
	static Feature2DLine_ptr cast(Feature2D_ptr &f);

	// Methods (public)
	bool				append(Edge_ptr &e);
	Entity2D::Fit2D		getFit();
	LineEntity2D_ptr	getActive();
	LineEntity2D_ptr	getPassive();
};

/**
 *	A 2D radius feature - a fillet between two straight lines.
 */
class Feature2DRad : public Feature2D
{
private:
	// Constructors
	Feature2DRad(Feature2DLine_ptr &f1, Feature2DLine_ptr &f2,
		Edges_ptr &b);

	// Fields (private)
	RadEntity2D_ptr				_active;
	vector<LineEntity2D_ptr>	_passive;

	// Methods (private)
	void _init();
	bool _intercept();
	bool _intercept(Edges_ptr &e);
	bool _intercept(Edge_ptr &e);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature2DRad &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature2DRad_ptr &f);

public:
	// Factories
	static Feature2DRad_ptr create(Feature2DLine_ptr &f1,
		Feature2DLine_ptr &f2, Edges_ptr &e);

	static Feature2DRad_ptr		cast(Feature2D_ptr &f);

	// Methods (public)
	RadEntity2D_ptr				getActive();
	vector<LineEntity2D_ptr>	getPassive();
	
};

/**
 *	Generic 3D feature
 */
class Feature3D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature3D> Feature3D_ptr;

class Feature3D
{
public:
	// Enumerations
	typedef enum Feature3DType
	{
		FEATURE3D_TYPE_STRAIGHT,
		FEATURE3D_TYPE_CORNER,
		FEATURE3D_TYPE_HELIX,
		FEATURE3D_TYPE_SPLIT,
		FEATURE3D_TYPE_SPECIAL,
		FEATURE3D_TYPE_TRANSITION
	};

protected:
	// Deconstructors
	virtual ~Feature3D();

	// Methods (private)
	void _init();

public:
	
};

/**
 *	A 3D straight line.
 */
class Feature3DStraight;
typedef shared_ptr<Feature3DStraight> Feature3DStraight_ptr;

class Feature3DStraight : public Feature3D
{

};

/**
 *	A flat bend - 2D dimensional turn with a z-direction offset.
 */
class Feature3DCorner;
typedef shared_ptr<Feature3DCorner> Feature3DCorner_ptr;

class Feature3DCorner
{

};

/**
 *	A corner with a height increase - includes the minimum required
 *	straight sections before and after.
 */
class Feature3DHelix;
typedef shared_ptr<Feature3DHelix> Feature3DHelix_ptr;

class Feature3DHelix
{

};

/**
 *	A vertically oriented radius feature - a fillet between two straight lines.
 */
class Feature3DTrans;
typedef shared_ptr<Feature3DTrans> Feature3DTrans_ptr;

class Feature3DTrans
{

};

#endif