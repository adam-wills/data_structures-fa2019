/**
 * @file flower.cpp
 * Implementation of the Flower class.
 */

#include "flower.h"

#include <cmath>
#include <cstdio>

#include "circle.h"
#include "color.h"
#include "rectangle.h"
#include "triangle.h"

using cs225::PNG;
using cs225::HSLAPixel;

const int STEM_HEIGHT = 32;
const int STEM_WIDTH = 2;
const HSLAPixel STEM_COLOR = color::GREEN;

const int LEAF_WIDTH = 16;
const int LEAF_HEIGHT = 16;
const HSLAPixel LEAF_COLOR = color::GREEN;

const int PISTIL_RADIUS = 12;
const HSLAPixel PISTIL_COLOR = color::YELLOW;

const int PETAL_RADIUS = 2;
const HSLAPixel PETAL_COLOR = color::RED;

Flower::Flower(const Vector2& center)
    : center_(center)
{
  Vector2 stem_center(center.x(), center.y() + STEM_HEIGHT / 2);
  Vector2 pistil_center(center.x(),center.y() - PISTIL_RADIUS / 2);
  Vector2 leaf_center(stem_center.x() - STEM_WIDTH / 2 + 1,
                          stem_center.y() + STEM_HEIGHT / 4);
  stem = new Rectangle(stem_center,STEM_COLOR,STEM_WIDTH,STEM_HEIGHT);
  pistil = new Circle(pistil_center,PISTIL_COLOR, PISTIL_RADIUS);
  leaf = new Triangle(LEAF_COLOR,
    Vector2(leaf_center.x(), leaf_center.y() - STEM_HEIGHT / 4),
    Vector2(leaf_center.x() - LEAF_WIDTH, leaf_center.y() - LEAF_HEIGHT),
    Vector2(leaf_center.x() - LEAF_WIDTH / 2, leaf_center.y()));
}

Flower::Flower(const Flower& other)
{
  copy(other);
}

Flower::~Flower()
{
  clear();
}

Flower& Flower::operator=(const Flower& other)
{
    if (this == &other) {
        return *this;
    }
    clear();
    copy(other);
    return *this;
}

void Flower::copy(const Flower& other)
{
  center_ = other.center_;
  stem = new Rectangle(*(other.stem));
  pistil = new Circle(*(other.pistil));
  leaf = new Triangle(*(other.leaf));
}

void Flower::clear()
{
  delete stem;
  delete pistil;
  delete leaf;
}

void Flower::drawPetals(PNG* canvas, const Vector2& center, int x, int y) const
{
    Circle petal(center, PETAL_COLOR, PETAL_RADIUS);
    petal.set_center(Vector2(center.x() + x, center.y() + y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + x, center.y() - y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - x, center.y() + y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - x, center.y() - y));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + y, center.y() + x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() + y, center.y() - x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - y, center.y() + x));
    petal.draw(canvas);
    petal.set_center(Vector2(center.x() - y, center.y() - x));
    petal.draw(canvas);
}

void Flower::draw(PNG* canvas) const
{
    stem->draw(canvas);
    pistil->draw(canvas);
    leaf->draw(canvas);
    for (int x = 0; x < PISTIL_RADIUS; x++) {
        const double radius2 = PISTIL_RADIUS * PISTIL_RADIUS;
        const int y = static_cast<int>(sqrt(radius2 - (x * x)));
        drawPetals(canvas, pistil->center(), x, y);
    }
}
