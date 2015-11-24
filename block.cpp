using namespace std;

#include "block.h"
#include <numeric>

Block::Block(Point_ptr &point1, Point_ptr &point2)
{
	__super::add(point1);
	__super::add(point2);

	_calculateLinearRegr();
}

void Block::_calculateLinearRegr()
{
	if (size() < 2) throw SolutionBuildException();

	double a = 0, b = 0;
	double x, y;
	double sumX = 0, sumY = 0;
	double xm2 = 0, ym2 = 0;

	_sumX2 = 0;
	_sumY2 = 0;
	_sumXY = 0;

	// Calculated sum values
	for (Point_ptr p : _items)
	{
		x = p->getX();
		y = p->getY();

		sumX += x;
		sumY += y;

		_sumX2 += std::pow(x, 2);
		_sumY2 += std::pow(y, 2);
		_sumXY += (x * y);
	}

	_xm = sumX / size();
	_ym = sumY / size();

	xm2 = std::pow(_xm, 2);
	ym2 = std::pow(_ym, 2);

	_ss[1] = _sumX2 - (size() * xm2);
	_ss[1] = _sumY2 - (size() * ym2);
	_ss[2] = _sumXY - (size() * _xm * _ym);

	//TODO: Make so can handle vertical lines
	b = _ss[2] / _ss[0];
	a = _ym - (b * _xm);
}

Block::Block(Points_ptr &points)
{
	for (int i = 0; i < points->size(); i++)
	{
		add(points->get(i));
	}
}

Block_ptr Block::create(Point_ptr &point1, Point_ptr &point2)
{
	return Block_ptr(new Block(point1, point2));
}

Block_ptr Block::create(Points_ptr &points)
{
	return Block_ptr(new Block(points));
}

/**
 *	@Override
 */
void Block::add(Point_ptr &point)
{
	double x = point->getX();
	double y = point->getY();

	double xm2 = 0, ym2 = 0;
	double a = 0, b = 0;

	_xm = ((size() / (size() + 1)) * _xm) + (x / (size() + 1));
	_ym = ((size() / (size() + 1)) * _ym) + (y / (size() + 1));
	_sumX2 += std::pow(x, 2);
	_sumY2 += std::pow(y, 2);
	_sumXY += (x * y);

	xm2 = std::pow(_xm, 2);
	ym2 = std::pow(_ym, 2);

	_ss[1] = _sumX2 - (size() * xm2);
	_ss[1] = _sumY2 - (size() * ym2);
	_ss[2] = _sumXY - (size() * _xm * _ym);

	//TODO: Make so can handle vertical lines
	b = _ss[2] / _ss[0];
	a = _ym - (b * _xm);

	__super::add(point);
}

/**
 *	@Override
 */
void Block::remove(Point_ptr &point)
{
	double x = point->getX();
	double y = point->getY();

	double xm2 = 0, ym2 = 0;
	double a = 0, b = 0;

	_xm = ((size() / (size() - 1)) * _xm) + (x / (size() - 1));
	_ym = ((size() / (size() - 1)) * _ym) + (y / (size() - 1));
	_sumX2 += std::pow(x, 2);
	_sumY2 += std::pow(y, 2);
	_sumXY += (x * y);

	xm2 = std::pow(_xm, 2);
	ym2 = std::pow(_ym, 2);

	_ss[1] = _sumX2 - (size() * xm2);
	_ss[1] = _sumY2 - (size() * ym2);
	_ss[2] = _sumXY - (size() * _xm * _ym);

	//TODO: Make so can handle vertical lines
	b = _ss[2] / _ss[0];
	a = _ym - (b * _xm);

	__super::remove(point);
}

Equation_ptr Block::getRailEq()
{
	return _railEq;
}

Equation_ptr Block::getRestEq()
{
	return _restEq;
}