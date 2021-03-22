#include <bits/stdc++.h>
#include "primitives.hpp"
using namespace std;
vector<float> TreeCoords;

vector<Interval> makeIntervals()
{
    vector<Interval> intervals;
    Interval *interval;

    if (TreeCoords.size() == 0)
    {
        return intervals;
    }

    for (auto x : TreeCoords)
        cout << x << " ";
    cout << endl;

    for (int i = 1; i < TreeCoords.size(); i++)
    {
        interval = new Interval(TreeCoords[i - 1], TreeCoords[i]);
        intervals.push_back(*interval);
        i++;
    }

    return intervals;
}

void inorder(ctree *tree)
{
    if (!tree)
        return;

    inorder(tree->left);

    if (tree->edgeType != "undef")
        TreeCoords.push_back(tree->coord);

    inorder(tree->right);
}

vector<Interval> stripeIntervals(StripePrime s)
{
    TreeCoords.clear();
    inorder(s.tree);

    cout << "Intervals :" << endl;

    vector<Interval> intervals = makeIntervals();

    for (auto x : intervals)
        cout << x.getBottom() << " " << x.getTop() << endl;
    cout << endl;

    return intervals;
}

vector<Edge> contour_pieces(Edge h, vector<StripePrime> &S)
{
    vector<Interval> intervals;
    StripePrime *sDash;

    if (h.getEdgeType() == "bottom")
    {
        for (auto s : S)
        {
            if (s.getYInterval().getTop() == h.getCoord())
            {
                sDash = &s;
                break;
            }
        }
    }
    else
    {
        for (auto s : S)
        {
            if (s.getYInterval().getBottom() == h.getCoord())
            {
                sDash = &s;
                break;
            }
        }
    }

    cout << h.getCoord() << ": " << h.getInterval().getBottom() << " " << h.getInterval().getTop() << endl;
    intervals = stripeIntervals(*sDash);
    vector<Interval> ans;

    float bottom = h.getInterval().getBottom();
    float top = h.getInterval().getTop();

    //100 - 700
    //intersection
    for (auto x : intervals)
    {
        // 100 - 400
        if (x.getTop() <= bottom or x.getBottom() >= top)
        {
            continue;
        }
        else
        {
            float newBottom = max(bottom, x.getBottom());
            float newTop = min(top, x.getTop());
            Interval *interval = new Interval(newBottom, newTop);
            ans.push_back(*interval);
        }
    }

    vector<Interval> finAns;
    int flag = 0;

    for (auto &x : ans)
    {
        //100 - 400
        //400 - 700
        if (x.getTop() < top and x.getBottom() > bottom)
        {
            Interval *i1 = new Interval(bottom, x.getBottom());
            Interval *i2 = new Interval(x.getTop(), top);
            finAns.push_back(*i1);
            finAns.push_back(*i2);
            flag = 1;
        }
        else if (x.getTop() == top and x.getBottom() == bottom)
        {
            flag = 1;
        }
        else
        {
            if (x.getBottom() > bottom)
            {
                top = x.getBottom();   
            }
            else if (x.getTop() < top)
            {
                bottom = x.getTop();
            }
        }
    }

    if (!flag)
    {
        Interval *interval = new Interval(bottom, top);
        finAns.push_back(*interval);
    }

    vector<Edge> edges;

    for (auto fin : finAns)
    {
        Edge *edge = new Edge(fin, h.getCoord(), h.getEdgeType());
        edges.push_back(*edge);
    }

    return edges;
}

vector<Edge> contour(vector<Edge> &H, vector<StripePrime> &S)
{
    vector<Edge> ans;

    for (auto h : H)
    {
        vector<Edge> partAns = contour_pieces(h, S);
        for (auto edge : partAns)
        {
            ans.push_back(edge);
        }
    }

    return ans;
}

/*
1 3 2 4
1 1 2 2
2 2 3 3
3 3 4 4
3 1 4 2
*/

