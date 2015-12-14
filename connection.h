#ifndef CONNECTION_H
#define CONNECTION_H

/**
 *	connection.h
 *	---------------------------------------------------------------------------
 *	A Connection object is a representation of a rail connection (e.g. weld)
 */

using namespace std;

#include <memory>
#include "attachable.h"

/**
 *	Represents a single join (e.g. Weld).
 */
class Connection;
typedef shared_ptr<Connection> Connection_ptr;

class Connection : public Attachable
{
public:
	// Enumerations
	typedef enum Type
	{
		CONNECTION_TYPE_JOIN,
		CONNECTION_TYPE_WELD
	};

private:
	// Constructors
	Connection(double pos);

	// Fields (private)
	Type	_type;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Connection &c);
	friend std::ostream &operator<<(std::ostream &strm,
		const Connection_ptr &c);

	friend bool operator==(Connection &c1, Connection &c2);
	friend bool operator!=(Connection &c1, Connection &c2);

public:
	// Factories
	static Connection_ptr create(double pos);

	// Methods (public)
	Type	getType();
};

#endif