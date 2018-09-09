#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<math.h>
//global constants for controlling several functions
float mov=100,movb1=20,movb2=43,movc1=0,movp=-160,boymov=0,sunmov=.1;
int oddeven=1, freeze=6000000,carmov=-100,frame=1,textcon=1;

// function for rendering text to screen
void drawstring(float x,float y,float z,char *string)
{
	char *ct;
	glRasterPos3f(x,y,z);

	for(ct=string;*ct!='\0';ct++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ct);
	}
}

//draws hills in the background
void hills(void)
{
    glColor3f(95.8/255,122.8/255,67.0/255);
    int i=0;
    //small hills
    for(i=-100; i<150; i+=15)
    {
        glBegin(GL_POLYGON);
            glColor3f(95.8/255,122.8/255,67.0/255);
            glVertex2f(i,0.0);
            glColor3f(27.8/255,83.8/255,72.0/255);
            glVertex2f(i-10,-10);
            glVertex2f(i+10,-10);
        glEnd();
    }
    //large hills
    for(i=-100; i<150; i+=45)
    {
        glBegin(GL_POLYGON);
            glColor3f(166.8/255,160.8/255,74.0/255);
            glVertex2f(i,5.0);
            glColor3f(27.8/255,83.8/255,72.0/255);
            glVertex2f(i-10,-10);
            glVertex2f(i+20,-10);
        glEnd();
    }
}

// draws car after the police arrival
void car(void)
{
    //drawing car body
    glColor3f(.1,.5,0);
    glBegin(GL_POLYGON);
        glVertex2f(carmov-10,-10.0);
        glVertex2f(carmov+10,-10);
        glVertex2f(carmov+20,-40.0);
        glVertex2f(carmov+30,-40.0);
        glVertex2f(carmov+30,-50);
        glVertex2f(carmov+30,-50);
        glVertex2f(carmov-10,-50);
    glEnd();

    glColor3f(.3,.3,.3);
    glBegin(GL_POLYGON);
        glVertex2f(carmov-5,-13.0);
        glVertex2f(carmov+5,-13);
        glVertex2f(carmov+13,-30.0);
        glVertex2f(carmov-5,-30.0);
    glEnd();

    glColor3f(1,1,1);
        drawstring(carmov,-37,0.0,"Police");
    glColor3f(1,1,1);

    //car wheel

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.1,.1,0.1);
    int seg=30;

    float red=10;
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+carmov+5,red*sinf(i*2*3.14/seg)-50);
    glEnd();

    //control car move
    if (carmov<-90)
        carmov+=5;
}

// draw tree in the background
void tree(void)
{
    //tree upper portion using triangle fan
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,.8-sunmov*.01,0);
    int seg=10;

    float red=30;
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)-20,red*sinf(i*2*3.14/seg)+40);
    glEnd();

    //wood portion
    glLineWidth(50);
    glBegin(GL_LINES);
    glColor3f(69.0/255, 50.5/255, 18.2/255);
    glVertex3f(-18, -25, 0.0);
    glColor3f(130.0/255, 97.5/255, 46.2/255);
    glVertex3f(-18, 30, 0);
    glEnd();
}

