#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  //adj list stores both incoming and outgoing edges
  return adjList.at(v.key()).size();


}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.emplace(std::string(key),v);
  adjList[key] = std::list<edgeListIter>{};
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  if (vertexMap.find(key) == vertexMap.end()) {return;}

  for (std::list<edgeListIter> adjEdges : adjList) {
    if (adjEdges == adjList.at(key)) {continue;}

    for (edgeListIter edgeRef : adjList.at(key)) {
      adjEdges.remove(edgeRef);
    }
  }
  for (edgeListIter edgeRef : adjList.at(key)) {
    edgeList.erase(edgeRef);
  }

  adjList.erase(adjList.find(key));
  vertexMap.erase(vertexMap.find(key));
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  if (vertexMap.find(v1.key()) == vertexMap.end()) {insertVertex(v1.key());}
  if (vertexMap.find(v2.key()) == vertexMap.end()) {insertVertex(v2.key());}

  E & e = *(new E(v1, v2));
  std::reference_wrapper<E> eRef{e};
  edgeListIter it = edgeList.insert(edgeList.begin(),eRef);
  adjList.at(v1.key()).insert(adjList.at(v1.key()).begin(),1,it);
  adjList.at(v2.key()).insert(adjList.at(v2.key()).begin(),1,it);
  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2

  V & srcVtx = vertexMap.at(key1).get();
  V & destVtx = vertexMap.at(key2).get();
  E & e = *(new E(srcVtx,destVtx));
  std::reference_wrapper<E> eRef{e};
  if (adjList.at(key1).size() < adjList.at(key2).size()) {
    auto it = std::find(adjList.at(key1).begin(),adjList.at(key1).end(),eRef);
    removeEdge(*it);
  }
  else {
    auto it = std::find(adjList.at(key2).begin(),adjList.at(key2).end(),eRef);
    removeEdge(*it);
  }


}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
    if (it == edgeList.end()) {return;}
    //E & edge = (*it).get();
    adjList.at(edge.source().key()).remove(it);
    adjList.at(edge.dest().key()).remove(it);

    edgeList.erase(it);

}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  const V & srcVtx = vertexMap.at(key).get();
  const E & dummyE = *(new E(srcVtx,srcVtx));
  if (dummyE.directed()) {
    for (edgeListIter it: adjList.at(key)) {
      const std::reference_wrapper<E> e = *it;
      if (e.get().source() == srcVtx) {edges.push_back(e);}
    }
  }
  else {
    for (edgeListIter it: adjList.at(key)) {
      edgest.push_back(*it);
    }
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const
{
  // TODO: Part 2
  V & v1 = vertexMap.at(key1).get();
  V & v2 = vertexMap.at(key2).get();
  const E & e1 = *(new E(v1,v2));
  /*
  if (!edge1.directed()) {

    for (const std::reference_wrapper<E> adjEdge : incidentEdges(key1)) {
      const E & e = adjEdge.get();
      if (adjEdge.dest() == vertexMap.at(key2)) {return true;}
    }
    return false;
  }
  else {
    for (const std::reference_wrapper<E> adjEdge : incidentEdges(key1)) {

      if (edge2.dest() == v2) {return true;}
    }
    }
  }
  */
  for (const std::reference_wrapper<E> adjEdge : incidentEdges(key1)) {
    const E & e2 = adjEdge.get();
    if (e2 == e1) {return true;}
  }
  return false;
}
