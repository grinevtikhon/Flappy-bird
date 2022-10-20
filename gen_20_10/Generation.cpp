#include "Generation.h"

Generation::Generation(vector<int> _v, int _group_size, int _n, double _dispersion)
{

	group_size = _group_size;

	dispersion = _dispersion;

	for (int i = 0; i < _n * _group_size; ++i)
		gen.push_back(_v);
}

void Generation::calculate_generation()
{
	for (int i = 0; i < gen.size(); ++i)
	{
		gen[i].setInput(input);
		gen[i].setAnswer(ans);
		gen[i].calculate_mistake();
	}

	sort(gen.begin(), gen.begin());

	return;
}

void Generation::set_input(vector<double> _v)
{
	input = _v;
}

vector<double> Generation::get_input()
{
	return input;
}

void Generation::set_ans(vector<double> _v)
{
	ans = _v;
}

vector<double> Generation::get_ans()
{
	return ans;
}

void Generation::generate_next_generation()
{
	int j = gen.size() - 1;
	for (int i = 0; i < group_size; ++i)
	{
		gen[i].mutate(gen[j], dispersion);
	}
}
