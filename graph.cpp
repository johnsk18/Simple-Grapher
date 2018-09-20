#include <iostream>
#include "function.h"
#include "graph.h"

void Graph::create () {
	graph = new char*[height()];
	for (int i = 0; i < height(); ++i) { 
		graph[i] = new char[width()];
		for (int j = 0; j < width(); ++j) graph[i][j] = ' ';
	}
	for (int i = 0; i < width(); ++i) { (graph[y_scale_pos][i]) = '-'; }
	for (int i = 0; i < height(); ++i) { graph[i][x_scale_neg] = '|'; }
	graph[y_scale_pos][x_scale_neg] = '+';
}

void Graph::clear() {
	clearGraph();
	for (int i = 0; i < height(); ++i) { delete [] graph[i]; }
	delete [] graph;
}

void Graph::print() {
	std::cout << std::endl;
	for (int i = 0; i < height(); ++i) {
		for (int j = 0; j < width(); ++j) {
			if (j == width() - 1) {
				std::cout << graph[i][j];
			} else if (i == y_scale_pos) {
				std::cout << graph[i][j] << '-';
			} else {
				std::cout << graph[i][j] << ' ';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Graph::points() {
	if (!pt_chain) return;
	Point* tmp = pt_chain;
	std::cout << "Points on Graph:";
	while (tmp) {
		std::cout << " (" << tmp->x << "," << tmp->y << ")";
		tmp = tmp->next;
	}
	std::cout << std::endl;
}

void Graph::addPoint_(int x, int y) {
	if ((*this)[y][x] == '.') {
		return;
	}
	(*this)[y][x] = '.';
	if (!pt_chain) {
		pt_chain = new Point(x,y);
		return;
	}
	Point* tmp = pt_chain, *tmp2 = NULL;
	while (pt_chain) {
		tmp2 = pt_chain;
		pt_chain = pt_chain->next;
	}
	tmp2->next = new Point(x,y);
	tmp2->next->prev = tmp2;
	if (tmp) pt_chain = tmp;
}

void Graph::addPoint(int x, int y) {
	if ((*this)[y][x] == '.') {
		std::cout << "(" << x << "," << y << ") is already on the graph." << std::endl;
		return;
	}
	(*this)[y][x] = '.';
	std::cout << "(" << x << "," << y << ") plotted." << std::endl;
	if (!pt_chain) {
		pt_chain = new Point(x,y);
		return;
	}
	Point* tmp = pt_chain, *tmp2 = NULL;
	while (pt_chain) {
		tmp2 = pt_chain;
		pt_chain = pt_chain->next;
	}
	tmp2->next = new Point(x,y);
	tmp2->next->prev = tmp2;
	if (tmp) pt_chain = tmp;
}

void Graph::clearPoint_(int x, int y) {
	Point* tmp = findPoint(x,y);
	if (tmp) {
		if (!tmp->prev) {
			pt_chain = pt_chain->next;
			if (pt_chain) pt_chain->prev = NULL;
			delete tmp;
		} else if (!tmp->next) {
			tmp->prev->next = NULL;
			delete tmp;
		} else {
			if (tmp->next) tmp->prev->next = tmp->next;
			if (tmp->prev) tmp->next->prev = tmp->prev;
			delete tmp;
		}
	}
	if (x == 0 && y == 0) (*this)[0][0] = '+';
	else if (x == 0) (*this)[y][x] = '|';
	else if (y == 0) (*this)[y][x] = '-';
	else (*this)[y][x] = ' ';
}

void Graph::clearPoint(int x, int y) {
	clearPoint_(x,y);
	std::cout << "(" << x << "," << y << ") cleared." << std::endl; 
}

Point* Graph::findPoint(int x, int y) {
	Point* tmp = pt_chain;
	while (tmp) {
		if (x == tmp->x && y == tmp->y) break;
		tmp = tmp->next;
	}
	return tmp;
}

void Graph::plot(Function f) {
	int x = 0;
	while (f.plug(x-1) <= y_scale_pos && f.plug(x-1) >= -y_scale_neg && x-1 >= -x_scale_neg) --x;
	while (f.plug(x) <= y_scale_pos && f.plug(x) >= -y_scale_neg && x <= x_scale_pos) {
		addPoint_(x,f.plug(x));
		++x;
	}
}