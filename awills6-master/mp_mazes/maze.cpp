/* Your code here! */
#include "maze.h"
#include "cs225/PNG.h"
#include <stack>
#include <ctime>
#include <algorithm>
#include <iostream>
//#include "cs225/HSLAPixel.h"
#include <math.h>

using cs225::PNG;

SquareMaze::SquareMaze()
  : width_(0),
    height_(0),
    endIdx_(-1),
    walls_(nullptr),
    maze_(0)
{
  //Nothin'
}


SquareMaze::~SquareMaze()
{
  for (MazeCell* cell : maze_) {delete cell;}
}


void SquareMaze::makeMaze(int width, int height)
{

  width_ = width;
  height_ = height;
  int newSize = width_*height_;

  if (!maze_.empty()) {
    for (MazeCell* cell : maze_) {delete cell;}
  }
  maze_.resize(newSize);

  walls_ = new DisjointSets();
  walls_->addelements(newSize);

  std::vector<std::vector<int>> walls(0);
  for (int i = 0; i < width_; ++i) {
    for (int j = 0; j < height_; ++j) {
      int idx = getIdx(i,j);
      maze_[idx] = new MazeCell(idx);

      std::vector<int> rightWall{i,j,0};
      walls.push_back(rightWall);
      std::vector<int> bottomWall{i,j,1};
      walls.push_back(bottomWall);
    }
  }

  srand(std::time(nullptr));

  while(walls_->size(walls_->find(0)) < newSize) {
    int wallIdx = rand()%walls.size();
    std::vector<int> wallVec = walls[wallIdx];
    auto pos = walls.begin() + wallIdx;
    walls.erase(pos); // erase from vector to avoid revisiting

    // ignore right and down walls at their respective borders
    if ((wallVec[0] == width_-1 && wallVec[2] == 0)
      ||(wallVec[1] == height_-1 && wallVec[2] == 1)) {continue;}

    std::vector<int> neighbor(wallVec);
    neighbor[wallVec[2]] += 1; // set neighbor to cell below for downWall/cell to the right for rightWall
    int thisIdx = getIdx(wallVec[0],wallVec[1]);
    int neighborIdx = getIdx(neighbor[0],neighbor[1]);

    if (walls_->find(thisIdx) != walls_->find(neighborIdx)) {
      maze_[thisIdx]->adj_bool[wallVec[2]] = true;
      maze_[neighborIdx]->adj_bool[wallVec[2]+2] = true;
      walls_->setunion(thisIdx,neighborIdx);
    }
  }
  delete walls_;
}


bool SquareMaze::checkEdges(int x, int y, int dir) const
{

  if ((x == 0 && dir == 2) || (x == width_-1 && dir == 0)
    ||(y == 0 && dir == 3) || (y == height_-1 && dir == 1)) {return false;}

  return inMaze(x,y);
}

bool SquareMaze::inMaze(int x, int y) const
{
  if (x < 0 || y < 0 || x > width_-1 || y > height_-1) {return false;}
  return true;
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
  if (!checkEdges(x,y,dir)) {return false;}

  std::vector<int> xy{x,y};
  int shift = dir / 2;  //determines if a different index should be checked
  int adj_idx = dir % 2;  //determines whether right or down is being checked
  xy[adj_idx] -= shift; // check idx to left/below for dir = 2 or 3
  return maze_[getIdx(xy[0],xy[1])]->adj_bool[adj_idx];
}


void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  //dont delete (or create) walls on border of maze
  if (!checkEdges(x,y,dir)) {return;}

    std::vector<int> xy{x,y};
    int shift = dir / 2;
    int adj_idx = dir % 2;  //determines whether right or down is being checked
    xy[adj_idx] -= shift; // check idx to left/below for dir = 2/3
    //adj_[idx] determines if two cells are connected in a given direction:
    // wall exists between two indices => indices are not adjacent
    maze_[getIdx(xy[0],xy[1])]->adj_bool[adj_idx] = !exists;

}


std::vector<int> SquareMaze::solveMaze()
{
  int size = width_*height_;
  std::vector<int> dist(size,0);
  std::vector<int> prev(size,-1);
  std::vector<bool> visited(size,false);

  int maxDist = 0;
  int maxDistIdx = 0;
  DFS(dist,prev,visited,maxDistIdx,maxDist);
  endIdx_ = maxDistIdx;

  std::vector<int> solution{};
  int idx = endIdx_;
  int prevIdx = prev[idx];
  while(prevIdx != -1) {
    for (int i = 0; i < 4; ++i) {
      if (maze_[prevIdx]->adj_idx[i] == idx) {
        solution.push_back(i);
        break;
      }
    }
    idx = prevIdx;
    prevIdx = prev[idx];
  }
  std::reverse(solution.begin(),solution.end());
  return solution;
}


