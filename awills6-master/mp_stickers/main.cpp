#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"

using cs225::Image;
using cs225::StickerSheet;

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image face, comp,segf;
  face.readFromFile("face960x600.png");
  comp.readFromFile("comp1820x1200.png");
  segf.readFromFile("segfault.png");
  double fact = 0.9;
  double offset = 48;
  unsigned newX = (unsigned)offset;
  StickerSheet mySheet(comp,13);
  for (int i = 0; i < 10; i++) {
    comp.scale(fact);
    mySheet.addSticker(comp,newX,0);
    offset *= fact;
    newX += (unsigned)offset;
  }
  face.scale(fact/2);
  newX += fact*offset;
  mySheet.addSticker(face,400,70);

  newX += fact*offset;
  segf.scale(5);
  mySheet.addSticker(segf,450,100);
  mySheet.render().writeToFile("segf.png");



  return 0;
}
