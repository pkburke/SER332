//========================================================================
// SER 332 Project # - Name
//========================================================================
#include <GL\glut.h>

//========================================================================
// ***** DECLARATIONS *****
void init();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void menu(int option);
void createMenus();

void display();

//========================================================================
// ***** GLOBALS *****
int width = 650;
int height = 650;

int mouse_button;
int mouse_x = 0;
int mouse_y = 0;

float scale = 1;
float x_angle = 0;
float y_angle = 0;

GLdouble aspect = 1;

//========================================================================
// ***** MAIN *****
void main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Hello OpenGL");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	init();

	glutMainLoop();
}

//========================================================================
// ***** INIT & RESHAPE *****
void init() {
	glClearColor(0.53, 0.81, 0.92, 0.0);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);

	createMenus();
}

//------------------------------------------------------------------------
void reshape(int w, int h) {
	if(h <= 0) h = 1;
	width = w;
	height = h;
	aspect = width / (float) height;
}

//========================================================================
// ***** MOUSE & MOTION *****
void mouse(int button, int state, int x, int y) {
	mouse_x = x;
	mouse_y = y;
	mouse_button = button;
}

//------------------------------------------------------------------------
void motion(int x, int y) {
	if(mouse_button == GLUT_LEFT_BUTTON) {
		y_angle += (x - mouse_x) / (float) width * 360.0;
		x_angle += (y - mouse_y) / (float) height * 360.0;
	}
	if(mouse_button == GLUT_RIGHT_BUTTON) {
		scale += (y - mouse_y) / 100.0;
		if(scale < 0.1) {
			scale = 0.1;
		}
		if(scale > 100) {
			scale = 100;
		}
	}
	mouse_x = x;
	mouse_y = y;
}

//========================================================================
// ***** KEYBOARD *****
void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'C': case 'c':
		y_angle = 0;
		x_angle = 0;
		break;
	default:
		exit(0);
	}
}

//========================================================================
// ***** MENUS *****
void menu(int option) {
	switch(option) {
	default:
		exit(0);
	}
}

//------------------------------------------------------------------------
void createMenus() {
	glutCreateMenu(menu);
	glutAddMenuEntry("Quit", 99);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

//========================================================================
// ***** DISPLAY *****
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, aspect, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 2, 0, 0, 0, 0, 0, 0, -1);

	glPushMatrix();
	glScalef(scale, scale, scale);
	glRotatef(x_angle, 1, 0, 0);
	glRotatef(y_angle, 0, 1, 0);

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 0);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);

	glColor3f(0, 0, 1);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, -1);
	glVertex3f(-1, 0, -1);

	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}
