#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
using namespace std;
#define pb      push_back
#define ll      long long
#define pi      2*acos(0)
#define fr(i,n) for(i=0;i<n;i++)
#define fr1(i,n)for(i=1;i<=n;i++)

struct P
{
    double x,y;
    P(double x=0,double y=0)
    {
        this->x=x,this->y=y;
    }
};

//2D Start
P MV(P aa,P bb){ return P(bb.x-aa.x,bb.y-aa.y);}//Make Vector
P ROT(P aa,double rad){return P(aa.x*cos(rad)-aa.y*sin(rad),aa.x*sin(rad)+aa.y*cos(rad));} //rotation with an angle(on radian)
//2D End
vector<float>vertices;
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------

double rotate_y=0,rotate_x=0,rotate_z=0;
double pos_x=0,pos_y=0,prev_x=0,prev_y=0;
int windowWidth=600,windowHeight=600;
int nowRotate=0;
int tot=0,refreshMills=16,angle=180;
vector<P>v;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    //clear screen
    glLoadIdentity();   // Reset transformations
    glTranslatef( pos_x, pos_y, 0.0 );   // Other Transformations
    // Rotate when user changes rotate_x , rotate_y and rotate_z
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    glBegin(GL_POLYGON);    //make polygon
    glColor3f( 1.0, 1.5, 0.2 );
    fr(i,v.size())glVertex3f(v[i].x,v[i].y,-.7);
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void idle(){glutPostRedisplay();}   // Post a re-paint request to activate display()
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'a') pos_x -= .2,tot=0;
    else if (key == 'd') pos_x += .2,tot=0;
    else if (key == 'w') pos_y += .2,tot=0;
    else if (key == 's') pos_y -= .2,tot=0;
    if(key>='0'&&key<='9') tot=(tot*10)+(key-'0');
    if(key=='g') angle=tot,tot=0;
    if(key=='x') nowRotate=0,tot=0;
    if(key=='y') nowRotate=1,tot=0;
    if(key=='z') nowRotate=2,tot=0;
    idle();
}

int cx=0,cy=0,cz=0,cnt=0;

void specialKeys( int key, int x, int y )
{
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)cy=-1;
    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT)cy=1;
    else if (key == GLUT_KEY_UP) cx=1;
    else if (key == GLUT_KEY_DOWN) cx=-1;
    else if( key == GLUT_KEY_PAGE_UP) cz=1;
    else if(key== GLUT_KEY_PAGE_DOWN)cz=-1;
   // glutPostRedisplay();
}
void cntCheck(int &wk)
{
    if(cnt==angle)
        {
            cnt=0;
            wk=0;
        }
}

void updateRotate()
{
    if(cx==1)
    {
        rotate_x++,cnt++;
        cntCheck(cx);
    }
    if(cx==-1)
    {
        rotate_x--,cnt++;
         cntCheck(cx);
    }
    if(cy==1)
    {
        rotate_y++,cnt++;
        cntCheck(cy);
    }
    if(cy==-1)
    {
        rotate_y--,cnt++;
         cntCheck(cy);
    }
    if(cz==1)
    {
        rotate_z++,cnt++;
        cntCheck(cz);
    }
    if(cz==-1)
    {
        rotate_z--,cnt++;
        cntCheck(cz);
    }
}

void timer( int value )
{
    updateRotate();
    glutTimerFunc( refreshMills, timer, 0 );
    idle();
}

// ----------------------------------------------------------
// mouse Callback Function
// ----------------------------------------------------------
void onMouseButton(int button, int state, int x, int y)
{
    int b;
    switch(button) {
    case GLUT_LEFT_BUTTON:
	{
		if(nowRotate==0)cx=1;
		else if(nowRotate==1)cy=1;
		else cz=1;
	}
	break;
    case GLUT_MIDDLE_BUTTON:
	{
		float mx=x;
    		float my=y;
    		pos_x=(mx/320-1.0);
    		pos_y=-(my/240 -1.0);

		prev_x=pos_x;
		prev_y=pos_y;

	} break;
    case GLUT_RIGHT_BUTTON:
	{
		if(nowRotate==0)cx=-1;
		else if(nowRotate==1)cy=-1;
		else cz=-1;
	}
	break;
    }
    //idle();
}

void get()
{
    int n,i;
    cout<<"Enter the order of polygon: ";
    while(cin>>n&&n<3)cout<<"Order must be greater than or equal to 3!!!\nEnter the order of polygon: ";
    P a,b,c,ab;
    b.x=0.5;
    ab=MV(a,b);
    v.pb(P(b.x,0));
    float angle=(2*pi)/n;
    fr1(i,n-1)
    {
        c=ROT(ab,angle);
        v.pb(c);
        ab=c;
    }
}

void initGL()
{
    glClearColor(.2f,.3f,.3f,1.0f); //  Clear screen and Z-buffer
}

int main(int argc, char* argv[])
{
    get();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(300, 50);
    glutCreateWindow("Fun With Polygon");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutTimerFunc( 0, timer, 0 );
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(onMouseButton);
    initGL();
    glutMainLoop();
    return 0;
}
