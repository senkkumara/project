#ifndef PATH_H
#define PATH_H

/**
 *	path.h
 *	---------------------------------------------------------------------------
 *	A Path object is a collection of Feature3D objects that represent the rail
 *	trajectory.
 */

using namespace std;

#include <memory>
#include "application.h"
#include "plan.h"
#include "features.h"

class Path;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Path> Path_ptr;

class PathBuilderSnapshot;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<PathBuilderSnapshot> PathBuilderSnapshot_ptr;

class Path
{
public:
	// Enumerations
	enum Type
	{
		PATH_TYPE_UPPER,
		PATH_TYPE_LOWER
	};

private:
	// Constructors
	Path(Application_ptr &app, Specification &spec, Plan_ptr &plan);
	Path(Path_ptr &path);

	// Fields (private)
	Application_ptr _app;
	Specification	_spec;
	Feature3Ds_ptr	_opts[2];	// 0 -> left, 1 -> right

	// Methods (private)
	void	_build();
	void	_buildCorners(Feature3Ds_ptr &fs);
	void	_buildCorner();
	void	_buildHelix();
	void	_checkCorners();
	void	_buildLines();

public:
	// Factories
	static Path_ptr create(Application_ptr &app, Specification &spec,
		Plan_ptr &plan);

	static Path_ptr create(Path_ptr &path);
};

class PathBuilderSnapshot
{
private:
	// Constructors
	PathBuilderSnapshot();

	// Fields (private)
	Path::Type _type;

public:
	// Factories
	static PathBuilderSnapshot_ptr create();

	// Methods (public)
	bool isEmpty();
	Path::Type getType();
};

#endif