#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <GL/glut.h>
#include <GL/glu.h>

#include "materiales.h"
#include "extras.h"
#include "android.h"

#define TORSO 1 //Torso
#define HEAD  2 //Cabeza
#define NECK  3 //Cuello
#define URA   4 //UpperRightArm
#define LRA   5 //LowerRightArm
#define ULA   6 //UpperLeftArm
#define LLA   7 //LowerLeftArm
#define URL   8 //UpperRightLeg
#define LRL   9 //LowerRightLeg
#define ULL   10 //UpperLeftLeg
#define LLL   11 //LowerLeftLeg

GLfloat z, angx, angy;

const int NUM_PARTES = 11;

int current_light = LIGHT_WHITE;

int velocidad = 5;

int menu = TORSO;

void menuCallback (int id) {
	switch(id){
		case TORSO:
			menu = TORSO;
			break;
		case HEAD:
			menu = HEAD;
			break;
		case NECK:
			menu = NECK;
			break;
		case URA:
			menu = URA;
			break;
		case LRA:
			menu = LRA;
			break;
		case ULA:
			menu = ULA;
			break;
		case LLA:
			menu = LLA;
			break;
		case URL:
			menu = URL;
			break;
		case LRL:
			menu = LRL;
			break;
		case ULL:
			menu = ULL;
			break;
		case LLL:
			menu = LLL;
			break;
	}

	glutPostRedisplay();
}

//recorrido a profundidad: primero los hijos, luego los hermanos
void traverse (Node *node)
{
	//guardar la matriz actual porque las transformaciones a realizarse s�lo deben afectarle a �l y a sus hijos
	glPushMatrix();

	//transformar relativo a su padre
	glMultMatrixf(node->m);
	
	//dibujar el nodo
	node->draw();
	// primer recorrer los hijos (si hay)
	if (node->getChild() != NULL)
		traverse(node->getChild());
	glPopMatrix();
	// despu�s recorrer los hermanos (si hay)
	if(node->getSibling() != NULL)
		traverse(node->getSibling());
}
   
void displayevent(void)
{
	
	// limpia la escena (ventana)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// verfica superficies visibles
	glEnable( GL_DEPTH_TEST );
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_MODELVIEW);

	// Hagace la luz
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, left_light_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, left_light_position);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white_light);
	// y la luz se hizo

	// inicializa la Matriz de transformaci�n de coordenadas (Matriz del Modelo)
	glLoadIdentity();

	// zoom
	glTranslatef( 0, 0, z );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(0,1,0);
	
	traverse(torso);

	glutPostRedisplay();
	// muestra la escena
	glutSwapBuffers();
}

void specialkeyevent( int key, int Xx, int Yy )
{
	// manejo de teclas especiales
	int i = menu * 3;
	int x = 0;
	switch ( key ) {
	case GLUT_KEY_LEFT:	x = theta[i+1] - velocidad; theta[i+1] = (x < limits[i+1][0])? limits[i+1][0] : x; break;
	case GLUT_KEY_RIGHT: x = theta[i+1] + velocidad; theta[i+1] = (x > limits[i+1][1])? limits[i+1][1] : x; break;
	case GLUT_KEY_UP: x = theta[i] - velocidad; theta[i] = (x < limits[i][0])? limits[i][0] : x; break;
	case GLUT_KEY_DOWN: x = theta[i] + velocidad; theta[i] = (x > limits[i][1])? limits[i][1] : x; break;
	case GLUT_KEY_F1: x = theta[i+2] - velocidad; theta[i+2] = (x < limits[i+2][0])? limits[i+2][0] : x; break;
	case GLUT_KEY_F2: x = theta[i+2] + velocidad; theta[i+2] = (x > limits[i+2][1])? limits[i+2][1] : x; break;
	case GLUT_KEY_F3: stacks+=1; break;
	case GLUT_KEY_F4: stacks-=1; break;
	case GLUT_KEY_F5: slices+=1; break;
	case GLUT_KEY_F6: slices-=1; break;
	case GLUT_KEY_F7: break;
	case GLUT_KEY_F8: break;
	case GLUT_KEY_F9: break;
	case GLUT_KEY_F10: current_light = (current_light+1)%5; lightSelect(GL_LIGHT1, current_light); break; // Aun no sirve
	case GLUT_KEY_F11: z += 0.1; break;
	case GLUT_KEY_F12: z -= 0.1; break;
	case GLUT_KEY_INSERT: drawAxes = (drawAxes==0) ? 1 : 0; break;
	case GLUT_KEY_HOME: break;
	case GLUT_KEY_PAGE_UP: break;
	}
	// redibuja la escena
	glutPostRedisplay();
}

