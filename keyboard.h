#ifndef KEYBOARD_H
#define KEYBOARD_H

GLfloat z,
	camera_position[] = {0, 0, 10},
	camera_rotation[] = {0, 0, 0};

GLfloat camera_velocity = 1;

int velocidad = 5;

int menu = 1;

void keyboard(unsigned char, int, int);
void specialkeyevent(int, int, int);

void keyboard( unsigned char key, int x, int y ) {
	
	switch ( key ) {
	case 'l': // luz, mov derecha
		lightMove(GL_LIGHT0, light_velocity, 0, 0);
		break;
	case 'j': // luz, mov izquierda
		lightMove(GL_LIGHT0, -light_velocity, 0, 0);
		break;
	case 'i': // luz, mov arriba
		lightMove(GL_LIGHT0, 0, light_velocity, 0);
		break;
	case 'k': // luz, mov abajo
		lightMove(GL_LIGHT0, 0, -light_velocity, 0);
		break;
	case 'u': // luz, mov hacia pantalla
		lightMove(GL_LIGHT0, 0, 0, light_velocity);
		break;
	case 'o': // luz, mov hacia fondo
		lightMove(GL_LIGHT0, 0, 0, -light_velocity);
		break;

	case 'd': // camara, mov derecha
		camera_position[0] += camera_velocity;
		break;
	case 'a': // camara, mov izquierda
		camera_position[0] -= camera_velocity;
		break;
	case 'w': // camara, mov arriba
		camera_position[1] += camera_velocity;
		break;
	case 's': // camara, mov abajo
		camera_position[1] -= camera_velocity;
		break;
	case 'q': // camara, mov pantalla
		camera_position[2] += camera_velocity;
		break;
	case 'e': // camara, mov fondo
		camera_position[2] -= camera_velocity;
		break;


	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void specialkeyevent( int key, int Xx, int Yy ) {
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
	case GLUT_KEY_F9: display_light_source = (display_light_source == 0) ? 1 : 0; break;
	case GLUT_KEY_F10: current_light = (current_light+1)%5; lightSelect(GL_LIGHT0, current_light); break;
	case GLUT_KEY_F11: z += 0.1; break;
	case GLUT_KEY_F12: z -= 0.1; break;
	case GLUT_KEY_INSERT: drawAxes = (drawAxes==0) ? 1 : 0; break;
	case GLUT_KEY_HOME: break;
	case GLUT_KEY_PAGE_UP: break;
	}
	// redibuja la escena
	glutPostRedisplay();
}

#endif