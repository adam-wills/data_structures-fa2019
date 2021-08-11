/* Your code here! */
#pragma once
#include "dsets.h"
#include <iterator>
#include <vector>
#include <stack>
#include <map>
#include <random>
#include "cs225/PNG.h"

using cs225::PNG;
//using std::pair;

class SquareMaze {
  public:
    class MazeCell {
      public:
        std::vector<bool> adj_bool; // {right, bottom}
        std::vector<int> adj_idx;
        MazeCell() : adj_bool(0),adj_idx(0) {}
        MazeCell(int idx) : adj_bool(4,false),adj_idx(4,-1) {}
    };

    SquareMaze();

    ~SquareMaze();

    void makeMaze(int width, int height);

    bool canTravel(int x, int y, int dir) const;

    void setWall(int x, int y, int dir, bool exists);

    std::vector<int> solveMaze();

    PNG* drawMaze() const;

    PNG* drawMazeWithSolution();

    PNG* drawCreativeMaze();
  private:
    void getAdjList(int idx, MazeCell*& v);
    void DFS(std::vector<int>& dist,
             std::vector<int>& prev,
             std::vector<bool>& visited,
             int& maxDistIdx, int& maxDist);
    bool inMaze(int x, int y) const;
    bool checkEdges(int x, int y, int dir) const;
    int getIdx(int x, int y) const;
    int width_;
    int height_;
    int endIdx_;
    DisjointSets* walls_;
    std::vector<MazeCell*> maze_;




};
