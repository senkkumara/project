#ifndef CHAIR_H
#define CHAIR_H

/**
 *	chair.h
 *	---------------------------------------------------------------------------
 *	A Chair object represents a chair instance.
 */

using namespace std;

#include <memory>
#include "attachable.h"

/**
 *	Represents a chair.
 */
class Chair;
typedef shared_ptr<Chair> Chair_ptr;

class Chair : public Attachable
{

};

#endif