#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "MyGraphic.h"
#include "Network.h"
#include "Generation.h"

using namespace std;

double foo(double x)
{
	return pow(sin(x), 7);
}



int main()
{

	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));

	MyGraphic da;

	vector<int> sloi{ 1,5,  1 };

	Network net(sloi);

	for(double i = 100; true; i += 1)
	{
		da.set_zoomX(i);
		da.set_zoomY(i);

		da.clear();
		da.draw_function(foo, 1, 10, sf::Color::Blue);
		da.draw_function( net , 1, 10, sf::Color::Green);
		da.display();

	}
	
}