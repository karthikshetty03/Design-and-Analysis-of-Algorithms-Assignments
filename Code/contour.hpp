#include <bits/stdc++.h>
#include "primitives.hpp"
using namespace std;

/// Rectangle DAC algorithm called to form stripes and calculate contours class Contour
class Contour
{
public:
  /// leaf nodes of ctree of a particular edge
  vector<float> TreeCoords;
  void inorder(ctree *tree);
  vector<Interval> makeIntervals();
  vector<Interval> stripeIntervals(StripePrime s);
  vector<Edge> contour_pieces(Edge h, vector<StripePrime> &S);
  vector<Edge> contour(vector<Edge> &H, vector<StripePrime> &S);
  vector<Interval> partition(vector<float> coords);
  vector<Interval> setMinusLRHelper(vector<Interval> minusFrom, vector<Interval> &L1, vector<Interval> &R2);
  void setL(vector<Interval> &Lorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2);
  void setR(vector<Interval> &Rorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2);
  void setP(vector<float> &P, vector<float> P1, vector<float> P2);
  float findMedianCoord(vector<Edge> V, vector<Edge> &V1, vector<Edge> &V2);
  bool properSubset(Interval A, Interval B);
  vector<StripePrime> copy(vector<StripePrime> &S, vector<float> &P, Interval I);
  void blacken(vector<StripePrime> &S, vector<Interval> &J);
  vector<StripePrime> concat(vector<StripePrime> &S1, vector<StripePrime> &S2, vector<float> &P, Interval x_ext);
  void Stripes(vector<Edge> &V, Interval x_ext, vector<Interval> &L, vector<Interval> &R, vector<float> &P, vector<StripePrime> &S);
  map<int, vector<Interval>> RectangleDAC2(vector<Rectangle> rect);
};