vector<Interval> partition(vector<float> coords)
{
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

vector<Interval> setMinusLRHelper(vector<Interval> minusFrom, vector<Interval> &L1, vector<Interval> &R2)
{
    vector<Interval> s;

    //find L1 intersection R2 (LR) --> s
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

    //remove elements of LR (--> s) if nay from minusFromSet
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

void setL(vector<Interval> *Lorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2)
{
    vector<Interval> s, finalSet;

    //L1/LR
    s = setMinusLRHelper(L1, L1, R2);

    //s --> now union with l2
    for (auto &interval : s)
        finalSet.push_back(interval);

    for (auto &interval : L2)
        finalSet.push_back(interval);

    for (auto &finterval : finalSet)
        (*Lorig).push_back(finterval);
}

void setR(vector<Interval> *Rorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2)
{
    vector<Interval> s, finalSet;

    //R2/LR
    s = setMinusLRHelper(R2, L1, R2);

    //s --> now union with R1
    for (auto &interval : s)
        finalSet.push_back(interval);

    for (auto &interval : R1)
        finalSet.push_back(interval);

    for (auto &finterval : finalSet)
        (*Rorig).push_back(finterval);
}

void setP(vector<float> *P, vector<float> P1, vector<float> P2)
{
    set<float> P1UnionP2;

    for (auto &p1 : P1)
        P1UnionP2.insert(p1);

    for (auto &p2 : P2)
        P1UnionP2.insert(p2);

    for (auto &p : P1UnionP2)
        (*P).push_back(p);
}

float findMedianCoord(vector<Edge> V, vector<Edge> &V1, vector<Edge> &V2)
{

    vector<float> points;
    set<float> s;

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

bool properSubset(Interval A, Interval B)
{
    return A.getBottom() >= B.getBottom() and A.getTop() <= B.getTop();
}

vector<StripePrime> copy(vector<StripePrime> *S, vector<float> *P, Interval I)
{
    vector<Interval> intervals = partition(*P);
    vector<StripePrime> Sdash;
    ctree *tree = NULL;

    for (auto &interval : intervals)
    {
        StripePrime *S1 = new StripePrime(I, interval, tree);
        Sdash.push_back(*S1);
    }

    for (auto &stripeDash : Sdash)
    {
        for (auto &stripe : *S)
        {
            if (properSubset(stripeDash.getYInterval(), stripe.getYInterval()))
            {
                stripeDash.setTree(stripe.tree);
                break;
            }
        }
    }

    return Sdash;
}

void blacken(vector<StripePrime> *S, vector<Interval> *J)
{
    for (auto &stripe : *S)
    {
        for (auto &interval : *J)
        {
            if (properSubset(stripe.getYInterval(), interval))
            {
                ctree *tree = NULL;
                stripe.setTree(tree);
                break;
            }
        }
    }
}

vector<StripePrime> concat(vector<StripePrime> *S1, vector<StripePrime> *S2, vector<float> *P, Interval x_ext)
{
    vector<Interval> intervals = partition(*P);
    vector<StripePrime> Sdash;
    ctree *tree = NULL;

    for (auto &interval : intervals)
    {
        StripePrime *S = new StripePrime(x_ext, interval, tree);
        Sdash.push_back(*S);
    }

    for (auto &stripeDash : Sdash)
    {
        float ans = 0;
        StripePrime *s1Dash, *s2Dash;

        for (auto &s1 : *S1)
        {
            if (s1.getYInterval().getBottom() == stripeDash.getYInterval().getBottom() and
                s1.getYInterval().getTop() == stripeDash.getYInterval().getTop())
            {
                s1Dash = &s1;
                break;
            }
        }

        for (auto &s2 : *S2)
        {
            if (s2.getYInterval().getBottom() == stripeDash.getYInterval().getBottom() and
                s2.getYInterval().getTop() == stripeDash.getYInterval().getTop())
            {
                s2Dash = &s2;
                break;
            }
        }

        if (s1Dash->tree and s2Dash->tree and s1Dash->tree != s2Dash->tree)
        {
            ctree *tree = new ctree(s1Dash->getXInterval().getTop(), "undef", s1Dash->tree, s2Dash->tree);
            stripeDash.setTree(tree);
        }
        else if (s1Dash->tree and !s2Dash->tree)
        {
            stripeDash.setTree(s1Dash->tree);
        }
        else if (!s1Dash->tree and s2Dash->tree)
        {
            stripeDash.setTree(s2Dash->tree);
        }
        else
        {
            stripeDash.setTree(NULL);
        }
    }

    return Sdash;
}

void Stripes(vector<Edge> V, Interval x_ext, vector<Interval> *L, vector<Interval> *R, vector<float> *P, vector<StripePrime> *S)
{
    if (V.size() == 1)
    {
        Edge edge = V[0];
        (*L).clear();
        (*R).clear();
        (*P).clear();
        (*S).clear();

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

        vector<Interval> intervals = partition(*P);

        //A) --> S: = {(i x, iy, 0) ] ix = x e x t and i y ~ p a r t i t i o n (P)}
        for (auto &interval : intervals)
        {
            ctree *temp = NULL;
            StripePrime *stripe = new StripePrime(x_ext, interval, temp);
            (*S).push_back(*stripe);
        }

        for (int i = 0; i < (*S).size(); i++)
        {
            Interval interval = ((*S)[i]).getYInterval();

            if (interval.getBottom() == edge.getInterval().getBottom() and
                interval.getTop() == edge.getInterval().getTop())
            {
                ctree *tree;

                if (edge.getEdgeType() == "left")
                {
                    tree = new ctree(edge.getCoord(), "left", NULL, NULL);
                }
                else
                {
                    tree = new ctree(edge.getCoord(), "right", NULL, NULL);
                }

                ((*S)[i]).setTree(tree);
            }
        }
    }
    else
    {
        vector<Interval> L1, L2, R1, R2;
        vector<float> P1, P2;
        vector<StripePrime> S1, S2, S_left, S_right;
        vector<Edge> V1, V2;

        //DIvide
        float xm = findMedianCoord(V, V1, V2);

        Interval *i1 = new Interval(x_ext.getBottom(), xm);
        Interval *i2 = new Interval(xm, x_ext.getTop());

        //COnquer
        Stripes(V1, *i1, &L1, &R1, &P1, &S1);
        Stripes(V2, *i2, &L2, &R2, &P2, &S2);

        //Merge
        setL(L, L1, R1, L2, R2);

        setR(R, L1, R1, L2, R2);
        setP(P, P1, P2);

        S_left = copy(&S1, P, *i1);
        S_right = copy(&S2, P, *i2);

        vector<Interval> R2minusLR, L1minusLR;

        R2minusLR = setMinusLRHelper(R2, L1, R2);
        L1minusLR = setMinusLRHelper(L1, L1, R2);

        blacken(&S_left, &R2minusLR);
        blacken(&S_right, &L1minusLR);

        *S = concat(&S_left, &S_right, P, x_ext);
    }
}

map<int, vector<Interval>> RectangleDAC2(vector<Rectangle> rect)
{

    vector<Edge> V;
    vector<StripePrime> S;
    vector<float> P;
    vector<Edge> H;

    for (auto &rectangle : rect)
    {
        Point p1 = rectangle.getP1();
        Point p2 = rectangle.getP2();

        Interval *interval = new Interval(p1.getY(), p2.getY());
        Interval *horizon = new Interval(p1.getX(), p2.getX());

        Edge *leftEdge = new Edge(*interval, p1.getX(), "left");
        Edge *rightEdge = new Edge(*interval, p2.getX(), "right");

        Edge *horizonBottomEdge = new Edge(*horizon, p1.getY(), "bottom");
        Edge *horizonTopEdge = new Edge(*horizon, p2.getY(), "top");

        V.push_back(*leftEdge);
        V.push_back(*rightEdge);

        H.push_back(*horizonBottomEdge);
        H.push_back(*horizonTopEdge);
    }

    Interval *interval = new Interval(INT_MIN, INT_MAX);
    vector<Interval> temp1, temp2;

    Stripes(V, *interval, &temp1, &temp2, &P, &S);

    vector<Edge> contourPieces = contour(H, S);
    map<int, vector<Edge>> stripeContours;
    map<int, vector<Interval>> newStripeContours;

    for (auto x : contourPieces)
    {
        stripeContours[x.getCoord()].push_back(x);
    }

    for (auto x : stripeContours)
    {
        int start = x.second[0].getInterval().getBottom();
        int end = x.second[0].getInterval().getTop();
        vector<Interval> ans;

        for (int i = 1; i < x.second.size(); i++)
        {

            if (x.second[i].getInterval().getBottom() <= end)
            {
                end = max(end, (int)x.second[i].getInterval().getTop());
            }
            else
            {
                Interval *temp = new Interval(start, end);
                ans.push_back(*temp);

                start = x.second[i].getInterval().getBottom();
                end = x.second[i].getInterval().getTop();
            }
        }

        Interval *temp = new Interval(start, end);
        ans.push_back(*temp);

        newStripeContours[x.first] = ans;
    }

    for (auto x : newStripeContours)
    {
        cout << "Stripe : " << x.first << endl;

        for (auto y : x.second)
        {
            cout << y.getBottom() << " " << y.getTop() << endl;
        }
    }

    return newStripeContours;

    /*
    1 2 3 4
    2 1 4 4
    5 3 6 6
    */
}