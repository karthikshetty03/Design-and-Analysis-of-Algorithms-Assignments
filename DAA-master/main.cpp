//To compile g++ main.cpp isorect.cpp primitives.cpp -lGL -lGLU -lglut

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "isorect.hpp"
using namespace std;

int inputMode;          //1 for manual, 2 for random points
bool isTopLeft=false;   //to check whether there are 2 points to create a rectangle or not
Point *P1,*P2;
Rectangle *rect;
int selected=-1;        //-1 if no point selected, index of that point if some point is selected
int selectedPart=0;     //1 if bottom right selected, 2 if top left, 0 if none

vector<Rectangle> rectangles;

/*
// to get the index of a selected point for deletion/dragging
int indexOf(float x, float y)
{
    for(int i=0;i<rectangles.size();i++)
    {
        //cout<<i;
        if(rectangles[i].getP1().getX()>x-5 && rectangles[i].getP1().getX()<x+5 && rectangles[i].getP1().getY()>y-5 && rectangles[i].getP1().getY()<y+5 )
        {
            selectedPart=1;
            return i;
        }
        if(rectangles[i].getP2().getX()>x-5 && rectangles[i].getP2().getX()<x+5 && rectangles[i].getP2().getY()>y-5 && rectangles[i].getP2().getY()<y+5 )
        {
            selectedPart=2;
            return i;
        }
    }
    return -1;
}

// handling mouse controls
void mouse( int button, int state, int x, int y)
{
    //adding new point by clicking left button
    if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        if(!isTopLeft)
        {
            P1=new Point(x,glutGet(GLUT_WINDOW_HEIGHT)-y);
            isTopLeft=true;
        }
        else{
            P2=new Point(x,glutGet(GLUT_WINDOW_HEIGHT)-y);
            rect=new Rectangle(*P1,*P2);
            rectangles.push_back(*rect);
            P1=NULL;
            P2=NULL;
            rect=NULL;
            isTopLeft=false;
        }

    }
    
    //dragging a point by pressing right mouse button when the cursor is at a point
    if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
    {
        selected=indexOf(x,glutGet(GLUT_WINDOW_HEIGHT)-y);
    }
    //if no point is selected when middle button is pressed
    if(state == GLUT_UP && button == GLUT_RIGHT_BUTTON)
    {
        selected=-1;
        selectedPart=0;
    }
 	glutPostRedisplay();
}

// function to drag the point and get new coordinates
void drag(int x,int y)
{
    if(selected!=-1)
    {
        if(selectedPart==1)
        {
            Point *q=new Point(x,glutGet(GLUT_WINDOW_HEIGHT)-y);
            rectangles[selected].setP1(*q);
            
        }
        if (selectedPart==2)
        {
            Point *q=new Point(x,glutGet(GLUT_WINDOW_HEIGHT)-y);
            rectangles[selected].setP2(*q);
        }
    }
    glutPostRedisplay();
}

// draw the scene on window
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glColor3f(1,0,0);
    glEnable(GL_POINT_SMOOTH);
    for(int i=0;i<rectangles.size();i++)
    {
        glBegin(GL_LINE_LOOP);
        float x1=rectangles[i].getP1().getX();
        float y1=rectangles[i].getP1().getY();
        float x2=rectangles[i].getP2().getX();
        float y2=rectangles[i].getP2().getY();
        glVertex2f(x1,y1);
        glVertex2f(x1,y2);
        glVertex2f(x2,y2);
        glVertex2f(x2,y1);
        glEnd();
        glBegin(GL_POINTS);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glEnd();
    }
    
    glDisable(GL_POINT_SMOOTH);
    glColor3f(0,0,0);
    glPointSize(2);
    //drawBezier(control);
	glFlush();
}

// handle window resize
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1;
}
*/

// main function

int main(int argc, char** argv)
{
    cout<<"Press to enter Rectangles:"<<endl<<"1 for Manual"<<endl<<"2 for Random"<<endl<<"3 for GUI"<<endl;
    cin>>inputMode;

    if(inputMode == 1)
    {
        int n;
        cout<<"Number of rectangles: ";
        cin>>n;
        cout<<"Enter Points in format x1 y1 x2 y2 (Bottom left and top Right Points):"<<endl;
        for(int i=0;i<n;i++)
        {
            float f1,f2,f3,f4;
            cin>>f1>>f2>>f3>>f4;

            Point *P1 = new Point(f1,f2);
            Point *P2 = new Point(f3,f4);
            
            Rectangle *r = new Rectangle(*P1,*P2);
            rectangles.push_back(*r);
        }
        //Algorithm Implementation
        //Output
        vector<Stripe> stripes = RectangleDAC(rectangles);
    }
    else if(inputMode == 2){
        int n;
        cout<<"Number of rectangles: ";
        cin>>n;
        for(int i=0;i<n;i++)
        {
            float f1,f2,f3,f4;

            f1 = (((float)rand())/(float)RAND_MAX)*1400;
            f2 = (((float)rand())/(float)RAND_MAX)*900;
            f3 = (((float)rand())/(float)RAND_MAX)*1400;
            f4 = (((float)rand())/(float)RAND_MAX)*900;

            Point *P1 = new Point(f1,f2);
            Point *P2 = new Point(f3,f4);

            Rectangle *r = new Rectangle(*P1,*P2);
            rectangles.push_back(*r);
        }
        //Algorithm Implementation
        //Output
        vector<Stripe> stripes = RectangleDAC(rectangles);
    }
    
	//glutInit(&argc, argv); /* initialize GLUT system */
	//glutInitDisplayMode(GLUT_RGB);
    //glutInitWindowSize(1500,1000); /* width=1500 pixels height=1000 pixels */
    //glutCreateWindow("Union of IsoRectangles");     /* create window */
	//glutReshapeFunc(changeSize);
    //glClearColor(1.0, 1.0, 1.0, 0.0); /* set background to white */
    //gluOrtho2D(0,1500, 0,1000); /* how object is mapped to window */
    //glutDisplayFunc(drawScene); /* set window's display callback */
	//glutMouseFunc(mouse);
    //glutMotionFunc(drag);
    //glutMainLoop(); /* start processing events... */

	return 0;
}