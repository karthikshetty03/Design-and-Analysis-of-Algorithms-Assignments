/**
 * Code to implement the line fitting dynamic programming algorithm
 * 
 * 
 * The cost of a particular set of segments is:  
 * sum(i from 1 to N) 
 *  Error_i + cost * amt,
 *
 * where,
 * 
 * Error_i is the error of the ith point of the segment, 
 * cost is the segment cost,
 * and amt is the number of segments used
 * 
 * The alogrithm accepts set of points and cost of introducing a segment as input 
 * It outputs the minimal cost and the corresponding set of segments
 * 
 * Two modes of inputs: 
 * 	1. Manually give the number of points say n, and enter n points in n lines
 * 
 *  2. First run script.cpp file which will take an input say n and generate n*5 points 
 *     These points are then written to points.txt file and read directly fron there
 * 
 * Time Complexity : O(N2)
 * Space Complexity: O(N2)
 * 
 *  /


#include <bits/stdc++.h>
using namespace std;

#define LIMIT_VAL 10000
#define infi numeric_limits<double>::infinity()

/// <Definiton of Point data structure
struct Point
{
	double x, y;

	bool operator<(const Point &m) const
	{
		return x < m.x;
	}
};

stack<int> seg;
struct Point pts[LIMIT_VAL + 1];
int num, i = 1, j = 1, k = 1, gap;
double sum_x, sum_y, sum_xy, sum_x_sqr, numr, denr, temp, mini, C;

vector<double> X(LIMIT_VAL + 1), Y(LIMIT_VAL + 1), XY(LIMIT_VAL + 1), X_sqr(LIMIT_VAL + 1);
vector<double> optimum(LIMIT_VAL + 1), seg_opti(LIMIT_VAL + 1);

vector<vector<double>> slope(LIMIT_VAL + 1, vector<double>(LIMIT_VAL + 1));
vector<vector<double>> intercept(LIMIT_VAL + 1, vector<double>(LIMIT_VAL + 1));
vector<vector<double>> error(LIMIT_VAL + 1, vector<double>(LIMIT_VAL + 1));

/// <helper function to initialize values
void init()
{
	X[0] = 0;
	Y[0] = 0;
	XY[0] = 0;
	X_sqr[0] = 0;
}

/// <helper function to update values in X, Y, Xy and X_sqr
void XYInitializer(int i, int j)
{
	X[j] = X[j - 1];
	X[j] += pts[j].x;

	Y[j] = Y[j - 1];
	Y[j] += pts[j].y;

	XY[j] = XY[j - 1];
	XY[j] += pts[j].x * pts[j].y;

	X_sqr[j] = X_sqr[j - 1];
	X_sqr[j] += pts[j].x * pts[j].x;
}

/// <helper function to updare sum_x, sum_y, sum_xy, sum_x_sqr
void sumInitializer(int i, int j)
{
	sum_x = X[j];
	sum_x -= X[i - 1];

	sum_y = Y[j];
	sum_y -= Y[i - 1];

	sum_xy = XY[j];
	sum_xy -= XY[i - 1];

	sum_x_sqr = X_sqr[j];
	sum_x_sqr -= X_sqr[i - 1];
}

/// <driver code
int main()
{
	cout << "Enter 1 for manual input, 2 to run input script\n";
	int inp;
	cin >> inp;

	ifstream ip;
	ofstream opp;

	/// <Input through script
	if (inp == 2)
	{
		ip.open("points.txt");
		ip >> num;
		cout << num << " points:" << endl;
		while (i <= num)
		{
			ip >> pts[i].x >> pts[i].y;
			i++;
		}

		i = 1;
		while (i <= num)
		{
			cout << pts[i].x << " " << pts[i].y << endl;
			i++;
		}
	}
	else ///<Manual input
	{
		opp.open("points.txt");
		double x, y;
		cout << "Enter the number of points : ";
		cin >> num;
		opp << num << endl;
		cout << "Enter " << num << " points :" << endl;

		for (int i = 1; i <= num; i++)
		{
			cin >> x >> y;
			pts[i].x = x;
			pts[i].y = y;
			opp << x << " " << y << endl;
		}
	}

	cout << "Enter the cost of creating a new segment : ";
	cin >> C;

	/// <Sort points
	sort(pts + 1, pts + num + 1);
	init();

	j = 1;
	while (j <= num)
	{
		XYInitializer(i, j);
		i = 1;
		while (i <= j)
		{
			gap = j - i + 1;
			sumInitializer(i, j);
			numr = gap * sum_xy - sum_x * sum_y;

			(numr != 0) ? (denr = gap * sum_x_sqr - sum_x * sum_x,
										 (denr != 0) ? slope[i][j] = (numr / double(denr)) : slope[i][j] == infi)
									: (slope[i][j] = 0.0);

			intercept[i][j] = (sum_y - slope[i][j] * sum_x) / double(gap);

			k = i;
			error[i][j] = 0.0;
			while (k <= j)
			{
				temp = pts[k].y;
				temp -= slope[i][j] * pts[k].x;
				temp -= intercept[i][j];
				double val = temp;
				val *= temp;
				error[i][j] += val;
				k++;
			}

			i++;
		}

		j++;
	}

	optimum[0] = 0;
	seg_opti[0] = 0;
	j = 1;
	while (j <= num)
	{
		i = 1;
		mini = infi;
		k = 0;
		while (i <= j)
		{
			temp = error[i][j] + optimum[i - 1];
			(temp < mini) ? (mini = temp, k = i) : 0;
			i++;
		}
		optimum[j] = mini + C;
		seg_opti[j] = k;
		j++;
	}

	ofstream title;
	title.open("title.txt");

	cout << endl
			 << "The cost of the optimal solution : " << optimum[num] << endl;
	title << endl
				<< "The cost of the optimal solution : " << optimum[num] << endl;

	i = num;
	j = seg_opti[num];
	while (i > 0)
	{
		seg.push(i);
		seg.push(j);
		i = j - 1;
		j = seg_opti[i];
	}

	ofstream op;
	op.open("segments.txt");

	cout << endl
			 << "An optimal solution is:" << endl;

	for (; !seg.empty();)
	{
		i = seg.top();
		seg.pop();
		j = seg.top();
		seg.pop();

		cout << "Segment (y = " << slope[i][j] << " * x + " << intercept[i][j]
				 << ") from points " << i << " to " << j
				 << " with square error " << error[i][j] << endl;

		op << pts[i].x << " " << pts[i].y << " " << pts[j].x << " " << pts[j].y << endl;
	}

	return 0;
}