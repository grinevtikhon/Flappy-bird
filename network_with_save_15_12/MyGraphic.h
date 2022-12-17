#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "Network.h"

using namespace std;

class MyGraphic
{
public:

	int windowHeight;
	int windowLength;

	long double zoomX;
	long double zoomY;

	string name;

	sf::RenderWindow window;

	MyGraphic(string _name);

	void create_window();

	void set_zoomX(long double _zoomX);
	void set_zoomY(long double _zoomY);

	void draw_dot(long double _x, long double _y, long double _radius, sf::Color _c);

	void draw_axis();

	void display();
	void clear();

	void draw_function(long double(*_func)(long double), long double _thickness, long double _accuracy, sf::Color _c);
	void draw_function(Network& _n, long double _thickness, long double _accuracy, sf::Color _c);

	void draw_dot(vector<long double> _x, vector<long double> _y, long double _radius, sf::Color _c);
	void draw_dot(vector<pair<long double, long double>> _dot, long double _radius, sf::Color _c);
};
