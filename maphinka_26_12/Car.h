#pragma once 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "MyConstants.h"

using namespace std;

class Car
{

public:


	double x, y;
	double v;
	double angle;
	double omega;
	double a_trenia;
	double a_brake;
	double a_gas;
	double a_nitro;
	double a_vozd;
	double max_speed;
	sf::RectangleShape shape;

	Car();

	void next_tick();

	void gas();

	void right_turn();

	void left_turn();

	void brake();

	void nitro();

	void draw(sf::RenderWindow& _window);
};

