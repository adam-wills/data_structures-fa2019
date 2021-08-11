#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <vector>
#include <string>


using cs225::HSLAPixel;
using cs225::PNG;


void rotate(std::string inputFile, std::string outputFile) {
  PNG* img_in = new PNG();
  if (!(img_in->readFromFile(inputFile))) {
    delete img_in;  // frees heap memory if readFromFile fails
    return;
  }
  unsigned x_max = img_in->width();
  unsigned y_max = img_in->height();
  PNG* img_out = new PNG(x_max,y_max);
  for (unsigned x = 0; x < x_max; x++) {
    for (unsigned y = 0; y < y_max; y++) {
      HSLAPixel & pixel1 = img_out->getPixel(x_max-x-1,y_max-y-1);
      pixel1 = img_in->getPixel(x,y); // set pixel at distance x from right side of page,
    }				      // distance y from bottom of page equal to former pixel at (x,y)
  }
  delete img_in;
  if(!(img_out->writeToFile(outputFile))) {
    delete img_out;
    return;
  }
  delete img_out;
  return;
}

// makes a burning ship fractal
cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  double x_inc = 0.013/double(width);   // finds the width per pixel
  double y_inc = 0.0036/double(height);
  int i_max  = 696;
  std::vector<double> nums{2,3,5,7,11,13,17}; // some primes i use later
  int sz = nums.size();
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel & pixel = png.getPixel(x,y);
      pixel.a = 1;

      double x_pos = x*x_inc - 1.635;  // x position, between [-1.635,-1.622]
      double Re_z = x_pos;	       //
      double y_pos = y*y_inc - 0.0036; // y position, between [-0.0036,0]
      double Im_z = y_pos;
      int i = 0;
      while (((Re_z*Re_z)+(Im_z*Im_z) < 4)&&(i < i_max)) {
        double x_temp = Re_z*Re_z - Im_z*Im_z + x_pos;
        Im_z = abs(2*Re_z*Im_z);
        Re_z = abs(x_temp);
        i += 1;
      }
      if (i == i_max) {
        double grad = double(x*y)/double(width*height);
        pixel.l = grad; // makes a luminance gradient
        pixel.h = 240+52*grad;
	pixel.s = 1;
        continue;
      }
      pixel.l = cos(6*3.141592*i*(1.0/i_max));
      pixel.s = 0.5 + 0.5*sin(4*3.141592*i*(1.0/i_max));
      pixel.h = (360.0/(i_max*17))*double(i)*nums[(i%sz)];
    }
  }
  return png;
}
