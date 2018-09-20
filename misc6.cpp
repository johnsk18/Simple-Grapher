#include <iostream>
#include <vector>
#include <limits>
#include "function.h"
#include "graph.h"

// Copyright Kaylan Johnson

// Function Prototypes
int main_input();
int graph_input();
int function_input();
int input_checker(int options);
int graph_select(std::vector<Graph*>& g);
int function_select(std::vector<Function*>& f);
Graph* graph_create();
Function* function_create();
bool point_possible(Graph*& g, int x, int y);
void all_graphs(std::vector<Graph*>& g);
void all_functions(std::vector<Function*>& f);

int main() {
	std::vector<Graph*> graphs;
	std::vector<Function*> functions;
	std::cout << "Welcome to this Simple Graphing Program! Coded by Kaylan Johnson." << std::endl;
	int input = 0;
	while (input != 1) {
		input = main_input();
		if (input == 1) { // Terminates Program
			break;
		} else if (input == 2) { // Graph
			while (input != 1) {
				input = graph_input();
				if (input == 1 || input == 6) { // Exits Graph Loop
					break;
				} else if (input == 2) { // Creates Graph
					Graph* g1 = graph_create();
					g1->print();
					graphs.push_back(g1);
				} else if (input == 3) { // Views Graphs
					if (graphs.empty()) std::cout << "\nThere are no graphs to view." << std::endl;
					else all_graphs(graphs);
				} else if (input == 4) { // Removes Graphs
					if (graphs.empty()) std::cout << "\nThere are no graphs to remove." << std::endl;
					else { 
						if (graphs.size() == 1) graphs.clear();
						else graphs.erase(graphs.begin() + graph_select(graphs));
					}
				} else if (input == 5) { // Adds Point
					int x, y;
					while (true) {
						try {
							std::cout << "\nChoose an x value: >> ";
							if (!(std::cin >> x)) throw 0;
							std::cout << "Choose a y value: >> ";
							if (!(std::cin >> y)) throw 0;
							break;
						} catch(...) {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "\nOne or more variables created an error. Try again." << std::endl;
						}
					}
					Graph* g1;
					if (graphs.empty()) {
						std::cout << "\nThere are no graphs to add to." << std::endl;
					} else {
						while (true) {
							if (graphs.size() == 1) g1 = graphs[0];
							else {
								std::cout << "Select a graph to add the point to." << std::endl;
								g1 = graphs[graph_select(graphs)];
							}
							if (point_possible(g1,x,y)) {
								g1->addPoint(x,y);
								g1->print();
								break;
							} else {
								std::cout << "\nPoint is not within bounds of the graph." << std::endl;
								std::cout << "\nType 1 to select a new graph. Type 2 to view options. >> ";
								int input1 = input_checker(2);
								if (input1 == 1) continue;
								else if (input1 == 2) break;
							}
						}
					}
				}
			}
		} else if (input == 3) { // Function
			while (input != 1) {
				input = function_input();
				if (input == 1 || input == 6) { // Exits Function Loop
					break;
				} else if (input == 2) { // Create Function
					Function* f1 = function_create();
					f1->print();
					functions.push_back(f1);
				} else if (input == 3) { // View Functions
					if (functions.empty()) std::cout << "\nThere are no functions to select." << std::endl;
					else all_functions(functions);
				} else if (input == 4) { // Remove Function
					if (functions.empty()) std::cout << "\nThere are no functions to remove." << std::endl;
					else { 
						if (functions.size() == 1) functions.clear();
						else functions.erase(functions.begin() + function_select(functions));
					}
				} else if (input == 5) { // Add Function to Graph
					if (graphs.empty()) {
						std::cout << "\nThere are no graphs to add a function to." << std::endl;
					} else if (functions.empty()) {
						std::cout << "\nThere are no functions to add to a graph." << std::endl;
					} else {
						Graph* g1;
						Function* f1;
						if (graphs.size() == 1) g1 = graphs[0];
						else {
							std::cout << "Select a graph to add the function to." << std::endl;
							g1 = graphs[graph_select(graphs)];
						}
						if (functions.size() == 1) f1 = functions[0];
						else {
							std::cout << "Select a function" << std::endl;
							f1 = functions[function_select(functions)];
						}
						g1->plot(*f1);
						g1->print();
					}
				}
			}
		} else if (input == 4) { // Reset
			graphs.clear();
			functions.clear();
			std::cout << "\nReset Complete.\n" <<std::endl;
		} 
	}
	std::cout << "\nTerminating..." << std::endl;
	for (unsigned i = 0; i < graphs.size(); ++i) delete graphs[i];
	for (unsigned i = 0; i < functions.size(); ++i) delete functions[i];
}

