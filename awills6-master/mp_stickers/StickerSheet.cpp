#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"


using cs225::Image;
using cs225::PNG;
using cs225::StickerSheet;
using std::vector;


  StickerSheet::StickerSheet(const Image& picture, unsigned max)
    : stickers_(max),
      x_(max),
      y_(max),
      stickers_idx(0),
      max_(max)
  {
    base_ = new Image(picture);
  }


  StickerSheet::StickerSheet(const StickerSheet& other)
  {
    copy_sticker_sheet(other);
  }


  StickerSheet::~StickerSheet()
  {
    clear_sticker_sheet();
  }


  const StickerSheet& StickerSheet::operator=(const StickerSheet& other)
  {
    if (this == &other) {return *this;}
    clear_sticker_sheet();
    copy_sticker_sheet(other);
    return *this;
  }


 void StickerSheet::copy_sticker_sheet(const StickerSheet& other)
 {
   this->base_ = new Image(*(other.base_));

   for (unsigned i = 0; i < this->stickers_idx; i++) {
     this->stickers_[i] = new Image(*(other.stickers_[i]));
     this->x_[i] = other.x_[i];
     this->y_[i] = other.y_[i];
   }
   this->stickers_idx = other.stickers_idx;
   this->max_ = other.max_;
   (this->stickers_).resize(this->max_);
   (this->x_).resize(this->max_);
   (this->y_).resize(this->max_);
 }


 void StickerSheet::clear_sticker_sheet()
 {
   for (unsigned i = 0; i < stickers_idx; i++) {
     delete stickers_[i];
   }
   stickers_.clear();
   x_.clear();
   y_.clear();
   delete base_;
 }


 void StickerSheet::changeMaxStickers(unsigned max)
 {
   if (max < stickers_idx) {
     for (unsigned i = max; i < stickers_idx; i++) {
       delete stickers_[i];
     }
     stickers_idx = max;
   }
   stickers_.resize(max);
   x_.resize(max);
   y_.resize(max);
   max_ = max;
 }


 int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y)
 {
   if (stickers_idx < max_) {
     stickers_idx += 1;
     stickers_[stickers_idx-1] = new Image(sticker);
     x_[stickers_idx-1] = x;
     y_[stickers_idx-1] = y;
     return static_cast<int>(stickers_idx);
   }
   return -1;
 }


 bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
 {
   if ((index >= stickers_idx)
    || (stickers_[index] == nullptr)
    || (index < 0)) {return false;}
   x_[index] = x;
   y_[index] = y;
   return true;
 }


 void StickerSheet::removeSticker(unsigned index)
 {
   if ((index < stickers_idx)&&(index >= 0)) {
     delete stickers_[index];
     stickers_.erase((stickers_.begin())+index);
     x_.erase((x_.begin())+index);
     y_.erase((y_.begin())+index);
     stickers_idx -= 1;
   }
 }


 Image* StickerSheet::getSticker(unsigned index)
 {
   if ((index >= stickers_idx)
    || (stickers_[index] == nullptr)
    || (index < 0)) {return nullptr;}

   else {
     return stickers_[index];
   }
 }


 Image StickerSheet::render() const
 {
   Image output = *base_;
   for (unsigned i = 0; i < stickers_idx; i++) {
     Image* current_im = stickers_[i];
     unsigned x_start = x_[i];
     unsigned y_start = y_[i];

     if (x_start+current_im->width() > output.width()) {
       unsigned newWidth = x_start+current_im->width();
       output.resize(newWidth,output.height());
     }
     if (y_start+current_im->height() > output.height()) {
       unsigned newHeight = y_start+current_im->height();
       output.resize(output.width(),newHeight);
     }

     for (unsigned x = 0; x < current_im->width(); x++) {
       for (unsigned y = 0; y < current_im->height(); y++) {
         HSLAPixel& current_p = current_im->getPixel(x,y);
         if (current_p.a == 0) {continue;}
         HSLAPixel& output_p = output.getPixel(x_start+x,y_start+y);
         output_p = current_p;
       }
     }
   }
   return output;
 }
