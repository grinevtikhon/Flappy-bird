#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//_____________ОКНО______________________________
#define WINDOW_HEIGHT 720			// высотса окна
#define WINDOW_LENGTH 1280			// длинна окна	
#define TICK 0.001f					// тик
#define G 2400						// ускорение свободного падения
#define PI 3.1415926536				// пи оно и в африке пи
#define PIXEL 4						// размер одного пикселя в рубах и птице
//_____________ПТИЦ_______________________________
#define JUMP_VELOCITY -700			// скорость птицы при прыжке
#define MAX_ROTATION 90				// максимальный угол наклона морды птицы
#define MIN_ROTATION -30			// минимальный угол наклона морды птицы
#define VELOCITY_ANGLE 500			// скорость изменения наклона морды
#define VELOCITY_GRAN 400			// скорость после которой морда начинает наклонятся
//_____________ТРУБЫ_____________________________
#define VELOCITY_PIPE -300			// скорость труб
#define MIN_DISTANCE_TO_WINDOW 200	// минимальное рассояние между центром проёма и границей окна
#define STARTING_DISTANCE -500		// расстояния от первой рубы до начала экрана(зависит от времяни перед началом игры)
#define DISTANCE_BETWEEN_PIPES 300	// расстояние через которые идут пары труб 
#define HOLE_HEIGHT 200				// ... высота проёма, в котороё должно пролететь птица

using namespace std;

//для меня
const bool otladka = false;
//////////////////////////
const int high_grass = 50;
 
//_____________ФУНКЦИИ______________
void stop_all_pipes();
/*
bool touch(flappy_bird &b, pipe &p);
void bird_vresols(flappy_bird &b);
void generate_pipe();
void delete_pipe();
void delete_all_pipes();
void stop_all_pipes();
void update_all_pipes();
void draw_all_pipes();
void next_tick();
void restart();
*/
//__________________________________
// 1280 * 720

sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Flappy bird");

