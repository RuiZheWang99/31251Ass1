#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <iostream>

#include <bits/stdc++.h> 
using namespace std;

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}


template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};


template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};


template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    
    
    Digraph();

    
    Digraph(const Digraph& d);

   
    Digraph(Digraph&& d) noexcept;

    
    ~Digraph() noexcept;

    
    Digraph& operator=(const Digraph& d);

   
    Digraph& operator=(Digraph&& d) noexcept;

    
    std::vector<int> vertices() const;

    
    std::vector<std::pair<int, int>> edges() const;

    
    std::vector<std::pair<int, int>> edges(int vertex) const;

   
    VertexInfo vertexInfo(int vertex) const;

    
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

   
    void addVertex(int vertex, const VertexInfo& vinfo);

    
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    
    void removeVertex(int vertex);

   
    void removeEdge(int fromVertex, int toVertex);

   
    int vertexCount() const noexcept;

   
    int edgeCount() const noexcept;

    
    int edgeCount(int vertex) const;

    
    bool isStronglyConnected() const;

   
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
  
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> vmap;

    void checkVertexExistence(int vertex) const;
    void dft(std::vector<int>& vertex_list, const std::pair<int, DigraphVertex<VertexInfo, EdgeInfo>>& vertex) const;


};


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

    
#endif
