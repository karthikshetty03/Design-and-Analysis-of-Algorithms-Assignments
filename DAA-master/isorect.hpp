#include<bits/stdc++.h>
#include<GL/glut.h>
#include "primitives.hpp"
using namespace std;

// RectangleDAC Algorithm returns the set of stripes for the set of rectangles
vector<Stripe> RectangleDAC1(vector<Rectangle> rect);
float measure(vector<Stripe> stripe);
