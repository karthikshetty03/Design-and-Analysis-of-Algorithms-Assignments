#include <bits/stdc++.h>
#include "primitives.hpp"
#include "contour.hpp"
using namespace std;

///Tree traversall to find leaf node coords
void Contour::inorder(ctree *tree)
{
    ///<
    if (!tree)
        return;

    this->inorder(tree->left);

    if (tree->edgeType != "undef")
        this->TreeCoords.push_back(tree->coord);

    this->inorder(tree->right);
}

///Make intervals of coordinates in vector TreeCoords
vector<Interval> Contour::makeIntervals()
{
    ///<
    vector<Interval> intervals;
    Interval *interval;

    if (this->TreeCoords.size() == 0)
    {
        return intervals;
    }

    for (int i = 1; i < this->TreeCoords.size(); i++)
    {
        interval = new Interval(this->TreeCoords[i - 1], this->TreeCoords[i]);
        intervals.push_back(*interval);
        i++;
    }

    return intervals;
}

///Helper function to call inorder traversal function and makeINtervals together
vector<Interval> Contour::stripeIntervals(StripePrime s)
{
    ///<
    this->TreeCoords.clear();
    inorder(s.tree);
    vector<Interval> intervals = makeIntervals();
    //cout <<"INTERVALS: "<<this->TreeCoords.size()<<endl;
    //for(auto x : intervals)
    //    cout << x.getBottom() <<" "<<x.getTop()<<endl;
    return intervals;
}

