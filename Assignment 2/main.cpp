/*
* A main function for you to build and run your
* own tests with.
* This file is not part of the marking, so you
* can do anything you want here.
*/
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

#include "directed_graph_algorithms.cpp"

int main() {
	
	directed_graph<char> d;
	
	d.add_vertex('A');
	d.add_vertex('B');
	d.add_vertex('C');
	d.add_vertex('D');
	d.add_vertex('E');
	
	d.add_edge('A', 'B');
	d.add_edge('A', 'C');
	d.add_edge('B', 'C');
	d.add_edge('B', 'E');
	d.add_edge('C', 'D');
	d.add_edge('D', 'E');
	
	std::cout << is_hamiltonian_dag(d);
}