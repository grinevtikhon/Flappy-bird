#include "Network.h"

Network::Network(vector<int> _layers_size)
{
	layers_size = _layers_size;

	for (int i = 0; i < layers_size.size(); ++i)
	{
		value.push_back({});
		bias.push_back({});

		errors.push_back({});
		delta_bias.push_back({});

		for (int j = 0; j < layers_size[i]; ++j)
		{
			value[i].push_back((rand() % 2000 - 1000.0) / 1000.0);
			bias[i].push_back((rand() % 2000 - 1000.0) / 1000.0);

			errors[i].push_back(0);
			delta_bias[i].push_back(0);
		}
	}

	for (int i = 0; i < layers_size.size() - 1; ++i)
	{
		weight.push_back({});
		delta_weight.push_back({});

		for (int j = 0; j < layers_size[i]; ++j)
		{
			weight[i].push_back({});
			delta_weight[i].push_back({});

			for (int l = 0; l < layers_size[i + 1]; ++l)
			{
				weight[i][j].push_back((rand() % 2000 - 1000.0) / 1000.0);
				delta_weight[i][j].push_back(0);
			}
		}
	}

}

void Network::calculate_network()
{
	for (int i = 1; i < layers_size.size(); ++i)
	{
		calculate_layer(i);
	}
}

void Network::calculate_layer(int _x)
{
	for (int i = 0; i < layers_size[_x]; ++i)
	{
		calculate_neuron(_x, i);
	}
}

void Network::calculate_neuron(int _x, int _y)
{

	if (_x == 0)
	{
		cout << "ALARM TI DAWN V CALCULATORE!!!";
		return;
	}

	value[_x][_y] = bias[_x][_y];

	for (int i = 0; i < layers_size[_x - 1]; ++i)
	{
		value[_x][_y] += value[_x - 1][i] * weight[_x - 1][i][_y];
	}

	value[_x][_y] = function(value[_x][_y]);
}

void Network::clear_delta()
{
	for (int i = 0; i < delta_bias.size(); ++i)
	{
		for (int j = 0; j < delta_bias[i].size(); ++j) {
			delta_bias[i][j] = 0;
		}
	}

	for (int i = 0; i < delta_weight.size(); ++i)
	{
		for (int j = 0; j < delta_weight[i].size(); ++j)
		{
			for (int l = 0; l < delta_weight[i][j].size(); ++l)
			{
				delta_weight[i][j][l] = 0;
			}
		}
	}
}

void Network::update_delta()
{
	for (int i = 0; i < delta_bias.size(); ++i)
	{
		for (int j = 0; j < delta_bias[i].size(); ++j) {
			bias[i][j] -= delta_bias[i][j];
		}
	}

	for (int i = 0; i < delta_weight.size(); ++i)
	{
		for (int j = 0; j < delta_weight[i].size(); ++j)
		{
			for (int l = 0; l < delta_weight[i][j].size(); ++l)
			{
				weight[i][j][l] -= delta_weight[i][j][l];
			}
		}
	}
}

void Network::clear_errors()
{
	for (int i = 0; i < errors.size(); ++i)
	{
		for (int j = 0; j < errors[i].size(); ++j)
		{
			errors[i][j] = 0;
		}
	}
}

void Network::backPropagate()
{
	clear_delta();

	global_error = 0;

	for (int i = 0; i < examples.size(); ++i)
	{
		calculate_error_network(examples[i]);
	}

	update_delta();
}

void Network::calculate_error_network(pair<vector<double>, vector<double>> _exmpl)
{

	clear_errors();

	value[0] = _exmpl.first;

	calculate_network();

	for (int i = 0; i < errors.back().size(); ++i) {

	}

	for (int i = 0; i < errors.back().size(); ++i) {
		errors.back()[i] = learn_rate * 2 * (value.back()[i] - _exmpl.second[i]);
		global_error += pow(value.back()[i] - _exmpl.second[i], 2);

	}

	for (int i = layers_size.size() - 1; i > 0; --i)
	{
		calculate_error_layer(i);
	}
}

void Network::calculate_error_layer(int _x)
{
	if (_x == 0)
	{
		cout << "ALAAARM TI NEPRAVELNO ERROR SCHITAESH!!!!!!";
		return;
	}

	for (int i = 0; i < layers_size[_x]; ++i)
	{ 
		calculate_error_neuron(_x, i);
	}
}

void Network::calculate_error_neuron(int _x, int _y)
{

	if (_x == 0)
	{
		cout << "ALAAARM TI NEPRAVELNO ERROR SCHITAESH!!!!!!";
		return;
	}

	delta_bias[_x][_y] += errors[_x][_y] * function_derivate(value[_x][_y]);

	for (int i = 0; i < layers_size[_x - 1]; ++i)
	{
		delta_weight[_x - 1][i][_y] += errors[_x][_y] * function_derivate(value[_x][_y]) * value[_x - 1][i];
		errors[_x - 1][i] += errors[_x][_y] * function_derivate(value[_x][_y]) * weight[_x - 1][i][_y];
	}

}

double Network::function(double _x)
{
	// sigmoid
	return (1.0 / (1.0 + exp(-_x)));
}

double Network::function_derivate(double _x)
{
	return (_x * (1.0 - _x));
}