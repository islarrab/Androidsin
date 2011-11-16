#ifndef ANDROID_H
#define ANDROID_H

#include <limits.h>

int stacks=50, slices=50;

int theta[36] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

// Formato:
// { {xmin, xmax}, {ymin, ymax}, {zmin, zmax}, ... }

int limits[36][2] = {
	{INT_MIN, INT_MAX}, {INT_MIN, INT_MAX}, {INT_MIN, INT_MAX}, // ???
	{INT_MIN, INT_MAX}, {INT_MIN, INT_MAX}, {INT_MIN, INT_MAX}, // Torso
	{-10,	10},	{-10,	10},	{-90,	90},	// Cabeza
	{0,		0},		{0,		0},		{0,		0},		// Cuello
	{-180,	45},	{-180,	0},		{-180,	0},		// Brazo derecho superior
	{-160,	0},		{0,		0},		{0,		0},		// Brazo derecho inferior
	{-180,	45},	{0,		180},	{0,		180},	// Brazo izquierdo superior
	{-160,	0},		{0,		0},		{0,		0},		// Brazo izquierdo inferior
	{-90,	10},	{-45,	10},	{-45,	45},	// Pierna derecha superior
	{0,		160},	{0,		0},		{0,		0},		// Pierna derecha inferior
	{-90,	10},	{-10,	45},	{-45,	45},	// Pierna izquierda superior
	{0,		160},	{0,		0},		{0,		0},		// Pierna izquierda inferior
};

int drawAxes = 0;

class Node {
public:
	Node();
    virtual void draw() const;
	Node* getSibling();
	Node* getChild();
	void setSibling(Node*);
	void setChild(Node*);
	GLfloat m[16];

private:
	Node* sibling;
	Node* child;
};

Node::Node() {
	sibling = NULL;
	child = NULL;
}

void Node::draw() const {
	printf("Using unimplemented draw\n");
}

Node* Node::getSibling() {
	return sibling;
}

Node* Node::getChild() {
	return child;
}

void Node::setSibling(Node* node) {
	sibling = node;
}

void Node::setChild(Node* node) {
	child = node;
}

// Inicio de partes del cuerpo

float TORSO_LENGTH = 0;
float TORSO_WIDTH = 0;
float ARM_LENGTH = 0;
float ARM_WIDTH = 0;
float LEG_LENGTH = 0;
float LEG_WIDTH = 0;
float NECK_LENGTH = 0;
float NECK_WIDTH = 0;
float HEAD_SIZE = 0;
float ANTENA_LENGTH = 10;
float ANTENA_RADIOUS = 0;

class Torso : public Node {
public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(90,1,0,0);
		glRotatef(theta[3],1,0,0);
		glRotatef(theta[4],0,1,0);
		glRotatef(theta[5],0,0,1);

		if (drawAxes) displayAxes();

		glCallList(TORSO_MATERIAL);

		gluCylinder(quad, TORSO_WIDTH, TORSO_WIDTH, TORSO_LENGTH, 100, 1);
		gluDisk(quad, 0, TORSO_WIDTH, 50, 1);
		glTranslatef(0, 0, TORSO_LENGTH);
		gluDisk(quad, 0, TORSO_WIDTH, 50, 1);
		glTranslatef(0, 0, -TORSO_LENGTH);
	}
};

class Neck : public Node {
public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[9],1,0,0);
		glRotatef(theta[10],0,1,0);
		glRotatef(theta[11],0,0,1);

		if (drawAxes) displayAxes();

		glCallList(NECK_MATERIAL);

		gluCylinder(quad, NECK_WIDTH, NECK_WIDTH, NECK_LENGTH, 100, 1);
	}
};	

