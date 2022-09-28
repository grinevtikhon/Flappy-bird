#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define EXPONENT 2.71828182846

using namespace std;

double sigma(double value)
{
	return 1.0f / (1.0f + pow(EXPONENT, -value));
}

struct neuron
{
	double value;
	vector <double> w;
	double bias;

	neuron(int n)
	{
		value = 0;

		bias = 0;

		w.resize(n, 1);
	}

	void print()
	{
		cout << "neuron : ";
		cout << "value = " << value;
		cout << " | ";
		cout << "w = [";

		for (int i = 0; i < w.size(); ++i) {
			if (i == w.size() - 1)
				cout << w[i];
			else
				cout << w[i] << ", ";
		}
		cout << "]";

		cout << " | ";
		cout << "bias = " << bias;
		cout << endl;

		return;
	}

	void setValue(double v)
	{
		value = v;
		return;
	}

};

struct line
{
	vector <neuron> nr;

	line()
	{

	}

	line(int a, int b)
	{
		nr.resize(a, b);
	}

	void make(int a, int b)
	{
		nr.resize(a, b);
		return;
	}

	void print()
	{
		cout << "line (" << endl;
		for (int i = 0; i < nr.size(); ++i)
		{
			nr[i].print();
			//cout << endl;
		}
		cout << ")" << endl;
	}

	void count(line &pr_line)
	{
		for (int i = 0; i < nr.size(); ++i) {
			nr[i].value = 0;

			for (int j = 0; j < pr_line.nr.size(); ++j) {
				nr[i].value += pr_line.nr[j].value * pr_line.nr[j].w[i];
			}

			nr[i].value += nr[i].bias;

			nr[i].value = sigma(nr[i].value);
		}

		return;
	}

};

struct network 
{
	vector <line> st;

	network(vector<int> v)
	{
		st.resize(v.size());

		for (int i = 0; i < v.size(); ++i) {
			if (i == v.size() - 1)
				st[i].make(v[i], 0);
			else
				st[i].make(v[i], v[i + 1]);
		}
	}

	void print() {
		cout << "network {" << endl << endl;
		for (int i = 0; i < st.size(); ++i)
		{
			st[i].print();
			cout << endl;
		}
		cout << "}  <---- this all network!" << endl;
	}

	void count()
	{
		for (int i = 1; i < st.size(); ++i)
			st[i].count(st[i - 1]);

		return;
	}

	void input(vector<double> v)
	{
		if (v.size() != st[0].nr.size()) {
			cout << "ALAARM!!!!! WRONG INPUT" << endl;
			return;
		}

		for (int i = 0; i < v.size(); ++i)
			st[0].nr[i].setValue(v[i]);

		return;
	}

	void answer(vector<double> v)
	{
		input(v);

		count();

		print();

		return;
	}

};


int main()
{
	//vector <int> v { 5, 5, 2 };
	network da({ 784, 16, 10, 10 });
	da.count();
	da.print();
	cout << "da TbI horosh!";
	return 0;
}
