/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "cs225/PNG.h"
#include <vector>

using std::vector;
using cs225::PNG;
using cs225::Image;

namespace cs225 {
  class StickerSheet {
    public:

      StickerSheet(const Image& picture, unsigned max);
      StickerSheet(const StickerSheet& other);
      ~StickerSheet();
      const StickerSheet& operator=(const StickerSheet& other);

      // changes the max number of stickers a StickerSheet can
      // hold. If stickers exist at an index above the new maximum,
      // those stickers are deleted
      void changeMaxStickers(unsigned max);

      // adds a sticker to the StickerSheet at location (x,y) and
      // returns the index of the sticker. If the sticker cannot be
      // added, returns -1
      int addSticker(Image& sticker, unsigned x, unsigned y);

      // changes the location of the sticker at a given index. returns
      // true if this was successful; returns false if given an invalid index
      bool translate(unsigned index, unsigned x, unsigned y);

      // deletes a sticker at a given index. indices are then shifted so
      // those stickers which had a higher index than the removed sticker
      // will have their index reduced by 1
      void removeSticker(unsigned index);

      // returns a pointer to the sticker at a given index. returns nullptr
      // if given an invalid index
      Image* getSticker(unsigned index);

      // returns the sticker sheet as an Image. resizes the base image if
      // any image would otherwise exceed the boundaries of the base image
      Image render() const;
    private:
      void copy_sticker_sheet(const StickerSheet& other);
      void clear_sticker_sheet();
      Image* base_;
      vector<Image*> stickers_;
      vector<unsigned> x_;
      vector<unsigned> y_;
      unsigned stickers_idx;
      unsigned max_;

  };
}
