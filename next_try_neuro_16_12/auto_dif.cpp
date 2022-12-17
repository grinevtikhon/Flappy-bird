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

using namespace std;

double fun(double x)
{
	return sin(x);
}

vector<int> sloi{ 1, 5, 5,1 };

vector<double> test;
vector<double> ans;

vector<pair<vector<double>, vector<double>>> xmpl;

int main()
{

	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));

	MyGraphic window("ABOBA");
	window.set_zoomX(40);
	window.set_zoomY(40);

	Network diana(sloi);

	for (double i = 0; i <= 1; i += 0.02)
	{
		test.push_back(i);
	}

	for (int i = 0; i < test.size(); ++i)
	{
		ans.push_back(fun(test[i]));

		xmpl.push_back({ {test[i]}, {ans[i]} });

		diana.examples.push_back({ {test[i]}, {ans[i]} });
	}

	

	

	while (true)
	{
		window.clear();

		window.draw_function(diana, 0.8, 10, sf::Color::Green);

		window.draw_function(fun, 0.4, 10, sf::Color::Cyan);

		window.draw_dot(test, ans, 2.8 , sf::Color::Magenta);

		window.display();

		diana.backPropagate();

		cout << diana.global_error << endl;
	
	}

}