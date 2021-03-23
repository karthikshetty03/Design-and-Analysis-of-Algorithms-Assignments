/*
Authors:
    Shetty Karthik Ravindra (2018A7PS0141H)
    Abhirath Singh Parmar (2018A7PS0520H)
    Koustubh Sharma (2018A7PS0114H)
    Rishabh Baid (2018A7PS)
*/

/*
Project Structure :

               | contour.cpp --> contour.hpp  |
 main.cpp ---> |                              | --> primitves.cpp  ---> primitves.hpp
               | isorect.cpp --> isorect.hpp  |

*/

/*

Compile and Run:
g++ main.cpp isorect.cpp contour.cpp primitives.cpp -o combined -lGL -lGLU -lglut
./combined

*/

#include <bits/stdc++.h>
#include "isorect.hpp"
#include "contour.hpp"
using namespace std;

vector<Rectangle> rectangles;
int inp = 1;

bool sortbyfirst(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second < b.second;

    return (a.first < b.first);
}

void printStripes(vector<Stripe> S)
{

    cout << "Y STRIPES:" << endl;
    for (auto stripe : S)
    {
        cout << stripe.getYInterval().getBottom() << " " << stripe.getYInterval().getTop() << endl;
    }
}

int main(int argc, char **argv)
{
    vector<Stripe> stripes;
    float ans = 0;
    cout << "Enter 1 for Manual Input of Rectangles" << endl;
    cout << "Enter 2 for Random Input of Rectangles" << endl;
    cin >> inp;

    int n;
    cout << "Number of rectangles: ";
    cin >> n;

    fstream my_file1;
    my_file1.open("my_file1.txt", ios::out);

    cout << "Enter Points in format x1 y1 x2 y2:" << endl;

    for (int i = 0; i < n; i++)
    {
        int f1, f2, f3, f4;

        if (inp == 1)
            cin >> f1 >> f2 >> f3 >> f4;
        else
        {
             float f11, f22, f33, f44;

            f11 = (((float)rand()) / (float)RAND_MAX) * 1400;
            f22 = (((float)rand()) / (float)RAND_MAX) * 900;
            f33 = (((float)rand()) / (float)RAND_MAX) * 1400;
            f44 = (((float)rand()) / (float)RAND_MAX) * 900;

            f1 = ceil(f11);
            f2 = ceil(f22);
            f3 = ceil(f33);
            f4 = ceil(f44);

            cout << f1 << " " << f2 << " " << f3 << " " << f4 << endl;
        }

        int x1 = min(f1, f3);
        int y1 = min(f2, f4);
        int x2 = max(f1, f3);
        int y2 = max(f2, f4);

        if (!my_file1)
        {
            cout << "File not created!";
        }
        else
        {
            my_file1 << x1 << " " << y1 << endl;
            my_file1 << x2 << " " << y2 << endl;
        }

        Point *P1 = new Point(x1, y1);
        Point *P2 = new Point(x2, y2);

        Rectangle *r = new Rectangle(*P1, *P2);
        rectangles.push_back(*r);
    }

    my_file1.close();

    stripes = RectangleDAC1(rectangles);
    ans = measure(stripes);
    cout << "The MeAsure for the given set of rectangles is : " << ans<<endl;

    printStripes(stripes);
    map<int, vector<Interval>> contourStripes = RectangleDAC2(rectangles);

    fstream my_file2;
    my_file2.open("my_file2.txt", ios::out);

    if (!my_file2)
    {
        cout << "File not created!";
    }
    else
    {
        my_file2 << endl;
        my_file2 << "The MeAsure for the given set of rectangles is : " << ans;
    }

    vector<pair<int, int>> arr, horizontal;

    for (auto x : contourStripes)
    {
        float y1 = x.first;
        float y2 = x.first;

        for (auto interval : x.second)
        {
            float x1 = interval.getBottom();
            float x2 = interval.getTop();
            arr.push_back({x1, y1});
            arr.push_back({x2, y2});
            horizontal.push_back({x1, y1});
            horizontal.push_back({x2, y2});
        }
    }

    sort(arr.begin(), arr.end(), sortbyfirst);

    fstream my_file;
    my_file.open("my_file.txt", ios::out);

    if (!my_file)
    {
        cout << "File not created!";
    }
    else
    {
        cout << "File created successfully!";

        for (auto x : arr)
        {
            my_file << x.first << " " << x.second << endl;
        }

        for (auto x : horizontal)
        {
            my_file << x.first << " " << x.second << endl;
        }

        my_file.close();
    }

    return 0;
}