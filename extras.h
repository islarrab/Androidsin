#ifndef EXTRAS_H
#define EXTRAS_H

#include <math.h>
GLuint texture[2]; //Arreglo de texturas
const int BLACK = 0;
const int WHITE = 1;
const int BLUE = 2;
const int GREEN = 3;
const int RED = 4;
const int PURPLE = 5;
const int YELLOW = 6;
const int CYAN = 7;
const int RAND = 8;

void displayAxes();
void drawCube(float);
void drawSquarePrism(float,float,float);
void coloring(int);
void drawHalfSphere(GLfloat, GLint, GLint);

void displayAxes() {
	float size = 10;

	glBegin(GL_LINES);

	// Eje X
	coloring(BLUE);
	glVertex3f(0,0,0);
	glVertex3f(size,0,0);

	// Eje Y
	coloring(RED);
	glVertex3f(0,0,0);
	glVertex3f(0,size,0);

	// Eje Z
	coloring(GREEN);
	glVertex3f(0,0,0);
	glVertex3f(0,0,size);

	glEnd();
}

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

void coloring(int color){
	switch(color){
	case 0: glColor3f(0.2,0.2,0.2); break; // Negro
	case 1: glColor3f(1,1,1); break; // Blanco
	case 2: glColor3f(0,0,1); break; // Azul
	case 3: glColor3f(0,1,0); break; // Verde
	case 4: glColor3f(1,0,0); break; // Rojo
	case 5: glColor3f(1,0,1); break; // Morado
	case 6: glColor3f(0,1,1); break; // Cyan
	case 7: glColor3f(1,1,0); break; // Amarillo
	case 8: coloring(rand() % 7 + 1); break; // Multicolor
	}
}

#endif
