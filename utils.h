#ifndef UTILS_H
#define UTILS_H

/**
 *	utils.h
 *	---------------------------------------------------------------------------
 *	Contains the "utils" namespace which in turn contains miscellaneous,
 *	multi-purpose methods.
 */

using namespace std;

namespace utils
{
	/**
	 *	Dynamically cast a shared_ptr from one type to another.
	 */
	template<class P1, class P2, class C2> P2 cast(P1 &obj)
	{
		return dynamic_pointer_cast<C2>(obj);
	};
};

#endif