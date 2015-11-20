using namespace std;

#include <iostream>
#include "main.h"
#include "job.h"

int main()
{
	while (true) {
		// Get filename
		std::string filename;
		cout << "Please enter a filename: " << endl;
		cin >> filename;

		// Clean filename
		if (filename.length() < 1)
		{
			// Default value
			std::string filename = "C:/temp/55912.pts";
		}
		else
		{
			if (filename == "exit") {
				break;
			}
			filename = "C:/temp/" + filename;
		}

		// Create application
		try {
			Job_ptr jb = Job::create(filename);
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}

		cout << endl;
	}
}