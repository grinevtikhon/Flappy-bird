#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
//#include "MyCostants.h"

using namespace std;

class Network
{
public:

	long double fun(long double x);
	long double diffun(long double x);
	long double obrfun(long double y);

	vector<int> sloi;

	vector<vector<long double>> value;
	vector<vector<long double>> delta;

	vector<vector<long double>> bias;
	vector<vector<long double>> bias_change;

	vector<vector<vector<long double>>> w;
	vector<vector<vector<long double>>> w_change;

	vector<pair<vector<long double>, vector<long double>>> example;

	long double prev_mistake;

	long double mistake;

	long double accuracy;

	Network(vector<int> _v);
	Network(string _path);

private:

	void generateRandomW();
	void generateRandomBias();

	void calculate_neuron(int& _x, int& _y);
	void calculate_line(int _x);

public:

	void calculate_network();

	void add_example(vector<long double> _input, vector<long double> _output);
	void clear_examples();


private:

	void setInput(vector<long double> _v);

	vector<long double> getAnswer();

	void clear_mistake();

public:

	bool operator<(Network& _n);	//
	bool operator<=(Network& _n);	//
	bool operator==(Network& _n);	// for genetic algorithm dlia sravnenia mistakes
	bool operator>(Network& _n);	//
	bool operator>=(Network& _n);	//

	void mutate(Network& _n, long double _dispersion); // for gen algorithm

	long double get_mistake();

	vector<long double> fuction(vector<long double> _x);

	void update_network();

private:

	void clear_changes();

	void clear_delta();

	void update_network_for_dot(vector<long double>& _dot, vector<long double>& _ans);
	
	void update_line(int _x);

	void update_neuron(int _x, int _y);

	void upload_new_changes();

public:

	void save_network_in_file(string _path);

};
