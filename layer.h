#ifndef LAYER_H
#define LAYER_H

/**
 *	layer.h
 *	---------------------------------------------------------------------------
 *	A layer object contains facets, edges and points that are at a given 
 *	z-distance. Generally speaking the capture the geometry of individual
 *	steps or landings.
 */

using namespace std;

#include <memory>
#include "surface.h"
#include "rise.h"

class Layer;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Layer> Layer_ptr;

/**
 *	A near horizontal surface that represents a step or landing.
 */
class Layer : public Surface
{
public:
	// Enumerations
	enum Type
	{
		LAYER_TYPE_START,
		LAYER_TYPE_END,
		LAYER_TYPE_STRAIGHT,
		LAYER_TYPE_WINDER,
		LAYER_TYPE_LANDING,
		LAYER_TYPE_UNKNOWN
	};

	enum SubType
	{
		LAYER_SUB_TYPE_NONE,
		LAYER_SUB_TYPE_STANDARD,
		LAYER_SUB_TYPE_EXTENDED,
		LAYER_SUB_TYPE_CORNER_INNER,
		LAYER_SUB_TYPE_CORNER_OUTER,
		LAYER_SUB_TYPE_NARROW,
		LAYER_SUB_TYPE_90,
		LAYER_SUB_TYPE_180,
		LAYER_SUB_TYPE_UNKNOWN
	};

	enum Direction
	{
		LAYER_DIRECTION_STRAIGHT,
		LAYER_DIRECTION_LEFT,
		LAYER_DIRECTION_RIGHT,
		LAYER_DIRECTION_MISC,
		LAYER_DIRECTION_UNKNOWN
	};

private:
	// Constructors
	Layer();
	Layer(Facet_ptr &f);

	// Fields (private)
	Type		_type;
	SubType		_subType;
	Direction	_direction;
	Rise_ptr	_lower;
	Rise_ptr	_upper;

	// Methods (private)
	void _init();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,	const Layer &l);
	friend std::ostream &operator<<(std::ostream &strm,	const Layer_ptr &l);

	friend bool operator<(Layer &l1, Layer &l2);
	friend bool operator<=(Layer &l1, Layer &l2);
	friend bool operator==(Layer &l1, Layer &l2);
	friend bool operator!=(Layer &l1, Layer &l2);
	friend bool operator>=(Layer &l1, Layer &l2);
	friend bool operator>(Layer &l1, Layer &l2);

public:
	// Factories
	static Layer_ptr create();
	static Layer_ptr create(Facet_ptr &f);

	// Methods (private)
	Rise_ptr	lower();
	Rise_ptr	upper();
	Type		getType();
	SubType		getSubType();
	Direction	getDirection();
	void		setType(Type t);
	void		setSubType(SubType st);
	void		setDirection(Direction d);
	void		setLower(Rise_ptr &r);
	void		setUpper(Rise_ptr &r);
};

#endif