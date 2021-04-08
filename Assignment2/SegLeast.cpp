#include<bits/stdc++.h>

using namespace std;

#define N_MAXI 2000
#define infi numeric_limits<double>::infinity()


struct Point 
{
	double x, y;
	bool operator < (const Point& m) const 
	{
		return x < m.x;
	}
}; 

struct Point pts[N_MAXI+1];

vector<double> X(N_MAXI+1), Y(N_MAXI+1), XY(N_MAXI+1), X_sqr(N_MAXI+1), optimum(N_MAXI+1), seg_opti(N_MAXI+1);
vector<vector<double>> slope(N_MAXI+1,vector<double>(N_MAXI+1)), intercept(N_MAXI+1,vector<double>(N_MAXI+1)), error(N_MAXI+1,vector<double>(N_MAXI+1));

int main()	
{
	int num, i = 1, j = 1, k = 1, gap;
	double sum_x, sum_y, sum_xy, sum_x_sqr, numr, denr, temp, mini, C;
	
	cout << "Enter the number of points : ";
	cin >> num;
	cout << "Enter " << num << " points :" << endl;
	ifstream ip;
	ip.open("points.txt");

	while(i <= num)
	{
		ip >> pts[i].x >> pts[i].y;
		i++;
	}

	i = 1;
	while(i <= num) 
	{
		cout << i << " " << pts[i].x << " " << pts[i].y << endl;
		i++;
	}

	cout << "Enter the cost of creating a new segment : ";
	cin >> C;
	sort (pts+1, pts+num+1);

	X[0] = 0;
	Y[0] = 0;
	XY[0] = 0;
	X_sqr[0] = 0;

	j = 1;
	while(j <= num)	
	{
		X[j] = X[j-1] + pts[j].x;
		Y[j] = Y[j-1] + pts[j].y;
		XY[j] = XY[j-1] + pts[j].x*pts[j].y;
		X_sqr[j] = X_sqr[j-1] + pts[j].x*pts[j].x;
		i = 1;
		while(i <= j)	
		{
			gap = j - i + 1;
			sum_x = X[j] - X[i-1];
			sum_y = Y[j] - Y[i-1];
			sum_xy = XY[j] - XY[i-1];
			sum_x_sqr = X_sqr[j] - X_sqr[i-1];
			numr = gap*sum_xy - sum_x*sum_y;

<<<<<<< HEAD
			if(numr != 0)
			{
				denr = gap*sum_x_sqr - sum_x*sum_x;
				if(denr != 0)
					slope[i][j] = (numr / double(denr));
				else
					slope[i][j] == infi;
=======
int main()	{
	int N, i, j, k, interval;
	double x_sum, y_sum, xy_sum, xsqr_sum, num, denom;
	double tmp, mn, C;
	
	printf("Enter the number of points : ");
	scanf("%d", &N);
	printf("Enter %d points :\n", N);
	for (i = 1; i <= N; i++)
		scanf("%lf %lf", &points[i].x, &points[i].y);
	printf("Enter the cost of creating a new segment : ");
	scanf("%lf", &C);
	
	// sort the points in non-decreasing order of x coordinate
	sort (points + 1, points + N + 1);
	
	// precompute the error terms
	cumulative_x[0] = cumulative_y[0] = cumulative_xy[0] = cumulative_xSqr[0] = 0;
	for (j = 1; j <= N; j++)	{
		cumulative_x[j] = cumulative_x[j-1] + points[j].x;
		cumulative_y[j] = cumulative_y[j-1] + points[j].y;
		cumulative_xy[j] = cumulative_xy[j-1] + points[j].x * points[j].y;
		cumulative_xSqr[j] = cumulative_xSqr[j-1] + points[j].x * points[j].x;
		
		for (i = 1; i <= j; i++)	{
			interval = j - i + 1;
			x_sum = cumulative_x[j] - cumulative_x[i-1];
			y_sum = cumulative_y[j] - cumulative_y[i-1];
			xy_sum = cumulative_xy[j] - cumulative_xy[i-1];
			xsqr_sum = cumulative_xSqr[j] - cumulative_xSqr[i-1];
			
			num = interval * xy_sum - x_sum * y_sum;
			if (num == 0)
				slope[i][j] = 0.0;
			else {
				denom = interval * xsqr_sum - x_sum * x_sum;
				slope[i][j] = (denom == 0) ? INF : (num / double(denom));				
>>>>>>> 6acdab2 (Fixes and work on this)
			}
			else 
				slope[i][j] = 0.0;

            intercept[i][j] = (sum_y - slope[i][j]*sum_x) / double(gap);
			k = i;
			error[i][j] = 0.0;
           	while(k <= j)	
			{
            	temp = pts[k].y - slope[i][j]*pts[k].x - intercept[i][j];
            	error[i][j] += temp*temp;
				k++;
    		}
			i++;
		}
		j++;
	}

	optimum[0] = 0;
	seg_opti[0] = 0;
	j = 1;
	while(j <= num)	
	{
		i = 1;
		mini = infi;
		k = 0;
		while(i <= j)	
		{
			temp = error[i][j] + optimum[i-1];
			if(temp < mini)	
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

	cout << endl << "Enter the cost of the optimal solution : " << optimum[num] << endl;

	stack<int> seg;
	i = num;
	j = seg_opti[num];
	while(i > 0)	
	{
		seg.push(i);
		seg.push(j);
		i = j-1;
		j = seg_opti[i];
	}

	ofstream op;
	op.open("segments.txt");
	cout << endl << "An optimal solution is:" << endl;

	while(!seg.empty())	
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