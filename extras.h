#ifndef EXTRAS_H
#define EXTRAS_H

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
void coloring(int);

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
