/*
Authors:
    Shetty Karthik Ravindra (2018A7PS0141H)
    Abhirath Singh Parmar (2018A7PS0520H)
    Koustubh Sharma (2018A7PS0114H)
    Rishabh Baid (2018A7PS)
*/

/*
Project Structure :

               | contour.cpp --> contour.hpp  |
 main.cpp ---> |                              | --> primitves.cpp  ---> primitves.hpp
               | isorect.cpp --> isorect.hpp  |

*/

/*

Compile and Run:
g++ main.cpp isorect.cpp contour.cpp primitives.cpp -o combined -lGL -lGLU -lglut
./combined

*/

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "isorect.hpp"
#include "contour.hpp"
using namespace std;

int inputMode;
bool isTopLeft = false;
Point *P1, *P2;
Rectangle *rect;
int selected = -1;    //-1 if no point selected, index of that point if some point is selected
int selectedPart = 0; //1 if bottom right selected, 2 if top left, 0 if none

vector<Rectangle> rectangles;

void printStripes(vector<Stripe> S)
{

    cout << "Y STRIPES:" << endl;
    for (auto stripe : S)
    {
        cout << stripe.getYInterval().getBottom() << " " << stripe.getYInterval().getTop() << endl;
    }
}

// to get the index of a selected point for deletion/dragging
int indexOf(float x, float y)
{
    for (int i = 0; i < rectangles.size(); i++)
    {
        //cout<<i;
        if (rectangles[i].getP1().getX() > x - 5 && rectangles[i].getP1().getX() < x + 5 && rectangles[i].getP1().getY() > y - 5 && rectangles[i].getP1().getY() < y + 5)
        {
            selectedPart = 1;
            return i;
        }
        if (rectangles[i].getP2().getX() > x - 5 && rectangles[i].getP2().getX() < x + 5 && rectangles[i].getP2().getY() > y - 5 && rectangles[i].getP2().getY() < y + 5)
        {
            selectedPart = 2;
            return i;
        }
    }

    return -1;
}

// handling mouse controls
void mouse(int button, int state, int x, int y)
{
    //adding new point by clicking left button
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        if (!isTopLeft)
        {
            P1 = new Point(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
            isTopLeft = true;
        }
        else
        {
            P2 = new Point(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
            rect = new Rectangle(*P1, *P2);
            rectangles.push_back(*rect);
            P1 = NULL;
            P2 = NULL;
            rect = NULL;
            isTopLeft = false;
        }
    }

    //dragging a point by pressing right mouse button when the cursor is at a point
    if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
    {
        selected = indexOf(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
    }
    //if no point is selected when middle button is pressed
    if (state == GLUT_UP && button == GLUT_RIGHT_BUTTON)
    {
        selected = -1;
        selectedPart = 0;
    }
    glutPostRedisplay();
}

// function to drag the point and get new coordinates
void drag(int x, int y)
{
    if (selected != -1)
    {
        if (selectedPart == 1)
        {
            Point *q = new Point(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
            rectangles[selected].setP1(*q);
        }
        if (selectedPart == 2)
        {
            Point *q = new Point(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
            rectangles[selected].setP2(*q);
        }
    }
    glutPostRedisplay();
}

// draw the scene on window
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_POINT_SMOOTH);

    for (int i = 0; i < rectangles.size(); i++)
    {
        glBegin(GL_LINE_LOOP);

        float x1 = rectangles[i].getP1().getX();
        float y1 = rectangles[i].getP1().getY();
        float x2 = rectangles[i].getP2().getX();
        float y2 = rectangles[i].getP2().getY();

        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
        glEnd();
        glBegin(GL_POINTS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    glDisable(GL_POINT_SMOOTH);
    glColor3f(0, 0, 0);
    glPointSize(2);
    //drawBezier(control);
    glFlush();
}

// handle window resize
void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
    {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else
    {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

int main(int argc, char **argv)
{
    cout << "Input 1 or 2:" << endl;
    cout << "1 for Manual Input of Coordinates" << endl;
    cout << "2 for Random Input of Coordinates" << endl;

    cin >> inputMode;

    vector<Stripe> stripes;
    map<int, vector<Edge>> contourStripes;
    float ans = 0;

    int n;
    cout << "Number of rectangles: ";
    cin >> n;

    if (inputMode == 1)
    {
        cout << "Enter Points in format x1 y1 x2 y2:" << endl;

        for (int i = 0; i < n; i++)
        {
            int f1, f2, f3, f4;
            cin >> f1 >> f2 >> f3 >> f4;

            Point *P1 = new Point(min(f1, f3), min(f2, f4));
            Point *P2 = new Point(max(f1, f3), max(f2, f4));

            Rectangle *r = new Rectangle(*P1, *P2);
            rectangles.push_back(*r);
        }
    }
    else if (inputMode == 2)
    {
        for (int i = 0; i < n; i++)
        {
            float f11, f22, f33, f44;

            f11 = (((float)rand()) / (float)RAND_MAX) * 1400;
            f22 = (((float)rand()) / (float)RAND_MAX) * 900;
            f33 = (((float)rand()) / (float)RAND_MAX) * 1400;
            f44 = (((float)rand()) / (float)RAND_MAX) * 900;

            int f1, f2, f3, f4;

            f1 = ceil(f11);
            f2 = ceil(f22);
            f3 = ceil(f33);
            f4 = ceil(f44);

            cout << f1 << " " << f2 << " " << f3 << " " << f4 << endl;

            Point *P1 = new Point(min(f1, f3), min(f2, f4));
            Point *P2 = new Point(max(f1, f3), max(f2, f4));

            Rectangle *r = new Rectangle(*P1, *P2);
            rectangles.push_back(*r);
        }
    }

    stripes = RectangleDAC1(rectangles);
    ans = measure(stripes);
    printStripes(stripes);
    contourStripes = RectangleDAC2(rectangles);

    cout << "THE MEASURE FOR THE GIVEN SET OF RECTANGLES IS :" << endl;
    cout << ans << endl;

    //initialize GLUT system
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    //width=1500 pixels height=1000 pixels
    glutInitWindowSize(1500, 1000);

    //create window
    glutCreateWindow("Union of IsoRectangles");
    glutReshapeFunc(reshape);

    //set background to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //how object is mapped to window
    gluOrtho2D(0, 1500, 0, 1000);

    //set window's display callback
    glutDisplayFunc(drawScene);
    glutMouseFunc(mouse);
    glutMotionFunc(drag);

    //start processing events..
    glutMainLoop();

    return 0;
}