class Head : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[6],1,0,0);//-90
		glRotatef(theta[7],0,1,0);
		glRotatef(theta[8],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(HEAD_MATERIAL);

		drawHalfSphere(HEAD_SIZE, stacks, slices);
		gluDisk(quad, 0, HEAD_SIZE, 50, 1);

		glCallList(EYE_MATERIAL);

		// Ojo Derecho
		glPushMatrix();
			glTranslatef(-HEAD_SIZE/3, -HEAD_SIZE/1.2, HEAD_SIZE/2.5);
			gluSphere(quad, 0.3, 10, 10);
		glPopMatrix();

		// Ojo Izquierdo
		glPushMatrix();
			glTranslatef(HEAD_SIZE/3, -HEAD_SIZE/1.2, HEAD_SIZE/2.5);
			gluSphere(quad, 0.3, 10, 10);
		glPopMatrix();
		
		glCallList(HEAD_MATERIAL);

		// Antena Derecha
		glPushMatrix();
			glRotatef(30, 0, 1, 0);
			gluCylinder(quad, ANTENA_RADIOUS, ANTENA_RADIOUS, ANTENA_LENGTH, 50, 10);
			glTranslatef(0, 0, ANTENA_LENGTH);
			gluSphere(quad, ANTENA_RADIOUS, 10, 10);
		glPopMatrix();

		// Antena Izquierda
		glPushMatrix();
			glRotatef(-30, 0, 1, 0);
			gluCylinder(quad, ANTENA_RADIOUS, ANTENA_RADIOUS, ANTENA_LENGTH, 50, 10);
			glTranslatef(0, 0, ANTENA_LENGTH);
			gluSphere(quad, ANTENA_RADIOUS, 10, 10);
		glPopMatrix();

	}
};

class UpperRightArm : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[12],1,0,0);//90
		glRotatef(theta[13],0,1,0);
		glRotatef(theta[14],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(ARM_MATERIAL);

		gluSphere(quad, ARM_WIDTH, 50, 50);
		gluCylinder(quad, ARM_WIDTH, ARM_WIDTH, ARM_LENGTH, 50, 1);
	}
};

class LowerRightArm : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[15],1,0,0);//90
		glRotatef(theta[16],0,1,0);
		glRotatef(theta[17],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(ARM_MATERIAL);

		gluSphere(quad, ARM_WIDTH, 50, 50);
		gluCylinder(quad, ARM_WIDTH, ARM_WIDTH, ARM_LENGTH, 50, 1);
		glTranslatef(0,0, ARM_LENGTH);
		gluSphere(quad, ARM_WIDTH, 50, 50);
	}
};

class UpperLeftArm : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[18],1,0,0);//90
		glRotatef(theta[19],0,1,0);
		glRotatef(theta[20],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(ARM_MATERIAL);

		gluSphere(quad, ARM_WIDTH, 50, 50);
		gluCylinder(quad, ARM_WIDTH, ARM_WIDTH, ARM_LENGTH, 50, 1);
	}
};

class LowerLeftArm : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[21],1,0,0);//90
		glRotatef(theta[22],0,1,0);
		glRotatef(theta[23],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(ARM_MATERIAL);

		gluSphere(quad, ARM_WIDTH, 50, 50);
		gluCylinder(quad, ARM_WIDTH, ARM_WIDTH, ARM_LENGTH, 50, 1);
		glTranslatef(0,0, ARM_LENGTH);
		gluSphere(quad, ARM_WIDTH, 50, 50);
	}
};

class UpperRightLeg : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[24],1,0,0);//90
		glRotatef(theta[25],0,1,0);
		glRotatef(theta[26],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(LEG_MATERIAL);

		gluSphere(quad, LEG_WIDTH, 50, 50);
		gluCylinder(quad, LEG_WIDTH, LEG_WIDTH, LEG_LENGTH, 50, 1);
	}
};

class LowerRightLeg : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[27],1,0,0);//90
		glRotatef(theta[28],0,1,0);
		glRotatef(theta[29],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(LEG_MATERIAL);

		gluSphere(quad, LEG_WIDTH, 50, 50);
		gluCylinder(quad, LEG_WIDTH, LEG_WIDTH, LEG_LENGTH, 50, 1);
		glTranslatef(0,0, LEG_LENGTH);
		gluSphere(quad, LEG_WIDTH, 50, 50);
	}
};

class UpperLeftLeg : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[30],1,0,0);//90
		glRotatef(theta[31],0,1,0);
		glRotatef(theta[32],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(LEG_MATERIAL);

		gluSphere(quad, LEG_WIDTH, 50, 50);
		gluCylinder(quad, LEG_WIDTH, LEG_WIDTH, LEG_LENGTH, 50, 1);
	}
};

