#ifndef PLAN_H
#define PLAN_H

/**
 *	plan.h
 *	---------------------------------------------------------------------------
 *	A Plan object is a collection of Feature2D objects that represent the 2D
 *	top-down view of the rail trajectory.
 */

using namespace std;

#include <memory>
#include <vector>
#include "application.h"
#include "enums.h"
#include "collection.h"
#include "edge.h"
#include "edges.h"
#include "entities.h"
#include "entity.h"
#include "feature.h"
#include "features.h"
#include "regions.h"


class Plan;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Plan> Plan_ptr;

class PlanBuilderSnapshot;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<PlanBuilderSnapshot> PlanBuilderSnapshot_ptr;

class Plan
{
public:
	// Factories
	static Plan_ptr create(Application_ptr &app, Specification &spec);
	static Plan_ptr create(Application_ptr &app, Specification &spec, Side side);

	// Methods (public)
	bool	applyChanges(PlanBuilderSnapshot_ptr &s);
	bool	removeChanges(PlanBuilderSnapshot_ptr &s);

private:
	// Constructors
	Plan(Application_ptr &app, Specification &spec);
	Plan(Application_ptr &app, Specification &spec, Side side);

	// Fields (private)
	Application_ptr				_app;
	Specification				_spec;
	Side						_side;
	int							_iter;
	double						_quality;
	Edges_ptr					_active;
	Edges_ptr					_passive;
	SurfaceRegion2Ds_ptr		_regions;
	SurfaceTransition2Ds_ptr	_trans;
	Feature2Ds_ptr				_feats;

	// Methods (private)
	void			_init(Application_ptr &app, Specification &spec,
						  Side side);

	void			_build();
	void			_buildRegions();
	void			_buildTransitions();
	void			_checkTransitions();
	void			_optimise();
	void			_calculateQuality();
	void			_fixFeature(Feature2D_ptr &f);
	Entity2D::Fit2D	_mapFit();
};

/**
 *	A Plan Builder Snapshot objects stores the changes made by the plan builder
 *	between two iterations.
 */
class PlanBuilderSnapshot
{
public:
	// Enumerations (public)
	typedef enum Event
	{
		PLAN_EVENT_MERGE,
		PLAN_EVENT_SPLIT,
		PLAN_EVENT_ANGLE
	};

	// Factories
	static PlanBuilderSnapshot_ptr create();

	// Methods (public)
	Event getEvent();
	void setEvent(Event e);
	bool isEmpty();

private:
	// Constructors
	PlanBuilderSnapshot();

	// Fields (Private)
	Event _event;
	// Data fields...
};

#endif