//draw house beside the tree
void house(void)
{
    glColor3f(.8,.8,0);
    glBegin(GL_POLYGON);
    glVertex3f(-30, 0, 0.0);
    glVertex3f(-20, -7, 0);
    glVertex3f(-40, -10, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(.2,.2,0);
    glVertex3f(-30, 0, 0.0);
    glVertex3f(-50, 0, 0.0);
    glColor3f(.8,.8,0);
    glVertex3f(-60, -10, 0);
    glVertex3f(-40, -10, 0);
    glEnd();

    glColor3f(.6,.6,0);
    glBegin(GL_POLYGON);
    glVertex3f(-40, -20, 0.0);
    glVertex3f(-58, -20, 0.0);
    glVertex3f(-58, -10, 0);
    glVertex3f(-40, -10, 0);
    glEnd();

    glColor3f(.2,.2,0);
    glBegin(GL_POLYGON);
    glVertex3f(-40, -20, 0.0);
    glVertex3f(-60, -20, 0.0);
    glVertex3f(-60, -23, 0);
    glVertex3f(-40, -23, 0);
    glEnd();

    glColor3f(.6,.6,0);
    glBegin(GL_POLYGON);
    glVertex3f(-40, -20, 0.0);
    glVertex3f(-22, -17, 0.0);
    glVertex3f(-22, -7, 0);
    glVertex3f(-40, -10, 0);
    glEnd();

    glColor3f(.2,.2,0);
    glBegin(GL_POLYGON);
    glVertex3f(-40, -20, 0.0);
    glVertex3f(-22, -17, 0.0);
    glVertex3f(-22, -19, 0);
    glVertex3f(-40, -23, 0);
    glEnd();

    glColor3f(.2,.2,0);
    glBegin(GL_POLYGON);
    glVertex3f(-28, -10, 0.0);
    glVertex3f(-33, -11, 0.0);
    glVertex3f(-33, -16, 0);
    glVertex3f(-28, -15, 0);
    glEnd();

    glColor3f(.2,.2,0);
    glBegin(GL_POLYGON);
    glVertex3f(-48, -12, 0.0);
    glVertex3f(-52, -12, 0.0);
    glVertex3f(-52, -20, 0);
    glVertex3f(-48, -20, 0);
    glEnd();
}
//draw river in the background
void river(void)
{
    //river
    glColor3f(.1,.1,.8);
    glBegin(GL_POLYGON);
    glVertex3f(70, -10, 0.0);
    glVertex3f(72, -10, 0.0);
    glVertex3f(80, -12, 0);
    glVertex3f(100, -15, 0);
    glColor3f(162/255.0,222/255.0,205/255.0);
    glVertex3f(100, -25, 0);
    glVertex3f(83, -20, 0);
    glEnd();

    //boat
    glColor3f(.5,.5,0);
    glLineWidth(7);
    glBegin(GL_LINES);

    glVertex3f(80, -18, 0);
    glVertex3f(82, -20, 0);
    glVertex3f(82, -20, 0);
    glVertex3f(86, -20, 0);
    glVertex3f(86, -20, 0);
    glVertex3f(87, -18, 0);
    glEnd();
}

//draw river in the sky
void sun(void)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,1-sunmov/40,0);
    int seg=30;
    float red=10;
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)-60,red*sinf(i*2*3.14/seg)+30-sunmov);
    glEnd();
    sunmov+=.1;
}

