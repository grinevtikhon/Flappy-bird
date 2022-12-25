#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "Car.h"
#include "MyConstants.h"

using namespace std;

int main()
{

	cout.setf(ios::fixed);
	cout.precision(10);
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Gonochki");

	Car car;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			car.gas();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			car.left_turn();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			car.right_turn();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			car.brake();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			car.nitro();
		}

		car.next_tick();

		car.draw(window);

		window.display();
	}

	cout << "Hello World!\n";
}