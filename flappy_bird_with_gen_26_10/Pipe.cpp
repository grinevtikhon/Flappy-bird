#include "Pipe.h"

Pipe::Pipe()
{
	x1 = -1000;
	x2 = x1 + width_pipe;
	y1 = 0;
	y2 = 0;
	v_x = 0;
}

Pipe::Pipe(double _x1, double _y1, double _y2)
{
	x1 = _x1;
	x2 = _x1 + width_pipe;
	y1 = min(_y1, _y2);
	y2 = max(_y2, _y2);
	v_x = 0;
}

void Pipe::set_position(double _x1, double _y1, double _y2)
{
	x1 = _x1;
	x2 = _x1 + width_pipe;
	y1 = min(_y1, _y2);
	y2 = max(_y2, _y2);

	return;
}

void Pipe::next_tick()
{
	x1 = x1 + v_x * tick;
	x2 = x1 + width_pipe;

	return;
}

void Pipe::stop()
{
	v_x = 0;

	return;
}

void Pipe::start()
{
	v_x = -300;

	return;
}
