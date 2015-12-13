using namespace std;

#include "supports.h"

Supports::Supports(Application_ptr &app, Skeleton_ptr &skeleton)
{
	_app = app;
	_skeleton = skeleton;

	_findSlots();
	_allocateSlots();
}

Supports_ptr Supports::create(Application_ptr &app, Skeleton_ptr &skeleton)
{
	return Supports_ptr(new Supports(app, skeleton));
}

void Supports::_findSlots()
{
	//TODO: implement method
}

void Supports::_allocateSlots()
{
	//TODO: implement method
}

Application_ptr Supports::getApp()
{
	return _app;
}

Skeleton_ptr Supports::getSkeleton()
{
	return _skeleton;
}
vector<Slot_ptr> Supports::getSlots()
{
	return _slots;
}