//drawing girl with movement controlled by
void drawgirl(int rate)
{
//**********Drawing girl***********

    //drawing dress
    glBegin(GL_POLYGON);
        glColor3f(153.0/255,1.2/255,0.2/255);
        glVertex2f(mov,0.0);
        glColor3f(209.0/255,117.2/255,40.2/255);
        glVertex2f(mov-10,-40);
        glVertex2f(mov+10,-40);
    glEnd();

    //drawing hair
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0,0,0);
   int seg=20;
   float red=8;
   for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+mov,red*sinf(i*2*3.14/seg)+3);
    glEnd();

    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex3f(mov-7, 0, 0.0);
    glVertex3f(mov-7, -10, 0);
    glVertex3f(mov+7, -10, 0.0);
    glVertex3f(mov+7, 0, 0);
    glEnd();

    //drawing head
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,201.0/255,174.0/255);
    seg=40;
    red=8;
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+mov,red*sinf(i*2*3.14/seg));
    glEnd();

    //drawing face
    glColor3f(0,0,0);
    drawstring(mov-4,0,0.0,"^");

    glColor3f(0,0,0);
    drawstring(mov+3,0,0.0,"^");
    glColor3f(0,0,0);
    drawstring(mov-4,-1,0.0,"*");

    glColor3f(0,0,0);
    drawstring(mov+3,-1,0.0,"*");

    glColor3f(0,0,0);
    drawstring(mov,-3,0,"|");

    if (textcon>75 && textcon <85 || textcon>125 && textcon<155)
    {
        if(oddeven==1)
        {
            glColor3f(.8,0,0);
            drawstring(mov-1,-7,0.0,"-");
        }
        else
        {
            glColor3f(.8,0,0);
            drawstring(mov-1,-7,0.0,"o");
        }
    }
    else
    {
        glColor3f(.8,0,0);
            drawstring(mov-1,-7,0.0,"-");
    }

    //drawing leg
    glLineWidth(10);
    glColor3f(124.0, 126.0,77.0);

    int leftleg,rightleg;

    if (rate==0)
    {
        leftleg=-60;
        rightleg=-60;
    }
    else if (oddeven== 1)
    {
        oddeven=0;
        leftleg=-60;
        rightleg=-57;
    }
    else
    {
        oddeven=1;
        leftleg=-57;
        rightleg=-60;
    }

    glBegin(GL_LINES);
    glVertex3f(mov-5, -40, 0.0);
    glVertex3f(mov-5, leftleg, 0);
    glVertex3f(mov+5, -40, 0.0);
    glVertex3f(mov+5, rightleg, 0);

    //shoe
    glColor3f(0.0,0.0,0.0);
    glVertex3f(mov-4, leftleg, 0.0);
    glVertex3f(mov-9, leftleg, 0);
    glVertex3f(mov+6, rightleg, 0.0);
    glVertex3f(mov+1, rightleg, 0);

    glEnd();

    glColor3f(1.0,0.0,1.0);
    glBegin(GL_LINE);
        glVertex3f(mov-10,-40,0.0);
        glVertex3f(mov-1,-80,0.0);
    glEnd();

    //text rendering those girl thinks or tells
    //controlled by textcon
    if (textcon<15)
    {
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov+5, -25, 0);
        else
            glVertex3f(mov+5, -30, 0);

        glVertex3f(mov-5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov-5, -30, 0);
        else
            glVertex3f(mov-5, -25, 0);
        glEnd();
    }
    else if ( textcon<20)
    {
        //hand movement
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov+5, -25, 0);
        else
            glVertex3f(mov+5, -30, 0);

        glVertex3f(mov-5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov-5, -30, 0);
        else
            glVertex3f(mov-5, -25, 0);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-20,15,0.0);
            glVertex3f(mov-20,5,0.0);
            glVertex3f(mov+20,5,0.0);
            glVertex3f(mov+20,15,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,0,0.0);
            glVertex3f(mov-10,15,0.0);
            glVertex3f(mov+10,15,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,10,0.0,"Uff, Those bad boys");
        glColor3f(1,1,1);

    }
    else if( textcon<25)
    {

        //hand movement
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov+5, -25, 0);
        else
            glVertex3f(mov+5, -30, 0);

        glVertex3f(mov-5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov-5, -30, 0);
        else
            glVertex3f(mov-5, -25, 0);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-20,15,0.0);
            glVertex3f(mov-20,5,0.0);
            glVertex3f(mov+20,5,0.0);
            glVertex3f(mov+20,15,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,0,0.0);
            glVertex3f(mov-10,15,0.0);
            glVertex3f(mov+10,15,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,10,0.0,"   What should i do?");
        glColor3f(1,1,1);
    }
    else if(textcon<30)
    {
        //hand movement
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov+5, -25, 0);
        else
            glVertex3f(mov+5, -30, 0);

        glVertex3f(mov-5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov-5, -30, 0);
        else
            glVertex3f(mov-5, -25, 0);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-20,15,0.0);
            glVertex3f(mov-20,5,0.0);
            glVertex3f(mov+20,5,0.0);
            glVertex3f(mov+20,15,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,0,0.0);
            glVertex3f(mov-10,15,0.0);
            glVertex3f(mov+10,15,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,10,0.0,"     I better RUN!!!");
        glColor3f(1,1,1);
    }
    else if( textcon >55 && textcon < 60)
    {
        //hand movement
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov+5, -25, 0);
        else
            glVertex3f(mov+5, -30, 0);

        glVertex3f(mov-5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov-5, -30, 0);
        else
            glVertex3f(mov-5, -25, 0);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-20,30,0.0);
            glVertex3f(mov-20,20,0.0);
            glVertex3f(mov+20,20,0.0);
            glVertex3f(mov+20,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,5,0.0);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov+10,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,25,0.0,"Can't tolerate anymore");
    }
    else if( textcon>60 && textcon <65)
    {
        //hand movement
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);
        glVertex3f(mov+5, -30, 0);
        glVertex3f(mov-5, -15.0, 0.0);
        glVertex3f(mov-7, +0, 0);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-20,30,0.0);
            glVertex3f(mov-20,20,0.0);
            glVertex3f(mov+20,20,0.0);
            glVertex3f(mov+20,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,5,0.0);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov+10,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,25,0.0,"Have to do something");
        glColor3f(1,1,1);
    }
    else if( textcon>65 && textcon < 75)
    {

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-30,30,0.0);
            glVertex3f(mov-30,20,0.0);
            glVertex3f(mov+30,20,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,5,0.0);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov+10,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,25,0.0,"[dialing 999]");
        glColor3f(1,1,1);
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -20.0, 0.0);
        glVertex3f(mov+7, 0, 0);
        glLineWidth(20);
        glColor3f(0,0,0);
        glVertex3f(mov+7, 0, 0.0);
        glVertex3f(mov+7, 5, 0);
        glEnd();
    }

    else if( textcon>75 && textcon < 85)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-30,30,0.0);
            glVertex3f(mov-30,20,0.0);
            glVertex3f(mov+30,20,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,5,0.0);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov+10,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,25,0.0,"[Complaining to police]");
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -20.0, 0.0);
        glVertex3f(mov+7, 0, 0);
        glLineWidth(20);
        glColor3f(0,0,0);
        glVertex3f(mov+7, 0, 0.0);
        glVertex3f(mov+7, 5, 0);
        glEnd();
    }
    else if(textcon>=85 && textcon<= 125)
    {
        //hand movement
   glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);
        glVertex3f(mov+5, -30, 0);
        glVertex3f(mov-5, -15.0, 0.0);
        glVertex3f(mov-7, -30, 0);
        glEnd();
    }
    else if( textcon>125 && textcon < 135)
    {
        //hand movement
   glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);
        glVertex3f(mov+5, -30, 0);
        glVertex3f(mov-5, -15.0, 0.0);
        glVertex3f(mov-7, +0, 0);
        glEnd();
        //
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-30,30,0.0);
            glVertex3f(mov-30,15,0.0);
            glVertex3f(mov+30,15,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,5,0.0);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov+10,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,25,0.0,"For any help");
        glColor3f(1,1,1);

        glColor3f(1,1,1);
        drawstring(mov-20,20,0.0,"Dial 999");
        glColor3f(1,1,1);


    }
    else if( textcon>135 && textcon < 145)
    {
        //hand movement
   glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);
        glVertex3f(mov+5, -30, 0);
        glVertex3f(mov-5, -15.0, 0.0);
        glVertex3f(mov-7, +0, 0);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-30,30,0.0);
            glVertex3f(mov-30,15,0.0);
            glVertex3f(mov+30,15,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+0,5,0.0);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov+10,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov-20,25,0.0,"One Dial can save");
        glColor3f(1,1,1);
        drawstring(mov-20,20,0.0,"many of your life like me");
    }
    else if(textcon<145 && rate!=0)
    {
        //hand movement
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov+5, -25, 0);
        else
            glVertex3f(mov+5, -30, 0);

        glVertex3f(mov-5, -15.0, 0.0);

        if(textcon%2==0)
            glVertex3f(mov-5, -30, 0);
        else
            glVertex3f(mov-5, -25, 0);

        glEnd();

        //comment bg
    }
    else if(textcon>=145)
    {
        //hand movement
        glColor3f(1,201.0/255,174.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+5, -15.0, 0.0);
        glVertex3f(mov+5, -30, 0);

        glVertex3f(mov-5, -15.0, 0.0);
        glVertex3f(mov-7, +0, 0);
        glEnd();
    }
    if(mov<-100)
        mov=100;
    else
        mov=mov-rate;
    textcon++;

}
//draws police, rate for movement.
void police( int rate)
{
    //drawing face
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(176.8/255,115.8/255,98.0/255);
    int  seg=10;
    int red=7;
    //glVertex2f(0.0,0.0);
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+movp,red*sinf(i*2*3.14/seg));
    glEnd();

    //drawing hat
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(108.8/255,126.8/255,20.0/255);
    seg=10;
    red=10;
    for (int i=0; i <= seg/2; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+movp,red*sinf(i*2*3.14/seg));
    glEnd();

    //drawing neck


    glColor3f(176.8/255,115.8/255,98.0/255);


    glBegin(GL_POLYGON);
        glVertex2f(movp-4,-10.0);
        glVertex2f(movp+4,-10);
        glVertex2f(movp,0);
    glEnd();


    //drawing dress


    glColor3f(108.8/255,126.8/255,20.0/255);


    glBegin(GL_QUADS);
        glVertex2f(movp-8,-10.0);
        glVertex2f(movp-8,-40);
        glVertex2f(movp+8,-40);
        glVertex2f(movp+8,-10.0);
    glEnd();

    glColor3f(1,1,1);
        drawstring(movp-5,-30,0.0,"Police");
    glColor3f(1,1,1);

    //drawing leg

    glLineWidth(20);
    glColor3f(23.8/255,30.8/255,72.0/255);
    //leg movement
    int  leftleg=-60;
    int    rightleg=-57;
    if (rate==0)
    {
        leftleg=-60;
        rightleg=-60;
    }
    else if (oddeven== 1)
    {
        oddeven=0;
        leftleg=-60;
        rightleg=-57;
    }
    else
    {
        oddeven=1;
        leftleg=-57;
        rightleg=-60;
    }
    glBegin(GL_LINES);
    glVertex3f(movp-5, -40, 0.0);
    glVertex3f(movp-5, leftleg, 0);
    glVertex3f(movp+5, -40, 0.0);
    glVertex3f(movp+5, rightleg, 0);
    glEnd();

    //hand
    glLineWidth(10);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINES);
        if( rate>0)
        {
            glVertex3f(movp+20,-20,0.0);
            glVertex3f(movp,-20,0.0);
            glColor3f(0.0,0.0,0.0);
            glVertex3f(movp+20,-18,0.0);
            glVertex3f(movp+25,-18,0.0);

            glColor3f(0.0,0.0,0.0);


            glColor3f(0.0,0.0,0.0);
            glBegin(GL_LINES);
                glVertex3f(movp+2, rightleg, 0.0);
                glVertex3f(movp+9, rightleg, 0);
                glVertex3f(movp-8,  leftleg, 0.0);
                glVertex3f(movp-1,  leftleg, 0);

            glEnd();

        }
        else
        {
            glVertex3f(movp-20,-20,0.0);
            glVertex3f(movp,-20,0.0);
            glColor3f(0.0,0.0,0.0);
            glVertex3f(movp-20,-18,0.0);
            glVertex3f(movp-25,-18,0.0);

            glBegin(GL_LINES);
                glVertex3f(movp-2, leftleg, 0.0);
                glVertex3f(movp-9, leftleg, 0);
                glVertex3f(movp+8, rightleg, 0.0);
                glVertex3f(movp+1, rightleg, 0);
            glEnd();
        }
    glEnd();
    movp=movp+rate;
}
//draws boy, rate is the movement of the boy
//and boyno is the number of the boy
void drawboy(int rate,int boyno)
{
    float mov;
    if (boyno==2)
    {
    mov=movb2;
    movb2=movb2+rate;
    }
    else
    {
    mov=movb1;
    movb1=movb1+rate;
    }

    //************* Drawing boys*********

    //neck//
    glColor3f(188.8/255,116.8/255,35.0/255);
    glBegin(GL_POLYGON);
        glVertex2f(mov-0,0.0);
        glVertex2f(mov-10,-20);
        glVertex2f(mov+10,-20.0);
    glEnd();
    //for boy 1, draw cap. for boy 2 draw beard
    int cap;
    if (boyno==1)
        cap=0;
    else
        {
            cap=5;
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0,0,0);
            int  seg=6;
            int red=7;
            for (int i=0; i <= seg; i++)
                glVertex2f(red*cosf(i*2*3.14/seg)+mov,red*sinf(i*2*3.14/seg)-cap);
            glEnd();

        }

    //draw head
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(252.8/255,176.8/255,64.0/255);
    int  seg=10;
    int red=7;
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+mov,red*sinf(i*2*3.14/seg));
    glEnd();

    //drawing cap
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0,0.0,0.0);
    seg=5;
    red=10;
    for (int i=0+cap; i <= seg/2; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+mov,red*sinf(i*2*3.14/seg));
    glEnd();

     // face
    if(boyno==2)
    {
        glColor3f(0,0,0);
    drawstring(mov-4,0,0.0,"O-O");
    glColor3f(0,0,0);
    drawstring(mov-4,+2,0.0,"\\");
    glColor3f(0,0,0);
    drawstring(mov+4,+2,0.0,"/");
    }
    else
    {
        glColor3f(0,0,0);
    drawstring(mov-4,0,0.0,"~");
    glColor3f(0,0,0);
    drawstring(mov+2,0,0.0,"~");
    }
    //lips movement
    if(frame<80)
    {
        if(oddeven==1)
        {
            glColor3f(0,0,0);
        drawstring(mov-1,-5,0.0,"-");

        }
        else
        {
            glColor3f(0,0,0);
        drawstring(mov-1,-5,0.0,"o");
        }
    }
    else
    {
        glColor3f(0,0,0);
        drawstring(mov-1,-5,0.0,"-");
    }

    //drawing dress

    glBegin(GL_QUADS);
            if (boyno==1)
            glColor3f(15.8/255,116.8/255,188.0/255);
            else
            glColor3f(129.8/255,94.8/255,162.0/255);
        glVertex2f(mov-10,0.0);
        glVertex2f(mov-10,-40);
            if (boyno==1)
            glColor3f(15.8/255,0.8/255,140.0/255);
            else
            glColor3f(0.8/255,94.8/255,100.0/255);
        glVertex2f(mov+10,0.0);
        glVertex2f(mov+10,-40);
    glEnd();
    //drawing hand
    if(rate==0)
    {
        //hand movement
        glColor3f(188.8/255,116.8/255,35.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+7, -15.0, 0.0);
        glVertex3f(mov+7, -30, 0);
        glVertex3f(mov-7, -15.0, 0.0);
        glVertex3f(mov-7, -30, 0);
        glEnd();
    }
    else
    {
        //hand movement
        glColor3f(188.8/255,116.8/255,35.0/255);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3f(mov+7, -15.0, 0.0);
        glVertex3f(mov+7, +10, 0);

        glVertex3f(mov-7, -15.0, 0.0);
        glVertex3f(mov-7, +10, 0);


        glEnd();
    }

    //drawing leg

    glLineWidth(20);
    glColor3f(1.8/255,50.8/255,93.0/255);
    //leg movement logic
    int  leftleg=-60;
    int    rightleg=-57;

    if (rate==0)
    {
        leftleg=-60;
        rightleg=-60;
    }
    else if (oddeven== 1)
    {
        oddeven=0;
        leftleg=-60;
        rightleg=-57;
    }
    else
    {
        oddeven=1;
        leftleg=-57;
        rightleg=-60;
    }

    //leg
    glBegin(GL_LINES);
    glVertex3f(mov-5, -40, 0.0);
    glVertex3f(mov-5, leftleg, 0);
    glVertex3f(mov+5, -40, 0.0);
    glVertex3f(mov+5, rightleg, 0);

    //shoe
    glLineWidth(10);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(mov-2, leftleg, 0.0);
    glVertex3f(mov-9, leftleg, 0);
    glVertex3f(mov+8, rightleg, 0.0);
    glVertex3f(mov+1, rightleg, 0);
    glEnd();


    //throwing bad comments

    if(boyno==1 && textcon<5)
    {
        //do noting
    }
    else if( boyno==1 && textcon<10)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov-10,20,0.0);
            glVertex3f(mov+40,20,0.0);
            glVertex3f(mov+40,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+20,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0,"Bro, Look that girl");

    }
    else if(boyno==1 && textcon<15)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov-10,30,0.0);
            glVertex3f(mov-10,20,0.0);
            glVertex3f(mov+40,20,0.0);
            glVertex3f(mov+40,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov+20,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Whistle..]");
    }
    else if(boyno==1 && textcon<20)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Singing.] Shundori choleche..");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [..Singing.] eka pothe..");
    }
    else if(boyno==1 && textcon<25)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Singing.] shongi hole dosh..");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [..Singing.] ki tate..");
    }
    else if(boyno==1 && textcon<30)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Singing.] har meneche..");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [..Singing.] chader alo..");
    }
    else if(boyno==1 && textcon<35)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Singing.] ragle tomay lage..");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [..Singing.] aro valo..");
    }
    else if(boyno==1 && textcon<35)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Singing.] ragle tomay lage..");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [..Singing.] aro valo..");
    }
    else if(boyno==1 && textcon<40)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Throwing bad comments..]");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," ..Jeo na shathi, ooooo..");
    }
    else if(boyno==1 && textcon<45)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Throwing bad comments..]");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [....]");
    }

    else if(boyno==1 && textcon<50)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Throwing bad comments..]");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [........]");
    }
    else if(boyno==1 && textcon<55)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Throwing bad comments..]");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [...........]");
    }
    else if(boyno==1 && textcon<60)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Throwing bad comments..]");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [...............]");
        glColor3f(1,1,1);
    }
    else if(boyno==1 && textcon<65)
    {
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(mov,30,0.0);
            glVertex3f(mov,15,0.0);
            glVertex3f(mov+60,15,0.0);
            glVertex3f(mov+60,30,0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(mov,5,0.0);
            glVertex3f(mov+10,30,0.0);
            glVertex3f(mov+30,30,0.0);
        glEnd();

        glColor3f(1,1,1);
        drawstring(mov,25,0.0," [..Throwing bad comments..]");
        glColor3f(1,1,1);
        drawstring(mov,20,0.0," [......................]");
        glColor3f(1,1,1);
    }

}
//draw clouds using triangle fan
void cloud(float rate,int in,float red)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(233.8/255,243.8/255,245.0/255);
    int seg=10;
    //draw three circle
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+movc1+in,red*sinf(i*2*3.14/seg)+80);
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+movc1+10+in,red*sinf(i*2*3.14/seg)+70);
    for (int i=0; i <= seg; i++)
        glVertex2f(red*cosf(i*2*3.14/seg)+movc1-10+in,red*sinf(i*2*3.14/seg)+75);
      glEnd();
    //control movement of clouds
    if(movc1<-100)
        movc1=100;
    else if (movc1>100)
        movc1=-100;
    else
        movc1=movc1-rate;
}
// flashscreen starts with program starts contains useful information.
void flashscreen()
{
    //setting background color
    glColor3f(.0,.0,.2);
    glBegin(GL_QUADS);
        glColor3f(.0,.0,.2);
        glVertex2f(-100 ,-100.0);
        glVertex2f(+100,-100.0);
        glColor3f(.0,.0,.6);
        glVertex2f(+100,+100.0);
        glVertex2f(-100,+100.0);
    glEnd();
    // render text
    glColor3f(1,1,1);
        drawstring(-10,30,0.0,"Eve-teasing");
    glColor3f(1,1,1);
        drawstring(-80,20,0.0,"Eve-teasing  is  a  recent  phenomenon  in Bangladesh  focused  thorough  media  in  1990s.");
    glColor3f(1,1,1);
        drawstring(-80,10,0.0,"Now a days  particularly  around  two  thousands  of  the incidents occurred everywhere.");
    glColor3f(1,1,1);
        drawstring(-80,0,0.0,"Recent surveys of 512 educational institutions show 62% school girls are victims of eve-teasing. ");
    glColor3f(1,1,1);
        drawstring(-80,-10,0.0,"Another  research shows 87% girls of schools and colleges become victim  of  eve-teasing  while ");
    glColor3f(1,1,1);
        drawstring(-80,-20,0.0,"they  go  to  their school-college and back.  ");
    glColor3f(1,1,1);
        drawstring(-80,-30,0.0,"This Animation shows different forms of eve-teasing and the way of taking action against it");
}

