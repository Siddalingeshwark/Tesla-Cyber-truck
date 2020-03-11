#include <stdio.h>
#include <stdlib.h>     
#include <GL/glut.h>  
#include <math.h>  
#include<string.h>

/* ASCII code for the escape key. */
#define ESCAPE 27

GLint window; 
GLint window2;          
GLint Xsize=1400;
GLint Ysize=700;
char *name5="CAR SIMULATION USING OPEN GL";
char *name6="----------------------------";
char *name="PROJECT BY- ";
char name2[]=" Vamitha Teena Moras ";
char name3[]="       Tejakshi N S ";

GLfloat xt=0.0,yt=0.0,zt=0.0,xw=0.0;   /* x,y,z translation */

GLfloat xs=1.0,ys=1.0,zs=1.0;

GLfloat xangle=0.0,yangle=0.0,zangle=0.0,angle=0.0;   /* axis angles */

GLfloat r=0,g=0,b=1;
GLint light=1;
int count=1;
int view=0;
int flag1=0;//to switch car driving mode
int flag2=0,wheelflag=0;//to switch fog effect
GLfloat i=0.0;
GLfloat theta=0.0;
GLUquadricObj *t;

static void SpecialKeyFunc( int Key, int x, int y );

/* Simple  transformation routine */
void Transform(GLfloat Width, GLfloat Height)
{
  glViewport(0, 0, Width, Height);              /* Set the viewport */
  glMatrixMode(GL_PROJECTION);                  /* Select the projection matrix */
  glLoadIdentity();				/* Reset The Projection Matrix */
  gluPerspective(45.0,Width/Height,0.1,100.0);  /* Calculate The Aspect Ratio Of The Window */
  glMatrixMode(GL_MODELVIEW);                   /* Switch back to the modelview matrix */
}


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(GLfloat Width, GLfloat Height)	
{

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glLineWidth(2.0);              /* Add line width,   ditto */
  Transform( Width, Height ); /* Perform the transformation */
  //newly added
  t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);

glEnable(GL_LIGHTING);
GLfloat global_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
glEnable(GL_LIGHT0);

// Create light components
GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

// Assign created components to GL_LIGHT0
glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
glLightfv(GL_LIGHT0, GL_POSITION, position);
glDisable(GL_LIGHTING);                        //disable th lighting......
}

/* The function called when our window is resized  */
void ReSizeGLScene(GLint Width, GLint Height)
{
  if (Height==0)     Height=1;                   /* Sanity checks */
  if (Width==0)      Width=1;
  Transform( Width, Height );                   /* Perform the transformation */
}

void init()
{
    glClearColor(1,1,1,1);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1200.0,0.0,600.0,50.0,-50.0);
	glMatrixMode(GL_PROJECTION);
}
void output(float x, float y, char *string)                                    
{
	int len, i;
glColor3f(0.5,0.6,0.6);
	glRasterPos2f(x, y);
  glColor3f(0.0,1.0,1.0);			/* function to display text */			
	len = (int)strlen(string);

	for (i = 0; i < len; i++) 	
	{
		    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , string[i]);
	}
}

/* The main drawing function

   In here we put all the OpenGL and calls to routines which manipulate
   the OpenGL state and environment.

   This is the function which will be called when a "redisplay" is requested.
*/

void display_string(int x, int y, char *string, int font)
{
    int len,i;
        glColor3f(1.0,1.0,0.0);
	glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
    if(font==1)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	if(font==2)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	if(font==3)
	        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
	if(font==4)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
	}

}

