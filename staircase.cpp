using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "staircase.h"

Staircase::Staircase(string &filename)
{
	// Get points
	_points = Points::create(filename);
	
	// Sort points into layers
	_layers = Layers::create(_points);

	// Sort levels into features
	//_features = Features::create(_layers);
}

Staircase::~Staircase()
{
	
}

Staircase_ptr Staircase::create(string filename)
{
	return Staircase_ptr(new Staircase(filename));
}

shared_ptr<Staircase> create(string filename);

std::ostream &operator<<(std::ostream &strm, const Staircase &s)
{
	return strm;
}

shared_ptr<Points> Staircase::getPoints()
{
	return _points;
}

shared_ptr<Layers> Staircase::getLayers()
{
	return _layers;
}

shared_ptr<Features> Staircase::getFeatures()
{
	return _features;
}