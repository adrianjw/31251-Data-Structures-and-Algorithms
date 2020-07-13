#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

//A large selection of data structures from the standard
//library. You need not feel compelled to use them all,
//but as you can't add any, they're all here just in case.
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <cstddef>
#include <string>

//Forward declarations for classes below so they can be used below without worrying too much about the ordering.
template <typename vertex> class vertex_iterator;
template <typename vertex> class neighbour_iterator;
template <typename vertex> class directed_graph;

template <typename vertex>
class directed_graph {

private:

	//You will need to add some data members here
	//to actually represent the graph internally,
	//and keep track of whatever you need to.
	std::size_t num_vertex;
	unsigned int num_edge;
	std::vector<vertex> vertex_set;
	std::vector<std::vector<bool> > adj_matrix;

public:

	directed_graph(); //A constructor for directed_graph. The graph should start empty.
	~directed_graph(); //A destructor. Depending on how you do things, this may not be necessary.

	int index_of(const vertex&) const; //Returns the index of the given vertex in the vertex set.

	bool contains(const vertex&) const; //Returns true if the given vertex is in the graph, false otherwise.

	bool adjacent(const vertex&, const vertex&) const; //Returns true if the first vertex is adjacent to the second, false otherwise.

	void add_vertex(const vertex&); //Adds the passed in vertex to the graph (with no edges).
	void add_edge(const vertex&, const vertex&); //Adds an edge from the first vertex to the second.

	void remove_vertex(const vertex&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const vertex&, const vertex&); //Removes the edge between the two vertices, if it exists.

	std::size_t in_degree(const vertex&) const; //Returns number of edges coming in to a vertex.
	std::size_t out_degree(const vertex&) const; //Returns the number of edges leaving a vertex.
	std::size_t degree(const vertex&) const; //Returns the degree of the vertex (both in and out edges).

	std::size_t num_vertices() const; //Returns the total number of vertices in the graph.
	std::size_t num_edges() const; //Returns the total number of edges in the graph.

	std::vector<vertex> get_vertices() const; //Returns a vector containing all the vertices.
	std::vector<vertex> get_neighbours(const vertex&) const; //Returns a vector containing the neighbours of the given vertex.

	vertex_iterator<vertex> begin(); //Returns a graph_iterator pointing to the start of the vertex set.
	vertex_iterator<vertex> end(); //Returns a graph_iterator pointing to one-past-the-end of the vertex set.

	neighbour_iterator<vertex> nbegin(const vertex&); //Returns a neighbour_iterator pointing to the start of the neighbour set for the given vertex.
	neighbour_iterator<vertex> nend(const vertex&); //Returns a neighbour_iterator pointing to one-past-the-end of the neighbour set for the given vertex.

	std::vector<vertex> depth_first(const vertex&) const; //Returns the vertices of the graph in the order they are visited in by a
														  //depth-first traversal starting at the given vertex.
	std::vector<vertex> breadth_first(const vertex&) const; //Returns the vertices of the graph in the order they are visisted in by a
															//breadth-first traversal starting at the given vertex.

	directed_graph<vertex> out_tree(const vertex&); //Returns a spanning tree of the graph starting at the given vertex using the out-edges.
	directed_graph<vertex> in_tree(const vertex&); //Returns a spanning tree of the graph starting at the given vertex using the in-edges.

	bool reachable(const vertex&, const vertex&) const; //Returns true if the second vertex is reachable from the first (can you follow
														//a path of out-edges to get from the first to the second?). Returns false otherwise.

	void print_adj_matrix() const; //Prints the adjacency matrix to console.

};

//The vertex_iterator class provides an iterator
//over the vertices of the graph.
//This is one of the harder parts, so if you're
//not too comfortable with C++ leave this for last.
//If you are, there are many ways of doing this,
//as long as it passes the tests, it's okay.
//You may want to watch the videos on iterators before starting.
template <typename vertex>
class vertex_iterator {

private:

	//You may need data members here.
	vertex itr;
	directed_graph<vertex> graph;
	unsigned int position;

public:

	vertex_iterator(const vertex_iterator<vertex>&);
	vertex_iterator(const directed_graph<vertex>&, std::size_t);
	~vertex_iterator();
	vertex_iterator<vertex> operator=(const vertex_iterator<vertex>&);
	bool operator==(const vertex_iterator<vertex>&) const;
	bool operator!=(const vertex_iterator<vertex>&) const;
	vertex_iterator<vertex> operator++();
	vertex_iterator<vertex> operator++(int);
	vertex operator*();
	vertex* operator->();
};

//The neighbour_iterator class provides an iterator
//over the neighbours of a given vertex. This is
//probably harder (conceptually) than the graph_iterator.
//Unless you know how iterators work.
template <typename vertex>
class neighbour_iterator {

private:

	//You may need data members here.
	vertex itr;
	vertex v;
	directed_graph<vertex> graph;
	unsigned int position;

public:

	neighbour_iterator(const neighbour_iterator<vertex>&);
	neighbour_iterator(const directed_graph<vertex>&, const vertex&, std::size_t);
	~neighbour_iterator();
	neighbour_iterator<vertex> operator=(const neighbour_iterator<vertex>&);
	bool operator==(const neighbour_iterator<vertex>&) const;
	bool operator!=(const neighbour_iterator<vertex>&) const;
	neighbour_iterator<vertex> operator++();
	neighbour_iterator<vertex> operator++(int);
	vertex operator*();
	vertex* operator->();
};


//Define all your methods down here (or move them up into the header, but be careful you don't double up).
//If you want to move this into another file, you can, but you should #include the file here.
//Although these are just the same names copied from above, you may find a few more clues in the full
//method headers. Note also that C++ is sensitive to the order you declare and define things in - you
//have to have it available before you use it.

//Constructor
template <typename vertex> directed_graph<vertex>::directed_graph() {
	num_vertex = 0;
	num_edge = 0;
}

//Destructor
template <typename vertex> directed_graph<vertex>::~directed_graph() {}

//Returns the index of the given vertex in the vertex set.
template <typename vertex> int directed_graph<vertex>::index_of(const vertex& u) const {
	for (unsigned int i = 0; i < num_vertex; i++) {
		if (vertex_set[i] == u) {
			return i;
		}
	}
	return -1;
}

//Returns true if the given vertex is in the graph, false otherwise.
template <typename vertex> bool directed_graph<vertex>::contains(const vertex& u) const {
	for (auto i : vertex_set) {
		if (i == u) {
			return true;
		}
	}
	return false;
}

//Returns true if the first vertex is adjacent to the second, false otherwise.
template <typename vertex> bool directed_graph<vertex>::adjacent(const vertex& u, const vertex& v) const {
	if (contains(u) && contains(v)) {
		return adj_matrix[index_of(u)][index_of(v)];
	}
	else {
		return false;
	}
}

//Adds the passed in vertex to the graph (with no edges).
template <typename vertex> void directed_graph<vertex>::add_vertex(const vertex& u) {
	vertex_set.push_back(u);
	num_vertex++;

	adj_matrix.resize(num_vertex);
	for (unsigned int i = 0; i < num_vertex; i++) {
		adj_matrix[i].resize(num_vertex);
	}
}

//Adds an edge from the first vertex to the second.
template <typename vertex> void directed_graph<vertex>::add_edge(const vertex& u, const vertex& v) {
	if ((contains(u)) && (contains(v)) && (u != v)) {
		adj_matrix[index_of(u)][index_of(v)] = true;
		num_edge++;
	}
}

