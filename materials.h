#ifndef MATERIALS_H
#define MATERIALS_H

enum {
	GREEN_PLASTIC, WHITE_PLASTIC
} MaterialType;
enum {
	TORSO_MATERIAL, NECK_MATERIAL, HEAD_MATERIAL, EYE_MATERIAL,
	ARM_MATERIAL, LEG_MATERIAL
} MaterialDisplayList;


GLfloat 
	green_plastic_ambient[] = {0, 0, 0, 1}, 
	green_plastic_diffuse[] = {0.1, 0.35, 0.1, 1.0}, 
	green_plastic_specular[] = {0.45, 0.55, 0.45},
	green_plastic_shininess = 0.25,
	white_plastic_ambient[] = {0, 0, 0, 1}, 
	white_plastic_diffuse[] = {0.6, 0.6, 0.6, 1.0}, 
	white_plastic_specular[] = {0.7, 0.7, 0.7},
	white_plastic_shininess = 0.25;

void initMaterials();
void material(int, GLfloat*, GLfloat*, GLfloat*, GLfloat);
void materialSelect(int, int);
void lightSelect(GLenum, int);

void initMaterials() {
	// Se define los materiales
	materialSelect(TORSO_MATERIAL, GREEN_PLASTIC);
	materialSelect(NECK_MATERIAL, GREEN_PLASTIC);
	materialSelect(HEAD_MATERIAL, GREEN_PLASTIC);
	materialSelect(EYE_MATERIAL, WHITE_PLASTIC);
	materialSelect(ARM_MATERIAL, GREEN_PLASTIC);
	materialSelect(LEG_MATERIAL, GREEN_PLASTIC);
}

void material(int dlist, GLfloat * ambient, GLfloat * diffuse, 
	GLfloat * specular, GLfloat shininess) {
		printf("material(%f, %f, %f, %f)\n", diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
		glNewList(dlist, GL_COMPILE);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128);
		glEndList();
}

void materialSelect(int object, int value) {
	glutPostRedisplay();
	printf("materialSelect(%d, %d)\n", object, value);
	switch (value) {
	case GREEN_PLASTIC: 
		material(object, green_plastic_ambient, green_plastic_diffuse, green_plastic_specular, green_plastic_shininess);
		break;
	case WHITE_PLASTIC: 
		material(object, white_plastic_ambient, white_plastic_diffuse, white_plastic_specular, white_plastic_shininess);
		break;
	}
}

#endif