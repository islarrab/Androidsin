#ifndef SHAPES_H
#define SHAPES_H

#include <math.h>

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
	const double PI = 3.14159265;
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
	const double PI = 3.14159265;
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

#endif