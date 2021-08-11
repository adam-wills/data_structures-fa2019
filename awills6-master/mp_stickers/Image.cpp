#include <cmath>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Image.h"
#include <iostream>

using cs225::HSLAPixel;
using cs225::Image;
using cs225::PNG;


void Image::lighten() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.l = (pix.l + 0.1 >= 1.0) ? 1.0 : pix.l + 0.1;
    }
  }
}

void Image::lighten(double amount) {
  amount = std::fabs(amount);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.l = (pix.l + amount >= 1.0) ? 1.0 : pix.l + amount;
    }
  }
}

void Image::darken() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.l = (pix.l - 0.1 < 0.0) ? 0.0 : pix.l - 0.1;
    }
  }
}

void Image::darken(double amount) {
  amount = std::fabs(amount);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.l = (pix.l - amount < 0.0) ? 0.0 : pix.l - amount;
    }
  }
}

void Image::saturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.s = (pix.s + 0.1 >= 1.0) ? 1.0 : pix.s + 0.1;
    }
  }
}

void Image::saturate(double amount) {
  amount = std::fabs(amount);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.s = (pix.s + amount >= 1.0) ? 1.0 : pix.s + amount;
    }
  }
}

void Image::desaturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.s = (pix.s - 0.1 < 0.0) ? 0.0 : pix.s - 0.1;
    }
  }
}

void Image::desaturate(double amount) {
  amount = std::fabs(amount);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.s = (pix.s - amount <= 0.0) ? 0.0 : pix.s - amount;
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  unsigned w = this->width();
  unsigned h = this->height();
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      if ((pix.h + degrees) >= 360.0) {pix.h = (pix.h + degrees) - 360.0;}
      else if ((pix.h + degrees) < 0) {pix.h = (pix.h + degrees) + 360.0;}
      else {pix.h = pix.h + degrees;}
    }
  }
}

void Image::illinify() {
  double ilBlue = 11;
  double ilOrng = 216;
  double oMin = ilOrng - ((ilOrng-ilBlue)/2);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pix = this->getPixel(x,y);
      pix.h = (pix.h >= oMin)&&(pix.h <= oMin+180) ? ilOrng : ilBlue;
    }
  }
}

void Image::scale(double factor) {
  factor = std::fabs(factor);
  PNG* dummy = new PNG(*this);
  unsigned origWidth = this->width();
  unsigned origHeight = this->height();
  unsigned newWidth = (unsigned)((double)origWidth*factor);
  unsigned newHeight = (unsigned)((double)origHeight*factor);
  for (unsigned x = 0; x < origWidth; x++) {
    for (unsigned y = 0; y < origHeight; y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      pixel.l = 1.0;
      pixel.a = 1.0;
      pixel.h = 0;
      pixel.s = 0;
    }
  }
  this->resize(newWidth,newHeight);
  for (unsigned x = 0; x < newWidth; x++) {
    for (unsigned y = 0; y < newHeight; y++) {
      double x1 = (origWidth-1)*(((double)x)/newWidth);
      double y1 = (origHeight-1)*(((double)y)/newHeight);
      unsigned x0 = (unsigned)x1;
      unsigned y0 = (unsigned)y1;
      double delta_x = x1-x0;
      double delta_y = y1-y0;

      HSLAPixel& p00 = dummy->getPixel(x0,y0);
      HSLAPixel& p10 = dummy->getPixel(x0+1,y0);
      HSLAPixel& p01 = dummy->getPixel(x0,y0+1);
      HSLAPixel& p11 = dummy->getPixel(x0+1,y0+1);

      HSLAPixel& pNew = this->getPixel(x,y);
      pNew.h = blInterp(p00.h,p10.h,p01.h,p11.h,delta_x,delta_y);
      pNew.s = blInterp(p00.s,p10.s,p01.s,p11.s,delta_x,delta_y);
      pNew.l = blInterp(p00.l,p10.l,p01.l,p11.l,delta_x,delta_y);
      pNew.a = blInterp(p00.a,p10.a,p01.a,p11.a,delta_x,delta_y);

    }
  }
  delete dummy;
}

void Image::scale(unsigned w, unsigned h) {
  double h_ = this->height();
  double w_ = this->width();
  double ratio = std::min((double(w)/w_),(double(h)/h_));
  this->scale(ratio);
}

double Image::lInterp(double val0, double val1, double delta) // delta = (xNew - x0)/(x1 - x0)
{
  return val0 + delta*(val1-val0);
}

double Image::blInterp(double val00, double val10, double val01, double val11, double delta_x, double delta_y)
{
  return lInterp(lInterp(val00,val10,delta_x),lInterp(val01,val11,delta_x),delta_y);
}
