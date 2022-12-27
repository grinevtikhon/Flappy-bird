#include "Picture.h"

Picture::Picture()
{
	number = 0;
	answer = 0;
}

void Picture::launch_python()
{
	system("C: && \"C:\\Program Files\\Python39\\python.exe\" \"H:/school_project/Python/Converter/main.py\" " );
}

void Picture::set_picture(int _number)
{
	number = _number;

	out.open(path_out);
	out << number;
	out.close();

	launch_python();
	
	in_ans.open(path_in_ans);
	in_ans >> answer;
	in_ans.close();


	in_mat.open(path_in_mat);
	matrix.clear();
	for (int i = 0; i < 28 * 28; ++i)
	{
		int r, g, b;
		in_mat >> r >> g >> b;
		double pixel = (r + g + b) / (255 * 3);
		matrix.push_back(1 - pixel);
	}
	in_mat.close();



}

vector<double> Picture::get_matrix()
{
	return matrix;
}

int Picture::get_answer()
{
	return answer;
}
