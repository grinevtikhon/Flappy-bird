#include "Network.h"

#define start_accuracy 1
#define kostia 1


long double Network::fun(long double x)
{



	//if (x <= 0)
	//	return -1.0 / (x - 2.0);
	//else
	//	return  1.0 - 1.0 / (x + 2.0);

	return max(long double(0.0), x);

	//return 1.0f / (1 + pow(2.7182818284, -x)); // sigma function
}

long double Network::diffun(long double x)
{

	

	//if (x <= 0)
	//	return 1.0 / ((x - 2.0) * (x - 2.0));
	//else
	//	return  1.0 / ((x + 2.0) * (x + 2.0));

	if (x < 0)
		return 0;
	else
		return 1;

	//return pow(2.7182818284, x) / pow(pow(2.7182818284, x) + 1, 2);
}

long double Network::obrfun(long double y)
{

	return y;

	if (y <= 0)
		return 2.0 - 1.0 / y;
	else
		return (1.0 / (1.0 - y)) - 2;
	return -log((1.0 / y) - 1);
}

Network::Network(vector<int> _v)
{
	sloi = _v;

	accuracy = start_accuracy;

	prev_mistake = 10e18;

	value.resize(_v.size());
	for (int i = 0; i < _v.size(); ++i)
		value[i].resize(_v[i], 0);

	delta.resize(_v.size());
	for (int i = 0; i < _v.size(); ++i)
		delta[i].resize(_v[i], 0);

	bias.resize(_v.size());
	bias_change.resize(_v.size());
	for (int i = 0; i < bias.size(); ++i)
	{
		bias[i].resize(_v[i], 0);
		bias_change[i].resize(_v[i], 0);
	}

	w.resize(_v.size() - 1);
	w_change.resize(_v.size() - 1);
	for (int i = 0; i < w.size(); ++i)
	{
		w[i].resize(_v[i]);
		w_change[i].resize(_v[i]);
		for (int j = 0; j < w[i].size(); ++j)
		{
			w[i][j].resize(_v[i + 1], 0);
			w_change[i][j].resize(_v[i + 1], 0);
		}
	}

	generateRandomBias();
	generateRandomW();
}

Network::Network(string _path)
{

	ifstream file (_path);

	file >> accuracy;


	prev_mistake = 10e18;

	int sloi_size;
	
	file >> sloi_size;

	sloi.resize(sloi_size);

	for (int i = 0; i < sloi.size(); ++i)
	{
		file >> sloi[i];
	}

	value.resize(sloi.size());
	for (int i = 0; i < sloi_size; ++i)
	{
		value[i].resize(sloi[i], 0);
	}

	delta.resize(sloi.size());
	for (int i = 0; i < sloi.size(); ++i)
	{
		delta[i].resize(sloi[i], 0);
	}

	bias.resize(sloi.size());
	bias_change.resize(sloi.size());
	for (int i = 0; i < bias.size(); ++i)
	{
		bias[i].resize(sloi[i], 0);
		bias_change[i].resize(sloi[i], 0);
	}

	w.resize(sloi.size() - 1);
	w_change.resize(sloi.size() - 1);
	for (int i = 0; i < w.size(); ++i)
	{
		w[i].resize(sloi[i]);
		w_change[i].resize(sloi[i]);
		for (int j = 0; j < w[i].size(); ++j)
		{
			w[i][j].resize(sloi[i + 1], 0);
			w_change[i][j].resize(sloi[i + 1], 0);
		}
	}


	for (int i = 0; i < bias.size(); ++i)
		for (int j = 0; j < bias[i].size(); ++j)
			file >> bias[i][j];


	for (int i = 0; i < w.size(); ++i)
		for (int j = 0; j < w[i].size(); ++j)
			for (int k = 0; k < w[i][j].size(); ++k)
				file >> w[i][j][k];

	file.close();

}

void Network::generateRandomW()
{
	for (int i = 0; i < w.size(); ++i)
		for (int j = 0; j < w[i].size(); ++j)
			for (int k = 0; k < w[i][j].size(); ++k)
				w[i][j][k] = (rand() % 500 - 200) * 0.01;

	return;
}
void Network::generateRandomBias()
{
	for (int i = 0; i < bias.size(); ++i)
		for (int j = 0; j < bias[i].size(); ++j)
			bias[i][j] = (rand() % 100 - 50) * 0.01;

	return;
}

void Network::calculate_neuron(int& _x, int& _y)
{
	value[_x][_y] = 0;
	for (int i = 0; i < value[_x - 1].size(); ++i) {
		value[_x][_y] += value[_x - 1][i] * w[_x - 1][i][_y];
	}
	value[_x][_y] += bias[_x][_y];

	value[_x][_y] = fun(value[_x][_y]);

	return;
}

void Network::calculate_line(int _x)
{
	for (int i = 0; i < value[_x].size(); ++i)
		calculate_neuron(_x, i);

	return;
}

void Network::calculate_network()
{
	for (int i = 1; i < value.size(); ++i)
		calculate_line(i);

	return;
}

void Network::add_example(vector<long double> _input, vector<long double> _output)
{
	example.push_back({ _input, _output });
	return;
}

void Network::clear_examples()
{
	example.clear();
	return;
}


void Network::setInput(vector<long double> _v)
{
	value[0] = _v;

	return;
}

vector<long double> Network::getAnswer()
{
	return value.back();
}









