using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "staircase.h"

/**
 *	(Private) Constructs a staircase from points retrieved from
 *	a text file argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Staircase::Staircase(string &filename)
{
	_filename = filename;
	_points = Points::create(filename);
	_layers = Layers::create(_points);
	_features = Features::create(_layers);
}

/**
 *	Factory method using constructor that takes a filename as
 *	an argument.
 */
Staircase_ptr Staircase::create(string &filename)
{
	return Staircase_ptr(new Staircase(filename));
}

/**
 *	<< operator overload
 */
std::ostream &operator<<(std::ostream &strm, const Staircase &s)
{
	return strm;
}

/**
 *	Get the points the staircase comprises of.
 */
shared_ptr<Points> Staircase::getPoints()
{
	return _points;
}

/**
 *	Get the layers the staircase comprises of.
 */
shared_ptr<Layers> Staircase::getLayers()
{
	return _layers;
}

/**
 *	Get the features the staircase comprises of.
 */
shared_ptr<Features> Staircase::getFeatures()
{
	return _features;
}