void display1(void)
{
	  
	glClearColor(0.0,0.0,0.0,0.0);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
       display_string(250,550,name5,1); 
        display_string(250,542,name6,1);  
	display_string(100,500,name,1);
	display_string(300,500,name2,1);
	display_string(480,500,name3,1);
	display_string(350,470,"HELP",2);
	display_string(0,450,"MOUSE",2);
    display_string(10,430,"PRESS MIDDLE BUTTON----->CAR COLOR SELECTION",3);
	display_string(10,410,"PRESS RIGHT BUTTON------>DIFFERENT MODE",3);
	display_string(0,390,"KEYBOARD",2);
	display_string(10,370,"X-Y-Z KEYS FOR CORRESPONDING ROTATION",3);
	display_string(10,350,"d-D KEYS FOR TOGGLE THE TRANSPARENT TO DEPTH VIEW",3);
	display_string(10,330,"A-S-Q CAR CUSTOM SIZE SELECTION",3);
	display_string(10,310,"U-F FOR CAMERA VIEW SETTINGS",3);
	display_string(10,290,"USE UP ARROW AND DOWN ARROW TO MOVE CAR",3);
	display_string(10,270,"ESCAPE TO EXIT",3);

	display_string(300,200,"PRESS SPACE BAR TO ENTER",1);
  glutSwapBuffers();
  glutPostRedisplay();
}


