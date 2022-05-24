#include"Graph.h"


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");

	glutInit(&argc, argv);

	graph.set_Graph();
	graph.Komi();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W, H);
	glutCreateWindow("Коммивояжёр");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMainLoop();
	return 0;

}
