using namespace std;

#include "rails.h"

Rails::Rails(Skeleton_ptr &skeleton)
{
	_skeleton = skeleton;
}

Rails_ptr Rails::create(Skeleton_ptr &skeleton)
{
	return Rails_ptr(new Rails(skeleton));
}

Skeleton_ptr Rails::getSkeleton()
{
	return _skeleton;
}