void DrawGLScene()
{
  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* Clear The Screen And The Depth Buffer */
if(view==0)
{
init();
display1();
}
else
{
  if(count==1)
    
	InitGL(Xsize,Ysize); /* Initialize our window. */ 
  glClearColor(0,1,0,0);
  
  glPushMatrix();
  glLoadIdentity();
     glColor3f(1.0,1.0,0.0); 
    display_string(250,550,"car",1);
  glTranslatef(-1.0,0.0,-3.5);
  glRotatef(xangle,1.0,0.0,0.0);
  glRotatef(yangle,0.0,1.0,0.0);
  glRotatef(zangle,0.0,0.0,1.0);
  glTranslatef(xt,yt,zt);
  glScalef(xs,ys,zs);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  if(flag2&&flag1)
  {
  GLfloat fogcolour[4]={1.0,1.0,1.0,1.0};         

  glFogfv(GL_FOG_COLOR,fogcolour);              /* Define the fog colour */
  glFogf(GL_FOG_DENSITY,0.2);                   /* How dense */
  glFogi(GL_FOG_MODE,GL_EXP);                   /* exponential decay */
  glFogf(GL_FOG_START,3.0);                   /* Where wwe start fogging */
  glFogf(GL_FOG_END,100.0);                       /* end */
  glHint(GL_FOG_HINT, GL_FASTEST);              /* compute per vertex */
  glEnable(GL_FOG);/* ENABLE */
  }
  if(flag2==0)
  {
	  glDisable(GL_FOG);
  }
  glBegin(GL_QUADS);                /* start drawing the cube.*/
  
  /* top of cube*/
  //************************FRONT BODY****************************************
  glColor3f(r,g,b); 
  glVertex3f( 0.2, 0.4,0.6);        
  glVertex3f(0.6, 0.5,0.6);        
  glVertex3f(0.6, 0.5,0.2);        
  glVertex3f( 0.2,0.4,0.2);        

  /* bottom of cube*/
  glVertex3f( 0.2,0.2,0.6);        
  glVertex3f(0.6,0.2,0.6);      
  glVertex3f(0.6,0.2,0.2);        
  glVertex3f( 0.2,0.2,0.2);        

  /* front of cube*/
  glVertex3f( 0.2,0.2,0.6);        
  glVertex3f(0.2, 0.4,0.6);       
  glVertex3f(0.2,0.4,0.2);        
  glVertex3f( 0.2,0.2,0.2);        

  /* back of cube.*/            
  glVertex3f(0.6,0.2,0.6);        
  glVertex3f(0.6,0.5,0.6);        
  glVertex3f(0.6,0.5,0.2);        
  glVertex3f( 0.6,0.2,0.2);        

  /* left of cube*/
  glVertex3f(0.2,0.2,0.6);        
  glVertex3f(0.6,0.2,0.6);        
  glVertex3f(0.6,0.5,0.6);        
  glVertex3f(0.2,0.4,0.6);        

  /* Right of cube */
  glVertex3f(0.2,0.2,0.2);        
  glVertex3f( 0.6,0.2,0.2);       
  glVertex3f( 0.6,0.5,0.2);       
  glVertex3f( 0.2,0.4,0.2);       
//****************************************************************************
  glVertex3f(0.7,0.65,0.6);
  glVertex3f(0.7,0.65,0.2);
  glVertex3f(1.7,0.65,0.2);        //top cover
  glVertex3f(1.7,0.65,0.6);
//***************************back guard******************************
  glColor3f(r,g,b);            /* Set The Color To Blue*/
  glVertex3f( 1.8, 0.5,0.6);       
  glVertex3f(1.8, 0.5,0.2);        
  glVertex3f(2.1, 0.4, 0.2);        
  glVertex3f(2.1,0.4,0.6);        

  /* bottom of cube*/
  glVertex3f( 2.1,0.2,0.6);        
  glVertex3f(2.1,0.2,0.2);        
  glVertex3f(1.8,0.2,0.6);        
  glVertex3f( 1.8,0.2,0.6);        

  /* back of cube.*/            
  glVertex3f(2.1,0.4,0.6);        
  glVertex3f(2.1,0.4,0.2);        
  glVertex3f(2.1,0.2,0.2);        
  glVertex3f(2.1,0.2,0.6);        

  /* left of cube*/
  glVertex3f(1.8,0.2,0.2);        
  glVertex3f(1.8,0.5,0.2);        
  glVertex3f(2.1,0.4,0.2);        
  glVertex3f(2.1,0.2,0.2);        

  /* Right of cube */
  glVertex3f(1.8,0.2,0.6);        
  glVertex3f(1.8,0.5,0.6);        
  glVertex3f(2.1,0.4,0.6);        
  glVertex3f(2.1,0.2,0.6);        
//******************MIDDLE BODY************************************
  glVertex3f( 0.6, 0.5,0.6);        
  glVertex3f(0.6, 0.2,0.6);       
  glVertex3f(1.8, 0.2, 0.6);       
  glVertex3f(1.8,0.5,0.6);        

  /* bottom of cube*/
  glVertex3f( 0.6,0.2,0.6);        
  glVertex3f(0.6,0.2,0.2);        
  glVertex3f(1.8,0.2,0.2);        
  glVertex3f( 1.8,0.2,0.6);        

  /* back of cube.*/            
  glVertex3f(0.6,0.5,0.2);        
  glVertex3f(0.6,0.2,0.2);        
  glVertex3f(1.8,0.2,0.2);        
  glVertex3f(1.8,0.5,0.2);        
//*********************ENTER WINDOW**********************************
  glColor3f(0.5,0.3,0.9);           
  glVertex3f( 0.77, 0.63,0.2);        
  glVertex3f(0.75, 0.5,0.2);        //quad front window      
  glVertex3f(1.2, 0.5, 0.2);        
  glVertex3f( 1.22,0.63,0.2);

  glVertex3f(1.27,0.63,.2);
  glVertex3f(1.25,0.5,0.2);        //quad back window
  glVertex3f(1.65,0.5,0.2);
  glVertex3f(1.67,0.63,0.2);
  
  glColor3f(r,g,b);
  glVertex3f(0.7,0.65,0.2);
  glVertex3f(0.7,0.5,.2);       //first separation
  glVertex3f(0.75,0.5,0.2);
  glVertex3f(0.77,0.65,0.2);

  glVertex3f(1.2,0.65,0.2);
  glVertex3f(1.2,0.5,.2);       //second separation
  glVertex3f(1.25,0.5,0.2);
  glVertex3f(1.27,0.65,0.2);

  glVertex3f(1.65,0.65,0.2);
  glVertex3f(1.65,0.5,.2);     //3d sepa
  glVertex3f(1.7,0.5,0.2);
  glVertex3f(1.7,0.65,0.2);

  glVertex3f( 0.75, 0.65,0.2);        
  glVertex3f(0.75, 0.63,0.2);        //line strip      
  glVertex3f(1.7, 0.63, 0.2);        
  glVertex3f( 1.7,0.65,0.2);

  glVertex3f( 0.75, 0.65,0.6);        
  glVertex3f(0.75, 0.63,0.6);        //line strip      
  glVertex3f(1.7, 0.63, 0.6);        
  glVertex3f( 1.7,0.65,0.6);

  glColor3f(0.5,0.3,0.9);           
  glVertex3f( 0.77, 0.63,0.6);        
  glVertex3f(0.75, 0.5,0.6);        //quad front window      
  glVertex3f(1.2, 0.5, 0.6);        
  glVertex3f( 1.22,0.63,0.6);

  glVertex3f(1.27,0.63,.6);
  glVertex3f(1.25,0.5,0.6);        //quad back window
  glVertex3f(1.65,0.5,0.6);
  glVertex3f(1.67,0.63,0.6);
  
  glColor3f(r,g,b);
  glVertex3f(0.7,0.65,0.6);
  glVertex3f(0.7,0.5,.6);       //first separation
  glVertex3f(0.75,0.5,0.6);
  glVertex3f(0.77,0.65,0.6);

  glVertex3f(1.2,0.65,0.6);
  glVertex3f(1.2,0.5,.6);       //second separation
  glVertex3f(1.25,0.5,0.6);
  glVertex3f(1.27,0.65,0.6);

  glVertex3f(1.65,0.65,0.6);
  glVertex3f(1.65,0.5,.6);
  glVertex3f(1.7,0.5,0.6);
  glVertex3f(1.7,0.65,0.6);
  glEnd();
 //************************************************************** 
  glBegin(GL_QUADS);
  
  /* top of cube*/
  glColor3f(0.5,0.3,0.9);
  glVertex3f( 0.6, 0.5,0.6);        
  glVertex3f(0.6, 0.5,0.2);        //quad front window      
  glVertex3f(0.7, 0.65, 0.2);        
  glVertex3f( 0.7,0.65,0.6);

  glVertex3f(1.7,0.65,.6);
  glVertex3f(1.7,0.65,0.2);        //quad back window
  glVertex3f(1.8,0.5,0.2);
  glVertex3f(1.8,0.5,0.6);

  
//*****************************road and surrounding development***********************************
  if(flag1)
  {
	glPushMatrix();
	glTranslatef(xw,0,0);
  

  glColor3f(0,1,0);
  glVertex3f(-100,0.1,-100);
  glVertex3f(-100,0.1,0);         //a green surroundings
  glVertex3f(100,0.1,0);
  glVertex3f(100,0.1,-100);

  glColor3f(0.7,0.7,0.7);
  glVertex3f(-100,0.1,0);
  glVertex3f(-100,0.1,0.45);         //a long road
  glVertex3f(100,0.1,0.45);
  glVertex3f(100,0.1,0);

  glVertex3f(-100,0.1,0.55);
  glVertex3f(-100,0.1,1);         //a long road
  glVertex3f(100,0.1,1);
  glVertex3f(100,0.1,0.55);

  /*glColor3f(0,1,0);
  glVertex3f(-100,0.1,1);
  glVertex3f(-100,0.1,100);         //a green surroundings
  glVertex3f(100,0.1,100);
  glVertex3f(100,0.1,1);*/
    glPopMatrix();
  }
  glEnd();

  if(wheelflag)
  {
	  glPushMatrix();
	  glTranslatef(xw,0,0);
	  glColor3f(0.5,.2,0.3);
	  glBegin(GL_QUADS);
	  for(i=0.0;i<200.0;i=i+0.2)
	  {
		  glVertex3f(-100+i,0,1);
		  glVertex3f(-99.9+i,0,1);
		  glVertex3f(-99.9+i,0.2,1);
		  glVertex3f(-100+i,0.2,1);
		 i=i+0.5;
	  }
	  for(i=0;i<200;i=i+0.2)
	  {
		  glVertex3f(-100+i,0,0);
		  glVertex3f(-99.9+i,0,0);
		  glVertex3f(-99.9+i,0.2,0);
		  glVertex3f(-100+i,0.2,0);
		  i=i+0.5;
	  }
	  glEnd();
	  glPopMatrix();
  }
//*************************************************************************************************
glBegin(GL_TRIANGLES);                /* start drawing the cube.*/
  
  /* top of cube*/
  glColor3f(0.5,0.3,0.9);
  glVertex3f( 0.6, 0.5,0.6);                        
  glVertex3f( 0.7,0.65,0.6);       //tri front window
  glVertex3f(0.7,0.5,0.6);
           
  glVertex3f( 0.6, 0.5,0.2);                        
  glVertex3f( 0.7,0.65,0.2);       //tri front window
  glVertex3f(0.7,0.5,0.2);

  glVertex3f( 1.7, 0.65,0.2);                        
  glVertex3f( 1.8,0.5,0.2);       //tri back window
  glVertex3f( 1.7,0.5,0.2);
           
  glVertex3f( 1.7, 0.65,0.6);                        
  glVertex3f( 1.8,0.5,0.6);       //tri back window
  glVertex3f(1.7,0.5,0.6);

glEnd();
//************IGNITION SYSTEM**********************************
glPushMatrix();
   glColor3f(0.7,0.7,0.7);
   glTranslatef(1.65,0.2,0.3);
   glRotatef(90.0,0,1,0);
   gluCylinder(t,0.02,0.03,.5,10,10);
   
   glPopMatrix();  
//***********WHEEL*********************************************
  
glColor3f(0.7,0.7,0.7);
glPushMatrix();
  glBegin(GL_LINE_STRIP);
	  for( theta=0;theta<360;theta=theta+20)
	  {
  glVertex3f(0.6,0.2,0.62);
  glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
	  }
glEnd();

glBegin(GL_LINE_STRIP);
	  for(theta=0;theta<360;theta=theta+20)
	  {
  glVertex3f(0.6,0.2,0.18);
  glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
	  }
glEnd();

glBegin(GL_LINE_STRIP);
for(theta=0;theta<360;theta=theta+20)
	  {
  glVertex3f(1.7,0.2,0.18);
  glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
	  }
glEnd();

glBegin(GL_LINE_STRIP);
for(theta=0;theta<360;theta=theta+20)
	  {
  glVertex3f(1.7,0.2,0.62);
  glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
	  }
glEnd();
  glTranslatef(0.6,0.2,0.6);
  glColor3f(0,0,0);
  glutSolidTorus(0.025,0.07,10,25);

  glTranslatef(0,0,-0.4);
  glutSolidTorus(0.025,0.07,10,25);

  glTranslatef(1.1,0,0);
  glutSolidTorus(0.025,0.07,10,25);

  glTranslatef(0,0,0.4);
  glutSolidTorus(0.025,0.07,10,25);  
glPopMatrix();
//*************************************************************  
  glPopMatrix(); 
 }
  glFlush();
  glutSwapBuffers();
 glutPostRedisplay();
}


