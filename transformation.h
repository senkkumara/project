#ifndef TRANFORMATION_H
#define TRANSFORMATION_H

/**
 *	transformation.h
 *	---------------------------------------------------------------------------
 *	Contains classes involved in the creation of linear and non-linear 2D and
 *	3D transformation matrices.
 */

using namespace std;

#include <memory>
#include <vector>
#include "point.h"

class Transformation;			// Pre-declare class for shared pointer typedef
typedef shared_ptr<Transformation> Transformation_ptr;

class TransformationMatrix;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<TransformationMatrix> TransformationMatrix_ptr;

class TransformationMatrix2D;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<TransformationMatrix2D> TransformationMatrix2D_ptr;

class TransformationMatrix3D;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<TransformationMatrix3D> TransformationMatrix3D_ptr;

// Function pointer
typedef void(*Fn)(vector<double>);

/**
 *	A transformation records a function and the parameters input into it
 *	in order to generate the value of a cell of a transformation matrix.
 */
class Transformation
{
private:
	// Constructors
	Transformation(Fn fn, double p);
	Transformation(Fn fn, vector<double> p);

	// Fields (private)
	Fn				_fn;
	vector<double>	_inputs;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Transformation &t);

	friend std::ostream &operator<<(std::ostream &strm,
		const Transformation_ptr &t);

public:
	// Factories
	Transformation_ptr create(Fn fn, double p);
	Transformation_ptr create(Fn fn, vector<double> p);

	// Methods (public)
	Fn				getFn();
	vector<double>	getInputs();
};

/**
 *	A generic transformation matrix - a 3x3 or 4x4 matrix of Transformations.
 */
class TransformationMatrix
{
public:
	static TransformationMatrix_ptr parallel();
	static TransformationMatrix_ptr perpendicular();
};

/**
 *	A 3x3 transformation matrix - for 2D transformations.
 */
class TransformationMatrix2D
{
private:
	// Constructors
	TransformationMatrix2D();

	// Operator overloads
	TransformationMatrix2D_ptr operator+(const TransformationMatrix2D_ptr &t);
	friend std::ostream &operator<<(std::ostream &strm,
		const TransformationMatrix2D &t);

	friend std::ostream &operator<<(std::ostream &strm,
		const TransformationMatrix2D_ptr &t);

public:
	// Factories
	static TransformationMatrix_ptr create();
	static TransformationMatrix_ptr parallel();
	static TransformationMatrix_ptr perpendicular();
};

/**
 *	A 4x4 transformation matrix - for 3D transformations.
 */
class TransformationMatrix3D
{
private:
	// Constructors
	TransformationMatrix3D();

	// Operator overloads
	TransformationMatrix3D_ptr operator+(const TransformationMatrix3D_ptr &t);
	friend std::ostream &operator<<(std::ostream &strm,
		const TransformationMatrix3D &t);

	friend std::ostream &operator<<(std::ostream &strm,
		const TransformationMatrix3D_ptr &t);

public:
	// Factories
	static TransformationMatrix_ptr create();
	static TransformationMatrix_ptr parallel();
	static TransformationMatrix_ptr perpendicular();
};

/**
 *	Contains methods used for non-linear transformations.
 */
namespace Transformations
{
	double constant(vector<double> p);
};

#endif