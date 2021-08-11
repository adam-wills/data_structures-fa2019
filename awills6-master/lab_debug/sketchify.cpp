/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */

#include <cstdlib>
#include <cmath>
#include <iostream>  
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using cs225::HSLAPixel;
using cs225::PNG;


//outside functions weren't declared in h file

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image

PNG* setupOutput(unsigned w, unsigned h) {
  PNG* image = new PNG(w, h);
  return image;
}
**/

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying

HSLAPixel* myFavoriteColor() {
    HSLAPixel* p = new HSLAPixel(280, 0.8, 0.5);  // switched to declaration on heap;
    return p;  // i don't know what the point of making a separate function
}              // for this is but i fixed it
**/

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG(); // changed to a new PNG
    if (!(original->readFromFile(inputFile))) {     // check to see if load was successful
      std::cout << "read unsuccessful" << std::endl;
      delete original; // free space if unsuccessful
      return;
    }
    unsigned width = original->width();
    unsigned height = original->height();

    // Create out.png
    PNG* output = new PNG(width,height); // replacing setOutput

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = new HSLAPixel(280,0.8,0.5); // replacing myFavoriteColor

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++) {     // changed weird boundary statements
        for (unsigned x = 1; x < width; x++) {
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel & currOutPixel = output->getPixel(x, y);
            if (diff > 20) {                             
                currOutPixel = *myPixel; // dereferenced the pointer
            }
        }
    }
    delete original; 
    delete myPixel;
    // Save the output file
    if(!(output->writeToFile(outputFile))) {                    // might free memory if 
      std::cout << "failed to write image to file" << std::endl;// load fails
      delete output;                 
      return;                        
    }

    delete output;
    return;
}