/*  The function called whenever a "normal" key is pressed. */
void NormalKey(GLubyte key, GLint x, GLint y) 
{
    switch ( key )    { 
     case ESCAPE :
        printf("escape pressed. exit.\n");
	glutDestroyWindow(window);	/* Kill our window */
	exit(0); 			/* Very dirty exit */                  
        break;				/* Do we need this??? */
	 case ' ':view=1;
        glutPostRedisplay();
		 break;
     case 'x':
        xangle += 5.0;
        glutPostRedisplay();
        break;
     case 'X':
        xangle -= 5.0;
        glutPostRedisplay();
        break;

     case 'y':
        yangle += 5.0;
        glutPostRedisplay();
        break;
     case 'Y':
        yangle -= 5.0;
        glutPostRedisplay();
        break;

     case 'z':
        zangle += 5.0;
        glutPostRedisplay();
        break;
     case 'Z':
        zangle -= 5.0;
        glutPostRedisplay();
        break;
      case 'u':                          /* Move up */
        yt += 0.2;
        glutPostRedisplay();
        break;
     
	  case 'U':
        yt -= 0.2;                      /* Move down */
        glutPostRedisplay();
        break;

      case 'f':                          /* Move forward */
        zt += 0.2;
        glutPostRedisplay();
        break;
     
	  case 'F':
        zt -= 0.2;                      /* Move away */
        glutPostRedisplay();
        break;

	  case 's':zs+=.2;
		  glutPostRedisplay();
		  break;

	  case 'S':zs-=0.2;
		  glutPostRedisplay();
		  break;

	  case 'a':ys+=.2;
		  glutPostRedisplay();
		  break;

	  case 'A':ys-=0.2;
		  glutPostRedisplay();
		  break;

	  case 'q':xs+=.2;
		  glutPostRedisplay();
		  break;

	  case 'Q':xs-=0.2;
		  glutPostRedisplay();
		  break;
	  
	  case 'd':
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;

     case 'D':
        glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;	
     default:
	break;
    }

}

