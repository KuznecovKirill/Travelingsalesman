#pragma once
#include<queue>
#include<iostream>
#include<vector>
#include<iostream>
#include<iomanip>
#include<glut.h>
#include<string>
using namespace std;

int r;
int first_top, last_top, weight;
int W = 1280;
int H = 1024;

void drawButton1();
void drawButton2();
void drawCircle(int x, int y, int r);
void drawVertex(int n);
void drawWeight(int x, int y, int i);
void drawLine(int x1, int y1, int x2, int y2, int w);
void reshape(int w, int h); // если вершин будет много, то нужно увеличить окно
void setCoord(int i, int n);
void mouseClick(int but, int state, int x, int y);
void display();

struct Pos {  // для отрисовки
	int x;
	int y;
	Pos() {
		this->x = 0;
		this->y = 0;
	}
	Pos(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
Pos* P = new Pos[100];

class Graph {
private:
	vector<int> vertexList;
	int maxSize;
	vector<vector<int>> adj;
public:

	Graph(int size); //конструктор
	bool isFull(); //проверка на полноту
	bool isEmpty(); //проверка на пустоту
	void insert_vertex(const int& t); //добавление вершины в vertexList
	int get_vertex_index(const int& t); //получение индекса вершины
	int get_vertex_size(); //получение кол-ва вершин
	int get_adj(int i, int j); // получение элемента из матрицы смежности
	void insertedge(const int& v1, const int& v2, int weight);  // добавление ребра между вершинами
	void removeVertex(int& x); // удаление вершины
	void addVertex(); // добавление вершины через соответствующую кнопку
	void print(); // вывод матрицы
	int Komi(); // решение задачи
	void set_Graph(); // создание графа
	void drawGraph(); // отрисовка графа






};

Graph graph(10);

Graph::Graph(int size) {
	this->maxSize = size;
	this->adj = vector<vector<int>>(size, vector<int>(size));


	for (int i = 0; i < maxSize; ++i) {
		for (int j = 0; j < maxSize; ++j) {
			this->adj[i][j] = 0;
		}
	}
}

bool Graph::isFull() {
	return this->vertexList.size() == this->maxSize;
}

bool Graph::isEmpty() {
	return this->vertexList.size() == 0;
}

void Graph::insert_vertex(const int& t) {
	if (this->isFull()) {
		cout << "Невозможно добавить вершину." << endl;
		return;
	}
	this->vertexList.push_back(t);
}
int Graph::get_vertex_index(const int& t) {
	for (int i = 0; i < this->vertexList.size(); ++i) {
		if (this->vertexList[i] == t) {
			return i;
		}
	}
	return -1;

}

int Graph::get_vertex_size() {
	return this->vertexList.size();
}
int Graph::get_adj(int i, int j) {
	return this->adj[i][j];
}

void Graph::insertedge(const int& v1, const int& v2, int weight) {
	if (get_vertex_index(v1) != (-1)) {
		int v_pos1 = get_vertex_index(v1);
		int v_pos2 = get_vertex_index(v2);
		if (this->adj[v_pos1][v_pos2] != 0 && this->adj[v_pos2][v_pos1] != 0) {
			cout << "Ребро между вершинами есть." << endl;
			return;
		}
		else {
			this->adj[v_pos1][v_pos2] = weight;
			this->adj[v_pos2][v_pos1] = weight;
		}
	}
	else {
		cout << "Обеих вершин (или одной из них) нету в графе" << endl;
		return;
	}

}

void Graph::removeVertex(int& x) {
	while (x - 1 < vertexList.size()) {
		for (int i = 0; i < vertexList.size(); i++) {
			if (x >= vertexList.size()) {
				adj[i][x - 1] = 0;
			}
			else {
				adj[i][x - 1] = adj[i][x];
			}

		}
		for (int i = 0; i < vertexList.size(); i++) {
			if (x >= vertexList.size()) {
				adj[x - 1][i] = 0;
			}
			else {
				adj[x - 1][i] = adj[x][i];
			}

		}
		x++;
	}

	this->vertexList.pop_back();
	display();


}
void Graph::addVertex() {
	int q = graph.get_vertex_size() + 1;
	vector<vector<int>> adj_origin = this->adj;
	this->adj.assign(q, vector<int>(q));

	graph.maxSize = q;
	graph.insert_vertex(q);
	for (int i = 0; i < vertexList.size(); i++) {
		if (i == vertexList.size() - 1) {
			for (int z = 1; z < q; z++) {
				cout << "Расстояние между вершиной " << z << " и вершиной " << q << " :";
				cin >> weight;
				this->adj[q - 1][z - 1] = weight;
				this->adj[z - 1][q - 1] = weight;
			}

		}
		else {
			for (int j = 0; j < vertexList.size() - 1; j++) {
				this->adj[i][j] = adj_origin[i][j];
			}
		}

	}

	cout << endl;
	display();

}

void Graph::print() {
	if (!this->isEmpty()) {
		cout << "Матрица смежности: " << endl;
		cout << " -";
		for (int i = 0; i < vertexList.size(); i++) {
			cout << setw(4) << i + 1;
		}
		cout << endl;
		for (int i = 0; i < this->vertexList.size(); ++i) {
			cout << i + 1 << " ";
			for (int j = 0; j < this->vertexList.size(); ++j) {
				cout << setw(4) << this->adj[i][j];
			}
			cout << endl;
		}
	}
	else {
		cout << "Граф пуст." << endl;
	}
}

int Graph::Komi() {
	// Метод ветвей и границ
	vector<vector<int>> adj_Komi(vertexList.size(), vector<int>(vertexList.size()));
	for (int i = 0; i < this->vertexList.size(); i++) {
		for (int j = 0; j < this->vertexList.size(); j++) {
			if (i == j) {
				adj_Komi[i][j] = 1000; // нельзя попасть из города в N в город N
			}
			else {
				adj_Komi[i][j] = this->adj[i][j];
			}
		}
	}
	vector<vector<int>> adj_Komi_origin = adj_Komi; // делаем копию матрицы
	// 1. Поиск минимального элемента по строкам
	int* di = new int[vertexList.size()];
	int min;
	for (int i = 0; i < vertexList.size(); i++) {
		min = 10000;
		for (int j = 0; j < vertexList.size(); j++) {
			if (adj_Komi[i][j] < min) {
				min = adj_Komi[i][j];
			}
		}
		di[i] = min;
	}
	// 2. Редукция строк
	for (int i = 0; i < this->vertexList.size(); i++) {
		for (int j = 0; j < this->vertexList.size(); j++) {
			adj_Komi[i][j] -= di[i];
		}
	}
	cout << "Минимум по строкам:" << endl;
	cout << "- ";
	for (int i = 0; i < vertexList.size(); i++) {
		cout << setw(4) << i + 1;
	}
	cout << endl;
	for (int i = 0; i < vertexList.size(); i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < vertexList.size(); j++) {
			cout << setw(4) << adj_Komi[i][j];
		}
		cout << endl;
	}
	cout << endl;
	// 3. Поиск минимального элемента по столбцам
	int* dj = new int[vertexList.size()];
	for (int i = 0; i < vertexList.size(); i++) {
		int min = 10000;
		for (int j = 0; j < vertexList.size(); j++) {
			if (adj_Komi[j][i] < min) {
				min = adj_Komi[j][i];
			}
		}
		dj[i] = min;
	}
	// 4. Редукция столбцов
	for (int i = 0; i < this->vertexList.size(); i++) {
		for (int j = 0; j < this->vertexList.size(); j++) {
			adj_Komi[j][i] -= dj[i];
		}
	}

	cout << "Минимум по столбцам:" << endl;
	cout << "- ";
	for (int i = 0; i < vertexList.size(); i++) {
		cout << setw(4) << i + 1;
	}
	cout << endl;
	for (int i = 0; i < vertexList.size(); i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < vertexList.size(); j++) {
			cout << setw(4) << adj_Komi[i][j];
		}
		cout << endl;
	}
	cout << endl;

