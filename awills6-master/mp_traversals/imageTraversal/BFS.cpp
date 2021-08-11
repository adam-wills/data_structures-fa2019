#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)
  : //visited_((png.width()*png.height()),false),
    points_(),
    image_(png),
    start_(start.x,start.y),
    tol_(tolerance)
{
  /** @todo [Part 1] */

  if (inBounds(start_,start_,image_,tol_)) {
    points_.push(start);
  }
  else {push_next(start);}

  visited_[start_] = true;
}

//copy constructor (rule of 3)
BFS::BFS(BFS& other)
{
  copy_(other);
}

BFS::~BFS()
{
  clear_();
}

BFS& BFS::operator=(BFS& other)
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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(new BFS(*this),start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if (inBounds(point,start_,image_,tol_) && !visited_[point]) {
    points_.push(point);
  }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop(){
  /** @todo [Part 1] */

  if (empty()) {return Point(0, 0);}
  Point ret = points_.front();
  points_.pop();
  //visited_[ret] = true;
/*
  unsigned x = ret.x;
  unsigned y = ret.y;
  vector<Point> newPoints{Point(x+1,y),Point(x,y+1),Point(x-1,y),Point(x,y-1)};
  for (Point& nu: newPoints) {
    add(nu);
  }
  */
  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() {
  /** @todo [Part 1] */
  return (empty()) ? Point(0, 0) : points_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return points_.empty();
}

void BFS::clear_()
{
  //Nothing
}

void BFS::copy_(BFS& other)
{
  points_ = other.points_;
  image_ = other.image_;
  start_ = other.start_;
  tol_ = other.tol_;
}
