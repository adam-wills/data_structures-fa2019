/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"


int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  std::vector<Vertex> vertices = g_.getVertices();
  std::vector<Edge> edges = g_.getEdges();
  for (Vertex vertex : vertices) {
    residual_.insertVertex(vertex);
    flow_.insertVertex(vertex);
  }
  for (Edge edge: edges) {
    residual_.insertEdge(edge.source,edge.dest);
    residual_.setEdgeWeight(edge.source,edge.dest,edge.getWeight());
    residual_.insertEdge(edge.dest,edge.source);
    residual_.setEdgeWeight(edge.dest,edge.source,0);

    flow_.insertEdge(edge.source,edge.dest);
    flow_.setEdgeWeight(edge.source,edge.dest,0);
  }
  maxFlow_ = 0;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int capacity = residual_.getEdge(path[0],path[1]).getWeight();

  for (size_t i = 1; i < path.size()-1; ++i) {
    capacity = min(capacity,residual_.getEdge(path[i],path[i+1]).getWeight());
  }
  return capacity;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  std::vector<Vertex> path{};
  while (findAugmentingPath(source_,sink_,path)) {
    int path_cap = pathCapacity(path);
    maxFlow_ += path_cap;
    
    for (size_t i = 0; i < path.size()-1; ++i) {
      Edge forward = residual_.getEdge(path[i],path[i+1]);
      residual_.setEdgeWeight(path[i],path[i+1],forward.getWeight()-path_cap);

      Edge backward = residual_.getEdge(path[i+1],path[i]);
      residual_.setEdgeWeight(path[i+1],path[i],backward.getWeight()+path_cap);

      if (flow_.edgeExists(path[i],path[i+1])) {
        Edge edge = flow_.getEdge(path[i],path[i+1]);
        flow_.setEdgeWeight(path[i],path[i+1],edge.getWeight()+path_cap);
      }
      else {
        Edge edge = flow_.getEdge(path[i+1],path[i]);
        flow_.setEdgeWeight(path[i+1],path[i],edge.getWeight()-path_cap);
      }
    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