	delete[] di;
	delete[] dj;

	//5. Оценка нулевых элементов
	vector<vector<int>> temp_vector = adj_Komi;
	int* di_ = new int[vertexList.size()];

	for (int i = 0; i < vertexList.size(); i++) {
		int count = 0;
		int min_notNull_i = 10000;
		for (int j = 0; j < vertexList.size(); j++) {
			if (temp_vector[i][j] == 0) {
				count++;
			}
		}
		for (int j = 0; j < vertexList.size(); j++) {
			if (count < 2) {
				if (temp_vector[i][j] != 0 && temp_vector[i][j] < min_notNull_i) {
					min_notNull_i = temp_vector[i][j];
				}
			}
			else
				min_notNull_i = 0;

		}
		di_[i] = min_notNull_i;
	}


	int* dj_ = new int[vertexList.size()];

	for (int i = 0; i < vertexList.size(); i++) {
		int count = 0;
		int min_notNull_j = 10000;
		for (int j = 0; j < vertexList.size(); j++) {
			if (temp_vector[j][i] == 0) {
				count++;
			}
		}
		for (int j = 0; j < vertexList.size(); j++) {
			if (count < 2) {
				if (temp_vector[j][i] != 0 && temp_vector[j][i] < min_notNull_j) {
					min_notNull_j = temp_vector[j][i];
				}
			}
			else
				min_notNull_j = 0;

		}
		dj_[i] = min_notNull_j;
	}