int main_input() {
	std::cout << "\nMain Menu Options" << std::endl;
	std::cout << "1: Terminate Program" << std::endl;
	std::cout << "2: Graph" << std::endl;
	std::cout << "3: Function" << std::endl;
	std::cout << "4: Reset" << std::endl;
	std::cout << "\nType the number to select the option." << std::endl;
	return input_checker(4);
}

int graph_input() {
	std::cout << "\nGraph Menu Options" << std::endl;
	std::cout << "1: Terminate Program" << std::endl;
	std::cout << "2: Create Graph" << std::endl;
	std::cout << "3: View Graphs" << std::endl;
	std::cout << "4: Remove Graph" << std::endl;
	std::cout << "5: Add Point" << std::endl;
	std::cout << "6: Back" << std::endl;
	std::cout << "\nType the number to select the option." << std::endl;
	return input_checker(6);
}

int function_input() {
	std::cout << "\nFunction Menu Options" << std::endl;
	std::cout << "1: Terminate Program" << std::endl;
	std::cout << "2: Create Function" << std::endl;
	std::cout << "3: View Functions" << std::endl;
	std::cout << "4: Remove Function" << std::endl;
	std::cout << "5: Add Function to Graph" << std::endl;
	std::cout << "6: Back" << std::endl;
	std::cout << "\nType the number to select the option." << std::endl;
	return input_checker(6);
}

int input_checker(int options) {
	int input;
	while (!(std::cin >> input) || 1 > input || input > options) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Try typing a number from 1 to " << options << '.' << std::endl;
	}
	return input;
}

int graph_select(std::vector<Graph*>& g) {
	all_graphs(g);
	std::cout << "Type the number of the graph >> ";
	return input_checker(g.size()) - 1;
}

int function_select(std::vector<Function*>& f) {
	all_functions(f);
	std::cout << "Type the number of the function >> ";
	return input_checker(f.size()) - 1;
}

Graph* graph_create() {
	int x_neg, x_pos, y_neg, y_pos;
	while (true) {
		try {
			std::cout << "\nWhat would you like the x minimum to be? >> ";
			if (!(std::cin >> x_neg)) throw 0;
			std::cout << "\nWhat would you like the x maximum to be? >> ";
			if (!(std::cin >> x_pos)) throw 0;
			std::cout << "\nWhat would you like the y minimum to be? >> "; 
			if (!(std::cin >> y_neg)) throw 0;
			std::cout << "\nWhat would you like the y maximum to be? >> ";
			if (!(std::cin >> y_pos)) throw 0;
			return new Graph(-x_neg,x_pos,-y_neg,y_pos);
		} catch (...) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nOne or more variables created an error. Try again." << std::endl;
		}
	}
}

Function* function_create() {
	int a, b, c, d;
	while (true) {
		try {
			std::cout << "\nYou can create polynomial functions of this format: ";
			std::cout << "ax^3 + bx^2 + cx + d\n" << std::endl;
			std::cout << "Choose a: >> ";
			if (!(std::cin >> a)) throw 0;
			std::cout << "Choose b: >> ";
			if (!(std::cin >> b)) throw 0;
			std::cout << "Choose c: >> ";
			if (!(std::cin >> c)) throw 0;
			std::cout << "Choose d: >> ";
			if (!(std::cin >> d)) throw 0;
			return new Function(a,b,c,d);
		} catch (...) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nOne or more variables created an error. Try again." << std::endl;
		}
	}
}

bool point_possible(Graph*& g, int x, int y) {
	if (x >= g->neg_x() && x <= g->pos_x() && y >= g->neg_y() && y <= g->pos_y()) return true;
	return false;
}

void all_graphs(std::vector<Graph*>& g) {
	for (unsigned i = 1; i <= g.size(); ++i) {
		std::cout << "\nThis is Graph " << i << ':' << std::endl;
		g[i-1]->print();
	}
}

void all_functions(std::vector<Function*>& f) {
	for (unsigned i = 1; i <= f.size(); ++i) {
		std::cout << "\nThis is Function " << i << ": " << f[i-1]->getFunc() << std::endl;
	}
}