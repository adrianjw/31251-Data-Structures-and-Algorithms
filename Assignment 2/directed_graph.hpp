#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <unordered_set>
#include <unordered_map>

template <typename vertex>
class directed_graph {

private:

    std::unordered_set<vertex> vertices;
    std::unordered_map<vertex, std::unordered_set<vertex>> edges;

public:
	
    typedef typename std::unordered_set<vertex>::iterator vertex_iterator;
    typedef typename std::unordered_set<vertex>::iterator neighbour_iterator;
    typedef typename std::unordered_set<vertex>::const_iterator const_vertex_iterator;
    typedef typename std::unordered_set<vertex>::const_iterator const_neighbour_iterator;

    directed_graph() {}

    directed_graph(const directed_graph<vertex>& other) {
        vertices = other.vertices;
        edges = other.edges;
    }

    ~directed_graph() {}

    bool contains(const vertex& u) const { return vertices.count(u) > 0; }

    bool adjacent(const vertex& u, const vertex& v) const {
        if (contains(u)) {
            return edges.at(u).count(v) > 0;
        }
        return false;
    }

    void add_vertex(const vertex& u) {
        if (!contains(u)) {
            vertices.insert(u);
            edges[u] = std::unordered_set<vertex>();
        }
    }

    void add_edge(const vertex& u, const vertex& v) {
        if (contains(u) && contains(v) && u != v) {
            edges[u].insert(v);
        }
    }

    void remove_vertex(const vertex& u) {
        vertices.erase(u);
        edges.erase(u);
    }

    void remove_edge(const vertex& u, const vertex& v) {
        if (contains(u)) {
            edges[u].erase(v);
        }
    }

    std::size_t in_degree(const vertex& u) const {
        auto count = 0;
        for (auto v : vertices) {
            if (u != v) {
                count += edges.at(v).count(u);
            }
        }
        return count;
    }

    std::size_t out_degree(const vertex& u) const {
        return contains(u) ? edges.at(u).size() : 0;
    }

    std::size_t degree(const vertex& u) const {
        return in_degree(u) + out_degree(u);
    }

    std::size_t num_vertices() const {
        return vertices.size();
    }

    std::size_t num_edges() const {
        auto count = 0;
        for (auto entry : edges) {
            count += entry.second.size();
        }
        return count;
    }

    vertex_iterator begin() {
        return vertices.begin();
    }

    vertex_iterator end() {
        return vertices.end();
    }

    const_vertex_iterator begin() const {
        return vertices.cbegin();
    }

    const_vertex_iterator end() const {
        return vertices.cend();
    }

    neighbour_iterator nbegin(const vertex& u) {
        return edges.at(u).begin();
    }

    neighbour_iterator nend(const vertex& u) {
        return edges.at(u).end();
    }

    const_neighbour_iterator nbegin(const vertex& u) const {
        return edges.at(u).cbegin();
    }

    const_neighbour_iterator nend(const vertex& u) const {
        return edges.at(u).cend();
    }
};

#endif