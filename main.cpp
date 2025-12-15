#include <iostream>
#include "geom.hpp"
#include "IDraw.hpp"
#include "dot.hpp"
#include "vline.hpp"
#include "canvas.hpp"

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

  struct DLine : IDraw 
  {
    DLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct Rectangle: IDraw 
  {
    Rectangle(int x, int y, int a, int b);
    p_t begin() const override;
    p_t next(p_t p) const override;
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

  struct Triangl: IDraw 
  {
    Triangl(int x, int y, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int len;
  };

}

int main()
{
  using namespace top;
  IDraw* f[9] = {};
  p_t* p = new p_t[1];
  size_t s = 0;
  char* cnv = nullptr;
  int statusCode = 0;
  try 
  {
    f[0] = new Dot(0, 0);
    f[1] = new Dot(1, -5);
    f[2] = new Square(7, 7, 3);
    f[3] = new VLine(4, 5, 3);
    f[4] = new HLine(2, 7, 4);
    f[5] = new DLine(-3, 1, 4);
    f[6] = new Rectangle(-10, -4, 4, 7);
    f[7] = new Triangl(0, -10, 4);
    for (size_t i = 0; i < 8; ++i) 
    {
      getPoints(f[i], &p, s);
    }
    Frame_t fr = buildFrame(p, s);
    cnv = buildCanvas(fr, '.');
    paintCanvas(cnv, fr, p, s, 'o');
    printCanvas(cnv, fr);
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
  delete f[7];
  delete[] p;
  delete[] cnv;

  return statusCode;
}




top::HLine::HLine(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{
  if (len == 0) 
  {
    throw std::logic_error("USER invalid");
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
    throw std::invalid_argument("lenght can not be  <= 0");
  }
}

top::Square::Square(p_t p, int l)
{
  Square(p.x, p.y, l);
}

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
}

top::DLine::DLine(int x, int y, int len):
  start{x, y},
  length(len)
{}

top::p_t top::DLine::begin() const
{
  return start;
}

top::p_t top::DLine::next(p_t p) const
{
  if (p.x < start.x + length - 1) 
  {
    return {p.x + 1, p.y + 1};
  }
  return start;
}

top::Rectangle::Rectangle(int x, int y, int a, int b):
  start{x,y},
  a_(a),
  b_(b)
{}

top::p_t top::Rectangle::begin() const
{
  return start;
}

top::p_t top::Rectangle::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + a_ - 1) 
  {
    return {p.x, p.y + 1};
  } 
  else if (p.y == start.y + a_ - 1 && p.x < start.x + b_ - 1) 
  {
    return {p.x + 1, p.y};
  } 
  else if (p.x == start.x + b_ - 1 && p.y > start.y) 
  {
    return {p.x, p.y - 1};
  } 
  else if (p.y == start.y && p.x > start.x) 
  {
    return {p.x - 1, p.y};
  }
  return start;
}

top::Triangl::Triangl(int x, int y, int l):
  start{x, y},
  len(l)
{}

top::p_t top::Triangl::begin() const
{
  return start;
}

top::p_t top::Triangl::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + len - 1) 
  {
    return {p.x, p.y + 1};
  } 
  else if (p.y == start.y && p.x > start.x) 
  {
    return {p.x - 1, p.y};
  } 
  else 
  {
    return {p.x + 1, p.y - 1};
  }
  return start;
} 
