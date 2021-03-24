#include <bits/stdc++.h>
#include <GL/glut.h>
#include "primitives.hpp"
using namespace std;

/// RectangleDAC Algorithm returns the set of stripes for the set of rectangles
class isorect
{
public:
  float measure(vector<Stripe> stripe);
  void printStripe(vector<Stripe> S);
  vector<Interval> partition1(vector<float> coords);
  vector<Interval> setMinusLRHelper1(vector<Interval> minusFrom, vector<Interval> &L1, vector<Interval> &R2);
  void setL1(vector<Interval> *Lorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2);
  void setR1(vector<Interval> *Rorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2);
  void setP1(vector<float> *P, vector<float> P1, vector<float> P2);
  float findMedianCoord1(vector<Edge> V, vector<Edge> &V1, vector<Edge> &V2);
  bool properSubset1(Interval A, Interval B);
  vector<Stripe> copy1(vector<Stripe> *S, vector<float> *P, Interval I);
  void blacken1(vector<Stripe> *S, vector<Interval> *J);
  vector<Stripe> concat1(vector<Stripe> *S1, vector<Stripe> *S2, vector<float> *P, Interval x_ext);
  void Stripes1(vector<Edge> V, Interval x_ext, vector<Interval> *L, vector<Interval> *R, vector<float> *P, vector<Stripe> *S);
  vector<Stripe> RectangleDAC1(vector<Rectangle> rect);
};
