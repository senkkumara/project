#ifndef FEATURE2D_H
#define FEATURE2D_H

using namespace std;

#include <memory>
#include <vector>
#include "entities.h"
#include "entity.h"
#include "edges.h"
#include "edge.h"
#include "region.h"
#include "utils.h"

class Feature2D;
typedef shared_ptr<Feature2D> Feature2D_ptr;

enum Feature2DType
{
	F2D_LINE,
	F2D_RADIUS
};

class Feature2D
{
protected:
	// Deconstructors
	virtual ~Feature2D();

	// Fields (private)
	Edges_ptr			_boundary;
	LineEntity2D_ptr	_entry;
	LineEntity2D_ptr	_exit;
	Feature2DType		_type;	

	// Methods (private)
	void			_init();
	virtual bool	intercept() = 0;
	virtual bool	intercept(Edge_ptr &e) = 0;

public:
	// Methods (public)
	LineEntity2D_ptr	entry();
	LineEntity2D_ptr	exit();
	Feature2DType		getType();

};

class Feature2DLine;
typedef shared_ptr<Feature2DLine> Feature2DLine_ptr;

class Feature2DLine : public Feature2D
{
private:
	// Constructors
	Feature2DLine(Edge_ptr &e, Edges_ptr &b, Entity::Fit f);

	// Fields (private)
	Entity::Fit			_fit;
	Edges_ptr			_edges;
	LineEntity2D_ptr	_active;
	LineEntity2D_ptr	_passive;

	// Methods (private)
	void _init();
	bool intercept();
	bool intercept(Edge_ptr &e);

public:
	// Factories
	static Feature2DLine_ptr create(Edge_ptr &e, Edges_ptr &b, Entity::Fit f);
	static Feature2DLine_ptr cast(Feature2D_ptr &f);

	// Methods (public)
	bool				append(Edge_ptr &e);
	Entity::Fit			getFit();
	LineEntity2D_ptr	getActive();
	LineEntity2D_ptr	getPassive();
};

class Feature2DRad;
typedef shared_ptr<Feature2DRad> Feature2DRad_ptr;

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
	bool intercept();
	bool intercept(Edges_ptr &e);
	bool intercept(Edge_ptr &e);

public:
	// Factories
	static Feature2DRad_ptr create(Feature2DLine_ptr &f1,
		Feature2DLine_ptr &f2, Edges_ptr &e);

	static Feature2DRad_ptr		cast(Feature2D_ptr &f);

	// Methods (public)
	RadEntity2D_ptr				getActive();
	vector<LineEntity2D_ptr>	getPassive();
	
};

#endif