//draw background field and sky with gradient color
void background(void)
{
    //close grass field
    glBegin(GL_QUADS);
        glColor3f(119.8/255,160.8/255,21.0/255);
        glVertex2f(-100,-70.0);
        glVertex2f(+100,-70.0);
        glColor3f(34.8/255,62.8/255,25.0/255);
        glVertex2f(+100,-100.0);
        glVertex2f(-100,-100.0);
    glEnd();
    //road of soil
    glBegin(GL_QUADS);
        glColor3f(249.8/255,189.8/255,49.0/255);
        glVertex2f(-100,-70.0);
        glVertex2f(+100,-70.0);
        glColor3f(211.8/255,170.8/255,108.0/255);
        glVertex2f(+100,-30.0);
        glVertex2f(-100,-30.0);
    glEnd();
    //far field
    glBegin(GL_QUADS);
        glColor3f(119.8/255,160.8/255,21.0/255);
        glVertex2f(-100,-30.0);
        glVertex2f(+100,-30.0);
        glColor3f(179.8/255,193.8/255,0.0/255);
        glVertex2f(+100,-10.0);
        glVertex2f(-100,-10.0);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.2-sunmov/100,0.2-sunmov/100,1.0-sunmov/100);
        glVertex2f(-100,100.0);
        glVertex2f(+100,100.0);
        glColor3f(0.7-sunmov/100,0.7-sunmov/100,1.0-sunmov/100);
        glVertex2f(+100,-10.0);
        glVertex2f(-100,-10.0);
    glEnd();
    sun();// draw sun
}
//First sense consists of two boys and a moving girl
void firstScene(int rate)
{
    drawboy(0,1);
    drawboy(0,2);
    drawgirl(rate);
}
//second scene consists of two boys and static girl
void secondScene()
{
    drawboy(0,1);
    drawboy(0,2);
    drawgirl(0);
}
//third scene controls the boy movement using the sign of rate
void thirdScene(int rate)
{
    if (rate<0)
    {
    drawboy(rate,1);
    drawboy(rate,2);
    }
    else
    {
    drawboy(0,1);
    drawboy(0,2);
    }
    police(rate);
    car();
    drawgirl(0);
}
// fourth screen adds text the view port
void fourthScene()
{
    //set background color
    glColor3f(.0,.0,.2);
    glBegin(GL_QUADS);
        glVertex2f(-100 ,-100.0);
        glVertex2f(+100,-100.0);
        glVertex2f(+100,+100.0);
        glVertex2f(-100,+100.0);
    glEnd();
    //render different text
    glColor3f(1,1,1);
    if(frame<160)
    {
        drawstring(-50,20,0.0,"Do you know about 91.3% women  are victim of eve-teasing?");
    }
    else if (frame<170)
    {
        drawstring(-70,20,0.0,"Do you know out of these 87% incidents go to the age level of 10 to 18 years?");
    }
    else if (frame<180)
    {
        drawstring(-70,20,0.0,"Do you know 60%  women  are eve-teased  by mobile miss call and massages?");
    }
    else if (frame<195)
    {
        drawstring(-70,20,0.0,"To prevent any social problem including Eve-teasing, Bangladesh Government");
        glColor3f(1,1,1);
        drawstring(-70,10,0.0,"has launched emergency helpline service");
        glColor3f(1,1,1);
        drawstring(-70,0,0.0,"This 24/7 hours service can be used when:");
        glColor3f(1,1,1);
        drawstring(-70,-10,0.0,"1. Someone becomes victim of any danger.");
        glColor3f(1,1,1);
        drawstring(-70,-20,0.0,"2. Someone fears of any type of danger.");
        glColor3f(1,1,1);
        drawstring(-70,-30,0.0,"3. Someone witnesses of crime occurring. ");
        glColor3f(1,1,1);
        drawstring(-70,-40,0.0,"4. Someone needs emergency ambulance.");
        glColor3f(1,1,1);
    }
    else
    {
        glColor3f(1,1,1);
        drawstring(-70,20,0.0,"Remember, your life is not just your's, it surrounds with all of your beloved ones");
        glColor3f(1,1,1);
        glColor3f(1,1,1);
        drawstring(-55,10,0.0,"Protesting against crime can save many of our life like your's");
        glColor3f(1,1,1);
    }
}
//draw everything with respect to frame rate.
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //clear before drawing
    //draw objects
    background();
    hills();
    cloud(-1,0,10);
    cloud(-.1,-70,5);
    cloud(-.2,70,3);
    house();
    river();
    tree();
    //control drawing using frame count
    if (frame<=2)
        flashscreen();
    else if(frame<30)
        firstScene(1);
    else if (frame<60)
        firstScene(3);
    else if (frame<80)
        secondScene();
    else if( frame<115)
        thirdScene(7);
    else if( frame<155)
        thirdScene(-5);
    else
        fourthScene();
    frame++;
    glutSwapBuffers(); // swap the buffer to screen
}
//control flow of control
//calls display function after 'freeze' ns.
void Timer(int iUnused)
{
    glutPostRedisplay(); //calls display()
    glutTimerFunc(freeze, Timer, 0); //waits till freeze
}
//initialize color buffer for background
void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0); //sets buffer color
   glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0); //sets orthogonality
}
//works when window size is changed
//viewport is adjusted with the window size
void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
//mouse control:
//<left button> = start, <Right button>= pause
void mouse(int button,int state,int x,int y)
{
    switch(button)
    {   case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN)
        {
            freeze=600;
            Timer(0);
        }
        break;
        case GLUT_RIGHT_BUTTON:
        freeze=600000000;
        Timer(0);
        break;
    }
}
//keyboard control :
//<space> = pause, <back space> =start,<esc>=close window
void keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 32: freeze=600; Timer(0); break;
        case 8: freeze=600000000; Timer(0); break;
        case 27:exit(1);break;
    };
}
//program starts with calling the main function
int main(int argc, char** argv)
{
   glutInit(&argc, argv); //initialize the GLUT library
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); //using double buffering
   glutInitWindowSize (900, 700); //setting the window size
   glutInitWindowPosition (100, 10); //coordinate of the position of window
   glutCreateWindow (argv[0]); // create the window
   init(); //initialize
   glutDisplayFunc(display); //calls the display()
   glutReshapeFunc(reshape); //does when window is resized
   glutMouseFunc(mouse); //initialize mouse functions
   glutKeyboardFunc(keyboard); //initialize keyboard functions
   Timer(0); //set timer for controlling the refresh rate
   glutMainLoop(); //glutMainLoop enters the GLUT event processing loop
   return 0;
}
