using namespace std;

#include <iostream>
#include "main.h"
#include "staircase.h"

int main()
{
	while (true) {
		std::string filename;
		cout << "Please enter a filename: " << endl;
		cin >> filename;

		if (filename.length() < 1)
		{
			std::string filename = "C:/temp/55912.pts";
		}
		else
		{
			if (filename == "exit") {
				break;
			}
			filename = "C:/temp/" + filename;
		}

		Staircase_ptr sc = Staircase::create(filename);

		cout << endl;
		cout << "SUMMARY:" << endl;
		cout << "Points: " << sc->getPoints()->size() << endl;
		cout << "Layers: " << sc->getLayers()->size() << endl;
		cout << "Features: " << sc->getFeatures()->size() << endl;
		cout << endl;

		Features_ptr features = sc->getFeatures();
		for (int i = 0; i < features->size(); i++)
		{
			FeatureType type = features->get(i)->getType();
			cout << "Feature " << (i + 1) << " is a ";
			switch (type)
			{
			case FT_START:
				cout << "START" << endl;
				break;
			case FT_END:
				cout << "END" << endl;
				break;
			case FT_STRAIGHT:
				cout << "STRAIGHT consisting of " << features->get(i)->getLayers()->size();
				if (features->get(i)->getLayers()->size() > 1)
				{
					cout << " steps";
				}
				else
				{
					cout << " step";
				}
				cout << endl;
				break;
			case FT_WINDER:
				cout << "WINDER consisting of "  << features->get(i)->getLayers()->size();
				if (features->get(i)->getLayers()->size() > 1)
				{
					cout << " steps";
				}
				else
				{
					cout << " step";
				}
				cout << endl;
				break;
			case FT_LANDING_FLAT:
				cout << "FLAT LANDING" << endl;
				break;
			case FT_UNKNOWN:
				cout << "UNKNOWN" << endl;
				break;
			}
		}

		cout << endl << endl;
	}
}