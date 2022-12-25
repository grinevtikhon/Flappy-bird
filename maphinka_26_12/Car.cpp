#include "Car.h"

Car::Car() {
	x = 250;
	y = 250;
	v = 0;
	omega = 0; // anglee speed
	angle = 0;

	a_trenia = -2;
	a_gas = 0;
	a_brake = 0;
	a_nitro = 0;

	max_speed = 300.0;

	shape.setSize(sf::Vector2f(20, 10));
	shape.setFillColor(sf::Color::Red);

}

void Car::next_tick()
{
	angle += omega * TICK;
	x += v * cos(angle) * TICK;
	y += v * sin(angle) * TICK;
	if (x > 1000) x -= 1000;
	if (x < 0) x += 1000;
	if (y > 1000) y -= 1000;
	if (y < 0) y += 1000;
	a_vozd = -v * v * 0.001;
	v = max(0.0, v + TICK*(a_trenia + a_gas + a_brake + a_nitro + a_vozd));
	//v = min(v, 1e9);
	omega = 0;
	a_gas = 0;
	a_brake = 0;
	a_nitro = 0;
}

void Car::gas()
{
	a_gas = 6;
}

void Car::right_turn()
{
	omega = 0.5;
}

void Car::left_turn()
{
	omega = -0.5;
}

void Car::brake()
{
	a_brake = -11;
}

void Car::nitro()
{
	a_nitro = 30;
}



void Car::draw(sf::RenderWindow& _window)
{

	double fi = angle / PI * 180;
	double x1 = x - cos(angle) * shape.getSize().x / 2 + cos(PI / 2 - angle) * shape.getSize().y / 2;
	double y1 = y - sin(angle) * shape.getSize().x / 2 - sin(PI / 2 - angle) * shape.getSize().y / 2;

	shape.setRotation(fi);
	shape.setPosition(x1, y1);
	_window.draw(shape);

	return;
}
