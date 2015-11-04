using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "staircase.h"

Staircase::Staircase(string &filename)
{
	// Get points
	_pnts = Points::create(filename);

	// Sort points into layers
	_lyrs = Layers::create(_pnts);

	// Sort levels into features
	_feats = Features::create(_lyrs);
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
	return _pnts;
}

shared_ptr<Layers> Staircase::getLayers()
{
	return _lyrs;
}

shared_ptr<Features> Staircase::getFeatures()
{
	return _feats;
}