	//сумма минимумов по строке и столбцу вместо нулей
	for (int i = 0; i < vertexList.size(); i++) {
		for (int j = 0; j < vertexList.size(); j++) {
			if (temp_vector[i][j] == 0) {
				temp_vector[i][j] = di_[i] + dj_[j];
			}
		}
	}
	cout << "После оценки нулевых значений" << endl;
	cout << "- ";
	for (int i = 0; i < vertexList.size(); i++) {
		cout << setw(4) << i + 1;
	}
	cout << endl;
	for (int i = 0; i < vertexList.size(); i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < vertexList.size(); j++) {
			cout << setw(4) << temp_vector[i][j];
		}
		cout << endl;
	}
	cout << endl;
	delete[] di_;
	delete[] dj_;


	//6. Находим максимальный элемент из нулевых клеток
	vector<vector<int>> result(vertexList.size(), vector<int>(vertexList.size()));
	for (int i = 0; i < vertexList.size(); i++) {
		for (int j = 0; j < vertexList.size(); j++) {
			result[i][j] = 0;
		}
	}
	int way_count = 0;
	int way_i = -1;
	int way_j = -1;
	int i_n = -1;
	int j_n = -1;
	while (way_count < vertexList.size()) {
		int max_null = 0;
		for (int i = 0; i < vertexList.size(); i++) {
			if (i != way_i) {
				for (int j = 0; j < vertexList.size(); j++) {
					if (j != way_j) {
						if (temp_vector[i][j] < 700 && adj_Komi[i][j] == 0) {
							if (temp_vector[i][j] > max_null) {
								max_null = temp_vector[i][j];
								i_n = i;
								j_n = j;
							}
						}
					}
				}
			}
		}


		for (int i = 0; i < vertexList.size(); i++) {
			if (i != way_i) {
				for (int j = 0; j < vertexList.size(); j++) {
					if (j != way_j) {
						if (temp_vector[i][j] == max_null && adj_Komi[i][j] == 0) {
							result[i][j] = max_null;
							temp_vector[j][i] = 1000;
							way_i = i;
							way_j = j;
							way_count++;
						}

					}
				}
			}
		}


	}

	cout << "Итоговая матрица" << endl;
	cout << "- ";
	for (int i = 0; i < vertexList.size(); i++) {
		cout << setw(4) << i + 1;
	}
	cout << endl;
	for (int i = 0; i < vertexList.size(); i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < vertexList.size(); j++) {
			cout << setw(4) << result[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Минимальный путь с посещением всех вершин" << endl;
	int summ = 0;
	int i_count = 0;
	vector<int> min_way;
	for (int i = 0; i < vertexList.size(); i++) {
		for (int j = 0; j < vertexList.size(); j++) {
			if (result[i][j]) {
				cout << i + 1 << "->" << j + 1 << "->";
				min_way.push_back(i);
				i_count++;
				min_way.push_back(j);
				i_count++;
			}
		}
	}
	int first = min_way[0];
	min_way.push_back(first);
	cout << first + 1 << " = ";
	for (int i = 0; i < i_count; i++) {
		summ += adj_Komi_origin[min_way[i]][min_way[i + 1]];

	}
	cout << summ << endl;
	return 0;
}


void drawButton1() {
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex2i(0, H);
	glVertex2i(0, 7 * H / 8);
	glVertex2i(W / 8, 7 * H / 8);
	glVertex2i(W / 8, H);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(0, H);
	glVertex2i(0, 7 * H / 8);
	glVertex2i(W / 8, 7 * H / 8);
	glVertex2i(W / 8, H);
	glEnd();
	string b1 = "Udali";

	glRasterPos2i(4, H - 12);
	for (int i = 0; i < b1.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, b1[i]);
	}
}


