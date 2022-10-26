#include "Barriers.h"

Barriers::Barriers()
{
	generate_pipes();
	update_pipes();


}

void Barriers::generate_pipes()
{
	amount = Length / horizontal_distance + 5;

	for (int i = 0; i < amount; ++i)
		pipes.push_back({Pipe(), Pipe()});
	
}

void Barriers::next_tick()
{
	for (int i = 0; i < amount; ++i)
	{
		pipes[i].first.next_tick();
		pipes[i].second.next_tick();
	}

	update_pipes();

	return;
}

void Barriers::update_pipes()
{

	while (true)
	{
		if (pipes[first_element].first.x2 > -horizontal_distance)
			break;

		int x = max(pipes[(first_element + 1) % amount].first.x2 + horizontal_distance, 1.5 * Length);
		int y = rand() % (Height - 2 * min_dist) + min_dist;

		pipes[first_element].first.set_position(x, 0, y - vertical_distance / 2);
		pipes[first_element].first.set_position(x, Height, y + vertical_distance / 2);

		first_element = (first_element + 1) % amount;

	}

	return;

}

void Barriers::stop_pipes()
{
	for (int i = 0; i < amount; ++i)
	{
		pipes[i].first.stop();
		pipes[i].second.stop();
	}

	return;
}

void Barriers::start_pipes()
{
	for (int i = 0; i < amount; ++i)
	{
		pipes[i].first.start();
		pipes[i].second.start();
	}

	return;
}

void Barriers::reset()
{
	pipes.resize(0);

	amount = Length / horizontal_distance + 5;

	for (int i = 0; i < amount; ++i)
		pipes.push_back({ Pipe(), Pipe() });

	return;
}
