/**
 * @file sketchify.h
 * Declaration of the sketchify function.
 */

#pragma once

#include <string>
/**


#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

cs225::PNG* setupOutput(unsigned w, unsigned h);

cs225::HSLAPixel* myFavoriteColor();

**/

/**
 * Reads in an image, runs a simple "sketchify" algorithm on it to highlight
 * edges in the image, and then writes the resulting image back out to a
 * specified file.

 * @param inputFile the name of the PNG file to sketchify
 * @param outputFile the name of the file where the output will be written
 */
void sketchify(std::string inputFile, std::string outputFile);
