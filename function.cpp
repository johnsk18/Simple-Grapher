#include <iostream>
#include <sstream>
#include "function.h"
#include "graph.h"

std::string Function::getFunc() {
	std::ostringstream tmp;
	if (a > 1) tmp << a << "x^3";
	else if (a == 1) tmp << "x^3";
	if (b == 1) {
		if (a == 0) tmp << "x^2";
		else if (b > 0) tmp << " + " << "x^2";
		else tmp << " - " <<  "x^2";
	} else if (b != 0) {
		if (a != 0) {
			if (b > 0) tmp << " + " << b << "x^2";
			else tmp << " - " << -b << "x^2";
		} else { tmp << b << "x^2"; }
	}
	if (c == 1) {
		if (b == 0 && a == 0) tmp << "x";
		else if (b > 0) tmp << " + " << "x";
		else tmp << " - " <<  "x";
	} else if (c != 0) {
		if (b != 0) {
			if (c > 0) tmp << " + " << c << "x";
			else tmp << " - " << -c << "x";
		} else { tmp << c << "x"; }
	}
	if (d == 1) {
		if (c == 0 && b == 0 && a == 0) tmp << d;
		else if (d > 0) tmp << " + "<< d;
		else tmp << " - " << d;
	} else if (d != 0) {
		if (c != 0) {
			if (d > 0) tmp << " + " << d;
			else tmp << " - " << -d;
		} else { tmp << d; }
	} else {
		if (c == 0 && b == 0 && a == 0) tmp << d;
	}
	return tmp.str();
}

void Function::plot(int graph_size) {
	Graph g(graph_size);
	std::cout << "Graph of f(x) = " << getFunc() << std::endl;
	g.plot(*this);
	g.print();
}

std::string Function::getIntegral() {
	std::ostringstream tmp;
	if (a/4.0 == 1) tmp << "x^4";
	else if (a/4.0 > 0) tmp << a/4.0 << "x^4";
	if (b/3.0 == 1) {
		if (a/4.0 == 0) tmp << "x^3";
		else if (b/3.0 > 0) tmp << " + " << "x^3";
		else tmp << " - " <<  "x^3";
	} else if (b/3.0 != 0) {
		if (a/4.0 != 0) {
			if (b/3.0 > 0) tmp << " + " << b/3.0 << "x^3";
			else tmp << " - " << -b/3.0 << "x^3";
		} else { tmp << b/3.0 << "x^3"; }
	}
	if (c/2.0 == 1) {
		if (b/3.0 == 0 && a == 0) tmp << "x^2";
		else if (b/3.0 > 0) tmp << " + " << "x^2";
		else tmp << " - " <<  "x^2";
	} else if (c != 0) {
		if (b/3.0 != 0) {
			if (c/2.0 > 0) tmp << " + " << c/2.0 << "x^2";
			else tmp << " - " << -c/2.0 << "x^2";
		} else { tmp << c/2.0 << "x^2"; }
	}
	if (d == 1) {
		if (c/2.0 == 0 && b/3.0 == 0 && a/4.0 == 0) tmp << "x";
		else if (d > 0) tmp << " + " << "x";
		else tmp << " - " << "x";
	} else if (d != 0) {
		if (c/2.0 != 0) {
			if (d > 0) tmp << " + " << d << "x";
			else tmp << " - " << -d << "x";
		} else { tmp << d << "x"; }
	} else {
		if (c/2.0 == 0 && b/3.0 == 0 && a/4.0 == 0) tmp << d << "x";
	}
	tmp << " + C";
	return tmp.str();
}