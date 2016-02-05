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
#include "feature2d.h"
#include "feature2ds.h"
#include "entity.h"
#include "entities.h"
#include "edges.h"
#include "edge.h"

class Plan;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Plan> Plan_ptr;

class PlanBuilderSnapshot;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<PlanBuilderSnapshot> PlanBuilderSnapshot_ptr;

class Plan
{
private:
	// Constructors
	Plan(Application_ptr &app, Specification &spec, Side side);

	// Fields (private)
	Application_ptr		_app;
	Specification		_spec;
	Side				_side;
	int					_iter;
	Edges_ptr			_active;
	Edges_ptr			_passive;
	LineEntity2Ds_ptr	_lines;
	RadEntity2Ds_ptr	_rads;
	Feature2Ds_ptr		_feats;
	double				_quality;

	// Methods (private)
	void	_build();
	void	_buildLines();
	void	_buildRads();
	void	_checkRads();
	void	_optimise();
	void	_calculateQuality();
	void	_fixFeature(Feature2D_ptr &f);

public:
	// Factories
	static Plan_ptr create(Application_ptr &app, Specification &spec, Side side);

	// Methods (public)
	bool	applyChanges(PlanBuilderSnapshot_ptr &s);
	bool	removeChanges(PlanBuilderSnapshot_ptr &s);
};

/**
 *	A Plan Builder Snapshot objects stores the changes made by the plan builder
 *	between two iterations.
 */
class PlanBuilderSnapshot
{
public:
	typedef enum Event
	{
		PLAN_EVENT_MERGE,
		PLAN_EVENT_SPLIT,
		PLAN_EVENT_ANGLE
	};

private:
	// Constructors
	PlanBuilderSnapshot();

	// Fields (Private)
	Event _event;
	// Data fields...

public:
	// Factories
	static PlanBuilderSnapshot_ptr create();

	// Methods (public)
	Event getEvent();
	void setEvent(Event e);
	bool isEmpty();
};

#endif