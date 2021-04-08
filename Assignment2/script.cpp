/*
 * The script is generated as follows:
 * 
 * Step1 : Take n points on the x-axis
 * Step2: Choose k1 points from these and lift them byy = m1x + c1 + rand()
 * Step3: Take next k2 points and lift them by y = m2x + c2 + rand()
 * Step4: Continue step2 and step3 till all points are consumed
 * 
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
	ofstream out;
	out.open("points.txt");
	int n;
	cin >> n;
	int val = n * 5;
	cout << "Script generated " << val << " points succesfully!" << endl;
	out << val << endl;
	int m = 1;
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			float x = k++;
			float y = m * x + 10 * i + (rand() % 10) * 0.02;
			out << x << " " << y << endl;
		}
	}

	return 0;
}