#include "Image.h"

#include <iostream>
using cs225::Image;
int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(720,10000);
  alma.writeToFile("scale(720,10000).png");

  return 0;
}
