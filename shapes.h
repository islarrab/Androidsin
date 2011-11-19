#ifndef SHAPES_H
#define SHAPES_H

#include <math.h>

const double PI = 3.14159265;

void drawCube(float);
void drawSquarePrism(float,float,float);
void drawHalfSphere(GLfloat, GLint, GLint);
void drawSphere(GLfloat, GLfloat, GLint, GLint);

void drawCube(float size) {
	float a = size/2;
	float b = a*-1;
	coloring(BLUE);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin( GL_QUADS ); // frontal
	glNormal3d(0,0,1);
	glTexCoord2f(1.0f,1.0f); glVertex3f( b, b, a );
	glTexCoord2f(1.0f,0.0f); glVertex3f( a, b, a );
	glTexCoord2f(0.0f,0.0f); glVertex3f( a, a, a );
	glTexCoord2f(0.0f,1.0f); glVertex3f( b, a, a );
	glEnd();

	coloring(GREEN);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin( GL_QUADS ); // lateral derecha
	glTexCoord2f(1.0f,1.0f); glVertex3f( a, b, a );
	glTexCoord2f(1.0f,0.0f); glVertex3f( a, b, b );
	glTexCoord2f(0.0f,0.0f); glVertex3f( a, a, b );
	glTexCoord2f(0.0f,1.0f); glVertex3f( a, a, a );
	glEnd();

	coloring(RED);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin( GL_QUADS ); // superior
	glNormal3d(0,0,1);
	glTexCoord2f(1.0f,1.0f); glVertex3f( b, a, a );
	glTexCoord2f(1.0f,0.0f); glVertex3f( a, a, a );
	glTexCoord2f(0.0f,0.0f); glVertex3f( a, a, b );
	glTexCoord2f(0.0f,1.0f); glVertex3f( b, a, b );
	glEnd();

	coloring(PURPLE);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin( GL_QUADS ); // trasera
	glNormal3d(0,0,1);
	glTexCoord2f(1.0f,1.0f); glVertex3f( b, b, b );
	glTexCoord2f(1.0f,0.0f); glVertex3f( a, b, b );
	glTexCoord2f(0.0f,0.0f); glVertex3f( a, a, b);
	glTexCoord2f(0.0f,1.0f); glVertex3f( b, a, b );
	glEnd();

	coloring(CYAN);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin( GL_QUADS ); // lateral izquiera
	glNormal3d(0,0,1);
	glTexCoord2f(1.0f,1.0f); glVertex3f( b, b, a );
	glTexCoord2f(1.0f,0.0f); glVertex3f( b, b, b );
	glTexCoord2f(0.0f,0.0f); glVertex3f( b, a, b );
	glTexCoord2f(0.0f,1.0f); glVertex3f( b, a, a );
	glEnd();

	coloring(YELLOW);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glBegin( GL_QUADS ); // inferior
	glNormal3d(0,0,1);
	glTexCoord2f(1.0f,1.0f); glVertex3f( a, b, a );
	glTexCoord2f(1.0f,0.0f); glVertex3f( b, b, a );
	glTexCoord2f(0.0f,0.0f); glVertex3f( b, b, b );
	glTexCoord2f(0.0f,1.0f); glVertex3f( a, b, b );
	glEnd();
}

void drawSquarePrism(float x, float y, float z) {
	float xl = x/2;
	float xr = xl*-1;

	float yu = y;
	float yl = 0;

	float zf = z/2;
	float zb = zf*-1;

	coloring(BLUE);
	glBegin( GL_QUADS ); // frontal
	glVertex3f( xl, yl, zf );
	glVertex3f( xr, yl, zf );
	glVertex3f( xr, yu, zf );
	glVertex3f( xl, yu, zf );


	// lateral derecha
	coloring(GREEN);
	glVertex3f( xr, yl, zf );
	glVertex3f( xr, yl, zb );
	glVertex3f( xr, yu, zb );
	glVertex3f( xr, yu, zf );

	// superior
	coloring(RED);
	glVertex3f( xl, yu, zf );
	glVertex3f( xr, yu, zf );
	glVertex3f( xr, yu, zb );
	glVertex3f( xl, yu, zb );

	// trasera
	coloring(PURPLE);
	glVertex3f( xl, yl, zb );
	glVertex3f( xr, yl, zb );
	glVertex3f( xr, yu, zb );
	glVertex3f( xl, yu, zb );

	// lateral izquiera
	coloring(CYAN);
	glVertex3f( xl, yl, zf );
	glVertex3f( xl, yl, zb );
	glVertex3f( xl, yu, zb );
	glVertex3f( xl, yu, zf );

	// inferior
	coloring(YELLOW);
	glVertex3f( xr, yl, zf );
	glVertex3f( xl, yl, zf );
	glVertex3f( xl, yl, zb );
	glVertex3f( xr, yl, zb );

	glEnd();
}

