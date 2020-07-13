/*
 * Notice that the list of included headers has
 * expanded a little. As before, you are not allowed
 * to add to this.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
#include <utility>
#include <algorithm>
#include <limits>
#include <optional>
#include <exception>
#include <stdexcept>

#include "directed_graph.hpp"

/*
 * Returns true if all vertices of the graph have been visited,
 * false otherwise.
 */
template <typename vertex>
bool all_visited(std::unordered_map<vertex, bool> m) {
    
    for (auto itr = m.begin(); itr != m.end(); ++itr) {
        if (!itr->second) {
            return false;
        }
    }
    return true;
    
}

/*
 * Returns the vertices of the graph in the order they are visited in 
 * by a depth-first traversal (DFT) starting at the given vertex.
 */
template <typename vertex>
std::vector<vertex> dft(const directed_graph<vertex> & d, const vertex& u) {
    
    // Create variables.
    std::vector<vertex> ordered;
    std::stack<vertex> unordered;
    std::unordered_map<vertex, bool> visited;
    
    // Initialise variables.
    unordered.push(u);
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        visited.insert({*itr, false});
    }
    
    // Repeats the loop until the stack is empty.
    while (!unordered.empty()) {
        
        // Sets the top element of the stack to current vertex,
        // then removes it from the stack.
        vertex curr = unordered.top();
        unordered.pop();
        
        // Marks the current vertex as visited, and adds it to the vector.
        if (!visited.at(curr)) {
            visited.at(curr) = true;
            ordered.push_back(curr);
            
            // Adds all the neighbours of current vertex to the stack.
            for (auto itr = d.nbegin(curr); itr != d.nend(curr); ++itr) {
                unordered.push(*itr);
            }
        }
    }
    
    return ordered;
    
}

/*
 * Second part of the strongly connected components (SCC) algorithm.
 * Computes the strongly connected components of the graph
 * and adds them to the componenets vector.
 */
template <typename vertex>
void scc(const directed_graph<vertex> & d, const vertex & u, int & count,
         std::vector<std::vector<vertex>> & components, std::stack<vertex> & stack,
         std::unordered_map<vertex, int> & index, std::unordered_map<vertex, int> & low,
         std::unordered_map<vertex, bool> & on_stack, std::unordered_map<vertex, bool> & visited) {
    
    // Updates variables with new values.
    stack.push(u);
    index.at(u) = count;
    low.at(u) = count;
    on_stack.at(u) = true;
    visited.at(u) = true;
    ++count;
    
    // Calls this method recursively for each unvisited neighbour of vertex "u", 
    // and passes the neighbour as the new vertex, along with the updated variables.
    // Backtracks the graph once all neighbours have been visited, compares the
    // low value of vertex "u" and the low value of its neighbour, and sets the
    // smaller of the two as the new low value of the vertex.
    for (auto itr = d.nbegin(u); itr != d.nend(u); ++itr) {
        if (!visited.at(*itr)) {
            scc(d, *itr, count, components, stack, index, low, on_stack, visited);
            low.at(u) = std::min(low.at(u), low.at(*itr));
        }
        else if (on_stack.at(*itr)) {
            low.at(u) = std::min(low.at(u), index.at(*itr));
        }
    }
    
    // Creates a vector and adds all the vertices of a strongly connected compoenent to it,
    // then adds the vector to the vector of vectors.
    if (low.at(u) == index.at(u)) {
        std::vector<vertex> comp;
        vertex curr;
        
        do {
            curr = stack.top();
            stack.pop();
            on_stack.at(curr) = false;
            comp.push_back(curr);
        } while (u != curr);
        
        components.push_back(comp);
    }
    
}

/*
 * Computes a topological ordering of the vertices.
 * For every vertex u in the order, and any of its
 * neighbours v, v appears later in the order than u.
 */
template <typename vertex>
std::list<vertex> topological_sort(const directed_graph<vertex> & d) {
	
    // Create variables.
    auto g = d;
    std::list<vertex> topo_order;
    std::unordered_set<vertex> root;
    
    // Initialise variables.
    for (auto itr = g.begin(); itr != g.end(); ++itr) {
        if (g.in_degree(*itr) == 0) {
            root.insert(*itr);
        }
    }
    
    // Repeats the loop until root set is empty.
    while (!root.empty()) {
        
        // Adds the first element of the root set to the topological list
        // and removes it from set.
        vertex curr = *root.begin();
        root.erase(curr);
        topo_order.push_back(curr);
        
        // Creates a set and adds all the neighbours of current vextex to it.
        std::unordered_set<vertex> neighbours;
        for (auto itr = g.nbegin(curr); itr != g.nend(curr); ++itr) {
             neighbours.insert(*itr);
        }
        
        // Removes edges between the current vertex and its neighbour,
        // then adds the roots to the root set.
        for (auto itr = neighbours.begin(); itr != neighbours.end(); ++itr) {
            g.remove_edge(curr, *itr);
            if (g.in_degree(*itr) == 0) {
                root.insert(*itr);
            }
        }
    }
    
    return topo_order;
    
}

/*
 * Computes whether the input is a Directed Acyclic Graph (DAG).
 * A digraph is a DAG if there is no vertex that has a cycle.
 * A cycle is a non-empty set of [out-]edges that starts at one 
 * vertex, and returns to it.
 */