///function that calculates contour pieces corresponding to a [articular edge
vector<Edge> Contour::contour_pieces(Edge h, vector<StripePrime> &S)
{
    ///<
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

    intervals = this->stripeIntervals(*sDash);
    vector<Interval> ans;

    float bottom = h.getInterval().getBottom();
    float top = h.getInterval().getTop();

    //cout <<h.getCoord()<<": "<<bottom<<" "<<top<<endl;

    ///< Intersection with the edge
    for (auto x : intervals)
    {
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

    sort(ans.begin(), ans.end(), [](auto &lhs, auto &rhs) {
        if (lhs.getBottom() == rhs.getBottom())
            return lhs.getTop() < rhs.getTop();
        return lhs.getBottom() < rhs.getBottom();
    });

    vector<Interval> finAns;
    Interval *temp = new Interval(bottom, top);
    finAns.push_back(*temp);

    ///< Minus operation on intersection set from edge interval
    for (auto x : ans)
    {
        int bottomn = x.getBottom();
        int topn = x.getTop();
        vector<Interval> finNew;

        for (auto y : finAns)
        {
            if (y.getTop() <= bottomn or y.getBottom() >= topn)
            {
                Interval *temp = new Interval(y.getBottom(), y.getTop());
                finNew.push_back(*temp);
            }
            else
            {
                //3-8, 4-6
                if (y.getBottom() != bottomn)
                {
                    Interval *temp = new Interval(y.getBottom(), bottomn);
                    finNew.push_back(*temp);
                }

                if (y.getTop() != topn)
                {
                    Interval *temp = new Interval(topn, y.getTop());
                    finNew.push_back(*temp);
                }
            }
        }

        finAns.clear();

        for (auto it : finNew)
        {
            finAns.push_back(it);
        }
    }

    vector<Edge> edges;
    //cout << "FINANS"<<endl;
    for (auto x : finAns)
    {
        //cout << x.getBottom() <<" "<< x.getTop()<<endl;
        Edge *edge = new Edge(x, h.getCoord(), "undef");
        edges.push_back(*edge);
    }

    return edges;
}

///function to call contour stripes on each edge in a loop
vector<Edge> Contour::contour(vector<Edge> &H, vector<StripePrime> &S)
{
    ///<
    vector<Edge> ans;

    for (auto h : H)
    {
        vector<Edge> partAns = this->contour_pieces(h, S);

        for (auto edge : partAns)
        {
            ans.push_back(edge);
        }
    }

    return ans;
}

/// function to return intervals after partition
vector<Interval> Contour::partition(vector<float> coords)
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
vector<Interval> Contour::setMinusLRHelper(vector<Interval> minusFrom, vector<Interval> &L1, vector<Interval> &R2)
{
    ///<
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
void Contour::setL(vector<Interval> &Lorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2)
{
    ///<
    vector<Interval> s, finalSet;

    ///< L1/LR
    s = this->setMinusLRHelper(L1, L1, R2);

    ///< s --> now union with l2
    for (auto &interval : s)
        finalSet.push_back(interval);

    for (auto &interval : L2)
        finalSet.push_back(interval);

    for (auto &finterval : finalSet)
        Lorig.push_back(finterval);
}

/// function to perform R1 union (R2/LR) and push to Lorig
void Contour::setR(vector<Interval> &Rorig, vector<Interval> &L1, vector<Interval> &R1, vector<Interval> &L2, vector<Interval> &R2)
{
    vector<Interval> s, finalSet;

    ///< R2/LR
    s = this->setMinusLRHelper(R2, L1, R2);

    ///< s --> now union with R1
    for (auto &interval : s)
        finalSet.push_back(interval);

    for (auto &interval : R1)
        finalSet.push_back(interval);

    for (auto &finterval : finalSet)
        Rorig.push_back(finterval);
}

/// function to calculate union of P1 and P2
void Contour::setP(vector<float> &P, vector<float> P1, vector<float> P2)
{
    ///<
    set<float> P1UnionP2;

    for (auto &p1 : P1)
        P1UnionP2.insert(p1);

    for (auto &p2 : P2)
        P1UnionP2.insert(p2);

    for (auto &p : P1UnionP2)
        P.push_back(p);
}

bool custom_sorter1(Edge &lhs, Edge &rhs)
{
    if (lhs.getCoord() == rhs.getCoord())
    {
        if (lhs.getEdgeType() == "left")
            return true;
        else
            return false;
    }

    return lhs.getCoord() < rhs.getCoord();
}

/// function to calculate median of edge sets V1 and V2
float Contour::findMedianCoord(vector<Edge> V, vector<Edge> &V1, vector<Edge> &V2)
{
    ///<
    V1.clear();
    V2.clear();

    sort(V.begin(), V.end(), custom_sorter1);
    float median;

    int x = V.size() / 2;
    median = V[x].getCoord();

    for (int i = 0; i < x; i++)
    {
        V1.push_back(V[i]);
    }

    for (int i = x; i < V.size(); i++)
    {
        V2.push_back(V[i]);
    }

    return median;
}

/// helper function to check for subset of a set
bool Contour::properSubset(Interval A, Interval B)
{
    ///<
    return A.getBottom() >= B.getBottom() and A.getTop() <= B.getTop();
}

/// The copy function that returns stripes
vector<StripePrime> Contour::copy(vector<StripePrime> &S, vector<float> &P, Interval I)
{
    ///<
    vector<Interval> intervals = partition(P);
    vector<StripePrime> Sdash;
    ctree *tree = NULL;

    for (auto &interval : intervals)
    {
        StripePrime *S1 = new StripePrime(I, interval, tree);
        Sdash.push_back(*S1);
    }

    for (auto &stripeDash : Sdash)
    {
        for (auto &stripe : S)
        {
            if (properSubset(stripeDash.getYInterval(), stripe.getYInterval()))
            {
                if(stripe.tree) {
                    stripeDash.setTree(stripe.tree);
                    break;
                }
            }
        }
    }

    return Sdash;
}

/// The blacken function
void Contour::blacken(vector<StripePrime> &S, vector<Interval> &J)
{
    ///<
    for (auto &stripe : S)
    {
        for (auto &interval : J)
        {
            if (properSubset(stripe.getYInterval(), interval))
            {
                ctree *tree = NULL;
                stripe.setTree(tree);
            }
        }
    }
}

/// The concat function
vector<StripePrime> Contour::concat(vector<StripePrime> &S1, vector<StripePrime> &S2, vector<float> &P, Interval x_ext)
{
    ///<
    vector<Interval> intervals = partition(P);
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

        for (auto &s1 : S1)
        {
            if (s1.getYInterval().getBottom() == stripeDash.getYInterval().getBottom() and
                s1.getYInterval().getTop() == stripeDash.getYInterval().getTop())
            {
                s1Dash = &s1;
                break;
            }
        }

        for (auto &s2 : S2)
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

/// The main divide and conquer algorithm to calculate stripes
void Contour::Stripes(vector<Edge> &V, Interval x_ext, vector<Interval> &L, vector<Interval> &R, vector<float> &P, vector<StripePrime> &S)
{
    ///<
    if (V.size() == 1)
    {
        Edge edge = V[0];

        if (edge.getEdgeType() == "left")
        {
            L.push_back(edge.getInterval());
        }
        else
        {
            R.push_back(edge.getInterval());
        }

        P.push_back(INT_MIN);
        P.push_back(edge.getInterval().getBottom());
        P.push_back(edge.getInterval().getTop());
        P.push_back(INT_MAX);

        vector<Interval> intervals = this->partition(P);

        //A) --> S: = {(i x, iy, 0) ] ix = x e x t and i y ~ p a r t i t i o n (P)}
        for (auto &interval : intervals)
        {
            ctree *temp = NULL;
            StripePrime *stripe = new StripePrime(x_ext, interval, temp);
            S.push_back(*stripe);
        }

        for (int i = 0; i < (S).size(); i++)
        {
            Interval interval = ((S)[i]).getYInterval();

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

                S[i].setTree(tree);
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
        float xm = this->findMedianCoord(V, V1, V2);

        Interval *i1 = new Interval(x_ext.getBottom(), xm);
        Interval *i2 = new Interval(xm, x_ext.getTop());

        //COnquer
        this->Stripes(V1, *i1, L1, R1, P1, S1);
        this->Stripes(V2, *i2, L2, R2, P2, S2);

        //Merge
        this->setL(L, L1, R1, L2, R2);

        this->setR(R, L1, R1, L2, R2);
        this->setP(P, P1, P2);

        S_left = this->copy(S1, P, *i1);
        S_right = this->copy(S2, P, *i2);

        vector<Interval> R2minusLR, L1minusLR;

        R2minusLR = this->setMinusLRHelper(R2, L1, R2);
        L1minusLR = this->setMinusLRHelper(L1, L1, R2);

        this->blacken(S_left, R2minusLR);
        this->blacken(S_right, L1minusLR);

        S = this->concat(S_left, S_right, P, x_ext);
    }
}

/// Stripes function is called and then further contours to return conour peices mapped to corressponding y-stripes
map<int, vector<Interval>> Contour::RectangleDAC2(vector<Rectangle> rect)
{
    ///<
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

    this->Stripes(V, *interval, temp1, temp2, P, S);

    vector<Edge> contourPieces = contour(H, S);
    map<int, vector<Edge>> stripeContours;
    map<int, vector<Interval>> newStripeContours;

    for (auto x : contourPieces)
    {
        stripeContours[x.getCoord()].push_back(x);
    }

    for (auto &x : stripeContours)
    {
        sort(x.second.begin(), x.second.end(), [](auto &lhs, auto &rhs) {
            if (lhs.getInterval().getBottom() == rhs.getInterval().getBottom())
                return lhs.getInterval().getTop() < rhs.getInterval().getTop();
            return lhs.getInterval().getBottom() < rhs.getInterval().getBottom();
        });

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
        cout << "<--- Stripe " << x.first << " --->" << endl;
        for (auto y : x.second)
            cout << y.getBottom() << " " << y.getTop() << endl;
        cout << endl;
    }

    return newStripeContours;
}