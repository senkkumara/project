/**
 *	staircase.cpp
 *	-----------------------------------------------------------------------
 *	See "staircase.h" for a description.
 */

using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include "staircase.h"
#include "facet.h"
#include "exceptions.h"

/**
 *	(Private) Constructs a staircase from the file currently
 *	in session.
 *
 *	Do not use this directly, use the provided factory method.
 */
Staircase::Staircase()
{
	// do nothing...
}

/**
 *	(Private) Constructs a staircase from facets retrieved from
 *	a text file argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Staircase::Staircase(std::string &filename)
{
	_filename = filename;
	_findGeomType(filename);

	switch (_geomType)
	{
	case GEOM_FACET:
		_facets = Facets::create(filename);
		_layers = Layers::create(_facets);
		break;
	case GEOM_POINT:
		_points = Points::create(filename);
		_layers = Layers::create(_points);
		break;
	}

	_features = Features::create(_layers);
}

/**
 *	
 */
void Staircase::_findGeomType(std::string &filename)
{
	// Check file has an extension
	if (filename.find(".") == std::string::npos)
	{
		throw UnsupportedFileTypeException("NO EXTENSION");
	}

	std::stringstream ss(filename);
	std::size_t index = filename.find_last_of(".");
	std::string ext = filename.substr(index + 1);

	// Make uppercase to help comparison
	for (auto & c: ext) c = toupper(c);

	// Check for valid file extension
	if (ext == "STL")
	{
		_geomType = GEOM_FACET;
	}
	else if (ext == "DXF")
	{
		_geomType = GEOM_FACET;
	}
	else if (ext == "PTS")
	{
		_geomType = GEOM_POINT;
	}
	else
	{
		throw UnsupportedFileTypeException(ext);
	}
}

/**
 *	Factory method using the default constructor
 */
Staircase_ptr Staircase::create()
{
	return Staircase_ptr(new Staircase());
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
 *	Prints a summary report for the staircase.
 */
void Staircase::print()
{
	cout << endl;
	cout << "===== Staircase Report =====" << endl;
	cout << "Filename: " << getFilename() << endl;
	cout << "Points: " << getPoints()->size() << endl;
	cout << "Layers: " << getLayers()->size() << endl;
	cout << "Features: " << getFeatures()->size() << endl;
	cout << endl;

	Features_ptr features = getFeatures();
	for (int i = 0; i < features->size(); i++)
	{
		FeatureType type = features->get(i)->getType();
		cout << "Feature " << (i + 1) << " is a ";
		switch (type)
		{
		case FT_START:
			cout << "START" << endl;
			break;
		case FT_END:
			cout << "END" << endl;
			break;
		case FT_STRAIGHT:
			cout << "STRAIGHT consisting of "
				 << features->get(i)->getLayers()->size();

			if (features->get(i)->getLayers()->size() > 1)
			{
				cout << " steps";
			}
			else
			{
				cout << " step";
			}
			cout << endl;
			break;
		case FT_WINDER:
			cout << "WINDER consisting of " 
				 << features->get(i)->getLayers()->size();

			if (features->get(i)->getLayers()->size() > 1)
			{
				cout << " steps";
			}
			else
			{
				cout << " step";
			}
			cout << endl;
			break;
		case FT_LANDING_FLAT:
			cout << "FLAT LANDING" << endl;
			break;
		case FT_UNKNOWN:
			cout << "UNKNOWN" << endl;
			break;
		}
	}

	cout << endl << endl;
}

/**
 *	Get the filename the staircase was created from.
 */
std::string Staircase::getFilename()
{
	return _filename;
}

/**
 *	Get the points the staircase comprises of.
 */
Points_ptr Staircase::getPoints()
{
	return _points;
}

/**
 *	Get the layers the staircase comprises of.
 */
Layers_ptr Staircase::getLayers()
{
	return _layers;
}

/**
 *	Get the features the staircase comprises of.
 */
Features_ptr Staircase::getFeatures()
{
	return _features;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Staircase &s)
{
	return strm;
}