template <typename vertex>
bool is_dag(const directed_graph<vertex> & d) {
	
    // Returns true if the number of vertices of the graph is equal to the
    // number of vertices of its topological sort, false otherwise.
    return d.num_vertices() == topological_sort(d).size() ? true : false;
    
}

/*
 * Given a DAG, computes whether there is a Hamiltonian path.
 * A Hamiltonian path is a path that visits every vertex
 * exactly once.
 */
template <typename vertex>
bool is_hamiltonian_dag(const directed_graph<vertex> & d) {
	
    // Create and initialise variables.
    auto topo_order = topological_sort(d);
    int count = 1;
    
    // Returns true if there is an edge between each consecutive vertex, false otherwise.
    for (auto itr = topo_order.begin(); itr != topo_order.end() && count < topo_order.size(); ++itr) {
        auto it = itr;
        ++it;
        if (!d.adjacent(*itr, *it)) {
            return false;
        }
        count++;
    }
    return true;
    
}

/*
 * Computes the weakly connected components of the graph.
 * A [weak] component is the smallest subset of the vertices
 * such that the in and out neighbourhood of each vertex in
 * the set is also contained in the set.
 */
template <typename vertex>
std::vector<std::vector<vertex>> components(const directed_graph<vertex> & d) {
	
    // Create variables.
    std::vector<std::vector<vertex>> components;
    std::unordered_map<vertex, bool> visited;
    
    // Initialise variables.
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        visited.insert({*itr, false});
    }
    
    // Runs a traversal from an unvisited root if found,
    // and adds the connected componenet to the vector.
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        if (!visited.at(*itr) && d.in_degree(*itr) == 0) {
            auto comp = dft(d, *itr);
            for (auto itr = comp.begin(); itr != comp.end(); ++itr) {
                visited.at(*itr) = true;
            }
            components.push_back(comp);
        }
    }
    
    // Runs a traversal from an unvisited vertex if found,
    // and adds the connected componenet to the vector.
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        if (!visited.at(*itr)) {
            auto comp = dft(d, *itr);
            for (auto itr = comp.begin(); itr != comp.end(); ++itr) {
                visited.at(*itr) = true;
            }
            components.push_back(comp);
        }
    }
    
    return components;
    
}

/*
 * Computes the strongly connected components of the graph.
 * A strongly connected component is a subset of the vertices
 * such that for every pair u, v of vertices in the subset,
 * v is reachable from u and u is reachable from v.
 */
template <typename vertex>
std::vector<std::vector<vertex>> strongly_connected_components(const directed_graph<vertex> & d) {
	
    // Create variables.
    std::vector<std::vector<vertex>> components;
    std::stack<vertex> stack;
    std::unordered_map<vertex, int> index;
    std::unordered_map<vertex, int> low;
    std::unordered_map<vertex, bool> on_stack;
    std::unordered_map<vertex, bool> visited;
    int count = 0;
    
    // Initialise variables.
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        index.insert({*itr, count});
        low.insert({*itr, count});
        on_stack.insert({*itr, false});
        visited.insert({*itr, false});
    }
    
    // Calls the scc method if an unvisited vertex is found.
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        if (!visited.at(*itr)) {
            scc(d, *itr, count, components, stack, index, low, on_stack, visited);
        }
    }
    
    return components;
    
}

/*
 * Computes the shortest distance from u to every other vertex
 * in the graph d. The shortest distance is the smallest number
 * of edges in any path from u to the other vertex.
 * If there is no path from u to a vertex, set the distance to
 * be the number of vertices in d plus 1.
 */
template <typename vertex>
std::unordered_map<vertex, std::size_t> shortest_distances(const directed_graph<vertex> & d, const vertex & u) {
	
    // Create variables.
    std::unordered_map<vertex, std::size_t> shortest_path;
    std::unordered_map<vertex, bool> visited;
    
    // Initialise variables.
    shortest_path.insert({u,0});
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        shortest_path.insert({*itr, std::numeric_limits<unsigned int>::max() - 1});
        visited.insert({*itr, false});
    }
    
    // Sets vertex "u" as current vertex.
    vertex curr = u;
    
    // Repeats the loop until all vertices have been visited.
    while(!all_visited(visited)) {
    
        // Compares the tentative distance from current vertex to its neighbour
        // with the distance from current vertex to the current vertex plus 1,
        // and sets the new distance to the smaller of the two values.
        for (auto itr = d.nbegin(curr); itr != d.nend(curr); ++itr) {
            unsigned int a = shortest_path.at(*itr), b = shortest_path.at(curr) + 1;
            shortest_path.at(*itr) = std::min(a,b);
        }
        
        // Marks the current vertex as visited.
        visited[curr] = true;
        
        // Selects an unvisited vertex with smallest tentative distance
        // and sets it as the current vertex.
        std::unordered_map<std::size_t, vertex> temp;
        for (auto itr = shortest_path.begin(); itr != shortest_path.end(); ++itr) {
            if (!visited.at(itr->first)) {
                temp.insert({itr->second, itr->first});
            }
        }
        if (!temp.empty()) {
            curr = std::min_element(temp.begin(), temp.end())->second;
        }
    }
    
    // Sets the distances of vertices which cannot be reached from the given vertex
    // to the number of vertices in the graph plus 1.
    for (auto itr = shortest_path.begin(); itr != shortest_path.end(); ++itr) {
        if (itr->second >= std::numeric_limits<unsigned int>::max() - 1) {
            shortest_path.at(itr->first) = d.num_vertices() + 1;
        }
    }
    
	return shortest_path;
    
}