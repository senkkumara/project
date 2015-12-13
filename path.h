#ifndef PATH_H
#define PATH_H

using namespace std;

#include <memory>
#include "application.h"
#include "plan.h"
#include "feature3ds.h"

enum PathType
{
	PT_UPPER,
	PT_LOWER
};

class Path;
typedef shared_ptr<Path> Path_ptr;

class Path
{
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
	void	_build3DArc();
	void	_buildHelix();
	void	_checkCorners();
	void	_buildLines();

public:
	// Factories
	static Path_ptr create(Application_ptr &app, Specification &spec, Plan_ptr &plan);
	static Path_ptr create(Path_ptr &path);

};

#endif