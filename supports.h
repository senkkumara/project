#ifndef SUPPORTS_H
#define SUPPORTS_H

using namespace std;

#include <memory>
#include "skeleton.h"

class Supports;
typedef shared_ptr<Supports> Supports_ptr;

class Supports
{
private:
	// Constructors
	Supports(Skeleton_ptr &layout);

	// Member variables (private)
	Skeleton_ptr _skeleton;

public:
	// Factories
	static Supports_ptr create(Skeleton_ptr &layout);

	// Getters
	Skeleton_ptr getSkeleton();
};

#endif