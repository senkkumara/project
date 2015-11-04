#ifndef STAIRCASE_H
#define STAIRCASE_H

using namespace std;

#include <string>
#include <vector>
#include <memory>
#include "feature.h"
#include "layer.h"
#include "points.h"
#include "point.h"

class Staircase
{
private:
	Staircase(std::string &filename);
	Features_ptr _feats;
	Layers_ptr _lyrs;
	Points_ptr _pnts;
	void _extractPoints(std::vector<Point_ptr> &pnts, std::string &filename);
	Layer_ptr _findLayer(std::vector<Layer_ptr> &lyrs, Point_ptr pnt);
	void _sortPoints(std::vector<Layer_ptr> &lyrs, std::vector<Point_ptr> &pnts);
	void _sortLayers(std::vector<Feature_ptr> &feats, std::vector<Layer_ptr> &lyrs);
	friend std::ostream& operator<<(std::ostream &strm, const Staircase &s);
public:
	~Staircase();
	static shared_ptr<Staircase> create(string filename);
	Points_ptr getPoints();
	Layers_ptr getLayers();
	Features_ptr getFeatures();
};

typedef shared_ptr<Staircase> Staircase_ptr;

#endif