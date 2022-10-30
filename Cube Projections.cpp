#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// Global Variables
GLfloat d = 0;
GLuint a = 0, fullScr = 0;
GLuint mainWin, subWin1, subWin2, subWin3, height, width;
GLuint anglex = 0, angley = 0, anglez = 0, cavx = 0, cabx = 0, perx = 0, cavy = 0, caby = 0, pery = 0, cavz = 0, cabz = 0, perz = 0;

// Cube
GLfloat V[8][3] = {
	{-1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, -1.0, 1.0},
	{-1.0, -1.0, 1.0},
	{-1.0, 1.0, -1.0},
	{1.0, 1.0, -1.0},
	{1.0, -1.0, -1.0},
	{-1.0, -1.0, -1.0},
};

// Axes
GLfloat A[6][2] = {
	{-5.0, 0.0},
	{5.0, 0.0},
	{0.0, 5.0},
	{0.0, -5.0},
	{5.0, 5.0},
	{-5.0, -5.0},
};

// Initialization
void MyInit()
{
	glClearColor(0.9, 0.7, 0.5, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000.0 / 60.0, timer, 0);
}

void Display()
{
	glClearColor(1.0, 0.9, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Get Window Height and Width
	height = glutGet(GLUT_WINDOW_HEIGHT);
	width = glutGet(GLUT_WINDOW_WIDTH);

	glutSwapBuffers();
	glutPostRedisplay();
}

// Draw Axes
void DrawAxis(GLfloat x1[], GLfloat x2[], GLfloat y1[], GLfloat y2[], GLfloat z1[], GLfloat z2[])
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(y1);
	glVertex3fv(y2);
	glVertex3fv(z1);
	glVertex3fv(z2);
	glEnd();
	glPopAttrib();
}

// Draw Cube's Face
void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
	glBegin(GL_POLYGON);
	glVertex3fv(A);
	glVertex3fv(B);
	glVertex3fv(C);
	glVertex3fv(D);
	glEnd();
}

// Draw Cube
void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
	glColor3f(1, 0, 0);
	Face(V0, V1, V2, V3); // Front
	glColor3f(0, 1, 0);
	Face(V4, V5, V6, V7); // Back
	glColor3f(0, 0, 1);
	Face(V0, V4, V7, V3); // Left
	glColor3f(1, 1, 0);
	Face(V1, V5, V6, V2); // Right
	glColor3f(1, 0, 1);
	Face(V2, V3, V7, V6); // Bot
	glColor3f(0, 1, 1);
	Face(V0, V1, V5, V4); // Top
}

