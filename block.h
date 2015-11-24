#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include <vector>
#include "points.h"
#include "equation.h"

class Block;
typedef shared_ptr<Block> Block_ptr;

class Block : Collection<Point_ptr, Block_ptr>
{
private:
	// Constructors
	Block(Point_ptr &point1, Point_ptr &point2);
	Block(Points_ptr &points);

	// Fields (private)
	Equation_ptr	_railEq;
	Equation_ptr	_restEq;
	double			_xm;
	double			_ym;
	double			_sumX2;
	double			_sumY2;
	double			_sumXY;
	double			_ss[3];
	Points_ptr		_closest[2];
	double			_closestDistance[2];

	// Methods (private)
	void	_calculateLinearRegr();
	void	_calculateDeviations();
	double	_calculateDeviation(Point_ptr &point);
	void	_findPivots();
	void	_buildRailLine();
	void	_calculateQuality();

public:
	// Factories
	static Block_ptr create(Point_ptr &point1, Point_ptr &point2);
	static Block_ptr create(Points_ptr &points);

	// Methods
	void		add(Point_ptr &point);
	void		remove(Point_ptr &point);
	Block_ptr	split();

	// Getters
	Equation_ptr	getRailEq();
	Equation_ptr	getRestEq();
};

#endif