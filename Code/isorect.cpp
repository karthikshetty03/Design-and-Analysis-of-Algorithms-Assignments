#include <bits/stdc++.h>
#include "primitives.hpp"
#include "isorect.hpp"
using namespace std;

///function to calculate measures using y-stripes and x-unions
float isorect::measure(vector<Stripe> stripe)
{
    ///<
    float ans = 0;

    for (int i = 1; i < stripe.size() - 1; i++)
    {
        ans += stripe[i].x_union * (stripe[i].getYInterval().getTop() - stripe[i].getYInterval().getBottom());
    }

    return ans;
}

/// helper function to print stripes
void isorect::printStripe(vector<Stripe> S)
{
    ///<
    cout << "X UNIONS :" << endl;

    for (auto &stripe : S)
        cout << stripe.x_union << endl;
}

/// helper function to partition and return the intervals
vector<Interval> isorect::partition1(vector<float> coords)
{
    ///<
    vector<Interval> intervals;
    sort(coords.begin(), coords.end());

    for (int i = 0; i < coords.size() - 1; i++)
    {
        float y1 = coords[i];
        float y2 = coords[i + 1];

        if (y1 != y2)
        {
            Interval *interval = new Interval(y1, y2);
            intervals.push_back(*interval);
        }
    }

    return intervals;
}

/// helper function to calculate set/ LR
vector<Interval> isorect::setMinusLRHelper1(vector<Interval> minusFrom, vector<Interval> &L1, vector<Interval> &R2)
{
    vector<Interval> s;

    ///< find L1 intersection R2 (LR) --> s
    for (auto &l1 : L1)
    {
        for (auto &r2 : R2)
        {
            if (l1.getBottom() == r2.getBottom() and l1.getTop() == r2.getTop())
            {
                s.push_back(l1);
            }
        }
    }

    ///< remove elements of LR (--> s) if nay from minusFromSet
    for (auto &x : s)
    {
        auto itr = minusFrom.begin();
        for (auto &ele : minusFrom)
        {
            if (x.getBottom() == ele.getBottom() and x.getTop() == ele.getTop())
            {
                minusFrom.erase(itr);
            }

            itr++;
        }
    }

    return minusFrom;
}

/// function to perform L2 union (l1/LR) and push to Lorig
void isorect::setL1(vector<Interval> *Lorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2)
{
    vector<Interval> s, finalSet;

    ///< L1/LR
    s = this->setMinusLRHelper1(L1, L1, R2);

    ///< s --> now union with l2
    for (auto &interval : s)
        finalSet.push_back(interval);

    for (auto &interval : L2)
        finalSet.push_back(interval);

    for (auto &finterval : finalSet)
        (*Lorig).push_back(finterval);
}

/// function to perform R1 union (R2/LR) and push to Lorig
void isorect::setR1(vector<Interval> *Rorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2)
{
    vector<Interval> s, finalSet;

    ///< R2/LR
    s = this->setMinusLRHelper1(R2, L1, R2);

    ///< s --> now union with R1
    for (auto &interval : s)
        finalSet.push_back(interval);

    for (auto &interval : R1)
        finalSet.push_back(interval);

    for (auto &finterval : finalSet)
        (*Rorig).push_back(finterval);
}

/// function to calculate union of P1 and P2
void isorect::setP1(vector<float> *P, vector<float> P1, vector<float> P2)
{
    ///<
    set<float> P1UnionP2;

    for (auto &p1 : P1)
        P1UnionP2.insert(p1);

    for (auto &p2 : P2)
        P1UnionP2.insert(p2);

    for (auto &p : P1UnionP2)
        (*P).push_back(p);
}

bool cmp(Edge a, Edge b)
{
    return a.getCoord() < b.getCoord();
}

/// function to calculate median of edge sets V1 and V2
float isorect::findMedianCoord1(vector<Edge> V, vector<Edge> &V1, vector<Edge> &V2)
{
    vector<float> points;
    set<float> s;

    sort(V.begin(), V.end(), cmp);

    for (auto &v : V)
        s.insert(v.getCoord());

    for (auto x : s)
        points.push_back(x);

    sort(points.begin(), points.end());

    float median;

    if (points.size() & 1)
    {
        int x = points.size() / 2;
        median = points[x];
    }
    else
    {
        int x = points.size() / 2;
        int y = x - 1;
        median = (points[x] + points[y]) / 2;
    }

    set<float> temp;

    for (auto &v : V)
    {

        if (v.getCoord() < median)
        {
            V1.push_back(v);
        }
        else
        {
            V2.push_back(v);
        }
    }

    if (V1.size() == 0 and V2.size() >= 2)
    {
        V1.push_back(V2[0]);
        V2.erase(V2.begin());
    }

    return median;
}

/// helper function to check for subset of a set
bool isorect::properSubset1(Interval A, Interval B)
{
    ///<
    return A.getBottom() >= B.getBottom() and A.getTop() <= B.getTop();
}

/// The copy function that returns stripes
vector<Stripe> isorect::copy1(vector<Stripe> *S, vector<float> *P, Interval I)
{
    ///<
    vector<Interval> intervals = this->partition1(*P);
    vector<Stripe> Sdash;
    float temp = 0;

    for (auto &interval : intervals)
    {
        Stripe *S1 = new Stripe(I, interval, temp);
        Sdash.push_back(*S1);
    }

    for (auto &stripeDash : Sdash)
    {
        for (auto &stripe : *S)
        {
            if (properSubset1(stripeDash.getYInterval(), stripe.getYInterval()))
            {
                if (stripe.x_union < 1e9)
                {
                    stripeDash.setXunion(stripe.x_union);
                    break;
                }
            }
        }
    }

    return Sdash;
}

