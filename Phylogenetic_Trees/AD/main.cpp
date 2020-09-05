#include "additive_distance.hpp"

#define KEY_ESC 27

additive_distance *tree;

//
//funcion llamada a cada imagen
void glPaint(void) {
	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();

	//dibuja el arbol
	tree->display();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);
	//todas la informaciones previas se aplican al la matriz del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {
	//Inicializacion de la GLUT
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("Phylogenetic Tree"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL
	
	//Main Begin
	int n = 0;
	cout << "Ingrese cantidad de nodos: ";
	cin >> n;
	vector<string> nodes(n);
	//vector<vector<double>> dmatrix(n);
	//double d_val = 0.0;
	vector<vector<int>> dmatrix(n);
	int d_val = 0.0;
	cout << "Ingrese los nodos: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> nodes[i];
	}
	cout << "Ingrese la matriz: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> d_val;
			dmatrix[i].push_back(d_val);
		}
	}
	tree = new additive_distance(nodes, dmatrix);
	tree->generate();
	//Main End
	
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering
	
	return 0;
}
