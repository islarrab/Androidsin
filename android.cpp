#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "materials.h"
#include "lights.h"
#include "extras.h"
#include "android.h"
#include "keyboard.h"
#include "Render.h"
#include "mouse.h"


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
#define SWORD 12 //Espada
#define ANIMA 13 //Animación


// The time in milliseconds between timer ticks
#define TIMERMSECS 1

GLfloat angx, angy;

bool interruptor = true; //Para interruptor

const int NUM_PARTES = 11;

int direccion = 1; //empieza positivo
bool animation = false;

//Prototipos
static void animate(int value);

//Metodo para cargar imagenes de texturas.
void cargaImagenes(){
	//Lectura y Carga de Imagenes en el Arreglo
	texture[0] = LoadTexture("Data/ladrillos.tga");
	texture[1] = LoadTexture("Data/marmol.tga");
}

void animacion() {
	if(!animation) {
		animation = true;
		glutTimerFunc(TIMERMSECS, animate, 0);
	} else {
		animation = false;
	}
}

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
	case SWORD:
		menu = SWORD;
		break;
	case ANIMA:
		//menu = ANIMA;
		// Llamar a función animate(int)
		//glutTimerFunc(TIMERMSECS, animate, 0);
		animacion();
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

void displayevent(void) {

	// limpia la escena (ventana)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// verfica superficies visibles
	glEnable( GL_DEPTH_TEST );
	
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_MODELVIEW);

	// inicializa la Matriz de transformaci�n de coordenadas (Matriz del Modelo)
	glLoadIdentity();
	
	// movimiento de camara
	glTranslatef(-camera_position[0], -camera_position[1], -camera_position[2]);

	// Para la rotacion con el mouse
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0,3.4,0);
	glEnable(GL_TEXTURE_2D);
	drawCube(20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	if (display_light_source) drawLightSource();

	traverse(torso);

	glutPostRedisplay();
	// muestra la escena
	glutSwapBuffers();
}

void reshapeevent(GLsizei width, GLsizei LENGTH) {
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
			case 10: ANTENA_RADIUS = atof( (linea.substr( linea.find(":") + 1 )).c_str() ); break;
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

static void animate(int value) {
	// Set up the next timer tick (do this first)

	if(animation)
		glutTimerFunc(TIMERMSECS, animate, 0);

	if(theta[15] < -60 || theta[15] >0){
		theta[15] = 0;
		direccion = 1;
	}

	if(theta[15] == -60 )
		direccion = 1;
	else if(theta[15] == 0 )
		direccion = -1;	

	theta[15] = theta[15] + (3 * direccion);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//Lectura de Archivo
	lecturaDeArchivo();
	//Ciclo infinito
	//if(interruptor)
	// inicializaci�n del GLUT
	glutInit( &argc, argv );

	// inicialiaci�n de la ventana
	glutInitWindowSize( 600, 600 );
	glutInitWindowPosition( 100, 100 );
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("");

	glutSetWindowTitle("Android");

	// inicializaci�n de los datos del programa
	z = -10;
	cargaImagenes();
	//interruptor = false;
	//}
	initMaterials();
	initLights();
	initTree();

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* degrees field of view */ 50.0,
		/* aspect ratio */ 1.0, /* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.0);      /* up is in positive Y direction */
	glTranslatef(0.0, 0.0, -1.0);


	// Start the timer
	//glutTimerFunc(TIMERMSECS, animate, 0);

	// registro de los eventos
	glutReshapeFunc( reshapeevent ); // Manejo de Cambio de Ventana
	glutDisplayFunc( displayevent ); // Funcion de Dibujo
	glutSpecialFunc( specialkeyevent ); // Manejo de Teclado
	glutKeyboardFunc( keyboard );
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);


	//Menu Mouse
	//Sub menus for arms
	int subMenuBrazos1 = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Superior",URA);
	glutAddMenuEntry("Inferior",LRA);
	glutAddMenuEntry("Espada", SWORD);
	int subMenuBrazos2 = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Superior",ULA);
	glutAddMenuEntry("Inferior",LLA);
	int subMenuBrazos = glutCreateMenu(menuCallback);
	glutAddSubMenu("Derecho", subMenuBrazos1);
	glutAddSubMenu("Izquierdo", subMenuBrazos2);

	//Sub menus for legs
	int subMenuPiernas1 = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Superior",URL);
	glutAddMenuEntry("Inferior",LRL);
	int subMenuPiernas2 = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Superior",ULL);
	glutAddMenuEntry("Inferior",LLL);
	int subMenuPiernas = glutCreateMenu(menuCallback);
	glutAddSubMenu("Derecha", subMenuPiernas1);
	glutAddSubMenu("Izquierda", subMenuPiernas2);

	glutCreateMenu(menuCallback);
	glutAddMenuEntry("Torso",TORSO);
	glutAddMenuEntry("Cabeza",HEAD);
	glutAddSubMenu("Brazos", subMenuBrazos);
	glutAddSubMenu("Piernas", subMenuPiernas);
	glutAddMenuEntry("Mover espada", ANIMA);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// lazo de eventos
	glutMainLoop();

	return 0;
} // main