void drawButton2() {
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex2i(0, 6 * H / 8);
	glVertex2i(0, 5 * H / 8);
	glVertex2i(W / 8, 5 * H / 8);
	glVertex2i(W / 8, 6 * H / 8);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(0, 6 * H / 8);
	glVertex2i(0, 5 * H / 8);
	glVertex2i(W / 8, 5 * H / 8);
	glVertex2i(W / 8, 6 * H / 8);
	glEnd();

	string b2 = "Dobav";
	glRasterPos2i(0, H - 256);
	for (int i = 0; i < b2.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, b2[i]);
	}
}


void drawCircle(int x, int y, int r) {
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		double t = (i * 3.1415926f / float(180));
		glVertex2f(r * cos(t) + x, r * sin(t) + y);
	}
	glEnd();

	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 360; i++) {
		float t = (i * 3.1415926f / float(180));
		glVertex2f(r * cos(t) + x, r * sin(t) + y);
	}
	glEnd();

}

void drawWeight(int x, int y, int i) {
	GLvoid* f = GLUT_BITMAP_HELVETICA_12;
	string s = to_string(i);
	glRasterPos2i(x - 4, y - 4);
	for (int j = 0; j < s.length(); j++) {
		glutBitmapCharacter(f, s[j]);
	}
}

void drawVertex(int n) {
	for (int i = 0; i < n; i++) {
		drawCircle(P[i].x, P[i].y, r);
		drawWeight(P[i].x, P[i].y, i + 1);
	}
}
void drawLine(int x1, int y1, int x2, int y2, int w) {
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	drawWeight((x1 + x2) / 2 + 10, (y1 + y2) / 2 + 10, w);
}


void setCoords(int i, int n) {
	int x0 = W / 2;
	int y0 = H / 2;
	int r0;
	if (W > H) {
		r = 5 * (H / 16) / n;
		r0 = H / 2 - r - 10;
	}
	else {
		r = 5 * (W / 16) / n;
		r0 = W / 2 - r - 10;
	}
	double t = (i * 3.141592 / n) * 2.0f;
	P[i].x = r0 * cos(t) + x0;
	P[i].y = r0 * sin(t) + y0;
}

void Graph::drawGraph() {
	int n = graph.get_vertex_size();
	for (int i = 0; i < n; i++) {
		setCoords(i, n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int w = graph.get_adj(i, j);
			if (w != 0) {
				drawLine(P[i].x, P[i].y, P[j].x, P[j].y, w);
			}
		}

	}
	drawVertex(n);
}


void mouseClick(int but, int state, int x, int y) {
	if (x <= (W / 8) && y <= (H / 8)) {
		if (but == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			int q;
			cout << endl;
			cout << "Введите номер вершины для удаления: ";
			cin >> q;
			graph.removeVertex(q);
			graph.print();

		}
	}
	if (x <= (W / 8) && y >= (H / 8) && y <= (3 * H / 8)) {
		if (but == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			int q;
			cout << endl;
			cout << "Добавление вершины: " << endl;
			graph.addVertex();

		}
	}
}


void Graph::set_Graph() {
	int topverts;
	cout << "Введите кол-во вершин: ";
	cin >> topverts;
	graph.maxSize = topverts;
	graph.adj = vector<vector<int>>(topverts, vector<int>(topverts));


	for (int i = 1; i <= topverts; i++) {
		graph.insert_vertex(i);
	}
	for (int i = 1; i <= topverts; i++) {
		for (int j = i + 1; j <= topverts; j++) {
			cout << "Вес между ребром " << i << " и ребром " << j << ": ";
			cin >> weight;
			graph.insertedge(i, j, weight);


		}
	}
	cout << endl;
	graph.print();

}
void reshape(int w, int h) {
	W = w;
	H = h;
	glViewport(0, 0, (GLsizei)W, (GLsizei)H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)W, 0, (GLdouble)H);
	glutPostRedisplay();
}

void display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, W, 0, H);
	glViewport(0, 0, W, H);
	glClearColor(0, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawButton1();
	drawButton2();
	graph.drawGraph();
	glutSwapBuffers();
}
