#ifndef SKELETON_H
#define SKELETON_H

using namespace std;

#include <memory>
#include "collection.h"
#include "application.h"
#include "plan.h"
#include "path.h"

class Skeleton;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Skeleton> Skeleton_ptr;

class SkeletonBuilderSnapshot;		// Pre-declare class for shared pointer
									// typedef

typedef shared_ptr<SkeletonBuilderSnapshot> SkeletonBuilderSnapshot_ptr;

class Skeleton
{
private:
	// Constructors
	Skeleton(Application_ptr &app, Specification &spec);

	// Fields (private)
	int					_iter;		// Track iterative attempts to build
	Application_ptr		_app;		// Geometry to build skeleton on
	Specification		_spec;		// Additional app details
	Plan_ptr			_plan;
	Path_ptr			_upper;
	Path_ptr			_lower;
  //vector<DatumCurve>	_curves;
	vector<SkeletonBuilderSnapshot_ptr>	_snaps;

	// Methods (private)
	void _init();
	PlanBuilderSnapshot_ptr _buildPlan();
	PathBuilderSnapshot_ptr _buildLower();
	PathBuilderSnapshot_ptr _buildUpper();
	void					_buildDatums();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Skeleton &p);

	friend std::ostream &operator<<(std::ostream &strm,
		const Skeleton_ptr &p);

public:
	// Factories
	static Skeleton_ptr create(Application_ptr &app, Specification &spec);

	// Methods (public)
	int					getIterations();
	Application_ptr		getApp();
	Plan_ptr			getPlan();
  //vector<DatumCurve>	getCurves();
	Path_ptr			lower();
	Path_ptr			upper();
};

class SkeletonBuilderSnapshot
{
private:
	// Constructors
	SkeletonBuilderSnapshot();

	// Fields (private)
	PlanBuilderSnapshot_ptr _planSnap;
	PathBuilderSnapshot_ptr _lowerSnap;
	PathBuilderSnapshot_ptr _upperSnap;

public:
	// Factories
	static SkeletonBuilderSnapshot_ptr create();

	// Methods (public)
	bool isValid();
};

#endif