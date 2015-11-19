using namespace std;

#include "surface.h"

Surface::Surface()
{

}

Surface::Surface(Geometry_ptr &geometry)
{

}

void Surface::_build(Geometry_ptr &geometry)
{

}

void Surface::_findInterfaces()
{

}

void Surface::_findInterface(Layer_ptr &layer1, Layer_ptr &Layer2)
{

}

Layers_ptr Surface::getLayers()
{
	return _layers;
}

Rises_ptr Surface::getRises()
{
	return _rises;
}