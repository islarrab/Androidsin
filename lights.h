#ifndef LIGHTS_H
#define LIGHTS_H

enum {
	LIGHT_OFF, LIGHT_WHITE, LIGHT_RED, LIGHT_GREEN, LIGHT_BLUE
} LightValues;

const GLfloat light_velocity = 0.5;
int current_light = LIGHT_WHITE;
int display_light_source = 0;

GLfloat 
	red_light[] = {1, 0, 0, 1}, 
	green_light[] = {0, 1, 0, 1},
	blue_light[] = {0, 0, 1, 1},
	white_light[] = {1, 1, 1, 1}, 
	no_light[] = {0, 0, 0, 1},
	light0_position[] = {-1, 0, 1, 0};

void initLights();
void lightSelect(GLenum, int);
void lightMove(GLenum, GLfloat, GLfloat, GLfloat);

void initLights() {
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
}

void lightSelect(GLenum which, int value) {
	glEnable(which);
	switch (value) {
	case LIGHT_OFF:
		glDisable(which);
		break;
	case LIGHT_RED:
		glLightfv(which, GL_DIFFUSE, red_light);
		break;
	case LIGHT_WHITE:
		glLightfv(which, GL_DIFFUSE, white_light);
		break;
	case LIGHT_GREEN:
		glLightfv(which, GL_DIFFUSE, green_light);
		break;
	case LIGHT_BLUE:
		glLightfv(which, GL_DIFFUSE, blue_light);
		break;
	}
	glutPostRedisplay();
}

void lightMove(GLenum which, GLfloat x, GLfloat y, GLfloat z) {
	switch(which) {
	case GL_LIGHT0: 
		light0_position[0] += x;
		light0_position[1] += y;
		light0_position[2] += z;
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		break;
	}
}

void drawLightSource() {
	glPushMatrix();
	GLUquadric* quad = gluNewQuadric();
	glColor4f(1, 1, 1, 1);
	glTranslatef(light0_position[0], light0_position[1], light0_position[2]);
	gluSphere(quad, 0.1, 5, 5);
	glPopMatrix();
}
#endif