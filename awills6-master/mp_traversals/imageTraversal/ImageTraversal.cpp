#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"


/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/** Public helper function to allow BFS/DFS to access calculateDelta
 * @param point comparison pixel
 * @return true if pixel is within bounds of PNG and tolerance
 *         false, else
 */
bool ImageTraversal::inBounds(const Point& point,
                              const Point& start,
                              const PNG& image,
                              double tol)
{
  bool inFrame = (point.y < image.height() && point.x < image.width());
  if (!inFrame) {return false;}

  const HSLAPixel& startP = image.getPixel(start.x,start.y);
  const HSLAPixel& thisP = image.getPixel(point.x,point.y);
  bool inTol = (calculateDelta(thisP,startP) < tol);
  return (inTol);
}

void ImageTraversal::push_next(const Point& point) {
  unsigned x = point.x;
  unsigned y = point.y;
  vector<Point> newPoints{Point(x+1,y),Point(x,y+1),Point(x-1,y),Point(x,y-1)};
  for (Point& nu: newPoints) {add(nu);}
}
/*
int ImageTraversal::getIdx(const Point & point) const {
  return (int)(point.y*image_.width() + point.x);
}
*/
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal_(nullptr)
{
  //Nothing
}

/**
 * custom iterator constructor
 */
 ImageTraversal::Iterator::Iterator(ImageTraversal* traversal,const Point& start)
  : traversal_(traversal),
    start_(start)
{
  //traversal_->add(start);
  current_ = traversal_->pop();
  traversal_->push_next(current_);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator& ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (!traversal_->empty()) {
    traversal_->visited_[current_] = true;
    traversal_->push_next(current_);

    if (traversal_->empty()) {
      traversal_ = nullptr;
      return *this;
    }
    current_ = traversal_->peek();

    while (traversal_->visited_[current_]) {
      if (traversal_->empty()) {
        traversal_ = nullptr;
        return *this;
      }
      current_ = traversal_->pop();
    }
    //traversal_->visited_[current_] = true;
  }
  else {
    traversal_ = nullptr;
  }
  return *this;
}

/*
int ImageTraveral::getIdx(const Point & point) const {
  return (int)(point.y*image_.width() + point.x);
}
*/

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator& other) {
  /** @todo [Part 1] */
  /*
  bool thisEmpty = (traversal_) ? false : true;
  bool otherEmpty = (other.traversal_) ? false : true;

  if (thisEmpty && otherEmpty) {return true;}
  else if (!thisEmpty && !otherEmpty) {return (!(traversal_ == other.traversal_));}
  else {return false;}
  */
  return !(this->traversal_ == nullptr);
}
