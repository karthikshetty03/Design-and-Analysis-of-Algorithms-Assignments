#include<bits/stdc++.h>
#include<GL/glut.h>
#include "primitives1.hpp"
using namespace std;

// RectangleDAC Algorithm returns the set of stripes for the set of rectangles
vector<Stripe> RectangleDAC(vector<Rectangle> rect);
float measure(vector<Stripe> stripe);