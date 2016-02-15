using namespace std;

#include <iostream>
#include "main.h"
#include "job.h"

#include "point.h"
#include "entity.h"

int main()
{
	Point_ptr p1 = Point::create(-4.0,-2.0,0.0);
	Point_ptr p2 = Point::create(-2.0,-4.0,0.0);
	Point_ptr p3 = Point::create(2.0,4.0,0.0);
	Point_ptr p4 = Point::create(4.0,2.0,0.0);

	Points_ptr p = Points::create();
	p->add(p1);
	p->add(p2);
	p->add(p3);
	p->add(p4);

	LineEntity2D_ptr l = LineEntity2D::create(p, Entity2D::FIT2D_LEFT);
	LineEntity2D_ptr l2 = LineEntity2D::createParallel(l, 1.0);

	while (true)
	{

	}

	/*
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
	*/
}