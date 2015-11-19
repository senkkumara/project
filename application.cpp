/**
 *	application.cpp
 *	-----------------------------------------------------------------------
 *	See "application.h" for a description.
 */

using namespace std;

#include <iostream>
#include <string>

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
	_geometry = Geometry::create(_filename);
	/*_layer = Layers::create(_geometry);
	_features = Features::create(_layers);*/
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Application &s)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Application");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Application_ptr &s)
{
	return strm << *s;
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
	cout << "Points: " << getGeometry()->getPoints()->size() << endl;
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

/**
 *	Get the geometry the application comprises of.
 */
Geometry_ptr Application::getGeometry()
{
	return _geometry;
}

/**
 *	Get the edges comprising the left boundary.
 */
Edges_ptr Application::left()
{
	return _leftBoundary;
}

/**
 *	Get the edges comprising the right boundary.
 */
Edges_ptr Application::right()
{
	return _rightBoundary;
}