#include <iostream>
#include <fstream>

#include "Picture.h"

using namespace std;


int reverseInt(int i)
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}
void read_mnist()
{
    ifstream file(/*full_path*/"H:\\school_project\\resources\\test_pictures\\train-images.idx3-ubyte", ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char*)&number_of_images, sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*)&n_rows, sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char*)&n_cols, sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        for (int i = 0; i < number_of_images; ++i)
        {
            //cout << "picture number:" << i << endl;;
            for (int r = 0; r < n_rows; ++r)
            {
                //cout << "roe number : " << r << " ";
                for (int c = 0; c < n_cols; ++c)
                {
                    //cout << "|" << c << "|";
                    unsigned char temp = 0;
                    file.read((char*)&temp, sizeof(temp));
                    //cout << (int)temp << " ";
                    double kost = int(temp) / 255.0;
                    if (kost >= 0.5)
                    {
                        cout << "#";
                    }
                    else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    else
    {
        cout << "BRUH\n";
    }
}

int main()
{

    read_mnist();

    return 0;


    Picture picture;

    while (true)
    {
        int buf;
        cin >> buf;
        picture.set_picture(buf);
        vector<double> v = picture.get_matrix();

        for (int i = 0; i < v.size(); ++i)
        {
            if (int(v[i]) == 1) {
                cout << "#";
            }
            else {
                cout << " ";
            }
            //cout << int(v[i]) << " ";
            if (i % 28 == 27)
            {
                cout << endl;
            }
        }

    }
}