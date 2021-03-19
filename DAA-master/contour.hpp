#include<bits/stdc++.h>
#include<GL/glut.h>
#include "primitives.hpp"
using namespace std;

// RectangleDAC Algorithm returns the set of stripes for the set of rectangles
map<int, vector<Interval>> RectangleDAC2(vector<Rectangle> rect);
float contour(vector<Stripe> stripe);