void reshapeevent(GLsizei width, GLsizei LENGTH)
{
	// establecer el �rea de visualizacion en la ventana
	glViewport(0,0,width,LENGTH);

	// seleccionar la matriz de Proyecci�n
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Vista en Perspectiva
	gluPerspective(90,(GLfloat)width/(GLfloat)LENGTH,  0.01, 20);

	// Restaurar a la matriz del Modelo (escena)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

} // reshape

using namespace std;
void lecturaDeArchivo()
{
	ifstream archivo; // Apuntador de archivo para leer las medidas de las partes
	string linea;

	archivo.open("medidas.txt");
	if(archivo.is_open()) // Checar si se pudo abrir el archivo a leer
	{
		int pos = 0;
		while((! archivo.eof()) && pos <= NUM_PARTES) // Mientras no sea fin de archivo
		{
	    	getline(archivo, linea);
			switch(pos){
				case 0: TORSO_LENGTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 1: TORSO_WIDTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 2: ARM_LENGTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 3: ARM_WIDTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 4: LEG_LENGTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 5: LEG_WIDTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 6: NECK_LENGTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 7: NECK_WIDTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 8: HEAD_SIZE = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 9: ANTENA_LENGTH = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
				case 10: ANTENA_RADIOUS = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
			}
			//medidas[pos] = atof( (linea.substr( linea.find(":") + 1 )).c_str() );
			pos++;           
		}
		archivo.close(); // Cerrar el archivo despues de obtener las medidas
    	} else {
        	cout << "ERROR: No se pudo abrir archivo." << endl;
			exit(1);
    	}

	cout << TORSO_LENGTH << endl;
	cout << TORSO_WIDTH << endl;
	cout << ARM_LENGTH << endl;
	cout << ARM_WIDTH << endl;
	cout << LEG_LENGTH << endl;
	cout << LEG_WIDTH << endl;
	cout << NECK_LENGTH << endl;
	cout << NECK_WIDTH << endl;
	cout << HEAD_SIZE << endl;

}

int main(int argc, char** argv)
{
	//Lectura de Archivo
	lecturaDeArchivo();
	//Ciclo infinito

	// inicializaci�n del GLUT
	glutInit( &argc, argv );

	// inicialiaci�n de la ventana
	glutInitWindowSize( 600, 600 );
	glutInitWindowPosition( 100, 100 );
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("");

	glutSetWindowTitle("Android");

	// inicializaci�n de los datos del programa
	z = -10;
	initMaterials();
	initTree();

	// registro de los eventos
	glutReshapeFunc( reshapeevent ); // Manejo de Cambio de Ventana
	glutDisplayFunc( displayevent ); // Funcion de Dibujo
	glutSpecialFunc( specialkeyevent ); // Manejo de Teclado

	//Menu Mouse
	glutCreateMenu(menuCallback);

	glutAddMenuEntry("Torso",TORSO);
	glutAddMenuEntry("Cabeza",HEAD);
	glutAddMenuEntry("Brazo Derecho Superior",URA);
	glutAddMenuEntry("Brazo Derecho Inferior",LRA);
	glutAddMenuEntry("Brazo Izquierdo Superior",ULA);
	glutAddMenuEntry("Brazo Izquierdo Inferior",LLA);
	glutAddMenuEntry("Pierna Derecha",URL);
	glutAddMenuEntry("Pierna Derecha Inferior",LRL);
	glutAddMenuEntry("Pierna Izquierda",ULL);
	glutAddMenuEntry("Pierna Izquierda Inferior",LLL);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// lazo de eventos
	glutMainLoop();

	return 0;
} // main