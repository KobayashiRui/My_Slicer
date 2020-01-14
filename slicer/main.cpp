#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

#include <Eigen/Dense>

#include "stl_read.h"
#include "slice_data.h"

#define accuracy 100000

void make_line(std::vector<line>&,plane, triangle);

int main(int argc, char *argv[])
{
  std::string stl_file_name;

  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
  }

  auto info = parse_stl(stl_file_name);

  std::vector<triangle> triangles = info.triangles;
  std::cout << "STL HEADER = " << info.name << std::endl;
  std::cout << "# triangles = " << triangles.size() << std::endl;
  std::cout << "End" << std::endl;
  //for (auto t : info.triangles) {
  //  std::cout << t << std::endl;
  //}

  //交点の計算(線分を求める)
  std::vector<line> line_datas;
  point origin = point(0,0,0.1);
  point plane_normal = point(0,0,1);
  plane slice_plane = plane(origin, plane_normal);

  for (auto t : info.triangles) {
    make_line(line_datas,slice_plane, t);
  }

  for (auto line : line_datas){
    std::cout << "LINE_DATA-----------" << std::endl;
    std::cout << "Data:" << line.p1.x << "," << line.p1.y << "," << line.p1.z << std::endl;
    std::cout << "Data:" << line.p2.x << "," << line.p2.y << "," << line.p2.z << std::endl;
    std::cout << "--------------------" << std::endl;
  }
  std::cout << "finish" << std::endl;

}

void make_line(std::vector<line>&line_datas ,plane _plane, triangle _triangle){
  //垂線距離を求める
  //平面の法線
  Eigen::Vector3f p_normal, ap, bp, cp; 
  p_normal << _plane.normal.x, _plane.normal.y, _plane.normal.z;
  //頂点1A
  ap << _triangle.v1.x - _plane.p.x,  _triangle.v1.y - _plane.p.y, _triangle.v1.z - _plane.p.z;
  //頂点2B
  bp << _triangle.v2.x - _plane.p.x,  _triangle.v2.y - _plane.p.y, _triangle.v2.z - _plane.p.z;
  //頂点3C
  cp << _triangle.v3.x - _plane.p.x,  _triangle.v3.y - _plane.p.y, _triangle.v3.z - _plane.p.z;


  //TODO　最適化
  float A = (std::round(p_normal.dot(ap)*accuracy))/accuracy;
  float B = (std::round(p_normal.dot(bp)*accuracy))/accuracy;
  float C = (std::round(p_normal.dot(cp)*accuracy))/accuracy;

  //各頂点が平面上にある = 終了
  if( A == 0 && B == 0 && C==0){
    return ;
  }


  std::vector<point> line_points;
  
  //平面上にある頂点を取得
  if( A == 0){
    line_points.push_back(_triangle.v1);
  }
  if( B == 0){
    line_points.push_back(_triangle.v2);
  }
  if( C == 0){
    line_points.push_back(_triangle.v3);
  }

  //2頂点による線が決まればこれで終了
  if( line_points.size() == 2){
    line_datas.push_back(line(line_points[0], line_points[1]));
    return ;
  }
  

  //辺ABについて
  if( (A > 0 && B < 0) || (A <0 && B >0)){
    //直線AB
    Eigen::Vector3f ab;
    ab <<  _triangle.v2.x - _triangle.v1.x, _triangle.v2.y - _triangle.v1.y, _triangle.v2.z - _triangle.v1.z;
    //比率を求める
    float rate = std::abs(A) / (std::abs(A) + std::abs(B));
    ab *= rate;
    line_points.push_back(point(ab(0)+_triangle.v1.x,ab(1)+_triangle.v1.y,ab(2)+_triangle.v1.z));
    //2頂点による線が決まればこれで終了
    if( line_points.size() == 2){
      line_datas.push_back(line(line_points[0], line_points[1]));
      return ;
    }
  }
  //辺BCについて
  if( (B > 0 && C < 0) || (B <0 && C >0)){
    //直線BC
    Eigen::Vector3f bc;
    bc <<  _triangle.v3.x - _triangle.v2.x, _triangle.v3.y - _triangle.v2.y, _triangle.v3.z - _triangle.v2.z;
    //比率を求める
    float rate = std::abs(B) / (std::abs(B) + std::abs(C));
    bc *= rate;
    line_points.push_back(point(bc(0)+_triangle.v2.x,bc(1)+_triangle.v2.y,bc(2)+_triangle.v2.z));
    //2頂点による線が決まればこれで終了
    if( line_points.size() == 2){
      line_datas.push_back(line(line_points[0], line_points[1]));
    return ;
    }

  }
  //辺ACについて
  if( (A > 0 && C < 0) || (A <0 && C >0)){
    //直線AC
    Eigen::Vector3f ac;
    ac <<  _triangle.v3.x - _triangle.v1.x, _triangle.v3.y - _triangle.v1.y, _triangle.v3.z - _triangle.v1.z;
    //比率を求める
    float rate = std::abs(A) / (std::abs(A) + std::abs(C));
    ac *= rate;
    line_points.push_back(point(ac(0)+_triangle.v1.x,ac(1)+_triangle.v1.y,ac(2)+_triangle.v1.z));
    //2頂点による線が決まればこれで終了
    if( line_points.size() == 2){
      line_datas.push_back(line(line_points[0], line_points[1]));
    return ;
    }
  }
  
}