class LowerLeftLeg : public Node {
	public:
	void draw() const {
		GLUquadric* quad = gluNewQuadric();
		glRotatef(theta[33],1,0,0);//90
		glRotatef(theta[34],0,1,0);
		glRotatef(theta[35],0,0,1);
		
		if (drawAxes) displayAxes();

		glCallList(LEG_MATERIAL);

		gluSphere(quad, LEG_WIDTH, 50, 50);
		gluCylinder(quad, LEG_WIDTH, LEG_WIDTH, LEG_LENGTH, 50, 1);
		glTranslatef(0,0, LEG_LENGTH);
		gluSphere(quad, LEG_WIDTH, 50, 50);
	}
};

Torso* torso = new Torso();
Neck* neck = new Neck();
Head* head = new Head();
UpperRightArm* urArm = new UpperRightArm();
LowerRightArm* lrArm = new LowerRightArm();
UpperLeftArm* ulArm = new UpperLeftArm();
LowerLeftArm* llArm = new LowerLeftArm();
UpperRightLeg* urLeg = new UpperRightLeg();
LowerRightLeg* lrLeg = new LowerRightLeg();
UpperLeftLeg* ulLeg = new UpperLeftLeg();
LowerLeftLeg* llLeg = new LowerLeftLeg();

void initTree() {
	// Se arma el arbol
	// Torso	
	torso->setChild(neck);
	
	// Cabeza
	neck->setChild(head);
	neck->setSibling(ulArm);

	// Brazo Derecho
	urArm->setSibling(ulLeg);
	urArm->setChild(lrArm);

	// Brazo Izquierdo
	ulArm->setSibling(urArm);
	ulArm->setChild(llArm);
	
	// Pierna Izquierda
	ulLeg->setSibling(urLeg);
	ulLeg->setChild(llLeg);

	// Pierna Derecha
	urLeg->setChild(lrLeg);

	//utilizar las funciones de OpenGL para crear la matriz
	
	// Torso
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, torso->m);

	// Cuello
	glLoadIdentity();
	glRotatef(180, 1, 0, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, neck->m);

	// Cabeza
	glLoadIdentity();
	glTranslatef(0,0,NECK_LENGTH);
	glGetFloatv(GL_MODELVIEW_MATRIX, head->m);

	// Brazo Derecho Superior
	glLoadIdentity();
	glTranslatef(-(TORSO_WIDTH+0.4), 0, 0.7);
	glGetFloatv(GL_MODELVIEW_MATRIX, urArm->m);

	// Brazo Derecho Inferior
	glLoadIdentity();
	glTranslatef(0, 0, ARM_LENGTH);
	glGetFloatv(GL_MODELVIEW_MATRIX, lrArm->m);

	// Brazo Izquierdo Superior
	glLoadIdentity();
	glTranslatef(TORSO_WIDTH+0.4, 0, 0.7);
	glGetFloatv(GL_MODELVIEW_MATRIX, ulArm->m);

	// Brazo Izquierdo Inferior
	glLoadIdentity();
	glTranslatef(0, 0, ARM_LENGTH);
	glGetFloatv(GL_MODELVIEW_MATRIX, llArm->m);

	// Pierna Derecha Superior
	glLoadIdentity();
	glTranslatef(-TORSO_WIDTH/2, 0, TORSO_LENGTH);
	glGetFloatv(GL_MODELVIEW_MATRIX, urLeg->m);

	// Pierna Derecha Inferior
	glLoadIdentity();
	glTranslatef(0, 0, LEG_LENGTH);
	glGetFloatv(GL_MODELVIEW_MATRIX, lrLeg->m);

	// Pierna Izquierda Superior
	glLoadIdentity();
	glTranslatef(TORSO_WIDTH/2, 0, TORSO_LENGTH);
	glGetFloatv(GL_MODELVIEW_MATRIX, ulLeg->m);
	
	// Pierna Izquierda Inferior
	glLoadIdentity();
	glTranslatef(0, 0, LEG_LENGTH);
	glGetFloatv(GL_MODELVIEW_MATRIX, llLeg->m);
}

#endif