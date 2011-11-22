#include <stdio.h>			// Standard Input/Output
#include <GL/gl.h>			// Libreria OpenGL32
#include <GL/glut.h>		// Libreria Glaux
#include <GL/glu.h>			// Libreria GLu32
#include "Render.h"

/* Graficas Computacionales - José Luis Gordillo
   Desarrollo de ejemplo - Cynthia Aidee Treviño Lopez
   
   Manejo de Texturas - Dibuja un Cubo en OpenGL, Vertice X Vertice
   Cada una de las Caras presenta una textura diferente
   Funciones Extras: Manejo de Teclado.
                 F1, F2 -> Rotación.
                 F3, F4-> Traslación en Z 
                 Flechas Arriba, Abajo, Izquierda, Derecha -> Cambios de Posicion
   Restricciones: Archivos .tga */

GLfloat angr, z1;
GLuint	texture[6],x,y,z;
bool interruptor = true;


void cargaImagenes(){
  //Lectura y Carga de Imagenes en el Arreglo
     texture[0] = LoadTexture("Data/ladrillos.tga");
     texture[1] = LoadTexture("Data/marmol.tga");
}

void displayevent(void)
{
	// limpia la escena (ventana)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// verfica superficies visibles
	glEnable( GL_DEPTH_TEST );
    
        //Habilita el manejo de texturas
        glEnable(GL_TEXTURE_2D);
  
	// inicializa la Matriz de transformación de coordenadas (Matriz del Modelo)
	glLoadIdentity();

	// traslada la escena al centro del espacio
	glTranslatef( -0.5, -0.5f, z1 );
	// rota la escena
	glRotatef( angr, x,y,z);

	// construcción de la escena
	// dibuja un cubo en la coord 0,0,0 con dimensiones 1 x 1 x -1
	
	glBindTexture(GL_TEXTURE_2D,texture[1]); // Se mapea la textura actual
	glBegin( GL_QUADS ); // frontal
      glTexCoord2f(1.0f,1.0f); glVertex3f( 1, 0, 0);
      glTexCoord2f(1.0f,0.0f); glVertex3f( 1, 1, 0);
      glTexCoord2f(0.0f,0.0f); glVertex3f( 1, 1, 1);
      glTexCoord2f(0.0f,1.0f); glVertex3f( 1, 0, 1);
	glEnd();
    
    glBindTexture(GL_TEXTURE_2D,texture[1]); // Se mapea la textura actual
	glBegin( GL_QUADS ); // lateral derecha
	 glTexCoord2f(1.0f,1.0f); glVertex3f( 1, 1, 0);
	 glTexCoord2f(1.0f,0.0f); glVertex3f( 0, 1, 0);
	 glTexCoord2f(0.0f,0.0f); glVertex3f( 0, 1, 1);
	 glTexCoord2f(0.0f,1.0f); glVertex3f( 1, 1, 1);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,texture[1]); // Se mapea la textura actual
	glBegin( GL_QUADS ); // superior
	 glTexCoord2f(1.0f,1.0f); glVertex3f( 0, 0, 1);
	 glTexCoord2f(1.0f,0.0f); glVertex3f( 0, 1, 1);
	 glTexCoord2f(0.0f,0.0f); glVertex3f( 1, 1, 1);
	 glTexCoord2f(0.0f,1.0f); glVertex3f( 1, 0, 1);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,texture[1]); // Se mapea la textura actual
	glBegin( GL_QUADS ); // trasera
     glTexCoord2f(1.0f,1.0f); glVertex3f( 0, 0, 1);
	 glTexCoord2f(1.0f,0.0f); glVertex3f( 0, 1, 1);
	 glTexCoord2f(0.0f,0.0f); glVertex3f( 0, 1, 0);
	 glTexCoord2f(0.0f,1.0f); glVertex3f( 0, 0, 0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,texture[1]); // Se mapea la textura actual
	glBegin( GL_QUADS ); // lateral izquiera
     glTexCoord2f(1.0f,1.0f); glVertex3f( 0, 0, 1);
	 glTexCoord2f(1.0f,0.0f); glVertex3f( 1, 0, 1);
	 glTexCoord2f(0.0f,0.0f); glVertex3f( 1, 0, 0);
	 glTexCoord2f(0.0f,1.0f); glVertex3f( 0, 0, 0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,texture[1]); // Se mapea la textura actual
	glBegin( GL_QUADS ); // inferior
     glTexCoord2f(1.0f,1.0f); glVertex3f( 0, 0, 0);
	 glTexCoord2f(1.0f,0.0f); glVertex3f( 0, 1, 0);
     glTexCoord2f(0.0f,0.0f); glVertex3f( 1, 1, 0);
	 glTexCoord2f(0.0f,1.0f); glVertex3f( 1, 0, 0);
	glEnd();

	// muestra la escena
	glutSwapBuffers();

}

void specialkeyevent( int key, int Xx, int Yy )
{
 // manejo de teclas especiales
 
 switch ( key ) {
	
    case GLUT_KEY_UP:  x=1; y=-1; z=-1; break;
	case GLUT_KEY_DOWN:  x=-1; y=1; z=-1; break;
	case GLUT_KEY_RIGHT:  x=-1; y=-1; z=1; break;
	case GLUT_KEY_LEFT:  x=1; y=1; z=1; break;
	
    // cambia la z para la traslación del cubo (adelante y atras)
	case GLUT_KEY_F3:    z1 += 0.1; break;
	case GLUT_KEY_F4:    z1 -= 0.1; break;

	// cambia el delta del angulo de rotación
 	case GLUT_KEY_F1:    angr+= 0.5; break;
	case GLUT_KEY_F2:    angr-= 0.5; break;
 }
 // redibuja la escena
 glutPostRedisplay();
}

void reshapeevent(GLsizei width, GLsizei height)
{
	// establecer el área de visualizacion en la ventana
	glViewport(0,0,width,height);

	// seleccionar la matriz de Proyección
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Vista en Perspectiva
	gluPerspective(45,(GLfloat)width/(GLfloat)height,  0.01, 20);

	// Restaurar a la matriz del Modelo (escena)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

} // reshape


int main(int argc, char** argv)
{
  //Ciclo infinito
if (interruptor){ //Inicializacion
    	cargaImagenes();
	// inicialización del GLUT
	glutInit( &argc, argv );

	// inicialiación de la ventana
	glutInitWindowSize( 300, 300 );
	glutInitWindowPosition( 100, 100 );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow( "" );

	glutSetWindowTitle( "Manejo de Texturas" );

	// inicialización de los datos del programa
	angr  = 45;
	z1 = -5;
	x=1;
	y=1;
	z=1;
	
    interruptor = false; //Asegura que la inicializacion no se realize en c/iteracion
}
    glutReshapeFunc (reshapeevent); //Manejo de Cambio de Ventana
	glutDisplayFunc( displayevent ); // Funcion de Dibujo
	glutSpecialFunc( specialkeyevent ); //Manejo de Teclado
	
	// lazo de eventos
	glutMainLoop();

	return 0;
} // main
