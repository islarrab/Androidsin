#ifndef MEDIDAS_H
#define MEDIDAS_H

enum {
	GREEN_PLASTIC, WHITE_PLASTIC
} MaterialType;
enum {
	TORSO_MATERIAL = 1, NECK_MATERIAL = 2, HEAD_MATERIAL = 3, EYE_MATERIAL = 4
} MaterialDisplayList;
enum {
	LIGHT_OFF, LIGHT_WHITE, LIGHT_RED, LIGHT_GREEN
} LightValues;

GLfloat 
	red_light[] = {1.0, 0.0, 0.0, 1.0}, 
	green_light[] = {0.0, 1.0, 0.0, 1.0}, 
	white_light[] = {1.0, 1.0, 1.0, 1.0}, 
	left_light_position[] = {-1.0, 0.0, 1.0, 0.0}, 
	right_light_position[] = {10, 0.0, -5, 0.0},
	green_plastic_ambient[] = {0, 0, 0, 1}, 
	green_plastic_diffuse[] = {0.1, 0.35, 0.1, 1.0}, 
	green_plastic_specular[] = {0.45, 0.55, 0.45},
	green_plastic_shininess = 0.25,
	white_plastic_ambient[] = {0, 0, 0, 1}, 
	white_plastic_diffuse[] = {0.55, 0.55, 0.55, 1.0}, 
	white_plastic_specular[] = {0.7, 0.7, 0.7},
	white_plastic_shininess = 0.25;

void initMaterials();
void material(int, GLfloat*, GLfloat*, GLfloat*, GLfloat);
void materialSelect(int, int);

void material(int dlist, GLfloat * ambient, GLfloat * diffuse, 
	GLfloat * specular, GLfloat shininess) {
		glNewList(dlist, GL_COMPILE);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		glEndList();
}

void materialSelect(int object, int value) {
	glutPostRedisplay();
	switch (value) {
	case GREEN_PLASTIC: material(object, green_plastic_ambient, green_plastic_diffuse, green_plastic_specular, green_plastic_shininess);
	case WHITE_PLASTIC: material(object, white_plastic_ambient, white_plastic_diffuse, white_plastic_specular, white_plastic_shininess);
	}
}

void initMaterials() {
	// Se define los materiales
	materialSelect(TORSO_MATERIAL, GREEN_PLASTIC);
	materialSelect(NECK_MATERIAL, GREEN_PLASTIC);
	materialSelect(HEAD_MATERIAL, GREEN_PLASTIC);
	materialSelect(EYE_MATERIAL, WHITE_PLASTIC);
}

#endif