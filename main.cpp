using namespace std;

#include <iostream>
#include "main.h"
#include "staircase.h"

int main()
{
	std::string filename = "C:/temp/55912.pts";
	Staircase_ptr sc = Staircase::create(filename);

	cout << "Points: " << sc->getPoints()->size() << endl;
	cout << "Layers: " << sc->getLayers()->size() << endl;
	cout << "Features: " << sc->getFeatures()->size() << endl;

	// pause
	int i;
	cin >> i;
}