/**
 * @file lab_intro.h
 * Declarations of image manipulation functions.
 */

#pragma once

#include "cs225/PNG.h"


/*
 * Outputs PNG in grayscale (Saturation turned to 0)
*/
cs225::PNG grayscale(cs225::PNG image);

/*
 * outputs PNG with a spotlight effect centered around (centerX,centerY),
 * such that the luminance is reduced by 0.5% per every 1 pixel's distance
 * from the center for up to an 80% decrease in luminance
*/
cs225::PNG createSpotlight(cs225::PNG image, int centerX, int centerY);

/*
 * Turns every hue to either Illini Blue or Illini Orange, whichever
 * is closest
*/
cs225::PNG illinify(cs225::PNG image);

/*
 * At each pixel, if secondImage's... oh these are commented in the other file
*/
cs225::PNG watermark(cs225::PNG firstImage, cs225::PNG secondImage);
