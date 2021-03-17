#include<bits/stdc++.h>
#include "primitives.hpp"

using namespace std;

vector<Interval> partition(vector<float> coords) {
    vector<Interval> intervals;
    sort(coords.begin(), coords.end());

    for(int i = 0;i < coords.size()-1; i++) {
        float y1 = coords[i];
        float y2 = coords[i+1];

        if(y1 != y2) {
            Interval *interval = new Interval(y1, y2);
            intervals.push_back(*interval);
        }
    }

    return intervals;
}

set<Interval> setMinusLRHelper(vector<Interval>& minusFrom, vector<Interval>& L1,  vector<Interval>& R2) {
    set<Interval> s, minusFromSet;

    //conversion to set
    for(auto x : minusFrom) {
        minusFromSet.insert(x);
    }

    //find L1 intersection R2 (LR) --> s
    for(auto &l1 : L1) {
        for(auto &r2 : R2) {
            if(l1.getBottom() == r2.getBottom() and l1.getTop() == r2.getTop()) {
                s.insert(l1);
            }
        }
    }

    //remove elements of LR (--> s) if nay from minusFromSet
    for(auto &s : s) {
        auto itr = minusFromSet.find(s);
        if(itr != minusFromSet.end()) {
            minusFromSet.erase(itr);
        }
    }

    //minusFromSet/LR
    return minusFromSet;
}

void setL(vector<Interval> *Lorig, vector<Interval>& L1, vector<Interval>& R1, vector<Interval>& L2, vector<Interval>& R2) {
    set<Interval> s, finalSet;

    //L1/LR
    s = setMinusLRHelper(L1, L1, R2);

    //s --> now union with l2
    for(auto interval : s) {
        finalSet.insert(interval);
    }

    for(auto interval : L2) {
        finalSet.insert(interval);
    }

    for(auto finterval : finalSet) {
        (*Lorig).push_back(finterval);
    }
}

void setR(vector<Interval> *Rorig, vector<Interval>& L1, vector<Interval>& R1, vector<Interval>& L2, vector<Interval>& R2) {
    set<Interval> s, finalSet;
    
    //R2/LR
    s = setMinusLRHelper(L1, L1, R2);

    //s --> now union with R1
    for(auto interval : s) {
        finalSet.insert(interval);
    }

    for(auto interval : R1) {
        finalSet.insert(interval);
    }

    for(auto &finterval : finalSet) {
        (*Rorig).push_back(finterval);
    }
}


void setP(vector<float> *P, vector<float> P1, vector<float> P2) {
    set<float> P1UnionP2;

    for(auto p1 : P1) {
        P1UnionP2.insert(p1);
    }

    for(auto p2 : P2) {
        P1UnionP2.insert(p2);
    }

    for(auto p : P1UnionP2) {
        (*P).push_back(p);
    }
}

float findMedianCoord(vector<Edge> V, vector<Edge>& V1, vector<Edge>& V2) {
    vector<float> points;
    
    for(auto &v : V) 
        points.push_back(v.getCoord());

    sort(points.begin(), points.end());

    float median;

    if(points.size() &1) {
        int x = points.size()/2 + 1;
        median = points[x];
    }
    else {
        int x = points.size()/2;
        int y = x - 1;
        median = (points[x] + points[y])/2;
    }

    for(auto &v : V) {
        if(v.getCoord() < median) {
            V1.push_back(v);
        }
        else {
            V2.push_back(v);
        }
    }

    //cout << median << endl;
    return median;
}

vector<Stripe> copy(vector<Stripe> *S, vector<float> *P, Interval I) {

}

void blacken(vector<Stripe> *S, set<Interval> *intervals) {

}

vector<Stripe> concat(vector<Stripe> *S1, vector<Stripe> *S2, vector<float> *P, Interval x_ext) {

}

void Stripes(vector<Edge> V, Interval x_ext, vector<Interval> *L, vector<Interval> *R, vector<float> *P, vector<Stripe> *S) {
    if(V.size() == 1) {
        Edge edge = V[0];

        if(edge.getEdgeType() == "left") {
            (*L).push_back(edge.getInterval());
        } else {
            (*R).push_back(edge.getInterval());
        }

        (*P).push_back(INT_MIN);
        (*P).push_back(edge.getInterval().getBottom());
        (*P).push_back(edge.getInterval().getTop());
        (*P).push_back(INT_MAX);

        vector<Interval> intervals = partition(*P);

        for(auto interval : intervals) {
            vector<Interval> temp;
            Stripe* stripe = new Stripe(x_ext, interval, temp);
            (*S).push_back(*stripe);
        }

        for(int i = 0;i < (*S).size(); i++) {
            Interval interval = ((*S)[i]).getYInterval();
            if(interval.getBottom() == edge.getInterval().getBottom() && interval.getTop() == edge.getInterval().getTop()) {
                Interval *tempInterval;

                if(edge.getEdgeType() == "left") {
                    tempInterval = new Interval(edge.getCoord(), x_ext.getTop());
                } else {
                    tempInterval = new Interval(x_ext.getBottom(), edge.getCoord());
                }

                vector<Interval> temp;
                temp.push_back(*tempInterval);
                ((*S)[i]).setXunion(temp);
            }
        }

        return;
    } else {
        vector<Interval> L1, L2, R1, R2;
        vector<float> P1, P2;
        vector<Stripe> S1, S2;
        vector<Edge> V1, V2;

        float xm = findMedianCoord(V, V1, V2);

        Interval *i1 = new Interval(x_ext.getBottom(), xm);
        Stripes(V1, *i1, &L1, &R1, &P1, &S1);

        Interval *i2 = new Interval(xm, x_ext.getTop());
        Stripes(V2, *i2, &L2, &R2, &P2, &S2);

        setL(L, L1, R1, L2, R2);
        setR(R, L1, R1, L2, R2);
        setP(P, P1, P2);

        S1 = copy(&S1, &P1, *i1);
        S2 = copy(&S2, &P2, *i2);

        set<Interval> R2minusLR, L1minusLR;
        
        R2minusLR = setMinusLRHelper(R2, L1, R2);
        L1minusLR = setMinusLRHelper(L1, L1, R2);

        blacken (&S1, &R2minusLR);
        blacken (&S2, &L1minusLR);

        *S = concat(&S1, &S2, &P, x_ext);

        //calculate measure
        
    }
}

vector<Stripe> RectangleDAC(vector<Rectangle> rect) {

    vector<Edge> V;
    vector<Stripe> S;
    vector<float> P;

    for(auto rectangle: rect) {
        Point p1 = rectangle.getP1();
        Point p2 = rectangle.getP2();

        Interval *interval = new Interval(p1.getY(), p2.getY());

        Edge *leftEdge = new Edge(*interval, p1.getX(), "left");
        Edge *rightEdge = new Edge(*interval, p2.getX(), "right");

        V.push_back(*leftEdge);
        V.push_back(*rightEdge);

        P.push_back(p1.getY());
        P.push_back(p2.getY());
    }

    Interval *interval = new Interval(INT_MIN, INT_MAX);
    vector<Interval> temp;
    P.push_back(INT_MIN);
    P.push_back(INT_MAX);
    
    Stripes(V, *interval, &temp, &temp, &P, &S);
    return S;
}


//int main() {
//    return 0;
//}