void SquareMaze::DFS(std::vector<int>& dist,
                     std::vector<int>& prev,
                     std::vector<bool>& visited,
                     int& maxDistIdx, int& maxDist)
{
  std::stack<int> stack;
  visited[0] = true;
  getAdjList(0,maze_[0]);
  stack.push(0);

  while (!stack.empty()) {
    int v_idx = stack.top();
    stack.pop();
    MazeCell*& v = maze_[v_idx];

    for (int new_idx : v->adj_idx) {

      if (new_idx > 0 && !visited[new_idx]) {
        prev[new_idx] = v_idx;
        dist[new_idx] = dist[v_idx]+1;

        int y_new = new_idx / width_;
        if (y_new == height_-1) {         //check for maze endpoint
          if (dist[new_idx] > maxDist) {
            maxDistIdx = new_idx;
            maxDist = dist[new_idx];
          }
          else if (dist[new_idx] == maxDist) {
            if (new_idx%width_ < maxDistIdx%width_) {
              maxDistIdx = new_idx;
              maxDist = dist[new_idx];
            }
          }
        }

        visited[new_idx] = true;
        getAdjList(new_idx,maze_[new_idx]);
        stack.push(new_idx);
      }
    }
  }
  return;
}


void SquareMaze::getAdjList(int idx, SquareMaze::MazeCell*& v)
{
  for (int i = 0; i < 4; ++i) {
    if (v->adj_bool[i]) {
      int sign = pow(-1,i/2);
      int weight = (i%2 == 0) ? 1 : width_;
      v->adj_idx[i] = idx + sign*weight;
    }
  }
}


PNG* SquareMaze::drawMaze() const
{
  int w_output = width_*10+1;
  int h_output = height_*10+1;
  PNG* output = new PNG(w_output,h_output);

  for (int y = 0; y < h_output; ++y) {
    cs225::HSLAPixel& p = output->getPixel(0,y);
    p.h = p.s = p.l = 0;
    p.a = 1;
  }

  for (int x = 10; x < w_output; ++x) {
    cs225::HSLAPixel& p = output->getPixel(x,0);
    p.h = p.s = p.l = 0;
    p.a = 1;
  }

  for (int x = 0; x < width_; ++x) {
    for (int y = 0; y < height_; ++y) {

      for (int i = 0; i < 2; ++i) {
        if (maze_[getIdx(x,y)]->adj_bool[i]) {continue;}

        std::vector<int> xy{10*x,10*y};
        xy[i] += 10;
        for (int j = 0; j <= 10; ++j) {
          cs225::HSLAPixel& p = output->getPixel(xy[0],xy[1]);
          p.h = p.s = p.l = 0;
          p.a = 1;
          xy[abs(i-1)] += 1; // i = 0 : xy[-1] = x[1]; i = 1 : xy[0]
        }
      }
    }
  }

  return output;
}

PNG* SquareMaze::drawMazeWithSolution()
{
  PNG* output = drawMaze();

  std::vector<int> solution = solveMaze();
  std::vector<int> xy{5,5};
  for (int dir : solution) {
    /*
    int sign = 1;
    if (dir > 2) {sign = -1;}
    int idx = dir % 2;
    for (int i = 0; i < 10; ++i) {
      std::vector<int> line(xy);
      line[idx] += sign;
      cs225::HSLAPixel& p = output->getPixel(line[0],line[1]);
      p.h = 0;
      p.s = 1;
      p.s = 0.5;
      p.a = 1;
    }
    xy[idx] += 10*sign;
    */
    switch(dir)
    {
      case 0:
        for (int i = 0; i < 11; ++i) {
          cs225::HSLAPixel& p = output->getPixel(xy[0]+i,xy[1]);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        xy[0] += 10;
        break;

      case 1:
        for (int i = 0; i < 11; ++i) {
          cs225::HSLAPixel& p = output->getPixel(xy[0],xy[1]+i);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        xy[1] += 10;
        break;

      case 2:
        for (int i = 0; i < 11; ++i) {
          cs225::HSLAPixel& p = output->getPixel(xy[0]-i,xy[1]);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        xy[0] -= 10;
        break;

      case 3:
        for (int i = 0; i < 11; ++i) {
          cs225::HSLAPixel& p = output->getPixel(xy[0],xy[1]-i);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        xy[1] -= 10;
        break;
    }
  }

  int x = endIdx_ % width_;
  int y = endIdx_ / width_;
  for (int k = 1; k < 10; ++k) {
    cs225::HSLAPixel& p = output->getPixel(10*x+k,(y+1)*10);
    p.l = 1;
  }

  return output;
}

int SquareMaze::getIdx(int x, int y) const
{
  return y*width_ + x;
}

PNG* SquareMaze::drawCreativeMaze()
{


  PNG* output = drawMazeWithSolution();

  return output;
}
