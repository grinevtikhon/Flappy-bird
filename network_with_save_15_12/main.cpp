#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
#include <queue>

#include "MyGraphic.h"
#include "Network.h"
//#include "Generation.h"

//#include "Flappy_bird.h"
//#include "Pipe.h"
//#include "Barriers.h"
//#include "Scoreboard.h"


using namespace std;


vector<int> sloi{ 1, 5, 5, 5, 1 };

long double etolon_fuction(long double x)
{
	long double y = pow(x, 3) / 10;
	return y;
}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(20);
	srand(time(NULL));

	MyGraphic window("my geogebra -_-");

	Network arcady(sloi);
	//arcady.accuracy = 1;

	vector<pair<long double, long double>> example{ {1, 1}, {2, 2}, {3, 2}, {-7, 6}, {-3, 2}, {5, 5}, };

	//for (long double i = -5; i <= 5; i += 0.001)
	//{
	//	example.push_back({ i, etolon_fuction(i) });
		//arcady.add_example({ i }, { etolon_fuction(i) });
	//}
	for (int i = 0; i < example.size(); ++i)
	{
		arcady.add_example({ example[i].first }, { arcady.fun(example[i].second) });
	}

	window.set_zoomX(10);
	window.set_zoomY(10);
	long long step = 0;
	while (true)
	{
		
		window.clear();

		//window.draw_function(etolon_fuction, 1, 10, sf::Color::Blue);

		arcady.update_network();
		if (step % 1 == 0)
		{
			cout << arcady.get_mistake() << "\t" << arcady.accuracy << endl;

			window.draw_function(arcady, 1, 20, sf::Color::Cyan);


			window.draw_dot(example, 2, sf::Color(228, 0, 224));

			window.display();
		}
		if (step % 10 == 0)
		{
			arcady.save_network_in_file("H:\\Visual Studio 2022\\Flappy_bird\\Flappy_bird\\networks\\3.txt");
		}
		++step;
		
	}

}















/*
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

	sf::Clock clock;

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
		
		car.next_tick(clock.restart().asSeconds());

		car.draw(window);

		window.display();
	}

	cout << "Hello World!\n";
}
*/