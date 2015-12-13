#ifndef RAILS_H
#define RAILS_H

using namespace std;

#include <memory>
#include "skeleton.h"

class Rails;
typedef shared_ptr<Rails> Rails_ptr;

class Rails
{
private:
	// Constructors
	Rails(Skeleton_ptr &layout);

	// Member variables (private)
	Skeleton_ptr _skeleton;

public:
	// Factories
	static Rails_ptr create(Skeleton_ptr &layout);

	// Getters
	Skeleton_ptr getSkeleton();
};

#endif