/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel {
    public:
      double h; //denotes the hue, from [0,360)
      double s; //denotes the saturation, from [0,1]
      double l; //denotes the luminance, from [0,1]
      double a; //denotes the alpha channel, the transparence of the pixel, from [0,1]

      HSLAPixel(); // default constructor

      HSLAPixel(double hue, double saturation, double luminance);

      HSLAPixel(double hue, double sautration, double luminance, double alpha);

  };
}
