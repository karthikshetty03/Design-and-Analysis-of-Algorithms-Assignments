/*
 * Actual Code starts from here
 * First we define all the necessary data structures
 * Then the implementation for the least square fit algorithm
 */

#include <bits/stdc++.h>
#define MAXN 1000
#define int long long int
#define endl "\n"
#define INF numeric_limits<double>::infinity()
using namespace std;

/// <Defining Point data structure
class Point
{
public:
    double x, y;

    bool operator<(const Point &that) const
    {
        return x < that.x;
    }

} points[MAXN + 1];

// <For Computing E[i][j] which is the square error of a segment:
// <that is best fit to the points {points[i], points[i+1], ..., points[j]}
// <cumulative_x[i] is sum(points[j].x) for 1 <= j <= i
// <cumulative_y[i] is sum(points[j].y) for 1 <= j <= i
// <cumulative_xy[i] is sum(points[j].x * points[j].y) for 1 <= j <= i
// <cumulative_xSqr[i] is sum(points[j].x * points[j].x) for 1 <= j <= i
// <slope[i][j] is the slope of the segment that is best fit to
// <the points {points[i], points[i+1], ..., points[j]}
// <intercept[i][j] is the y-intercept of the segment that is best fit to
// <the points {points[i], points[i+1], ..., points[j]}
// <E[i][j] is the square error of the segment that is best fit to
// <the points {points[i], points[i+1], ..., points[j]}

double cumulative_x[MAXN + 1], cumulative_y[MAXN + 1], cumulative_xy[MAXN + 1], cumulative_xSqr[MAXN + 1];
double slope[MAXN + 1][MAXN + 1], intercept[MAXN + 1][MAXN + 1], E[MAXN + 1][MAXN + 1];

// <OPT[i] is the optimal solution (minimum cost) for the points {points[1], points[2], ..., points[i]}
double OPT[MAXN + 1];

// <[opt_segment[i], i] is the last segment in the optimal solution
// <for the points {points[1], points[2], ..., points[i]}
double opt_segment[MAXN + 1];

int32_t main()
{
    int N, i, j, k, interval;
    double x_sum, y_sum, xy_sum, xsqr_sum, num, denom;
    double tmp, mn, C;

    cout << "Enter the number of points : ";
    cin >> N;

    cout << "Enter " << N << " points in next " << N << " lines" << endl;

    i = 1;
    while (i <= N)
    {
        cin >> points[i].x >> points[i].y;
        i++;
    }

    cout << "Enter the cost of creating a new segment : ";
    cin >> C;

    // <sort the points in non-decreasing order of x coordinate
    sort(points + 1, points + N + 1);

    // <precompute the error terms
    cumulative_x[0] = cumulative_y[0] = cumulative_xy[0] = cumulative_xSqr[0] = 0;

    j = 1;
    while (j <= N)
    {
        cumulative_x[j] = cumulative_x[j - 1] + points[j].x;
        cumulative_y[j] = cumulative_y[j - 1] + points[j].y;
        cumulative_xy[j] = cumulative_xy[j - 1] + points[j].x * points[j].y;
        cumulative_xSqr[j] = cumulative_xSqr[j - 1] + points[j].x * points[j].x;

        i = 1;
        while (i <= j)
        {
            interval = j - i + 1;
            x_sum = cumulative_x[j] - cumulative_x[i - 1];
            y_sum = cumulative_y[j] - cumulative_y[i - 1];
            xy_sum = cumulative_xy[j] - cumulative_xy[i - 1];
            xsqr_sum = cumulative_xSqr[j] - cumulative_xSqr[i - 1];

            num = interval * xy_sum - x_sum * y_sum;
            if (num == 0)
                slope[i][j] = 0.0;
            else
            {
                denom = interval * xsqr_sum - x_sum * x_sum;
                slope[i][j] = (denom == 0) ? INF : (num / double(denom));
            }
            intercept[i][j] = (y_sum - slope[i][j] * x_sum) / double(interval);

            k = i;
            E[i][j] = 0.0;

            while (k <= j)
            {
                tmp = points[k].y - slope[i][j] * points[k].x - intercept[i][j];
                E[i][j] += tmp * tmp;
                k++;
            }

            i++;
        }

        j++;
    }

    // find the cost of the optimal solution
    OPT[0] = opt_segment[0] = 0;

    j = 1;
    while (j <= N)
    {
        k = 0;
        i = 1;
        mn = INF;

        while (i <= j)
        {
            tmp = E[i][j] + OPT[i - 1];
            (tmp < mn) ? mn = tmp, k = i : 0;
            i++;
        }

        OPT[j] = mn + C;
        opt_segment[j] = k;
        j++;
    }

    cout << endl;
    cout << "Cost of the optimal solution : " << OPT[N] << endl;

    // <find the optimal solution
    stack<int> segments;

    i = N;
    j = opt_segment[N];

    while (i > 0)
    {
        segments.push(i);
        segments.push(j);
        i = j - 1;
        j = opt_segment[i];
    }

    fstream my_file1;
    my_file1.open("segments.txt", ios::out);

    if (!my_file1)
    {
        cout << "File not created!";
    }

    cout << endl;
    cout << "An optimal solution :" << endl;

    while (!segments.empty())
    {
        i = segments.top();
        segments.pop();

        j = segments.top();
        segments.pop();

        cout << "Segment (y = " << slope[i][j] << " * x + " << intercept[i][j];
        cout << " from point" << i << " to point" << j << endl;
        my_file1 << points[i].x << " " << points[i].y << " " << points[j].x << " " << points[j].y << endl;
        cout << "(Square Error: " << E[i][j] <<")"<< endl;
    }

    return 0;
}