/// The blacken function
void isorect::blacken1(vector<Stripe> *S, vector<Interval> *J)
{
    ///<
    for (auto &stripe : *S)
    {
        for (auto &interval : *J)
        {
            if (properSubset1(stripe.getYInterval(), interval))
            {
                float temp = stripe.getXInterval().getTop() - stripe.getXInterval().getBottom();
                if (temp < 1e9)
                {
                    stripe.setXunion(temp);
                    break;
                }
            }
        }
    }
}

/// The concat function
vector<Stripe> isorect::concat1(vector<Stripe> *S1, vector<Stripe> *S2, vector<float> *P, Interval x_ext)
{
    ///<
    vector<Interval> intervals = this->partition1(*P);
    vector<Stripe> Sdash;
    float temp = 0;

    for (auto &interval : intervals)
    {
        Stripe *S = new Stripe(x_ext, interval, temp);
        Sdash.push_back(*S);
    }

    for (auto &stripeDash : Sdash)
    {
        float ans = 0;

        for (auto &s1 : *S1)
        {
            if (s1.getYInterval().getBottom() == stripeDash.getYInterval().getBottom() and
                s1.getYInterval().getTop() == stripeDash.getYInterval().getTop())
            {
                ans += s1.x_union;
                break;
            }
        }

        for (auto &s2 : *S2)
        {
            if (s2.getYInterval().getBottom() == stripeDash.getYInterval().getBottom() and
                s2.getYInterval().getTop() == stripeDash.getYInterval().getTop())
            {
                ans += s2.x_union;
                break;
            }
        }

        stripeDash.setXunion(ans);
    }

    return Sdash;
}

/// The main divide and conquer algorithm to calculate stripes
void isorect::Stripes1(vector<Edge> V, Interval x_ext, vector<Interval> *L, vector<Interval> *R, vector<float> *P, vector<Stripe> *S)
{
    ///<
    if (V.size() == 1)
    {
        Edge edge = V[0];
        // (*L).clear();
        // (*R).clear();
        // (*P).clear();
        // (*S).clear();

        if (edge.getEdgeType() == "left")
        {
            (*L).push_back(edge.getInterval());
        }
        else
        {
            (*R).push_back(edge.getInterval());
        }

        (*P).push_back(INT_MIN);
        (*P).push_back(edge.getInterval().getBottom());
        (*P).push_back(edge.getInterval().getTop());
        (*P).push_back(INT_MAX);

        vector<Interval> intervals = this->partition1(*P);

        for (auto &interval : intervals)
        {
            float temp = 0;
            Stripe *stripe = new Stripe(x_ext, interval, temp);
            (*S).push_back(*stripe);
        }

        for (int i = 0; i < (*S).size(); i++)
        {
            Interval interval = ((*S)[i]).getYInterval();

            if (interval.getBottom() == edge.getInterval().getBottom() and
                interval.getTop() == edge.getInterval().getTop())
            {
                float tempInterval;

                if (edge.getEdgeType() == "left")
                {
                    tempInterval = x_ext.getTop() - edge.getCoord();
                }
                else
                {
                    tempInterval = edge.getCoord() - x_ext.getBottom();
                }

                ((*S)[i]).setXunion(tempInterval);
            }
        }
    }
    else
    {
        vector<Interval> L1, L2, R1, R2;
        vector<float> P1, P2;
        vector<Stripe> S1, S2, S_left, S_right;
        vector<Edge> V1, V2;

        //DIvide
        float xm = this->findMedianCoord1(V, V1, V2);

        Interval *i1 = new Interval(x_ext.getBottom(), xm);
        Interval *i2 = new Interval(xm, x_ext.getTop());

        //COnquer
        this->Stripes1(V1, *i1, &L1, &R1, &P1, &S1);
        this->Stripes1(V2, *i2, &L2, &R2, &P2, &S2);

        //Merge
        this->setL1(L, L1, R1, L2, R2);
        this->setR1(R, L1, R1, L2, R2);
        this->setP1(P, P1, P2);

        S_left = this->copy1(&S1, P, *i1);
        S_right = this->copy1(&S2, P, *i2);

        vector<Interval> R2minusLR, L1minusLR;

        R2minusLR = this->setMinusLRHelper1(R2, L1, R2);
        L1minusLR = this->setMinusLRHelper1(L1, L1, R2);

        this->blacken1(&S_left, &R2minusLR);
        this->blacken1(&S_right, &L1minusLR);

        *S = this->concat1(&S_left, &S_right, P, x_ext);
    }
}

/// Stripes function is called and stripes are returned
vector<Stripe> isorect::RectangleDAC1(vector<Rectangle> rect)
{
    ///<
    vector<Edge> V;
    vector<Stripe> S;
    vector<float> P;

    for (auto &rectangle : rect)
    {
        Point p1 = rectangle.getP1();
        Point p2 = rectangle.getP2();

        Interval *interval = new Interval(p1.getY(), p2.getY());

        Edge *leftEdge = new Edge(*interval, p1.getX(), "left");
        Edge *rightEdge = new Edge(*interval, p2.getX(), "right");

        V.push_back(*leftEdge);
        V.push_back(*rightEdge);
    }

    Interval *interval = new Interval(INT_MIN, INT_MAX);
    vector<Interval> temp1, temp2;

    this->Stripes1(V, *interval, &temp1, &temp2, &P, &S);
    this->printStripe(S);

    return S;
}