// vvvvvvvvvv SHNIAGA vvvvvvvvv


void Network::clear_mistake()
{
	mistake = 0;

	return;
}

long double Network::get_mistake()
{
	return mistake;
}

bool Network::operator<(Network& _n)
{
	return get_mistake() < _n.get_mistake();
}

bool Network::operator<=(Network& _n)
{
	return get_mistake() <= _n.get_mistake();
}

bool Network::operator==(Network& _n)
{
	return get_mistake() == _n.get_mistake();
}

bool Network::operator>(Network& _n)
{
	return get_mistake() > _n.get_mistake();
}

bool Network::operator>=(Network& _n)
{
	return get_mistake() >= _n.get_mistake();
}

void Network::mutate(Network& _n, long double _dispersion)
{
	for (int i = 0; i < _n.w.size(); ++i)
		for (int j = 0; j < _n.w[i].size(); ++j)
			for (int k = 0; k < _n.w[i][j].size(); ++k)
			{
				long double buf = (rand() % 40000 - 20000.0) / 20000.0;
				_n.w[i][j][k] = w[i][j][k] + buf * _dispersion;

			}
				

	for (int i = 0; i < _n.bias.size(); ++i)
		for (int j = 0; j < _n.bias[i].size(); ++j)
		{
			long double buf = (rand() % 40000 - 20000.0) / 20000.0;

			_n.bias[i][j] = bias[i][j] + buf * _dispersion;
		}

	return;
}

vector<long double> Network::fuction(vector<long double> _x)
{
	setInput(_x);
	calculate_network();
	return getAnswer();
}

void Network::update_network()
{
	clear_mistake();
	clear_changes();
	
	for (int i = 0; i < example.size(); ++i)
	{

		update_network_for_dot(example[i].first, example[i].second);

		for (int j = 0; j < value.back().size(); ++j)
		{
			mistake += pow(example[i].second[j] - value.back()[j], 2);
		}
	}
	prev_mistake = mistake;
	upload_new_changes();
	return;

}

void Network::clear_changes()
{

	for (int i = 0; i < bias_change.size(); ++i)
		for (int j = 0; j < bias_change[i].size(); ++j)
			bias_change[i][j] = 0;

	for (int i = 0; i < w_change.size(); ++i)
		for (int j = 0; j < w_change[i].size(); ++j)
			for (int k = 0; k < w_change[i][j].size(); ++k)
				w_change[i][j][k] = 0;

	return;
}

void Network::clear_delta()
{
	for (int i = 0; i < delta.size(); ++i)
		for (int j = 0; j < delta[i].size(); ++j)
			delta[i][j] = 0;
}

void Network::update_network_for_dot(vector<long double>& _dot, vector<long double>& _ans)
{
	clear_delta();
	setInput(_dot);
	calculate_network();
	for (int i = 0; i < delta.back().size(); ++i)
	{
		delta.back()[i] = (value.back()[i] - _ans[i]);
		delta.back()[i] *= accuracy;

		for (int j = value.size()-1; j >= 1; --j)
		{
			update_line(j);
		}

	}



	return;
}

void Network::update_line(int _x)
{
	for (int i = 0; i < value[_x].size(); ++i)
		update_neuron(_x, i);
}

void Network::update_neuron(int _x, int _y)
{

	if (_x == 0)
		return;
	//cout << diffun(obrfun(value[_x][_y])) << endl;
	delta[_x][_y] *= diffun(obrfun(value[_x][_y]));
	

	bias_change[_x][_y] += delta[_x][_y];

	for (int i = 0; i < w[_x - 1].size(); ++i)
	{
		w_change[_x - 1][i][_y] += value[_x - 1][i] * delta[_x][_y];
		delta[_x - 1][i] += delta[_x][_y] * w[_x-1][i][_y];
	}


}

void Network::upload_new_changes()
{
	for (int i = 0; i < bias_change.size(); ++i)
		for (int j = 0; j < bias_change[i].size(); ++j)
		{
			if (abs(bias_change[i][j]) > 0.1)
			{
				//cout << "ALAAAARM!!!\n";
			}
			bias[i][j] -= bias_change[i][j];
		}
			

	for (int i = 0; i < w_change.size(); ++i)
		for (int j = 0; j < w_change[i].size(); ++j)
			for (int k = 0; k < w_change[i][j].size(); ++k)
			{
				if (abs(w_change[i][j][k]) > 0.1)
				{
					//cout << "ALAAAARM!!!\n";
				}
				w[i][j][k] -= w_change[i][j][k];
			}

	return;
}

void Network::save_network_in_file(string _path)
{
	ofstream file(_path);

	file << accuracy << endl << endl;

	int sloi_size = sloi.size();

	file << sloi_size << endl << endl;

	for (int i = 0; i < sloi.size(); ++i)
	{
		file << sloi[i] << " ";
	}

	file << endl;

	for (int i = 0; i < bias.size(); ++i)
	{
		for (int j = 0; j < bias[i].size(); ++j)
			file << bias[i][j] << " ";
		file << endl;
	}

	file << endl << endl;

	for (int i = 0; i < w.size(); ++i)
	{
		for (int j = 0; j < w[i].size(); ++j)
		{
			for (int k = 0; k < w[i][j].size(); ++k)
				file << w[i][j][k] << " ";
			file << endl;
		}
		file << endl << endl;
	}

	file.close();
}

