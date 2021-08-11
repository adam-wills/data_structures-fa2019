/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"

namespace cs225{

  class Image : public PNG{

    public:
      // lightens image by increasing luminance by 0.1 (max 1)
      void lighten();

      // lightens image by a given amount (input value treated as positive)
      void lighten(double amount);

      // decreases luminance by 0.1 (min 0)
      void darken();

      // decreases luminance by a given amount (input treated as positive)
      void darken(double amount);

      // increases saturation by 0.1 (max 1)
      void saturate();

      // increases saturation by a given amount (input treated as positive)
      void saturate(double amount);

      // decreases saturation by 0.1 (min 0)
      void desaturate();

      // decreases saturation by a given amount (input treated as positive)
      void desaturate(double amount);

      // greyscales image by reducing saturation to 0
      void grayscale();

      // currently broken and I dont know why
      void rotateColor(double degrees);

      // switches all colors to Illini colors
      void illinify();

      // scales image by a given factor
      void scale(double factor);

      // scales image to either specified width or height while
      // maintaining aspect ratio and maximizing resultant size
      void scale(unsigned w, unsigned h);

      
    private:

      // performs linear interpolation of the form valNew = val0 + (xNew - x0) * ((val1 - val0)/(x1 - x0))
      double lInterp(double val0, double val1, double delta);

      // performs bilinear interpolation by treating the resultant values from two linear interpolations
      // in the x direction as inputs for a third linear interpolation in the y direction
      double blInterp(double val00, double val10, double val01, double val11, double delta_x, double delta_y);
  };
}
