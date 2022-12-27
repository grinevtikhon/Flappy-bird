#pragma once

#include<iostream>
#include<cmath>
#include<vector>
#include <time.h>

using namespace std;

class Network
{

public:

	double learn_rate = 0.0005;

	vector<int> layers_size;

	vector<vector<double>> value;

	vector<vector<double>> bias;
	vector<vector<vector<double>>> weight;

	double global_error;

	vector<vector<double>> errors;

	vector<vector<double>> delta_bias;
	vector<vector<vector<double>>> delta_weight;

	vector<pair<vector<double>, vector<double>>> examples;

	Network(vector<int> _layers_size);

	void calculate_network();
	void calculate_layer(int _x);
	void calculate_neuron(int _x, int _y);

	void clear_delta();
	void update_delta();

	void clear_errors();

	void backPropagate();

	void calculate_error_network(pair<vector<double>, vector<double>> _exmpl);
	void calculate_error_layer(int _x);
	void calculate_error_neuron(int _x, int _y);

	double function(double _x);
	double function_derivate(double _x);

};
