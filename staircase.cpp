using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "staircase.h"
#include "exceptions.h"

/**
 *	(Private) Constructs a staircase from the file currently
 *	in session.
 *
 *	Do not use this directly, use the provided factory method.
 */
Staircase::Staircase()
{
	//TODO: Implement method.
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
	_extractGeometry(filename);
	//_points = Points::create(filename);
	//_layers = Layers::create(_points);
	//_features = Features::create(_layers);
}

/**
 *	
 */
void Staircase::_extractGeometry(std::string &filename)
{
	// Check file has an extension
	if (filename.find(".") == std::string::npos)
	{
		throw UnsupportedFileTypeException();
	}

	std::stringstream ss(filename);
	std::size_t index = filename.find_last_of(".");
	std::string ext = filename.substr(index + 1);

	// Make uppercase to help comparison
	for (auto & c: ext) c = toupper(c);

	// Check for valid file extension
	if (ext == "STL")
	{
		_extractGeometryFromSTL(filename);
	}
	else if (ext == "DXF")
	{
		_extractGeometryFromDXF(filename);
	}
	else
	{
		throw UnsupportedFileTypeException();
	}
}

void Staircase::_extractGeometryFromDXF(std::string &filename)
{

}

void Staircase::_extractGeometryFromSTL(string &filename)
{
	std::string line;
	ifstream file(filename);
	
	if (file.is_open())
	{
		bool get = false;
		while (getline(file, line))
		{
			// Look for start of a facet loop - start collecting vertices
			if (line.find("outer loop") != std::string::npos)
			{
				get = true;
				continue;
			}

			// Look for the end of a facet loop - stop collecting vertices
			if (line.find("endloop") != std::string::npos)
			{
				get = false;
				continue;
			}

			// Get vertices
			if (get && line.find("vertex") != std::string::npos)
			{
				// Remove "      vertex " prefix
				stringstream ss(line = line.substr(line.find("vertex") + 7));
				string item;
				int count = 0;			// Only extract three entries (x, y, z)
				vector<double> coords;

				while (getline(ss, item, ' ') && count < 3)
				{
					coords.push_back(atof(item.c_str()));
					count++;
				}
			}
		}

		file.close();
	}
	else
	{
		throw FileNotFoundException();
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
			cout << "STRAIGHT consisting of " << features->get(i)->getLayers()->size();
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
			cout << "WINDER consisting of "  << features->get(i)->getLayers()->size();
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
string Staircase::getFilename()
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