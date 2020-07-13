#include <iostream>
#include <vector>

#include "directed_graph.hpp"

int main() {
	
	directed_graph<std::string> g;
	
	g.add_vertex("vertex_0");
	g.add_vertex("vertex_1");
	g.add_vertex("vertex_2");
	g.add_vertex("vertex_3");
	g.add_vertex("vertex_4");
	g.add_vertex("vertex_5");
	
	g.add_edge("vertex_0", "vertex_1");
	g.add_edge("vertex_1", "vertex_2");
	g.add_edge("vertex_2", "vertex_3");
	g.add_edge("vertex_3", "vertex_4");
	g.add_edge("vertex_4", "vertex_1");
	g.add_edge("vertex_3", "vertex_5");
	
	std::cout << "Graph Matrix:\n";
	std::cout << "Number of vertices: " << g.num_vertices() << "\n";
	std::cout << "Number of edges: " << g.num_edges() << "\n\n";
	g.print_adj_matrix();
    
	std::cout << "Graph vertices:\n";
	for (vertex_iterator<std::string> v_itr = g.begin(); v_itr != g.end(); ++v_itr) {
		std::cout << *v_itr << "\n";
	}
	
	std::cout << "\n";
	
	std::cout << "Neightbour vertices of vertex_3:" << std::endl;
	for (neighbour_iterator<std::string> n_itr = g.nbegin("vertex_3"); n_itr != g.nend("vertex_3"); ++n_itr) {
		std::cout << *n_itr << "\n";
	}
}