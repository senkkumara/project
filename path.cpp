using namespace std;

#include "path.h"

Path_ptr Path::create(Application_ptr &app, Specification &spec, Plan_ptr &plan)
{
	return Path_ptr(new Path(app, spec, plan));
}

Path_ptr Path::create(Path_ptr &path)
{
	return Path_ptr(new Path(path));
}

Path::Path(Application_ptr &app, Specification &spec, Plan_ptr &plan)
{

}

Path::Path(Path_ptr &path)
{

}

PathBuilderSnapshot_ptr PathBuilderSnapshot::create()
{
	return PathBuilderSnapshot_ptr(new PathBuilderSnapshot());
}

bool PathBuilderSnapshot::isEmpty()
{
	//TODO: implement method
	return true;
}

Path::Type PathBuilderSnapshot::getType()
{
	return _type;
}

PathBuilderSnapshot::PathBuilderSnapshot()
{
	//TODO: implement method
}