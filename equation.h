#ifndef EQUATION_H
#define EQUATION_H

using namespace std;

#include <memory>
#include <map>
#include "point.h"
#include "points.h"

enum EquationType
{
	EQUT_LINEAR,
	EQUT_CIRCULAR
};

class Equation;
typedef shared_ptr<Equation> Equation_ptr;

class Equation
{
private:
	// Constructors
	Equation(Point_ptr &point1, Point_ptr &point2);	// Linear
	Equation(Points_ptr &points);					// Linear (regression)
	Equation(map<std::string, double> coeff, Equation type);

	// Methods

public:
	// Constructors


};

#endif