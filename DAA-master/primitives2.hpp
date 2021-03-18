#include<bits/stdc++.h>
using namespace std;

//Point
class Point {
	float x;
	float y;

public:
	Point();
	Point(float x,float y);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
};

//Rectangle
class Rectangle {
	Point P1,P2;

public:
	Rectangle(Point P1, Point P2);
	Point getP1();
	Point getP2();
	void setP1(Point P1);
	void setP2(Point P2);
};

//Interval
class Interval {
public:
	float bottom;
	float top;

		Interval();
		Interval(float bottom, float top);
		float getTop();
		float getBottom();
		
	  bool operator<(const Interval& t) const
    { 
        return (this->bottom < t.bottom); 
    } 
};

//Edge
class Edge {
public:
	Interval interval;
	float coord;
	string edgeType;
	Edge(Interval interval, float coord, string edgeType);
	string getEdgeType();
	Interval getInterval();
	float getCoord();
};

//Stripe
class ctree {
	public:
		float coord;
		ctree* left;
		ctree* right;
		string edgeType;
		ctree(float coord, string edgeType, ctree* left, ctree* right);
		
};

class Stripe {
	public:
		Interval x_interval;
		Interval y_interval;
		ctree *tree;

		Stripe();
		Stripe(Interval x_interval, Interval y_interval, ctree* tree);
		void setTree(ctree* tree);
		Interval getXInterval();
		Interval getYInterval();
};