static void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key ) {
	case GLUT_KEY_UP:
		if(!wheelflag)
		xt += 0.2;
		if(wheelflag)
		{
		angle+=5;
		xw+=0.2;
		}
	    glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		if(!wheelflag)
		xt -= 0.2;
		if(wheelflag)
		{
		angle+=5;
		xw-=0.2;
		}               
        glutPostRedisplay();
		break;
	}
}

void myMenu(int id)
{
		if (id==1)
	{
		flag1=0;
		wheelflag=0;
	glutPostRedisplay();

	}
	if(id ==2)
	{
		flag1=1;
		flag2=0;
		wheelflag=0;
		//xangle += 5.0;
		glutPostRedisplay();
	}
	if(id==3)
	{
	    flag1=1;
		flag2=1;
		wheelflag=0;
		//xangle += 5.0;
		glutPostRedisplay();
	}
	if (id==4)
	{
		 wheelflag=1;
		 glutPostRedisplay();
	}
	if (id==5)
	{
		if(light)
		{
			count++;
			glDisable(GL_LIGHTING);
			light=0;
		}
		else
		{
			light=1;
			glEnable(GL_LIGHTING);
		}
	}
}

void colorMenu(int id)
{
		if (id==1)
	{
		r=g=0;
		b=1;
	glutPostRedisplay();

	}
	if(id ==2)
	{
		r=0.8;
		b=g=0;
		glutPostRedisplay();
	}
	if(id==3)
	{
	    g=1;
		r=b=0;
		glutPostRedisplay();
	}
	if (id==4)
	{
		 r=b=g=0;
		 glutPostRedisplay();
	}
	if(id==5)
	{
		b=0;
		r=g=1;
        glutPostRedisplay();
	}
	if(id==6)
	{
		b=r=g=.7;
        glutPostRedisplay();
	}

}

