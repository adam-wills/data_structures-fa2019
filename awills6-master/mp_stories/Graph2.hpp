#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <climits>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path{};
  std::unordered_map<std::string,std::string> previous{};
  std::unordered_map<std::string,unsigned> distance{};
  std::unordered_map<std::string,bool> visited{};
  for (auto it = vertexMap.begin(); it != vertexMap.end(); ++it) {
    previous.emplace((*it).first,"");
    distance.emplace((*it).first,INT_MAX);
    visited.emplace((*it).first,false);
  }
  distance[start] = 0;
  visited[start] = true;
  std::queue<std::string> q{};
  q.push(start);

  while (!q.empty()) {
    std::string v = q.front();
    q.pop();
    visited[v] = true;
    for (edgeListIter it : adjList.at(v)) {
      E & edge = (*it).get();
      std::string destV = edge.dest().key();

      if (!visited[destV]) {
        q.push(destV);
        if (distance[v] + 1 < distance[destV]) {
          distance[destV] = distance[v]+1;
          previous[destV] = v;
        }
      }
    }
  }
  while (!q.empty()) {q.pop();}
  path.insert(path.end(),end);
  std::string prev = previous[end];
  path.insert(path.begin(),prev);
  while (prev != start) {
    if (previous.find(prev) == previous.end()) {
      break;
    }
    prev = previous[prev];
    path.insert(path.begin(),prev);
  }
  return path;
}
