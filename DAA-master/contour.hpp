#include<bits/stdc++.h>
#include<GL/glut.h>
#include "primitives2.hpp"
using namespace std;

// RectangleDAC Algorithm returns the set of stripes for the set of rectangles
vector<Stripe> RectangleDAC(vector<Rectangle> rect);
float contour(vector<Stripe> stripe);