#include <iostream>
#include <cstddef>
namespace top
{
  struct p_t
  {
    int x, y;
  };
  struct IDraw
  {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };
  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }
  bool operator!=(p_t a, p_t b)
  {
    return a.x != b.x || a.y != b.y;
  }
  struct Dot: IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t o;
    Dot(int x, int y);
    explicit Dot(p_t dd);
  };
  struct frame_t
  {
    p_t left_bot;
    p_t right_tot;
  };
  void make_f(IDraw ** b, size_t k);
  void get_points(IDraw * b, p_t ** ps, size_t & s);
  frame_t build_frame(const p_t * pts, size_t s);
  char * build_canvas(frame_t f);
  void paint_canvas(char * cnv, frame_t fr, const p_t * ps, size_t k, char f);
  void print_canvas(const char * cnv, frame_t fr);
  struct VLine : IDraw
  {
    VLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
  struct HLine : IDraw
  {
    HLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
  struct Square : IDraw
  {
    Square(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
}
int main()
{
  using namespace top;
  IDraw * f[3] = {};
  p_t * p = nullptr;
  char * cnv = nullptr;
  size_t s = 0;
  int err = 0;
  try
  {
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(f[i], & p, s);
    }
    frame_t fr = build_frame(p, s);
    cnv = build_canvas(fr);
    paint_canvas(cnv, fr, p, s, '#');
    print_canvas(cnv, fr);
  }
  catch(...)
  {
    err = 1;
  }
  delete[] f[0];
  delete[] f[1];
  delete[] f[2];
  delete[] p;
  delete[] cnv;
  return err;
}
void extend(top::p_t ** pts, size_t s, top::p_t p)
{
  top::p_t * res = new top::p_t [s + 1];
  for (size_t i = 0; i < s; ++i)
  {
    res[i] = (*pts)[i];
  }
  res[s] = p;
  delete[] * pts;
  *pts = res;
}
size_t top::points(const IDraw & d, p_t ** pts, size_t s)
{
  p_t p = d.begin();
  extend(pts, s, p);
  size_t delta = 1;
  while(d.next(p) != d.begin())
  {
    p = d.next(p);
    extend(pts, s + delta, p);
    ++delta;
  }
  return delta;
}
top::Dot::Dot(int x, int y):
IDraw(), o{x, y}
{}
top::p_t top::Dot::begin() const 
{
  return o;
}
top::p_t top::Dot::next(p_t) const
{
  return begin();
}
void top::make_f(IDraw ** f, size_t k)
{
}
void top::get_points(IDraw * b, p_t ** ps, size_t & s)
{
}
top::frame_t top::build_frame(const p_t * pts, size_t s)
{
  if (!s)
  {
    throw std::logic_error("bad size");
  }
  int minx = pts[0].x, maxx = minx;
  int miny = pts[0], maxy = miny;
  for (size_t i = 1; i < s; ++i)
  {
    minx = std::min(minx, pts[i].x);
    maxx = std::max(maxx, pts[i].x);
    miny = std::min(miny, pts[i].y);
    maxy = std::max(maxy, pts[i].y);
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}
char * top::build_canvas(frame_t fr)
{
}
void top::paint_canvas(char * cnv, frame_t fr, const p_t * ps, size_t k, char f)
{
}
void top::print_canvas(const char * cnv, frame_t fr)
{
}
top::VLine::VLine(int x, int y, int len) : IDraw(), start{x,y}, length(len)
{}
top::p_t top::VLine::begin() const
{
  return start;
}
top::p_t top::VLine::next(p_t p) const
{
  if (p.y == start.y + length) {
    return start;
  }
  return p_t{start.x, p.y + 1};
}
top::HLine::HLine(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{}
top::p_t top::HLine::begin() const
{
  return start;
}
top::p_t top::HLine::next(p_t p) const
{
  if (p.x == start.x + length) {
    return start;
  }
  return p_t{p.x + 1, start.y };
}
top::Square::Square(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{}
top::p_t top::Square::begin() const
{
  return start;
}
top::p_t top::Square::next(p_t p) const
{
  if (p.y == start.y && p.x < start.x + length) {
    return p_t{p.x + 1, p.y};
  } else if (p.x == start.x + length && p.y < start.y + length) {
    return p_t{p.x, p.y + 1};
  } else if (p.y == start.y + length && p.x > start.x) {
    return p_t{p.x - 1, p.y};
  } else if (p.x == start.x && p.y > start.y) {
    return p_t{p.x, p.y - 1};
  }
  return start;
}