void drawHalfSphere(GLfloat r, GLint slices, GLint stacks){
	int i,j;
	double arc = 2*PI/slices;
	double z0 = 0;
	double z1 = 0;
	double disc_r0 = r;
	double disc_r1 = r;
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i<stacks; i++) {
		z0 = z1;
		z1 = r/stacks*(i+1);
		disc_r0 = disc_r1;
		disc_r1 = sqrt(r*r-z1*z1);

		for (j = 0; j<=slices; j++) {
			double angle = arc*j;

			double x0 = cos(angle) * disc_r0;
			double y0 = sin(angle) * disc_r0;
			double x1 = cos(angle) * disc_r1;
			double y1 = sin(angle) * disc_r1;
			glNormal3f(x0,y0,z0);
			glVertex3f(x0,y0,z0);
			glNormal3f(x1,y1,z1);
			glVertex3f(x1,y1,z1);
		}
	}
	glEnd();
}

void drawSphere(GLfloat r, GLfloat ang, GLint slices, GLint stacks){
	int i, j;
	double arc_xy = (ang*PI/180.0)/slices;
	double arc_z = PI/stacks;
	double z0 = r;
	double z1 = r;
	double disc_r0 = 0;
	double disc_r1 = 0;

	for (i=0; i<stacks; i++) {
		double angle1 = arc_z * (i+1);
		z0 = z1;
		z1 = cos(angle1)*r;
		disc_r0 = disc_r1;
		disc_r1 = sin(angle1)*r;
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j<=slices; j++) {
			double angle = arc_xy*j;
			double x0 = cos(angle) * disc_r0;
			double y0 = sin(angle) * disc_r0;
			double x1 = cos(angle) * disc_r1;
			double y1 = sin(angle) * disc_r1;
			glNormal3f(x0,y0,z0);
			glVertex3f(x0,y0,z0);
			glNormal3f(x1,y1,z1);
			glVertex3f(x1,y1,z1);
		}
		glEnd();
	}

}

void drawCylinder(GLfloat rx, GLfloat ry, GLfloat z, GLint slices, GLint stacks) {
	GLfloat stack_height = z/stacks;
	GLfloat slice_angle = 2*PI/slices;
	int i,j;
	for (i=0; i<stacks; i++) {
		glBegin(GL_QUAD_STRIP);
		for (j=0; j<=slices; j++) {
			GLfloat ang = slice_angle*j;
			GLfloat x = cos(ang)*rx;
			GLfloat y = sin(ang)*ry;
			glNormal3f(x, y, 0);
			glVertex3f(x, y, 0);
			glVertex3f(x, y, stack_height*(i+1));
		}
		glEnd();
	}
}

void drawEllipse(GLfloat rx, GLfloat ry, GLint slices) {
	GLfloat slice_angle = 2*PI/slices;
	int i;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	for (i=0; i<=slices; i++) {
		GLfloat ang = slice_angle*i;
		GLfloat x = cos(ang)*rx;
		GLfloat y = sin(ang)*ry;

		glVertex3f(x, y, 0);
	}
	glEnd();
}

void drawSword(GLfloat length) {
	GLfloat 
		GRIP_WIDTH = 0.2,
		GRIP_LENGTH = 1,
		POMMEL_SIZE = 0.4,
		GUARD_RX = 0.8,
		GUARD_RY = 1.4,
		BLADE_RX = 0.2,
		BLADE_RY = 0.8;
	
	glPushMatrix();
	  drawCylinder(GRIP_WIDTH,GRIP_WIDTH,GRIP_LENGTH,5,1);
	  glPushMatrix();
	    glTranslatef(0,0,-POMMEL_SIZE/2);
	    drawSphere(POMMEL_SIZE, 360, 5, 5);
	  glPopMatrix();
	  glTranslatef(0,0,1);
	  drawCylinder(GUARD_RX, GUARD_RY, 0.1, 10, 1);
	  glPushMatrix();
		glRotatef(180,1,0,0);
		drawEllipse(GUARD_RX, GUARD_RY, 10);
	  glPopMatrix();
	  glTranslatef(0, 0, 0.1);
	  drawEllipse(GUARD_RX, GUARD_RY, 10);
	  drawCylinder(BLADE_RX, BLADE_RY, length, 4, 1);
	  glTranslatef(0, 0, length);
	  
	  glBegin(GL_TRIANGLE_FAN);
	  glNormal3f(0, 0, 1);
	  glVertex3f(0, 0, 1);
	  glNormal3f(0, BLADE_RY, 0);
	  glVertex3f(0, BLADE_RY, 0);
	  glNormal3f(BLADE_RX, 0, 0);
	  glVertex3f(BLADE_RX, 0, 0);
	  glNormal3f(0, -BLADE_RY, 0);
	  glVertex3f(0, -BLADE_RY, 0);
	  glNormal3f(-BLADE_RX, 0, 0);
	  glVertex3f(-BLADE_RX, 0, 0);
	  glNormal3f(0, BLADE_RY, 0);
	  glVertex3f(0, BLADE_RY, 0);
	  glEnd();
	glPopMatrix();
}

#endif