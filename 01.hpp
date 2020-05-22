// Digraph.hpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph. The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <iostream>

// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> vmap;

    void checkVertexExistence(int vertex) const;
    void dft(std::vector<int>& vertex_list, const std::pair<int, DigraphVertex<VertexInfo, EdgeInfo>>& vertex) const;


};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
    : vmap{std::map<int, DigraphVertex<VertexInfo, EdgeInfo>>()}
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
    : vmap{d.vmap}
{
}

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
    : vmap{std::map<int, DigraphVertex<VertexInfo, EdgeInfo>>()}
{
    std::swap(vmap, d.vmap);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    if (this != &d)
    {
        vmap = d.vmap;
    }

    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    if (this != &d)
    {
        std::swap(vmap, d.vmap);
    }

    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> v_list;
    for (auto const& i : vmap)
    {
        v_list.push_back(i.first);
    }
    return v_list;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> e_list;
    for (auto const& i : vmap)
    {
        for (auto const& x : i.second.edges)
        {
            if (std::find(e_list.begin(), e_list.end(), std::pair<int, int>{x.fromVertex, x.toVertex}) == e_list.end())
            {
                e_list.push_back(std::pair<int, int>{x.fromVertex, x.toVertex});
            }
        }
    } 
    return e_list;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    checkVertexExistence(vertex);
    std::vector<std::pair<int, int>> e_list;
    for (auto const& i : vmap.find(vertex)->second.edges)
    {
        e_list.push_back(std::pair<int, int>{i.fromVertex, i.toVertex});
    }
    return e_list;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    checkVertexExistence(vertex);
    return vmap.find(vertex)->second.vinfo;
}

template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    checkVertexExistence(fromVertex);
    checkVertexExistence(toVertex);
    for (auto const& i : vmap)
    {
        for (auto const& x : i.second.edges)
        {
            if (x.fromVertex == fromVertex && x.toVertex == toVertex)
            {
                return x.einfo;
            }
        }
    }
    throw DigraphException("Edge does not exist");
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    if (vmap.find(vertex) != vmap.end())
    {
        throw DigraphException("Vertex number already exists");
    }
    vmap[vertex] = DigraphVertex<VertexInfo, EdgeInfo>{vinfo, std::list<DigraphEdge<EdgeInfo>>()};
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    checkVertexExistence(fromVertex);
    checkVertexExistence(toVertex);
    for (auto const& i : vmap[fromVertex].edges)
    {
        if (i.fromVertex == fromVertex && i.toVertex == toVertex)
        {
            throw DigraphException("Edge already exists");
        }
    }
    vmap[fromVertex].edges.push_back(DigraphEdge<EdgeInfo>{fromVertex, toVertex, einfo});
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    checkVertexExistence(vertex);
    vmap.erase(vertex);

    for (auto &i : vmap)
    {
        i.second.edges.remove_if([&vertex](DigraphEdge<EdgeInfo> ed){return ed.fromVertex == vertex || ed.toVertex == vertex;});
    }
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    checkVertexExistence(fromVertex);
    checkVertexExistence(toVertex);

    int original_size = edges().size();

    for (auto &i : vmap)
    {
        i.second.edges.remove_if([&fromVertex, &toVertex](DigraphEdge<EdgeInfo> ed){return ed.fromVertex == fromVertex && ed.toVertex == toVertex;});
    }
    if (original_size == edges().size())
    {
        throw DigraphException("Edge does not exist");
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return vertices().size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    return edges().size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    return edges(vertex).size();
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    for (const auto &v : vmap)
    {
        std::vector<int> vertex_list;

        dft(vertex_list, v);
        if (vertex_list.size() != vertices().size())
        {
            return false;
        }
    }
    return true;
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::dft(std::vector<int>& vertex_list, const std::pair<int, DigraphVertex<VertexInfo, EdgeInfo>>& vertex) const
{
    vertex_list.push_back(vertex.first);

    for (const auto &e : vertex.second.edges)
    {
        if (std::find(vertex_list.begin(), vertex_list.end(), e.toVertex) == vertex_list.end())
        {
            dft(vertex_list, *vmap.find(e.toVertex));
        }
    }
}

template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{

    std::vector<int> vertex_list;
    std::map<int, int> vertex_d;
    std::map<int, int> vertex_p;

    for (auto &v : vmap)
    {
        if (v.first == startVertex)
        {
            vertex_d[v.first] = 0;
            vertex_p[v.first] = v.first;
        }
        else
        {
            vertex_d[v.first] = INT_MAX;
        }
    }

    std::priority_queue<int> pq;
    pq.push(startVertex);

    while (!pq.empty())
    {
        int min_priority_vertex = pq.top();
        pq.pop();

        if (std::find(vertex_list.begin(), vertex_list.end(), min_priority_vertex) == vertex_list.end())
        {
            vertex_list.push_back(min_priority_vertex);

            for (auto &v : vmap.find(min_priority_vertex)->second.edges)
            {
                if (vertex_d[v.toVertex] > vertex_d[v.fromVertex] + edgeWeightFunc(v.einfo))
                {
                    vertex_d[v.toVertex] = vertex_d[v.fromVertex] + edgeWeightFunc(v.einfo);
                    vertex_p[v.toVertex] = min_priority_vertex;
                    pq.push(v.toVertex);
                }
            }
        }
    }

    return vertex_p;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::checkVertexExistence(int vertex) const
{
    if (vmap.find(vertex) == vmap.end())
    {
        throw DigraphException("Vertex " + std::to_string(vertex) + " does not exist");
    }
}

    
#endif // DIGRAPH_HPP

