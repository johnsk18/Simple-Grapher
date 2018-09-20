#ifndef _function_h_
#define _function_h_
#include <iostream>

class Function { // polynomials up to the third degree
	public:
		Function() : a(0), b(0), c(0), d(0) {}
		Function(int d) : a(0), b(0), c(0), d(d) {}
		Function(int c, int d) : a(0), b(0), c(c), d(d) {}
		Function(int b, int c, int d) : a(0), b(b), c(c), d(d) {}
		Function(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}
		friend class Graph;
		std::string getFunc();
		Function ddx() { return Function(0, a*3, b*2, c); }
		std::string getIntegral();
		void plot(int graph_size);
		int plug(int x) { return a*x*x*x + b*x*x + c*x + d; }
		void print() { std::cout << "Function: " << getFunc() << std::endl; }
		void print_integral() { std::cout << "Integrated Function: " << getIntegral() << std::endl; }
	private:
		int a;
		int b;
		int c;
		int d;
};

#endif