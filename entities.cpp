/**
 *	entities.cpp
 *	-----------------------------------------------------------------------
 *	See "entities.h" for a description.
 */

using namespace std;

#include "entities.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Entities::Entities()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entities &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Entities");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entities_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
Entities_ptr Entities::create()
{
	return Entities_ptr(new Entities());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Entity2Ds::Entity2Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entity2Ds &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Entity2Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entity2Ds_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
Entity2Ds_ptr Entity2Ds::create()
{
	return Entity2Ds_ptr(new Entity2Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
LineEntity2Ds::LineEntity2Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const LineEntity2Ds &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< LineEntity2Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const LineEntity2Ds_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
LineEntity2Ds_ptr LineEntity2Ds::create()
{
	return LineEntity2Ds_ptr(new LineEntity2Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
RadEntity2Ds::RadEntity2Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const RadEntity2Ds &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< RadEntity2Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const RadEntity2Ds_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
RadEntity2Ds_ptr RadEntity2Ds::create()
{
	return RadEntity2Ds_ptr(new RadEntity2Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Entity3Ds::Entity3Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entity3Ds &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Entity3Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entity3Ds_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
Entity3Ds_ptr Entity3Ds::create()
{
	return Entity3Ds_ptr(new Entity3Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
LineEntity3Ds::LineEntity3Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const LineEntity3Ds &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< LineEntity3Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const LineEntity3Ds_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
LineEntity3Ds_ptr LineEntity3Ds::create()
{
	return LineEntity3Ds_ptr(new LineEntity3Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
ArcEntity3Ds::ArcEntity3Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const ArcEntity3Ds &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< ArcEntity3Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const ArcEntity3Ds_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
ArcEntity3Ds_ptr ArcEntity3Ds::create()
{
	return ArcEntity3Ds_ptr(new ArcEntity3Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
HelixEntity3Ds::HelixEntity3Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const HelixEntity3Ds &e)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< HelixEntity3Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const HelixEntity3Ds_ptr &e)
{
	return strm << *e;
}

/**
 *	Factory method using default constructor.
 */
HelixEntity3Ds_ptr HelixEntity3Ds::create()
{
	return HelixEntity3Ds_ptr(new HelixEntity3Ds());
}