//Removes the given vertex and clears any incident edges.
template <typename vertex> void directed_graph<vertex>::remove_vertex(const vertex& u) {
	if (contains(u)) {
		int n = index_of(u);

		vertex_set.erase(vertex_set.begin() + n);
		num_vertex--;

        for (unsigned int i = 0; i < num_vertex; i++) {
            if (adj_matrix[n][i]) {
                num_edge--;
            }
            if (adj_matrix[i][n]) {
                num_edge--;
            }
        }

		adj_matrix.erase(adj_matrix.begin() + n);
		for (unsigned int i = 0; i < num_vertex; i++) {
			adj_matrix[i].erase(adj_matrix[i].begin() + n);
		}
	}
}

//Removes the edge between the two vertices, if it exists.
template <typename vertex> void directed_graph<vertex>::remove_edge(const vertex & u, const vertex & v) {
	if ((contains(u)) && (contains(v)) && (u != v)) {
		adj_matrix[index_of(u)][index_of(v)] = false;
		num_edge--;
	}
}

//Returns number of edges coming in to a vertex.
template <typename vertex> std::size_t directed_graph<vertex>::in_degree(const vertex & u) const {
	int count = 0;
	if (contains(u)) {
		for (unsigned int i = 0; i < num_vertex; i++) {
			if (adj_matrix[i][index_of(u)]) {
				count++;
			}
		}
	}
	return count;
}

//Returns the number of edges leaving a vertex.
template <typename vertex> std::size_t directed_graph<vertex>::out_degree(const vertex & u) const {
	int count = 0;
	if (contains(u)) {
		for (unsigned int i = 0; i < num_vertex; i++) {
			if (adj_matrix[index_of(u)][i]) {
				count++;
			}
		}
	}
	return count;
}

//Returns the degree of the vertex (both in and out edges).
template <typename vertex> std::size_t directed_graph<vertex>::degree(const vertex & u) const {
	return in_degree(u) + out_degree(u);
}

//Returns the total number of vertices in the graph.
template <typename vertex> std::size_t directed_graph<vertex>::num_vertices() const {
	return num_vertex;
}

//Returns the total number of edges in the graph.
template <typename vertex> std::size_t directed_graph<vertex>::num_edges() const {
	return num_edge;
}

//Returns a vector containing all the vertices.
template <typename vertex> std::vector<vertex> directed_graph<vertex>::get_vertices() const {
	return vertex_set;
}

//Returns a vector containing the neighbours of the given vertex.
template <typename vertex> std::vector<vertex> directed_graph<vertex>::get_neighbours(const vertex & u) const {
	std::vector<vertex> neighbours;
	if (contains(u)) {
		for (unsigned int i = 0; i < num_vertex; i++) {
			if (adj_matrix[index_of(u)][i]) {
				neighbours.push_back(vertex_set[i]);
			}
		}
	}
	return neighbours;
}

//Returns a graph_iterator pointing to the start of the vertex set.
template <typename vertex> vertex_iterator<vertex> directed_graph<vertex>::begin() {
	return vertex_iterator<vertex>(*this, 0);
}

//Returns a graph_iterator pointing to one-past-the-end of the vertex set.
template <typename vertex> vertex_iterator<vertex> directed_graph<vertex>::end() {
	return vertex_iterator<vertex>(*this, num_vertex);
}

//Returns a neighbour_iterator pointing to the start of the neighbour set for the given vertex.
template <typename vertex> neighbour_iterator<vertex> directed_graph<vertex>::nbegin(const vertex & u) {
	return neighbour_iterator<vertex>(*this, u, 0);
}

//Returns a neighbour_iterator pointing to one-past-the-end of the neighbour set for the given vertex.
template <typename vertex> neighbour_iterator<vertex> directed_graph<vertex>::nend(const vertex & u) {
	return neighbour_iterator<vertex>(*this, u, get_neighbours(u).size());
}

//Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
template <typename vertex> std::vector<vertex> directed_graph<vertex>::depth_first(const vertex & u) const {
	std::vector<vertex> ordered;

	if (contains(u)) {
		std::stack<vertex> unordered;
		unordered.push(u);

		std::vector<bool> visited;
		visited.resize(num_vertex);

		while (!unordered.empty()) {
			vertex n = unordered.top();
			unordered.pop();

			if (!visited[index_of(n)]) {
				visited[index_of(n)] = true;
				ordered.push_back(index_of(n));

				for (unsigned int i = num_vertex; i != 0; i--) {
					if (adj_matrix[index_of(n)][i - 1]) {
						unordered.push(i - 1);
					}
				}
			}
		}
	}

	return ordered;
}

//Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.
template <typename vertex> std::vector<vertex> directed_graph<vertex>::breadth_first(const vertex & u) const {
	std::vector<vertex> ordered;

	if (contains(u)) {
		std::queue<vertex> unordered;
		unordered.push(u);

		std::vector<bool> visited;
		visited.resize(num_vertex);

		while (!unordered.empty()) {
			vertex n = unordered.front();
			unordered.pop();

			if (!visited[index_of(n)]) {
				visited[index_of(n)] = true;
				ordered.push_back(index_of(n));

				for (unsigned int i = 0; i < num_vertex; i++) {
					if (adj_matrix[index_of(n)][i]) {
						unordered.push(i);
					}
				}
			}
		}
	}

	return ordered;
}

//Returns a spanning tree of the graph starting at the given vertex using the out-edges.
template <typename vertex> directed_graph<vertex> directed_graph<vertex>::out_tree(const vertex & u) {
	directed_graph<vertex> tree;

	if (contains(u)) {
		std::queue<std::pair<vertex, vertex> > unordered;
		unordered.push({ u,u });

		std::vector<bool> visited;
		visited.resize(num_vertex);

		while (!unordered.empty()) {
			std::pair<vertex, vertex> n = unordered.front();
			unordered.pop();

			if (!visited[index_of(n.second)]) {
				visited[index_of(n.second)] = true;

				if (!tree.contains(n.second)) {
					tree.add_vertex(n.second);
				}

				tree.add_edge(n.first, n.second);

				for (unsigned int i = 0; i < num_vertex; i++) {
					if (adj_matrix[index_of(n.second)][i]) {
						unordered.push({ n.second, vertex_set[i] });
					}
				}
			}
		}
	}

	return tree;
}

//Returns a spanning tree of the graph starting at the given vertex using the in-edges.
template <typename vertex> directed_graph<vertex> directed_graph<vertex>::in_tree(const vertex & u) {
	directed_graph<vertex> tree;

	if (contains(u)) {
		std::queue<std::pair<vertex, vertex> > unordered;
		unordered.push({ u,u });

		std::vector<bool> visited;
		visited.resize(num_vertex);

		while (!unordered.empty()) {
			std::pair<vertex, vertex> n = unordered.front();
			unordered.pop();

			if (!visited[index_of(n.first)]) {
				visited[index_of(n.first)] = true;

				if (!tree.contains(n.first)) {
					tree.add_vertex(n.first);
				}

				tree.add_edge(n.first, n.second);

				for (unsigned int i = 0; i < num_vertex; i++) {
					if (adj_matrix[i][index_of(n.first)]) {
						unordered.push({ vertex_set[i], n.first });
					}
				}
			}
		}
	}

	return tree;
}

//Returns true if the second vertex is reachable from the first, false otherwise.
template <typename vertex> bool directed_graph<vertex>::reachable(const vertex & u, const vertex & v) const {
	for (auto i : breadth_first(u)) {
		if (i == v) {
			return true;
		}
	}
	return false;
}

