#include "canvas.hpp"
#include <iostream>

namespace top {

  char* buildCanvas(Frame_t fr, char fill)
  {
    char* newcanws = new char[rows(fr)*cols(fr)];
    for (size_t i = 0; i < rows(fr)*cols(fr);++i) {
      newcanws[i] = fill;
    }
    return newcanws;
  }

  void paintCanvas(char* cnv, Frame_t fr, p_t * p, size_t k, char f)
  {
    for (size_t i = 0; i < k; ++i) {
      int dx = p[i].x - fr.leftBott.x;
      int dy = fr.rightTop.y - p[i].y;
      cnv[dy * cols(fr) + dx] = f;
    }
  }

  void printCanvas(char* cnv, Frame_t fr)
  {
    for (size_t i = 0; i < rows(fr); ++i) {
      for (size_t j = 0; j < cols(fr); ++j) {
        std::cout << cnv[i*cols(fr) + j];
      }
      std::cout << '\n';
    }
  }

}