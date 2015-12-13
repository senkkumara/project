using namespace std;

#include "rails.h"

Rails::Rails(Application_ptr &app, Skeleton_ptr &skel, Supports_ptr &sup)
{
	_app = app;
	_skeleton = skel;
	_supports = sup;
}

Rails_ptr Rails::create(Application_ptr &app, Skeleton_ptr &skel, Supports_ptr &sup)
{
	return Rails_ptr(new Rails(app, skel, sup));
}

Skeleton_ptr Rails::getSkeleton()
{
	return _skeleton;
}