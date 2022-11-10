#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>



//_____________ОКНО__________________________________________________________________________
#define WINDOW_HEIGHT 720			// высотса окна
#define WINDOW_LENGTH 1280			// длинна окна	
#define TICK 0.0008f				// тик
#define G 3200						// ускорение свободного падения
#define PI 3.1415926536				// пи оно и в африке пи
#define PIXEL 4						// размер одного пикселя в рубах и птице
//_____________ПТИЦ__________________________________________________________________________
#define JUMP_VELOCITY -840			// скорость птицы при прыжке/
#define MAX_ROTATION 90				// максимальный угол наклона морды птицы
#define MIN_ROTATION -25			// минимальный угол наклона морды птицы
#define VELOCITY_ANGLE 400			// скорость изменения наклона морды
#define VELOCITY_GRAN 500			// скорость после которой морда начинает наклонятся
#define HITBOX_X 54					// размер хитбокса по оси X
#define HITBOX_Y 56					// размер хитбокса по оси Y
//_____________ТРУБЫ_________________________________________________________________________
#define VELOCITY_PIPE -240			// скорость труб
#define MIN_DISTANCE_TO_WINDOW 200	// минимальное рассояние между центром проёма и границей окна
#define STARTING_DISTANCE 500		// расстояния от первой рубы до начала экрана(зависит от времяни перед началом игры)
#define DISTANCE_BETWEEN_PIPES 300	// расстояние через которые идут пары труб 
#define HOLE_HEIGHT 200				// высота проёма, в котороё должно пролететь птица
//_____________ЗАДНИЙ ФОН____________________________________________________________________
#define VELOCITY_BACKGROUND -50		// скорость заднего фона

using namespace std;

//для меня
const bool otladka = false;
///////////////////////////

// 1280 * 720

sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Flappy bird");

sf::Texture bird_texture;
sf::Texture lowerpipe_texture;
sf::Texture upperpipe_texture;
sf::Texture background_texture;

struct flappy_bird
{
	// птица имеет размеры 17 * 12 пикселей
	const double high = 11 * PIXEL;
	const double lenth = 16 * PIXEL;

	double velocity_x, velocity_y;
	double center_x, center_y;
	double rotation;

	bool alive;

	sf::Color c;
	sf::RectangleShape shape;

	flappy_bird()
	{
		rotation = 0;

		velocity_x = 0;
		velocity_y = 0;

		center_x = WINDOW_LENGTH / 2;
		center_y = WINDOW_HEIGHT / 2;

		alive = true;

		c = sf::Color(0, 0, 255);


		shape.setPosition(center_x - lenth / 2, center_y - high / 2);
		shape.setSize(sf::Vector2f(lenth, high));
		//shape.setTexture(&bird_texture);
		shape.setRotation(0);
		shape.setFillColor(sf::Color::White);
	}
	void draw()
	{
		//_______расчёт левого верхнего угла прямоугольника т к а=поворот делается относительно него
		double b = atan2(high, lenth);
		double a = rotation / 180 * PI;
		double gipotenuza = sqrt(high * high + lenth * lenth) / 2;
		double corner_x = center_x + gipotenuza * cos(a + b + PI);
		double corner_y = center_y + gipotenuza * sin(a + b + PI);
		//________рисуем птицу____________________
		shape.setPosition(corner_x, corner_y);
		shape.setRotation(rotation);
		window.draw(shape);
		return;
	}
	void next_tick()
	{
		//___________расчёт положение птицы_______________
		if (velocity_y > VELOCITY_GRAN)
			rotation = min(double(MAX_ROTATION), rotation + TICK * VELOCITY_ANGLE);

		center_y = center_y + velocity_y * TICK + ((G * TICK * TICK) / 2.0f);
		velocity_y = velocity_y + G * TICK;
		center_x = center_x + velocity_x * TICK;

		if (center_x > WINDOW_LENGTH)
			velocity_x = -abs(velocity_x);
		if (center_x < 0)
			velocity_x = abs(velocity_x);
		if (center_y > WINDOW_HEIGHT - high / 2)
		{
			velocity_y = -abs(velocity_y) * 0.3;
			center_y = WINDOW_HEIGHT - high / 2;
		}
		return;
	}
	void jump()
	{
		if (alive == true || otladka == true)
		{
			if (center_y < WINDOW_HEIGHT - high / 2)
			{
				velocity_y = JUMP_VELOCITY;
				rotation = MIN_ROTATION;
			}
		}
		return;
	}
	void die()
	{
		if (alive == true)
		{
			jump();
			alive = false;
			shape.setFillColor(sf::Color::Red);

		}
		return;
	}
	void reset()
	{
		rotation = 0;

		velocity_x = 0;
		velocity_y = 0;
		
		center_x = WINDOW_LENGTH / 2;
		center_y = WINDOW_HEIGHT / 2;

		alive = true;

		c = sf::Color(0, 0, 255);
		shape.setPosition(center_x - lenth / 2, center_y - high / 2);
		shape.setSize(sf::Vector2f(lenth, high));
		shape.setTexture(&bird_texture);
		shape.setRotation(0);
		shape.setFillColor(c);
	}
	void set_color(sf::Color color) {
		c = color;
	}
	void update_color() {
		shape.setFillColor(c);
	}
};


