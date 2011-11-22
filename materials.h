#ifndef MATERIALS_H
#define MATERIALS_H

enum {
	GREEN_PLASTIC, WHITE_PLASTIC, RUBY, STEEL, GOLD
} MaterialType;
enum {
	TORSO_MATERIAL, NECK_MATERIAL, HEAD_MATERIAL, EYE_MATERIAL,
	ARM_MATERIAL, LEG_MATERIAL, RUBY_MATERIAL, STEEL_MATERIAL, GOLD_MATERIAL
} MaterialDisplayList;


GLfloat 
	green_plastic_ambient[] = {0.05, 0.1, 0.05, 1}, 
	green_plastic_diffuse[] = {0.1, 0.35, 0.1, 1.0}, 
	green_plastic_specular[] = {0.45, 0.55, 0.45},
	green_plastic_shininess = 0.25,
	white_plastic_ambient[] = {0.1, 0.1, 0.1, 1}, 
	white_plastic_diffuse[] = {0.6, 0.6, 0.6, 1.0}, 
	white_plastic_specular[] = {0.7, 0.7, 0.7},
	white_plastic_shininess = 0.2,
	ruby_ambient[] = {0.1745, 0.01175, 0.01175, 0.55},
	ruby_diffuse[] = {0.61424, 0.04136, 0.04136, 0.55},
	ruby_specular[] = {0.727811, 0.626959, 0.626959},
	ruby_shininess = 0.6,
	steel_ambient[] = {0.23125, 0.23125, 0.23125, 1},
	steel_diffuse[] = {0.2775, 0.2775, 0.2775, 1},
	steel_specular[] = {0.773911, 0.773911, 0.773911},
	steel_shininess = 0.6,
	gold_ambient[] = {0.24725, 0.1995, 0.0745, 1},
	gold_diffuse[] = {0.75164, 0.60648, 0.22648, 1},
	gold_specular[] = {0.628281, 0.555802, 0.366065},
	gold_shininess = 0.4;

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
	materialSelect(RUBY_MATERIAL, RUBY);
	materialSelect(STEEL_MATERIAL, STEEL);
	materialSelect(GOLD_MATERIAL, GOLD);
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
	case RUBY: 
		material(object, ruby_ambient, ruby_diffuse, ruby_specular, ruby_shininess);
		break;
	case STEEL: 
		material(object, steel_ambient, steel_diffuse, steel_specular, steel_shininess);
		break;
	case GOLD: 
		material(object, gold_ambient, gold_diffuse, gold_specular, gold_shininess);
		break;
	}
}

#endif