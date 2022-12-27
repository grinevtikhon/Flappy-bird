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
	return (sin(x) + 1) /2;
}

vector<int> sloi{ 1, 20, 20, 10,  1 };

vector<double> test;
vector<double> ans;

vector<pair<vector<double>, vector<double>>> xmpl;

int main()
{

	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));

	MyGraphic window("ABOBA");
	window.set_zoomX(10);
	window.set_zoomY(100);

	Network diana(sloi);

	for (double i = -22; i <= 22; i += 0.2)
	{
		test.push_back(i);
	}

	//for (double i = 17; i <= 20; i += 0.2)
	//{
	//	test.push_back(i);
	//}

	for (int i = 0; i < test.size(); ++i)
	{
		ans.push_back(fun(test[i]));

		xmpl.push_back({ {test[i]}, {ans[i]} });

		diana.examples.push_back({ {test[i]}, {ans[i]} });
	}



	int st = 0;

	double pr_er = 100000;
	double er = 100000;
	while (true)
	{


		
		
		if (st % 1000 == 0)
		{
			window.clear();

			

			window.draw_function(fun, 0.4, 10, sf::Color::Cyan);

			window.draw_dot(test, ans, 2.2, sf::Color::Magenta);

			window.draw_function(diana, 1.2, 10, sf::Color::Green);

			window.display();

			cout << diana.global_error << endl;

			
		}

		//pr_er = er;
		//er = diana.global_error;
		//if (er > pr_er)
		//{
		//	diana.learn_rate /= 2;
		//}
		//else {
		//	diana.learn_rate = min(1.1* diana.learn_rate, 10.0);
		//}

		diana.backPropagate();


		++st;
	}

}