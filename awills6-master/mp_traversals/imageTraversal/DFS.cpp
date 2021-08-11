#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance)
  : points_(),
    image_(png),
    start_(start),
    tol_(tolerance)
{
  /** @todo [Part 1] */

  if (inBounds(start,start,image_,tol_)) {
    points_.push(start_);
    //visited_[start_] = true;
  }
  else {
    push_next(start_);
    visited_[start_] = true;
  }

}

//copy constructor (rule of 3)
DFS::DFS(DFS& other)
{
  copy_(other);
}

DFS::~DFS()
{
  clear_();
}

DFS& DFS::operator=(DFS& other)
{
  if (this != &other) {
    clear_();
    copy_(other);
  }
  return *this;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(new DFS(*this),start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}


/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */

  if (inBounds(point,start_,image_,tol_) && !visited_[point]) {
    points_.push(point);
  }
  /*
  unsigned x = point.x;
  unsigned y = point.y;
  vector<Point> newPoints{Point(x+1,y),Point(x,y+1),Point(x-1,y),Point(x,y-1)};
  for (Point& nu: newPoints) {
    bool valid = inBounds(nu,start_,image_,tol_) && !visited_[nu];
    if (valid) {points_.push(nu);}
  }
  */
}
/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop(){
  /** @todo [Part 1] */

  //while(!empty() && visited_[points_.top()]) {points_.pop();}
  if (empty()) {return Point(-1, -1);}
  Point ret = points_.top();
  points_.pop();
  //visited_[ret] = true;
  return ret;
}
/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() {
  /** @todo [Part 1] */
  //while (!empty() && visited_[points_.top()]) {points_.pop();}
  if (empty()) {return Point(-1, -1);}
  return points_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return points_.empty();
}
/*
int DFS::getIdx(const Point & point) const {
  return (int)(point.y*image_.width() + point.x);
}
*/
void DFS::clear_()
{
  //Nothing
}

void DFS::copy_(DFS& other)
{
  points_ = other.points_;
  image_ = other.image_;
  start_ = other.start_;
  tol_ = other.tol_;
}
