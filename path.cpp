using namespace std;

#include "path.h"

Path::Path(Application_ptr &app, Specification &spec, Plan_ptr &plan)
{

}

Path::Path(Path_ptr &path)
{

}

Path_ptr Path::create(Application_ptr &app, Specification &spec, Plan_ptr &plan)
{
	return Path_ptr(new Path(app, spec, plan));
}

Path_ptr Path::create(Path_ptr &path)
{
	return Path_ptr(new Path(path));
}

PathBuilderSnapshot::PathBuilderSnapshot()
{

}

PathBuilderSnapshot_ptr PathBuilderSnapshot::create()
{
	return PathBuilderSnapshot_ptr(new PathBuilderSnapshot());
}

Path::Type PathBuilderSnapshot::getType()
{
	return _type;
}