struct pipe
{
	// 26 159 пикселей
	const double high = 159 * PIXEL;
	const double lenth = 26 * PIXEL;

	double x1, y1, x2, y2;
	double velocity_x;

	bool type; // 0 - нижняя труба 1 - верхняя 

	sf::Color c;
	sf::RectangleShape shape;

	pipe()
	{
		cout << "+";
	}

	pipe(double _x1, double _y1, bool _type)
	{
		type = _type;
		if (type == 0)
		{
			x1 = _x1;
			x2 = _x1 + lenth;

			y1 = _y1;
			y2 = y1 + high;

			velocity_x = VELOCITY_PIPE;

			shape.setPosition(x1, y1);
			shape.setSize(sf::Vector2f(lenth, high));
			shape.setTexture(&lowerpipe_texture);

			c = sf::Color::White;
			shape.setFillColor(c);
		}
		else
		{
			x1 = _x1;
			x2 = _x1 + lenth;

			y2 = _y1;
			y1 = y2 - high;

			velocity_x = VELOCITY_PIPE;

			shape.setPosition(x1, y1);
			shape.setSize(sf::Vector2f(lenth, high));
			shape.setTexture(&upperpipe_texture);

			c = sf::Color::White;
			shape.setFillColor(c);
		}
	}

	void draw()
	{
		//shape.setTexture(&texture);
		shape.setPosition(x1, y1);
		window.draw(shape);

		return;
	}

	void next_tick()
	{
		x1 = x1 + velocity_x * TICK;
		x2 = x1 + lenth;
		return;
	}

	void stop()
	{
		velocity_x = 0.0f;
		return;
	}

	void move(double _x)
	{
		x1 = _x;
		x2 = x1 + lenth;
		return;
	}

	void update_y(double _y)
	{
		if (type == false)
		{
			y1 = _y;
			y2 = y1 + high;
		}
		else
		{
			y2 = _y;
			y1 = y2 - high;
		}
		return;
	}
	void set_color(sf::Color color) {
		c = color;
	}
	void update_color() {
		shape.setFillColor(c);
	}
};


struct heap_pipes
{
	vector<pipe> pipes;

	int first_pipe;
	int number_of_pipes;
	int last_pipe_x;
	
	sf::Color c;

	heap_pipes()
	{
		c = sf::Color::White;
	}

