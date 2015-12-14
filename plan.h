#ifndef PLAN_H
#define PLAN_H

/**
 *	plan.h
 *	---------------------------------------------------------------------------
 *	A Plan object is a collection of Feature2D objects that represent the 2D
 *	view of the rail trajectory.
 */

using namespace std;

#include <memory>
#include "application.h"
#include "collection.h"
#include "feature2d.h"
#include "feature2ds.h"
#include "entity.h"

class Plan;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Plan> Plan_ptr;

class PlanBuilderSnapshot;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<PlanBuilderSnapshot> PlanBuilderSnapshot_ptr;

class Plan
{
private:
	// Constructors
	Plan(Application_ptr &app, Specification &spec);

	// Fields (private)
	Application_ptr _app;
	Specification	_spec;
	Feature2Ds_ptr	_opts[2];	// 0 -> left, 1 -> right

	// Methods (private)
	void				_build();
	Feature2Ds_ptr		_build(Edges_ptr &act, Edges_ptr &pass, Entity2D::Fit2D fit);
	void				_buildLines(Feature2Ds_ptr &fs, Edges_ptr &act,Edges_ptr &pass, Entity2D::Fit2D fit);
	void				_checkLines(Feature2Ds_ptr &fs);
	void				_optimiseLines(Feature2Ds_ptr &fs);
	void				_buildRads(Feature2Ds_ptr &fs, Edges_ptr &p);
	void				_checkRads(Feature2Ds_ptr &fs);
	void				_optimiseRads(Feature2Ds_ptr &fs);

public:
	// Factories
	static Plan_ptr create(Application_ptr &app, Specification &spec);
};

class PlanBuilderSnapshot
{
private:
	// Constructors
	PlanBuilderSnapshot();

public:
	// Factories
	static PlanBuilderSnapshot_ptr create();

	// Methods (public)
	bool isEmpty();
};

#endif