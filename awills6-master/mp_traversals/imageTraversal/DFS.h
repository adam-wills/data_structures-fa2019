/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using std::stack;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);
  DFS(DFS& other);
  ~DFS();
  DFS& operator=(DFS& other);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek();
  bool empty() const;
  int getIdx(const Point & point) const;
  //bool inBounds(const Point& point);

private:
	/** @todo [Part 1] */
	/** add private members here*/
  stack<Point> points_;
  PNG image_;
  Point start_;
  double tol_;

  void clear_();
  void copy_(DFS& other);
};