	void generate()
	{
		number_of_pipes = (WINDOW_LENGTH + 2 * DISTANCE_BETWEEN_PIPES) / (26 * PIXEL + DISTANCE_BETWEEN_PIPES) + 1;
		number_of_pipes *= 2;

		first_pipe = 0;

		for (int i = 0; i < number_of_pipes / 2; ++i)
		{
			int buf_y = rand() % (WINDOW_HEIGHT - 2 * MIN_DISTANCE_TO_WINDOW) + MIN_DISTANCE_TO_WINDOW;

			if (i == 0)
			{
				pipes.push_back(pipe(WINDOW_LENGTH + STARTING_DISTANCE, buf_y - (HOLE_HEIGHT / 2), true));
				pipes.push_back(pipe(WINDOW_LENGTH + STARTING_DISTANCE, buf_y + (HOLE_HEIGHT / 2), false));
			}
			else
			{
				pipes.push_back(pipe(last_pipe_x + DISTANCE_BETWEEN_PIPES, buf_y - (HOLE_HEIGHT / 2), true));
				pipes.push_back(pipe(last_pipe_x + DISTANCE_BETWEEN_PIPES, buf_y + (HOLE_HEIGHT / 2), false));
			}

			last_pipe_x = pipes.back().x2;
		}
		return;
	}

	void clear()
	{
		pipes.resize(0);
		number_of_pipes = 0;
		first_pipe = 0;
		last_pipe_x = 0;
		return;
	}

	void next_tick()
	{
		if (number_of_pipes == 0)
			generate();
		for (int i = 0; i < number_of_pipes / 2; ++i)
		{
			pipes[2 * i].next_tick();
			pipes[2 * i + 1].next_tick();
			if (pipes[2 * i].x2 < 0)
			{
				pipes[2 * i].move(last_pipe_x + DISTANCE_BETWEEN_PIPES);
				pipes[2 * i + 1].move(last_pipe_x + DISTANCE_BETWEEN_PIPES);

				int buf_y = rand() % (WINDOW_HEIGHT - 2 * MIN_DISTANCE_TO_WINDOW) + MIN_DISTANCE_TO_WINDOW;

				pipes[2 * i].update_y(buf_y - (HOLE_HEIGHT / 2));
				pipes[2 * i + 1].update_y(buf_y + (HOLE_HEIGHT / 2));

				last_pipe_x = pipes[2 * i].x2;
				first_pipe = (2 * i + 2) % number_of_pipes;
			}
		}
		last_pipe_x = pipes[(first_pipe - 1 + number_of_pipes) % number_of_pipes].x2;
		//cout << last_pipe_x << endl;
		return;
	}

	void stop()
	{
		for (int i = 0; i < number_of_pipes; ++i)
			pipes[i].stop();
		return;
	}

	void draw()
	{
		for (int i = 0; i < number_of_pipes; ++i)
			pipes[i].draw();
		return;
	}

	void set_color(sf::Color color)
	{
		c = color;
		for (int i = 0; i < pipes.size(); ++i)
			pipes[i].set_color(c);
	}

	void update_color() {
		for (int i = 0; i < pipes.size(); ++i)
			pipes[i].update_color();
	}
};


struct background
{
	// 345 180
	const double length = 345 * PIXEL;
	const double hight = 180 * PIXEL;

	double x1, x2;
	double velocity;
	sf::RectangleShape fon;
	sf::Color c;

	background()
	{
		x1 = 0;
		x2 = x1 + length;
		velocity = VELOCITY_BACKGROUND;
		fon.setSize(sf::Vector2f(length, hight));
		c = sf::Color::White;
		fon.setFillColor(c);
	}

	void download_texture()
	{
		fon.setTexture(&background_texture);
		return;
	}

	void next_tick() {
		x1 = x1 + TICK * velocity;
		x2 = x1 + length;
		if (x2 <= 0)
		{
			x1 += length;
			swap(x1, x2);
		}
		return;
	}

	void draw()
	{
		fon.setPosition(x1, 0);
		window.draw(fon);
		fon.setPosition(x2, 0);
		window.draw(fon);
	}

	void stop()
	{
		velocity = 0;
		return;
	}

	void restart()
	{
		x1 = 0;
		x2 = x1 + length;
		velocity = VELOCITY_BACKGROUND;
	}
	void set_color(sf::Color color) {
		c = color;
	}
	void update_color() {
		fon.setFillColor(c);
	}
};

//_____________ФУНКЦИИ______________
void download_textures();
bool touch(flappy_bird& b, pipe& p);
void bird_vresols(flappy_bird& b);
void next_tick();
void restart();
//__________________________________

