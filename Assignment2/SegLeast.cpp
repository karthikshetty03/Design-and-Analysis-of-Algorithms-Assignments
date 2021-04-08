#include <bits/stdc++.h>
using namespace std;

#define N_MAXI 2000
#define infi numeric_limits<double>::infinity()

struct Point
{
	double x, y;
	bool operator<(const Point &m) const
	{
		return x < m.x;
	}
};

struct Point pts[N_MAXI + 1];
double sum_x, sum_y, sum_xy, sum_x_sqr, numr, denr, temp, mini, C;
vector<double> X(N_MAXI + 1), Y(N_MAXI + 1), XY(N_MAXI + 1), X_sqr(N_MAXI + 1), optimum(N_MAXI + 1), seg_opti(N_MAXI + 1);
vector<vector<double>> slope(N_MAXI + 1, vector<double>(N_MAXI + 1)), intercept(N_MAXI + 1, vector<double>(N_MAXI + 1)), error(N_MAXI + 1, vector<double>(N_MAXI + 1));

void init()
{
	X[0] = 0;
	Y[0] = 0;
	XY[0] = 0;
	X_sqr[0] = 0;
}

void XYInitializer(int i, int j)
{
	X[j] = X[j - 1] + pts[j].x;
	Y[j] = Y[j - 1] + pts[j].y;
	XY[j] = XY[j - 1] + pts[j].x * pts[j].y;
	X_sqr[j] = X_sqr[j - 1] + pts[j].x * pts[j].x;
}

void sumInitializer(int i, int j)
{
	sum_x = X[j] - X[i - 1];
	sum_y = Y[j] - Y[i - 1];
	sum_xy = XY[j] - XY[i - 1];
	sum_x_sqr = X_sqr[j] - X_sqr[i - 1];
}

int main()
{
	int num, i = 1, j = 1, k = 1, gap;
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
	else
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

			if (numr != 0)
			{
				denr = gap * sum_x_sqr - sum_x * sum_x;
				if (denr != 0)
					slope[i][j] = (numr / double(denr));
				else
					slope[i][j] == infi;
			}
			else
				slope[i][j] = 0.0;

			intercept[i][j] = (sum_y - slope[i][j] * sum_x) / double(gap);
			k = i;
			error[i][j] = 0.0;
			while (k <= j)
			{
				temp = pts[k].y - slope[i][j] * pts[k].x - intercept[i][j];
				error[i][j] += temp * temp;
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
			if (temp < mini)
			{
				mini = temp;
				k = i;
			}
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

	stack<int> seg;
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

	while (!seg.empty())
	{
		i = seg.top();
		seg.pop();
		j = seg.top();
		seg.pop();
		cout << "Segment (y = " << slope[i][j] << " * x + " << intercept[i][j] << ") from points " << i << " to " << j << " with square error " << error[i][j] << endl;
		op << pts[i].x << " " << pts[i].y << " " << pts[j].x << " " << pts[j].y << endl;
	}
	return 0;
}