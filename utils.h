#ifndef UTILS_H
#define UTILS_H

namespace utils
{
	template<class P1, class P2, class C2> P2 cast(P1 &obj)
	{
		return dynamic_pointer_cast<C2>(obj);
	};
};

#endif