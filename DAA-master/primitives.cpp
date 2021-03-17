#include "primitives.hpp"

//Point functions definitions
float Point::getX(){			// Returns x value of the point
	return this->x;
}
float Point::getY(){			// Returns y value of the point
	return this->y;
}
void Point::setX(float x){		// Sets a new x value of the point
	this->x=x;
}
void Point::setY(float y){		// Sets a new y value of the point
	this->y=y;
}
Point::Point(){					// Default Constructor
	this->x=0;
	this->y=0;
}
Point::Point(float x,float y){	// Constructor to initialize point with x,y values
	this->x=x;
	this->y=y;
}

//Rectangle functions definitions
Point Rectangle::getP1(){ 					//returns bottom left coordinates
	return this->P1;
}
Point Rectangle::getP2(){ 					//returns top right coordinates
	return this->P2;
}
void Rectangle::setP1(Point P1){ 			//sets bottom left coordinates
	this->P1=P1;
}
void Rectangle::setP2(Point P2){ 			//sets top right coordinates
	this->P2=P2;
}
Rectangle::Rectangle(Point P1, Point P2){	//Constructor to initialize rectangle
	this->P1=P1;
	this->P2=P2;
}

//Interval function definitions
Interval::Interval() {
	this->bottom = 0;
	this->top = 0;
}

Interval::Interval(float bottom, float top) {
	this->bottom = bottom;
	this->top = top;
}

float Interval::getBottom() {
	return this->bottom;
}

float Interval::getTop() {
	return this->top;
}

//Edge function definitions
Edge::Edge(Interval interval, float coord, string edgeType) {
	this->interval = interval;
	this->coord = coord;
	this->edgeType = edgeType;
}

string Edge::getEdgeType() {
	return this->edgeType;
}

Interval Edge::getInterval() {
	return this->interval;
}

float Edge::getCoord() {
	return this->coord;
}

//Stripe function definitions
Stripe::Stripe() {
	
	this->x_interval = Interval();
	this->y_interval = Interval();
	this->x_union = 0;
}

Stripe::Stripe(Interval x_interval, Interval y_interval, float x_union) {
	this->x_interval = x_interval;
	this->y_interval = y_interval;
	this->x_union = x_union;
}

void Stripe::setXunion(float x_union) {
	this->x_union = x_union;
}

Interval Stripe::getYInterval() {
	return this->y_interval;
}

Interval Stripe::getXInterval() {
	return this->x_interval;
}
//int main() {
//	return 0;
//}