#include<bits/stdc++.h>
using namespace std;

struct point {
  int x, y;
};

struct interval {
  float bottom, top;
};

struct lineSegment {
  interval a;
  float coord;
};

class rectangle {
public:
  float x_left, x_right, y_bottom, y_top;
  interval x_interval, y_interval;

  rectangle(int x1, int x2, int y1, int y2) {
    x_left = x1;
    x_right = x2;
    y_bottom = y1;
    y_top = y2;

    x_interval.bottom = x1;
    x_interval.top = x2;
    
    y_interval.bottom = y1;
    y_interval.top = y2;
  }
};

struct edge {
  interval a;
  float coord;
  string side;
};

class stripe {
public:
  interval x_interval, y_interval;
  vector<interval> x_set;

  stripe(vector<rectangle*> R) {
    
  }
};

vector<stripe*> STRIPES(stripe* s) {
  
}

vector<stripe*> rectangle_DAC(vector<rectangle*> R) {
  


}





















void printStripe(vector<stripe*> s) {

}

float measure(vector<stripe*> s) {

}

int main() {
  int n;
  cin >> n;
  
  vector<rectangle*> R;

  while(n--) {
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
    rectangle *r;
    r = new rectangle(x1, x2, y1, y2);
    R.push_back(r);

  }

  vector<stripe*> Stripe = rectangle_DAC(R);
  printStripe(Stripe);
  float ans = measure(Stripe);
  cout << ans;
  return 0;
}



