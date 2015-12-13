using namespace std;

#include "supports.h"

Supports::Supports(Skeleton_ptr &skeleton)
{
	_skeleton = skeleton;
}

Supports_ptr Supports::create(Skeleton_ptr &skeleton)
{
	return Supports_ptr(new Supports(skeleton));
}

Skeleton_ptr Supports::getSkeleton()
{
	return _skeleton;
}