struct flappy_bird
{
	// птица имеет размеры 17 * 12 пикселей
	const double high = 12 * PIXEL;
	const double lenth = 17 * PIXEL;
	double velocity_x, velocity_y;
	double center_x, center_y;
	double rotation;
	bool alive;
	sf::Color c;
	sf::RectangleShape shape;
	sf::Texture texture;
	flappy_bird() {
		rotation = 0;
		velocity_x = 0;
		velocity_y = 0;
		center_x = WINDOW_LENGTH / 2;
		center_y = WINDOW_HEIGHT / 2;
		alive = true;

		sf::Texture bird_textureBuffer;
		if (!bird_textureBuffer.loadFromFile("resources/FlappyBird_Bird.png"))
		{
			cout << "PTITA NE ZAGRUZILOS!!!!";
		}
		texture = bird_textureBuffer;

		c = sf::Color(0, 0, 255);
		shape.setPosition(center_x - lenth / 2, center_y - high / 2);
		shape.setSize(sf::Vector2f(lenth, high));
		shape.setTexture(&texture);
		shape.setRotation(0);
	} 
	void draw() {
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
	void next_tick() {
		//___________расчёт положение птицы_______________
		if (velocity_y > VELOCITY_GRAN) {
			rotation = min(double(MAX_ROTATION), rotation + TICK * VELOCITY_ANGLE);
		}
		center_y = center_y + velocity_y * TICK + ((G * TICK * TICK) / 2.0f);
		velocity_y = velocity_y + G * TICK;
		center_x = center_x + velocity_x * TICK;
		if (center_x > WINDOW_LENGTH) {
			velocity_x = -abs(velocity_x);
		}
		if (center_x < 0) {
			velocity_x = abs(velocity_x);
		}
		if (center_y > WINDOW_HEIGHT - high /2) {
			velocity_y = -abs(velocity_y);
		} 
		return;
	}
	void jump() {
		if (alive == true || otladka == true) {
			velocity_y = JUMP_VELOCITY;
			rotation = MIN_ROTATION;
		}
		return;
	}
	void die() {
		if (alive == true) {
			this->jump();
			alive = false;
			c = sf::Color::Red;
		}
		return;
	}
	void reset() {
		rotation = 0;
		velocity_x = 0;
		velocity_y = 0;
		center_x = WINDOW_LENGTH / 2;
		center_y = WINDOW_HEIGHT / 2;
		alive = true;

		c = sf::Color(0, 0, 255);
		shape.setPosition(center_x - lenth / 2, center_y - high / 2);
		shape.setSize(sf::Vector2f(lenth, high));
		shape.setTexture(&texture);
		shape.setRotation(0);
	}
};
// птица готова


struct pipe {
	// 26 159 пикселей
	const double high = 159 * PIXEL;
	const double lenth = 26 * PIXEL;
	double x1, y1, x2, y2;
	double velocity_x;
	bool type; // 0 - нижняя труба 1 - верхняя 
	sf::RectangleShape shape;
	sf::Texture texture;
	pipe(double _x1, double _y1, bool _type) {
		type = _type;
		if (type == 0){
			x1 = _x1;
			x2 = _x1 + lenth;
			y1 = _y1;
			y2 = y1 + high;
			velocity_x = VELOCITY_PIPE;

			sf::Texture pipe_textureBuffer;
			if (!pipe_textureBuffer.loadFromFile("resources/FlappyBird_LowerPipe.png"))
			{
				cout << "TRUBA NE ZAGRUZILOS!!!!";
			}
			texture = pipe_textureBuffer;
			shape.setPosition(x1, y1);
			shape.setSize(sf::Vector2f(lenth, high));
			shape.setTexture(&texture);
		}
		else {
			x1 = _x1;
			x2 = _x1 + lenth;
			y2 = _y1;
			y1 = y2 - high;
			velocity_x = VELOCITY_PIPE;

			sf::Texture pipe_textureBuffer;
			if (!pipe_textureBuffer.loadFromFile("resources/FlappyBird_UpperPipe.png"))
			{
				cout << "TRUBA NE ZAGRUZILOS!!!!";
			}
			texture = pipe_textureBuffer;
			shape.setPosition(x1, y1);
			shape.setSize(sf::Vector2f(lenth, high));
			shape.setTexture(&texture);
		}
	}
	void draw() {
		//shape.setTexture(&texture);
		shape.setPosition(x1, y1);
		window.draw(shape);

		return;
	}
	void next_tick() {
		x1 = x1 + velocity_x * TICK;
		x2 = x1 + lenth;
		return;
	}
	void stop() {
		velocity_x = 0.0f;
		return;
	}
};

flappy_bird bird;
queue <pipe> pipes;

bool touch(flappy_bird &b, pipe &p) {
	double x1, y1, x2, y2;
	x1 = p.x1 - b.lenth / 2;
	x2 = p.x2 + b.lenth / 2;
	y1 = p.y1 - b.high / 2;
	y2 = p.y2 + b.high / 2;
	if (x1 < b.center_x && b.center_x < x2 && y1 < b.center_y && b.center_y < y2) {
		return true;
	}
	return false;
}

void bird_vresols(flappy_bird &b) {
	bool ans = false;
	for (int i = 0; i < pipes.size(); ++i) {
		if (ans == false) {
			if (touch(b, pipes.front())) {
				ans = true;
			}
		}
		pipes.push(pipes.front());
		pipes.pop();
	}
	if (ans == true) {
		b.die();
		stop_all_pipes();
	}
	return;
}

void generate_pipe() {
	int buf_y = rand() % (WINDOW_HEIGHT - 2 * MIN_DISTANCE_TO_WINDOW) + MIN_DISTANCE_TO_WINDOW;
	if (pipes.empty()) {
		pipes.push(pipe(WINDOW_LENGTH + STARTING_DISTANCE, buf_y - (HOLE_HEIGHT / 2), true));
		pipes.push(pipe(WINDOW_LENGTH + STARTING_DISTANCE, buf_y + (HOLE_HEIGHT / 2), false));
	}
	if (pipes.back().x2 < WINDOW_LENGTH) {
		double buf = pipes.back().x2;
		pipes.push(pipe(buf + DISTANCE_BETWEEN_PIPES, buf_y - (HOLE_HEIGHT / 2), true));
		pipes.push(pipe(buf + DISTANCE_BETWEEN_PIPES, buf_y + (HOLE_HEIGHT / 2), false));
	}
	return;
}

void delete_pipe() {
	if (!pipes.empty()) {
		if (pipes.front().x2 < 0) {
			pipes.pop();
			delete_pipe();
		}
	}
	return;
}

void delete_all_pipes() {
	while (!pipes.empty()) {
		pipes.pop();
	}
}

void stop_all_pipes() {
	for (int i = 0; i < pipes.size(); ++i) {
		pipes.front().stop();
		pipes.push(pipes.front());
		pipes.pop();
	}
	return;
}

void update_all_pipes() {
	for (int i = 0; i < pipes.size(); ++i) {
		pipes.front().next_tick();
		pipes.push(pipes.front());
		pipes.pop();
	}
	return;
}

void draw_all_pipes() {
	for (int i = 0; i < pipes.size(); ++i) {
		pipes.front().draw();
		pipes.push(pipes.front());
		pipes.pop();
	}
}

void next_tick() {
	bird.next_tick();
	generate_pipe();
	delete_pipe();
	update_all_pipes();
	bird_vresols(bird);
	return;
}

void restart() {
	bird.reset();
	delete_all_pipes();
	return;
}

int main()
{
	srand(time(NULL));

	bool pr_space = false;
	bool now_space = false;
	bool pr_r = false;
	bool now_r = false;
	pipe a(WINDOW_LENGTH / 3 * 2, WINDOW_HEIGHT / 2 - 100, true);
	pipe b(WINDOW_LENGTH / 3 * 2, WINDOW_HEIGHT / 2 + 100, false);
	while (window.isOpen())
	{
		// считывание пробела + прыжок
		now_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		if (now_space == true && pr_space == false) {
			bird.jump();
		}
		pr_space = now_space;
		// мчитывание рестарта
		now_r = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		if (now_r == true && pr_r == false) {
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

		// рисуем тута
		window.clear(sf::Color::Black);

		draw_all_pipes();
		bird.draw();
		//cout << pipes.size() << endl;

		//for (int i = 0; i < pipes.size(); ++i) {
		//	rectangle.setPosition(pipes.front().x1, pipes.front().y1);
		//	rectangle.setSize(sf::Vector2f(pipes.front().x2 - pipes.front().x1, pipes.front().y2 - pipes.front().y1));
		//	window.draw(rectangle);
		//	//cout << pipes.front().x1 << " | " << pipes.front().x2 << " | " << pipes.front().y1 << " | " << pipes.front().y2 << endl;
		//	pipes.push(pipes.front());
		//	pipes.pop();
		//}
		//cout << pipes.size() << " | " << pipes.back().x2 << " | " << pipes.front().x2 << endl;

		//sf::RectangleShape ground;
		//ground.setPosition(0, Height - high_grass);
		//ground.setSize(sf::Vector2f(Length, high_grass));
		//ground.setFillColor(sf::Color(65, 25, 0));
		//window.draw(ground);

		//circle.setFillColor(sf::Color::Yellow);
		//circle.setPosition(bird.x - bird.r, bird.y - bird.r);
		//window.draw(circle);


		window.display();
	}

	return 0;
}