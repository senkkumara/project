using namespace std;

#include "feature.h"

Feature::Feature()
{

}

Feature::~Feature()
{
	//TODO: Add destructor
}

Feature_ptr Feature::create()
{
	return Feature_ptr(new Feature());
}

Layers_ptr Feature::getLayers()
{
	return _layers;
}