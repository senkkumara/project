using namespace std;

#include <iostream>
#include "main.h"
#include "job.h"

#include "point.h"
#include "entity.h"

#define EPSILON 0.00001

int main()
{
	/*
	LineEntity2D_ptr l1 = LineEntity2D::create();
	double x1[2] = {3.0, -33.0};
	double y1[2] = {3.0, -33.0};
	l1->setXCoefficients(x1);
	l1->setYCoefficients(y1);

	LineEntity2D_ptr l2 = LineEntity2D::create();
	double x2[2] = {-3.0, 0.0};
	double y2[2] = {3.0, 0.0};
	l2->setXCoefficients(x2);
	l2->setYCoefficients(y2);

	RadEntity2D_ptr r = RadEntity2D::create(l1, l2);
	*/

	while (true) {
		// Get filename
		std::string filename;
		cout << "Please enter a filename: " << endl;
		cin >> filename;
		cout << endl;

		// Clean filename
		if (filename.length() < 1)
		{
			// Default value
			std::string filename = "C:/temp/194003.stl";
		}
		else
		{
			if (filename == "exit") {
				goto EXIT;
			}
			filename = "C:/temp/" + filename;
		}

		// Get rail side
		std::string side;
		Side s;
		while (true)
		{
			cout << "Please choose a side for the rail (l/r): " << endl;
			cin >> side;
			cout << endl;
			
			if (side == "l" || side == "L")
			{
				s = SIDE_LEFT;
				break;
			}
			else if (side == "r" || side == "R")
			{
				s = SIDE_RIGHT;
				break;
			}
			else if (side == "exit")
			{
				goto EXIT;
			}
			else
			{
				cout << "Invalid selection, please try again..." << endl;
			}
		}
		
		Specification spec;
		spec.Mode = MODE_CLEAN;
		spec.Project = "0000001";
		spec.Filename = filename;
		spec.Side = s;

		// Create application
		try {
			Job_ptr jb = Job::create(spec);
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}

		cout << endl;
	}

EXIT:
	cout << "Exiting application... :)" << endl;
}