//Prints the adjacency matrix to console.
template <typename vertex> void directed_graph<vertex>::print_adj_matrix() const {
	for (auto i : adj_matrix) {
		for (auto j : i) {
			std::cout << j << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

//----------------------------------------------------------------------------------------------------------------------------------

//Copy constructor
template <typename vertex> vertex_iterator<vertex>::vertex_iterator(const vertex_iterator<vertex> & other) {
	this->itr = other.itr;
	this->graph = other.graph;
	this->position = other.position;
}

//Constructor
template <typename vertex> vertex_iterator<vertex>::vertex_iterator(const directed_graph<vertex> & graph, std::size_t position) {
	this->graph = graph;
	this->position = position;
	if (position < graph.num_vertices()) {
		this->itr = graph.get_vertices()[position];
	}
	else {
		this->itr = graph.get_vertices().back();
	}
}

//Destructor
template <typename vertex> vertex_iterator<vertex>::~vertex_iterator() {}

//Assign operator
template <typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator=(const vertex_iterator<vertex> & other) {
	this->itr = other.itr;
	this->graph = other.graph;
	this->position = other.position;
	return *this;
}

//Compare operator
template <typename vertex> bool vertex_iterator<vertex>::operator==(const vertex_iterator<vertex> & other) const {
	return position == other.position;
}

//Compare operator
template <typename vertex> bool vertex_iterator<vertex>::operator!=(const vertex_iterator<vertex> & other) const {
	return position != other.position;
}

//Increment operator
template <typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator++() {
	position++;
	if (position < graph.num_vertices()) {
		itr = graph.get_vertices()[position];
	}
	return *this;
}

//Increment operator
template <typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator++(int) {
	vertex_iterator<vertex> temp = *this;
	position++;
	if (position < graph.num_vertices()) {
		itr = graph.get_vertices()[position];
	}
	return temp;
}

//Dereference operator
template <typename vertex> vertex vertex_iterator<vertex>::operator*() {
	return itr;
}

//Arrow operator
template <typename vertex> vertex* vertex_iterator<vertex>::operator->() {
	return &itr;
}

//----------------------------------------------------------------------------------------------------------------------------------

//Copy constructor
template <typename vertex> neighbour_iterator<vertex>::neighbour_iterator(const neighbour_iterator<vertex> & other) {
	this->itr = other.itr;
	this->graph = other.graph;
	this->v = other.v;
	this->position = other.position;
}

//Constructor
template <typename vertex> neighbour_iterator<vertex>::neighbour_iterator(const directed_graph<vertex> & graph,
	                                                                      const vertex & u, std::size_t position) {
	this->graph = graph;
	this->v = u;
	this->position = position;
	if (position < graph.get_neighbours(v).size()) {
		this->itr = graph.get_neighbours(v)[position];
	}
	else {
		this->itr = graph.get_neighbours(v).back();
	}
}

//Destructor
template <typename vertex> neighbour_iterator<vertex>::~neighbour_iterator() {}

//Assign operator
template <typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator=(const neighbour_iterator<vertex> & other) {
	this->itr = other.itr;
	this->graph = other.graph;
	this->v = other.v;
	this->position = other.position;
	return *this;
}

//Compare operator
template <typename vertex> bool neighbour_iterator<vertex>::operator==(const neighbour_iterator<vertex> & other) const {
	return position == other.position;
}

//Compare operator
template <typename vertex> bool neighbour_iterator<vertex>::operator!=(const neighbour_iterator<vertex> & other) const {
	return position != other.position;
}

//Increment operator
template <typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator++() {
	position++;
	if (position < graph.get_neighbours(v).size()) {
		itr = graph.get_neighbours(v)[position];
	}
	return *this;
}

//Increment operator
template <typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator++(int) {
	neighbour_iterator<vertex> temp = *this;
	position++;
	if (position < graph.get_neighbours(v).size()) {
		itr = graph.get_neighbours(v)[position];
	}
	return temp;
}

//Derefernce operator
template <typename vertex> vertex neighbour_iterator<vertex>::operator*() {
	return itr;
}

//Arrow operator
template <typename vertex> vertex* neighbour_iterator<vertex>::operator->() {
	return &itr;
}

#endif