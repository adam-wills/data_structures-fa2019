/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;
namespace cs225 {

  HSLAPixel::HSLAPixel() {
    h = 0; //default other values to zero
    s = 0;
    l = 1; //initialize luminance to 1
    a = 1; //initialize pixel as completely opaque
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
    a = 1;
    h = hue;
    s = saturation;
    l = luminance;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance,double alpha) {
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
  }

}