//*************************** Main ***************************************************************

int main(int argc, char **argv) 
{  

/* Initialisation and window creation */

  glutInit(&argc, argv);               /* Initialize GLUT state. */

  glutInitDisplayMode(GLUT_RGBA |      /* RGB and Alpha */
                      GLUT_DOUBLE|     /* Double buffer */
                      GLUT_DEPTH);     /* Z buffer (depth) */

  glutInitWindowSize(Xsize,Ysize);         /* set initial window size. */
  glutInitWindowPosition(0,0);         /* upper left corner of the screen. */

  window = glutCreateWindow("3D CAR WITH TRANSFORMATIONS"); /* Open a window with a title. */ 

/* Now register the various callback functions */

  glutDisplayFunc(DrawGLScene);        /* Function to do all our OpenGL drawing. */
  glutReshapeFunc(ReSizeGLScene);
  glutKeyboardFunc(NormalKey);         /*Normal key is pressed */
  glutSpecialFunc( SpecialKeyFunc );
  InitGL(Xsize,Ysize);
  glutCreateMenu(myMenu);
	glutAddMenuEntry("car model mode", 1);
	glutAddMenuEntry("car driving mode", 2);
	glutAddMenuEntry("fog effect",3);
	glutAddMenuEntry("wheel effect",4);
	glutAddMenuEntry("toggle light",5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

glutCreateMenu(colorMenu);
	glutAddMenuEntry("blue", 1);
	glutAddMenuEntry("red", 2);
	glutAddMenuEntry("green",3);
	glutAddMenuEntry("black",4);
	glutAddMenuEntry("yellow",5);
	glutAddMenuEntry("grey",6);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
  /* Now drop into the event loop from which we never return */

  glutMainLoop();                      /* Start Event Processing Engine. */  
  return 1;
} 