// Cavalier Projection (Subwindow 1)
void CavDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection Matrix
	GLfloat cavalier[] =
		{1.0, 0.0, 0.0, 0.0,
		 0.0, 1.0, 0.0, 0.0,
		 ((sqrt(2)) / 2.0), ((sqrt(2)) / 2.0), -1.0, 0.0,
		 0.0, 0.0, 0.0, 1.0};

	glPushMatrix();
	glMultMatrixf(cavalier);
	Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
	glPopMatrix();

	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMultMatrixf(cavalier);
	glRotatef(anglex, 1, 0, 0); // Rotation of All Three Cubes Around x-axis
	glRotatef(angley, 0, 1, 0); // Rotation of All Three Cubes Around y-axis
	glRotatef(anglez, 0, 0, 1); // Rotation of All Three Cubes Around z-axis
	glRotatef(cavx, 1, 0, 0);	// Rotation of First Cube Around x-axis
	glRotatef(cavy, 0, 1, 0);	// Rotation of First Cube Around y-axis
	glRotatef(cavz, 0, 0, 1);	// Rotation of First Cube Around z-axis
	Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, -0.4, -5);
	DrawAxis(A[0], A[1], A[2], A[3], A[4], A[5]);
	glPopMatrix();

	// Adjust Scene in Fullscreen Mode
	if (height > 600)
	{
		glutSetWindow(mainWin);
		glClearColor(1.0, 0.9, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glutSetWindow(subWin1);

		glutReshapeWindow(0.58 * height, 0.45 * width);
		glutPositionWindow(30, 50);
	}

	// Adjust Scene in non Fullscreen Mode
	if (height == 600)
	{
		fullScr = 0;
		glutReshapeWindow(400, 500);
		glutPositionWindow(50, 50);
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

// Cabinet Projection (Subwindow 2)
void CabDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection Matrix
	GLfloat cabinet[] =
		{1.0, 0.0, 0.0, 0.0,
		 0.0, 1.0, 0.0, 0.0,
		 -((sqrt(3)) / 4.0), -1 / 4.0, 1.0, 0.0,
		 0.0, 0.0, 0.0, 1.0};

	glPushMatrix();
	glMultMatrixf(cabinet);
	Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
	glPopMatrix();

	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMultMatrixf(cabinet);
	glRotatef(anglex, 1, 0, 0); // Rotation of All Three Cubes Around x-axis
	glRotatef(angley, 0, 1, 0); // Rotation of All Three Cubes Around y-axis
	glRotatef(anglez, 0, 0, 1); // Rotation of All Three Cubes Around z-axis
	glRotatef(cabx, 1, 0, 0);	// Rotation of Second Cube Around x-axis
	glRotatef(caby, 0, 1, 0);	// Rotation of Second Cube Around y-axis
	glRotatef(cabz, 0, 0, 1);	// Rotation of Second Cube Around z-axis
	Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.7, -0.8, -5);
	DrawAxis(A[0], A[1], A[2], A[3], A[4], A[5]);
	glPopMatrix();

	// Adjust Scene in Fullscreen Mode
	if (height > 600)
	{
		glutSetWindow(mainWin);
		glClearColor(1.0, 0.9, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glutSetWindow(subWin2);
		glutReshapeWindow(0.58 * height, 0.45 * width);
		glutPositionWindow(530, 50);
	}

	// Adjust Scene in non Fullscreen Mode
	if (height == 600)
	{
		fullScr = 0;
		glutReshapeWindow(400, 500);
		glutPositionWindow(500, 50);
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

// Perspective Projection (Subwindow 3)
void PersDisplay()
{
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	int w = glutGet(GLUT_WINDOW_WIDTH);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 200); // Perspective Projection (View Angle: 60 Degrees in the y Direction, Distance from the Viewer to the Near Clipping Plane: 0.1 / Far Clipping Plane:200)
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
	glPopMatrix();

	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(1.0, 0.0, 0.0);
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 200);
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	glRotatef(anglex, 1, 0, 0); // Rotation of All Three Cubes Around x-axis
	glRotatef(angley, 0, 1, 0); // Rotation of All Three Cubes Around y-axis
	glRotatef(anglez, 0, 0, 1); // Rotation of All Three Cubes Around z-axis
	glRotatef(perx, 1, 0, 0);	// Rotation of Third Cube Around x-axis
	glRotatef(pery, 0, 1, 0);	// Rotation of Third Cube Around y-axis
	glRotatef(perz, 0, 0, 1);	// Rotation of Third Cube Around z-axis
	Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
	glPopMatrix();

	glPushMatrix();
	if (fullScr == 1)
		glTranslatef(-0.4, -1, -5);
	else
		glTranslatef(-0.2, -1, -5);
	DrawAxis(A[0], A[1], A[2], A[3], A[4], A[5]);
	glPopMatrix();

	// Adjust Scene in Fullscreen Mode
	if (height > 600)
	{
		fullScr = 1;
		glutSetWindow(mainWin);
		glClearColor(1.0, 0.9, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glutSetWindow(subWin3);
		glutReshapeWindow(0.58 * height, 0.45 * width);
		glutPositionWindow(1030, 50);
	}

	// Adjust Scene in non Fullscreen Mode
	if (height == 600)
	{
		fullScr = 0;
		glutReshapeWindow(400, 500);
		glutPositionWindow(950, 50);
	}

	glutPostRedisplay();

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	float aspect = (float)w / (float)h;
	if (h == 0)
		h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, -20.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

// Rotation around Axes with Key Press for Subwindow1 (Cavalier Projection)
void CavKeyboard(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'x':
		a = 1;
		anglex = (anglex + 5) % 360;
		glutPostRedisplay();
		break;

	case 'y':
		a = 2;
		angley = (angley + 5) % 360;
		glutPostRedisplay();
		break;

	case 'z':
		a = 3;
		anglez = (anglez + 5) % 360;
		glutPostRedisplay();
		break;

	case 'X':
		cavx = (cavx + 5) % 360;
		break;

	case 'Y':
		cavy = (cavy + 5) % 360;
		break;

	case 'Z':
		cavz = (cavz + 5) % 360;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

// Rotation around Axes with Key Press for Subwindow2 (Cabinet Projection)
void CabKeyboard(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'x':
		a = 1;
		anglex = (anglex + 5) % 360;
		glutPostRedisplay();
		break;

	case 'y':
		a = 2;
		angley = (angley + 5) % 360;
		glutPostRedisplay();
		break;

	case 'z':
		a = 3;
		anglez = (anglez + 5) % 360;
		glutPostRedisplay();
		break;

	case 'X':
		cabx = (cabx + 5) % 360;
		break;

	case 'Y':
		caby = (caby + 5) % 360;
		break;

	case 'Z':
		cabz = (cabz + 5) % 360;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

// Rotation around Axes with Key Press for Subwindow3 (Perspective Projection)
void PersKeyboard(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'x':
		a = 1;
		anglex = (anglex + 5) % 360;
		glutPostRedisplay();
		break;

	case 'y':
		a = 2;
		angley = (angley + 5) % 360;
		glutPostRedisplay();
		break;

	case 'z':
		a = 3;
		anglez = (anglez + 5) % 360;
		glutPostRedisplay();
		break;

	case 'X':
		perx = (perx + 5) % 360;
		break;

	case 'Y':
		pery = (pery + 5) % 360;
		break;

	case 'Z':
		perz = (perz + 5) % 360;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

// Zoom in/out when the Mouse is Clicked
void MouseClicked(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		glScalef(1.1, 1.1, 1.1);
	if (button == GLUT_RIGHT_BUTTON)
		glScalef(0.9, 0.9, 0.9);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);  // Initialize the GLUT Library
	glutInitWindowSize(1400, 600);	 // Set Window Size
	glutInitWindowPosition(0, 0); // Set Window Position
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Set Initial Display Mode
	mainWin = glutCreateWindow("Projections");  // Create Main Window
	glutDisplayFunc(Display);  // Set the Display Callback
	subWin1 = glutCreateSubWindow(mainWin, 50, 50, 400, 500); // Create Subwindow 1 (Cavalier Projection)
	MyInit();  // Initialize Subwindow 1
	glutDisplayFunc(CavDisplay);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseClicked);
	glutKeyboardFunc(CavKeyboard); // Keyboard Callback for Subwindow 1
	glutTimerFunc(1000.0 / 60.0, timer, 0);
	subWin2 = glutCreateSubWindow(mainWin, 500, 50, 400, 500); // Create Subwindow 2 (Cabinet Projection)
	MyInit();  // Initialize Subwindow 2
	glutDisplayFunc(CabDisplay);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(CabKeyboard); // Keyboard Callback for Subwindow 2
	glutMouseFunc(MouseClicked);
	glutTimerFunc(1000.0 / 60.0, timer, 0);
	subWin3 = glutCreateSubWindow(mainWin, 950, 50, 400, 500); // Create Subwindow 3 (Perspective Projection)
	MyInit(); // Initialize Subwindow 3
	glutDisplayFunc(PersDisplay);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(PersKeyboard); // Keyboard Callback for Subwindow 3
	glutMouseFunc(MouseClicked);
	glutTimerFunc(1000.0 / 60.0, timer, 0);
	glutMainLoop();
	return 0;
}