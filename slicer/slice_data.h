#ifndef SLICE_DATA_H
#define SLICE_DATA_H

#include "stl_read.h"

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