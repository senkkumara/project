#ifndef JOB_H
#define JOB_H

/**
 *	job.h
 *	---------------------------------------------------------------------------
 *	A Rails object is container for one or more Rail objects.
 *
 *	It forms one layer of the "Solution" stack.
 *
 *	During the building of the Rails object snapshots are taken of each
 *	iteration - this is to facilitate "back-stepping".
 */

using namespace std;

#include <memory>
#include <string>
#include "application.h"
#include "solution.h"
#include "solutions.h"
#include "specification.h"

/**
 *	Top-most object of the hierarchy - containing all others.
 */
class Job;
typedef shared_ptr<Job> Job_ptr;

class Job
{
private:
	// Constructors
	Job(Specification &spec);

	// Member variables (private)
	Specification		_spec;
	Application_ptr		_app;
	Solutions_ptr		_solutions;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Job &j);
	friend std::ostream &operator<<(std::ostream &strm, const Job_ptr &j);

public:
	// Factories
	static Job_ptr create(Specification &spec);

	// Methods (public)
	Specification		getSpecification();
	Application_ptr		getApplication();
	Solutions_ptr		getSolutions();
};

#endif