flappy_bird bird;
heap_pipes all_pipes;
background sky;

void download_textures()
{
	sf::Texture bird_textureBuffer;
	if (!bird_textureBuffer.loadFromFile("resources/FlappyBird_Bird.png"))
	{
		cout << "PTIZA NE ZAGRUZILOS!!!!" << endl;
		bird.set_color(sf::Color::Yellow);
	}
	bird_texture = bird_textureBuffer;

	sf::Texture upperpipe_textureBuffer;
	if (!upperpipe_textureBuffer.loadFromFile("FlappyBird_UpperPipe.png"))
	{
		cout << "VERHNIYA TRUBA NE ZAGRUZILOS!!!!" << endl;
		all_pipes.set_color(sf::Color(0, 255, 0));

	}
	upperpipe_texture = upperpipe_textureBuffer;

	sf::Texture lowerpipe_textureBuffer;
	if (!lowerpipe_textureBuffer.loadFromFile("H:/Visual Studio 2022/Flappy_bird/Flappy_bird/resources/FlappyBird_LowerPipe.png"))
	{
		cout << "NIZNIYA TRUBA NE ZAGRUZILOS!!!!" << endl;
		all_pipes.set_color(sf::Color(0, 255, 0));
	}
	lowerpipe_texture = lowerpipe_textureBuffer;

	sf::Texture background_textureBuffer;
	if (!background_textureBuffer.loadFromFile("Flappy_bird/resources/FlappyBird_Background.png"))
	{
		cout << "FON NE ZAGRUZILOS!!!!" << endl;
		sky.set_color(sf::Color(200, 200, 255));
	}
	background_texture = background_textureBuffer;

	sky.download_texture();

	return;
}


bool touch(flappy_bird& b, pipe& p)
{
	double x1, y1, x2, y2;

	x1 = p.x1 - HITBOX_X / 2;
	x2 = p.x2 + HITBOX_X / 2;
	y1 = p.y1 - HITBOX_Y / 2;
	y2 = p.y2 + HITBOX_Y / 2;

	if (x1 < b.center_x && b.center_x < x2 && y1 < b.center_y && b.center_y < y2)
		return true;
	if (b.center_y >= WINDOW_HEIGHT - b.high / 2)
		return true;
	return false;
}


void bird_vresols(flappy_bird& b)
{
	if (b.alive == false) {
		return;
	}
	bool ans = false;
	for (int i = 0; i < all_pipes.number_of_pipes; ++i)
	{
		if (touch(b, all_pipes.pipes[i]))
		{
			if (otladka == true)
				continue;
			b.die();
			all_pipes.stop();
			sky.stop();
			return;
		}
	}
	return;
}


void next_tick()
{
	bird.next_tick();
	all_pipes.next_tick();
	bird_vresols(bird);
	sky.next_tick();
	return;
}


void restart()
{
	bird.reset();
	all_pipes.clear();
	all_pipes.generate();
	sky.restart();
	return;
}

void update_all_color() {
	bird.update_color();
	all_pipes.update_color();
	sky.update_color();
}


int main()
{

	cout << _chdir("H:/Visual Studio 2022/Flappy_bird/Flappy_bird/resources") << endl;

	srand(time(NULL));

	download_textures();

	bird.reset(); // что бы загрузить текстуры

	all_pipes.generate();

	update_all_color();

	bool pr_space = false;
	bool now_space = false;
	bool pr_r = false;
	bool now_r = false;

	while (window.isOpen())
	{
		// считывание пробела + прыжок
		now_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		if (now_space == true && pr_space == false)
			bird.jump();
		pr_space = now_space;

		// считывание рестарта
		now_r = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		if (now_r == true && pr_r == false)
		{
			restart();
			bird.reset();
		}
		pr_r = now_r;
		//_____________________________________________________________

		next_tick();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// рисуем тута//
		window.clear(sf::Color::Black);

		sky.draw();
		all_pipes.draw();
		bird.draw();

		window.display();

	}

	return 0;
}