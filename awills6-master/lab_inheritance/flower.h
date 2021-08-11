/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "drawable.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
    Vector2 center_; // centers of member shapes derived from this center_
    Rectangle* stem;
    Circle* pistil; // changed member shape type from shape to [specific shape]*
    Triangle* leaf;

    void copy(const Flower& other); // helper function for copy/assignment
    void clear(); // helper function for destructor/assignment
    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
    Flower(const Flower& other); //rule of three
    ~Flower(); // rule of three (I needed a destructor since I changed base Shapes
               // from being declared on stack to heap)
    Flower& operator=(const Flower& other); //rule of three
    void draw(cs225::PNG* canvas) const;
};
