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
			return true;
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
class Stripe {
	public:
		Interval x_interval;
		Interval y_interval;
		float x_union;

		Stripe();
		Stripe(Interval x_interval, Interval y_interval, float x_union);
		void setXunion(float x_union);
		Interval getXInterval();
		Interval getYInterval();
};