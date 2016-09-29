// Core Libraries
#include <iostream>
#include <string>
#include <math.h>

// 3rd Party Libraries
#include <GLUT\glut.h>

// Defines and Core variables
#define FRAMES_PER_SECOND 60
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND; // Miliseconds per frame

int windowWidth = 1920;
int windowHeight = 1080;

int mousepositionX;
int mousepositionY;

bool keyDown[256];
GLfloat rY = 0.0f;
GLfloat rX = 0.0f;
GLfloat rZ = 0.0f;
GLfloat tY = 0.0f;
GLfloat tX = 0.0f;
GLfloat tZ = -100.0f;

// A few conversions to know
float degToRad = 3.14159f / 180.0f;
float radToDeg = 180.0f / 3.14159f;

/* function DisplayCallbackFunction(void)
* Description:
*  - this is the openGL display routine
*  - this draws the sprites appropriately
*/
void DisplayCallbackFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	

	glTranslatef(tX, tY, tZ);

	glRotatef(rX, 1.0f, 0, 0);
	glRotatef(rY, 0, 1.0f, 0);
	glRotatef(rZ, 0, 0, 1.0f);


	//face 1
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(-10, -10, 10);//1
	glVertex3f(-10, 10, 10);//2
	glVertex3f(10, 10, 10);//3
	glVertex3f(10, -10, 10);//4
	glEnd();
	
	//face2
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(10, -10, -10);//4
	glVertex3f(10, 10, -10);//3
	glVertex3f(-10, 10, -10);//2
	glVertex3f(-10, -10, -10);//1
	glEnd();

	//face3
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(10, -10, -10);
	glVertex3f(10, -10, 10);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 10, -10);
	glEnd();

	//face4
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(-10, 10, 10);
	glVertex3f(-10, 10, -10);
	glVertex3f(10, 10, -10);
	glVertex3f(10, 10, 10);
	glEnd();

	//face5
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-10, -10, 10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, 10, -10);
	glVertex3f(-10, 10, 10);
	glEnd();

	//face6
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(10, -10, 10);//4
	glVertex3f(10, -10, -10);//3
	glVertex3f(-10, -10, -10);//2
	glVertex3f(-10, -10, 10);//1
	glEnd();


	glutSwapBuffers();
}

/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	keyDown[key] = true;
}

/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	keyDown[key] = false;
}

void idleFunc()
{

}

/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	// key contols //
	if (keyDown['e'])
	{
		tZ += 2.0;
	}
	if (keyDown['q'])
	{
		tZ -= 2.0;
	}
	if (keyDown['w'])
	{
		tY += 2.0;
	}
	if (keyDown['s'])
	{
		tY -= 2.0;
	}
	if (keyDown['a'])
	{
		tX -= 2.0;
	}
	if (keyDown['d'])
	{
		tX += 2.0;
	}
	if (keyDown['k'])
	{
		rX += 3.0;
	}
	if (keyDown['i'])
	{
		rX -= 3.0;
	}
	if (keyDown['l'])
	{
		rY += 3.0;
	}
	if (keyDown['j'])
	{
		rY -= 3.0;
	}
	// this call makes it actually show up on screen //
	glutPostRedisplay();


	// this call gives it a proper frame delay to hit our target FPS //
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	windowHeight = h;
	windowWidth = w;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0f, (float)w/(float)h, 0.1f, 10000.0f);
	//				fov, aspect ratio, near, far
	glViewport(0, 0, w, h);

	windowWidth = w;
	windowHeight = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	// Handle mouse clicks
	if (state == GLUT_DOWN)
	{
		std::cout << "Mouse x:" << x << " y:" << y << std::endl;
	}
}


/* function MouseMotionCallbackFunction()
* Description:
*   - this is called when the mouse is clicked and moves
*/
void MouseMotionCallbackFunction(int x, int y)
{
}

/* function MousePassiveMotionCallbackFunction()
* Description:
*   - this is called when the mouse is moved in the window
*/
void MousePassiveMotionCallbackFunction(int x, int y)
{
	mousepositionX = x;
	mousepositionY = y;
}

void init()
{
	///// INIT OpenGL /////
	// Set color clear value
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	// Enable Z-buffer read and write (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D); // textures for future use

							 //Example03
	glLineWidth(4.0f);
	glPolygonMode(GL_FRONT, GL_LINE); //GL_FRONT_AND_BACK, GL_FILL
}


/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/

int main(int argc, char **argv)
{
	// initialize the window and OpenGL properly /
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("INFR1350U - Example");

	// set up our function callbacks /
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutIdleFunc(idleFunc);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutPassiveMotionFunc(MousePassiveMotionCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);

	init(); //Setup OpenGL States

	// start the event handler /
	glutMainLoop();
	return 0;
}