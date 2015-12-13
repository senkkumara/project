#ifndef TESTER_H
#define TESTER_H

/**
 *	tester.h
 *	---------------------------------------------------------------------------
 *
 */

using namespace std;

#include <memory>
#include <ostream>
#include <vector>
#include "layer.h"

class Tester;
typedef shared_ptr<Tester> Tester_ptr;

struct TestResult
{
public:
	TestResult(bool r)
	{
		result = r;
	};

	bool result;
};

typedef TestResult (*TestFn)(Layer_ptr);

class Tester
{
private:
	// Constructors
	Tester(Layer_ptr &layer);

	// Member variables (private)
	Layer_ptr _layer;

	// Member functions (private)
	void _init();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Tester &t);

public:
	// Factories
	static Tester_ptr create(Layer_ptr &layer);

	// Member functions (public)
	void run();

	// Getters
	Layer_ptr getLayer();
};

#endif