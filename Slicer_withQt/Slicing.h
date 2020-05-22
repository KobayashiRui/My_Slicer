/*
 * スライサーの処理部分
*/
#include "slice_data.h"
#include "polyclipping/clipper.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

#include <Eigen/Dense>


class Slicing
{
    private:

        void makeLine(std::vector<line>&,plane, triangle); //三角形と平面から線分を取り出す
        bool checkLine(std::vector<line>&, line); //重複判定をする関数

        void makePolygon(std::vector<line>&, std::vector<point>&); //ポリゴンデータを生成する

        void makeOffset(std::vector<std::vector<point>>&, std::vector<std::vector<point>>&); //ポリゴンデータの配列, オフセット生成後のデータ
        void addPoint(int , int , ClipperLib::Path *);
        void searchStartPoint(ClipperLib::Path &, int *, int &);
        void sortPolygon(ClipperLib::Path &, ClipperLib::Path &, int & , int *); //solutioポリゴン, sortedポリゴン, start idex, start point

        void make_gcode(std::vector<std::vector<point>>&, std::ofstream&, float&); 

        point float2int(point);
        float round_n(float, float);
        



    public:
        float ACCURACY;
        float M2MM;
        float LINE_DIFF;
        int WALL_THICKNESS;
        bool INFILL;
        float NOZZULE;
        float LAYER;
        float FILAMENT;

        Slicing();
        stl_data mesh_triangles;
        std::vector<std::vector<std::vector<point>>> layer_polygons_end; //各レイヤのごとにポリゴンデータ縮小処理済み
        std::vector<std::vector<std::vector<point>>> after_rotation_layer_polygons_end; //回転前のデータ
        bool ArcMode = false; //扇状スライサのON,OFF
        void SliceData();

};