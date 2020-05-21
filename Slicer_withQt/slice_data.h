/*
 *Slicingで使用するデータ構造
*/
#ifndef SLICE_DATA_H
#define SLICE_DATA_H

#include <string>
#include <vector>

struct point {
  float x;
  float y;
  float z;

  point() : x(0), y(0), z(0) {}
  point(float xp, float yp, float zp) : x(xp), y(yp), z(zp) {}
};

struct point_i {
  int x;
  int y;
  int z;

  point_i() : x(0), y(0), z(0) {}
  point_i(int xp, int yp, int zp) : x(xp), y(yp), z(zp) {}
};

struct triangle {
  //point normal;
  point v1;
  point v2;
  point v3;
  triangle(point v1p, point v2p, point v3p) :
     v1(v1p), v2(v2p), v3(v3p) {}
};

//std::ostream& operator<<(std::ostream& out, const triangle& t);

struct stl_data {
  std::string name;
  std::vector<triangle> triangles;

  stl_data(std::string namep) : name(namep) {}
  stl_data() : name("test") {}
};

//stl_data parse_stl(const std::string& stl_path);


struct line {
    point p1;
    point p2;

    line(point _p1, point _p2) : p1(_p1), p2(_p2) {}
};

struct plane {
    point p;
    point normal;

    plane(point _p, point _normal) : p(_p), normal(_normal) {}
};


#endif