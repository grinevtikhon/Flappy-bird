#include "MyGraphic.h"

MyGraphic::MyGraphic(string _name)
{
	name = _name;

	windowHeight = 600;
	windowLength = 600;

	zoomX = 1;
	zoomY = 1;

	create_window();
}


void MyGraphic::create_window()
{
	window.create(sf::VideoMode(windowLength, windowHeight), "da");
}

void MyGraphic::set_zoomX(long double _zoomX) {
	zoomX = _zoomX;
}
void MyGraphic::set_zoomY(long double _zoomY) {
	zoomY = _zoomY;
}

void MyGraphic::draw_dot(long double _x, long double _y, long double _radius, sf::Color _c)
{
	_x = (_x)*zoomX + long double(windowLength) / 2.0;
	_y = (-1.0) * (_y)*zoomY + long double(windowHeight) / 2.0;
	sf::CircleShape dot(_radius);
	dot.setFillColor(_c);
	dot.setPosition(_x - _radius / 2.0, _y - _radius / 2.0);
	window.draw(dot);
}

void MyGraphic::draw_axis()
{
	sf::RectangleShape x_axis(sf::Vector2f(windowLength, 1));
	x_axis.setPosition(0.0, long double(windowHeight) / 2.0);
	x_axis.setFillColor(sf::Color::Red);

	sf::RectangleShape y_axis(sf::Vector2f(1, windowHeight));
	y_axis.setPosition(long double(windowLength) / 2.0, 0.0);
	y_axis.setFillColor(sf::Color::Red);

	window.draw(x_axis);
	window.draw(y_axis);

	return;
}

void MyGraphic::display()
{
	window.display();
}

void MyGraphic::clear()
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	window.clear();
	draw_axis();
}

void MyGraphic::draw_function(long double(*_func)(long double), long double _thickness, long double _accuracy, sf::Color _c)
{
	for (int i = 0; i < int(_accuracy * windowLength); ++i) {
		long double l = -long double(windowLength) / (zoomX * 2.0);
		long double r = long double(windowLength) / (zoomX * 2.0);
		long double x = l + i * (r - l) / (_accuracy * windowLength);
		long double y = _func(x);
		draw_dot(x, y, _thickness, _c);
	}

	return;
}

void MyGraphic::draw_function(Network& _n, long double _thickness, long double _accuracy, sf::Color _c)
{
	for (int i = 0; i < int(_accuracy * windowLength); ++i) {
		long double l = -long double(windowLength) / (zoomX * 2.0);
		long double r = long double(windowLength) / (zoomX * 2.0);
		long double x = l + i * (r - l) / (_accuracy * windowLength);
		long double y = _n.obrfun(_n.fuction({x}).back());
		draw_dot(x, y, _thickness, _c);
	}

	return;
}

void MyGraphic::draw_dot(vector<long double> _x, vector<long double> _y, long double _radius, sf::Color _c)
{
	for (int i = 0; i < _x.size(); ++i)
	{
		draw_dot(_x[i], _y[i], _radius, _c);
	}

	return;
}

void MyGraphic::draw_dot(vector<pair<long double, long double>> _dot, long double _radius, sf::Color _c)
{
	for (int i = 0; i < _dot.size(); ++i)
	{
		draw_dot(_dot[i].first, _dot[i].second, _radius, _c);
	}

	return;
}
