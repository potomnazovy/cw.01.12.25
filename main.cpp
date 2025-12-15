#include <iostream>
#include "geom.hpp"
#include "IDraw.hpp"
#include "dot.hpp"
#include "canvas.hpp"
#include "vline.hpp"

namespace top 
{
  struct HLine : IDraw 
  {
    HLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct DiagonalLine : IDraw
  {
    DiagonalLine(int x, int y, int len);
    p_t begin() const override;
    p_t next (p_t p) const override;
    p_t start;
    int length;
  };
  
  struct Rectangle : IDraw
  {
    Rectangle(int x, int y, int a, int b);
    p_t begin() const override;
    p_t next (p_t p) const override;
    p_t start;
    int a_, b_;
  };

  struct Square: IDraw 
  {
    Square(int x, int y, int l);
    Square(p_t p, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int len;
  };
}

int main()
{
  top::IDraw* f[7] = {};
  top::p_t* p = nullptr;
  size_t s = 0;
  char* cnv = nullptr;
  int statusCode = 0;
  try 
  {
    f[0] = new top::Dot(0, 0);
    f[1] = new top::Dot(-1, -5);
    f[2] = new top::Square(7, 7, 3);
    f[3] = new top::VLine(4, 5, 3);
    f[4] = new top::HLine(2, 7, 4);
    f[5] = new top::DiagonalLine(-3, 1, 4);
    f[6] = new top::Rectangle(-10, -4, 4, 7);
    for (size_t i = 0; i < 7; ++i) 
    {
      top::getPoints(f[i], &p, s);
    }
    top::Frame_t fr = top::buildFrame(p, s);
    cnv = top::buildCanvas(fr, '.');
    top::paintCanvas(cnv, fr, p, s, 'o');
    top::printCanvas(cnv, fr);
  } 
  catch(...) 
  {
    statusCode = 1;
  }

  delete f[0];
  delete f[1];
  delete f[2];
  delete f[3];
  delete f[4];
  delete f[5];
  delete f[6];
  delete[] p;
  delete[] cnv;

  return statusCode;
}

top::p_t top::Dot::next(p_t p) const
{
  return begin();
}

top::p_t top::Dot::begin() const
{
  return o;
}

top::VLine::VLine(int x, int y, int len) : 
  IDraw(), 
  start{x,y}, 
  length(len)
{
  if (len == 0) 
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::VLine::begin() const
{
  return start;
}

top::p_t top::VLine::next(p_t p) const
{
  if (p.y == start.y + length - 1) 
  {
    return start;
  }
  if (length > 0) 
  {
    return p_t{start.x, p.y + 1};
  }
  return p_t{start.x, p.y - 1};
}

top::HLine::HLine(int x, int y, int len) : 
  IDraw(), 
  start{x, y}, 
  length(len)
{
  if (len == 0) 
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::HLine::begin() const
{
  return start;
}

top::p_t top::HLine::next(p_t p) const
{
  if (p.x == start.x + length - 1) 
  {
    return start;
  }
  if (length > 0) 
  {
    return p_t{p.x + 1, start.y };
  }
  return p_t{p.x - 1, start.y };
}

top::Square::Square(int x, int y, int l):
  IDraw(), 
  start{x, y}, 
  len(l)
{
  if (len <= 0) 
  {
    throw std::invalid_argument("length can not be <= 0");
  }
}

top::DiagonalLine::DiagonalLine(int x, int y, int len) : 
  IDraw(), 
  start{x, y}, 
  length(len)
{
  if (len <= 0)
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::DiagonalLine::begin() const
{
  return start;
}

top::p_t top::DiagonalLine::next(p_t p) const
{
  if (p.x - start.x == p.y - start.y)
  {
    if (p.x == start.x + length - 1 && p.y == start.y + length - 1)
    {
      return start;
    }
    return {p.x + 1, p.y + 1};
  }
  return start;
}

top::Square::Square(p_t p, int l):
  Square(p.x, p.y, l)
{}

top::p_t top::Square::begin() const
{
  return start;
}

top::p_t top::Square::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + len - 1) 
  {
    return {p.x, p.y + 1};
  } 
  else if (p.y == start.y + len - 1 && p.x < start.x + len - 1) 
  {
    return {p.x + 1, p.y};
  } 
  else if (p.x == start.x + len - 1 && p.y > start.y) 
  {
    return {p.x, p.y - 1};
  } 
  else if (p.y == start.y && p.x > start.x) 
  {
    return {p.x - 1, p.y};
  }
  return start;
}

top::Rectangle::Rectangle(int x, int y, int a, int b) : 
  IDraw(), 
  start{x, y}, 
  a_(a), 
  b_(b)
{
  if (a <= 0 || b <= 0)
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::Rectangle::begin() const
{
  return start;
}

top::p_t top::Rectangle::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + b_ - 1)
  {
    return {p.x, p.y + 1};
  }
  else if (p.y == start.y + b_ - 1 && p.x < start.x + a_ - 1)
  {
    return {p.x + 1, p.y};
  }
  else if (p.x == start.x + a_ - 1 && p.y > start.y)
  {
    return {p.x, p.y - 1};
  }
  else if (p.y == start.y && p.x > start.x)
  {
    return {p.x - 1, p.y};
  }
  return start;
}
