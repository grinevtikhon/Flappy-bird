#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class Picture
{

public:

	int number;
	int answer;

	ofstream out;

	ifstream in_mat;
	ifstream in_ans;

	const string path_out = "H:/school_project/resources/trash/picture_number.txt";
	const string path_in_mat = "H:/school_project/resources/trash/matrix.txt";
	const string path_in_ans = "H:/school_project/resources/trash/answer.txt";

	Picture();

	vector<double> matrix;

	void launch_python();

	void set_picture(int _number);

	vector<double> get_matrix();

	int get_answer();
};

