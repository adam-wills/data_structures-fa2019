/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using std::vector;
using std::queue;

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  BFS(BFS& other);
  ~BFS();
  BFS& operator=(BFS& other);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek();
  bool empty() const;
  int getIdx(const Point & point) const;

private:
  //vector<bool> visited_;
  queue<Point> points_;
  PNG image_;
  Point start_;
  double tol_;

  void copy_(BFS& other);
  void clear_();
};
