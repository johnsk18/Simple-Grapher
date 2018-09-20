#ifndef _graph_h_
#define _graph_h_

class Proxy { // necesary for multidimmensional subcript operator overload for graph class
	public:
		Proxy(char*& x, int x_) : x_axis(x), x_scale_neg(x_) {}
		char& operator[](int x) { return x_axis[x + x_scale_neg]; }
	private:
		char*& x_axis;
		int x_scale_neg;
};

class Point {
	public:
		Point(int x_, int y_) : x(x_), y(y_), prev(NULL), next(NULL) {}
		int x;
		int y;
		Point* prev;
		Point* next;
};

class Graph { // graph board
	public:
		Graph(int s)
		 : x_scale_neg(s), x_scale_pos(s), y_scale_neg(s), y_scale_pos(s), pt_chain(NULL) { create(); }
		Graph(int x_neg, int x_pos, int y_neg, int y_pos)
		 : x_scale_neg(x_neg), x_scale_pos(x_pos), y_scale_neg(y_neg), y_scale_pos(y_pos), 
		 	 pt_chain(NULL) { create(); }
		~Graph() { clear(); }
		int width() { return x_scale_neg + x_scale_pos + 1; }
		int height() { return y_scale_neg + y_scale_pos + 1; }
		int neg_x() const { return -x_scale_neg; }
		int	pos_x() const { return x_scale_pos; }
		int neg_y() const { return -y_scale_neg; }
		int pos_y() const { return y_scale_pos; }
		Proxy operator[](int y) { return Proxy(graph[y_scale_pos - y],x_scale_neg); }
		void addPoint(int x, int y);
		void clearPoint(int x, int y);
		void clearGraph() { while (pt_chain) clearPoint_(pt_chain->x,pt_chain->y); }
		void plot(Function f);
		void points();
		void print();
	private:
		void create();
		void clear();
		void addPoint_(int x, int y);
		void clearPoint_(int x, int y);
		Point* findPoint(int x, int y);
		int x_scale_neg;
		int x_scale_pos;
		int y_scale_neg;
		int y_scale_pos;
		char** graph;
		Point* pt_chain;
};

#endif