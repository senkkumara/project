/**
 *	application.cpp
 *	-----------------------------------------------------------------------
 *	See "application.h" for a description.
 */

using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include "application.h"
#include "facet.h"
#include "exceptions.h"

/**
 *	(Private) Constructs a application from the file currently
 *	in session.
 *
 *	Do not use this directly, use the provided factory method.
 */
Application::Application()
{
	// do nothing...
}

/**
 *	(Private) Constructs a application from facets retrieved from
 *	a text file argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Application::Application(std::string &filename)
{
	_filename = filename;
	_setGeomType(filename);

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
 *	(Private) Based on the extension of the filename argument, determine
 *	how the geometry is to be built (e.g. facet- or point-based).
 */
void Application::_setGeomType(std::string &filename)
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
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Application &s)
{
	return strm;
}

/**
 *	Factory method using the default constructor
 */
Application_ptr Application::create()
{
	return Application_ptr(new Application());
}

/**
 *	Factory method using constructor that takes a filename as
 *	an argument.
 */
Application_ptr Application::create(string &filename)
{
	return Application_ptr(new Application(filename));
}

/**
 *	Prints a summary report for the application.
 */
void Application::print()
{
	cout << endl;
	cout << "===== Application Report =====" << endl;
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
 *	Get the filename the application was created from.
 */
std::string Application::getFilename()
{
	return _filename;
}

/**
 *	Get the points the application comprises of.
 */
Points_ptr Application::getPoints()
{
	return _points;
}

/**
 *	Get the layers the application comprises of.
 */
Layers_ptr Application::getLayers()
{
	return _layers;
}

/**
 *	Get the features the application comprises of.
 */
Features_ptr Application::getFeatures()
{
	return _features;
}