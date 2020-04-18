#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

#include <Eigen/Dense>

#include "stl_read.h"
#include "slice_data.h"
#include "matplotlibcpp.h"

#define accuracy 100000
#define line_diff 0.0001

namespace plt = matplotlibcpp;

void make_line(std::vector<line>&,plane, triangle);
void make_polygon(std::vector<line>&, std::vector<point>&);

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

  std::vector<line> line_datas;

  //平面の定義
  point origin = point(0,0,0.1);
  point plane_normal = point(0,0,1);
  plane slice_plane = plane(origin, plane_normal);

  //line segumentの作成
  //交点の計算(線分を求める)
  for (auto t : info.triangles) {
    make_line(line_datas,slice_plane, t);
  }

  std::vector<point> polygon;
  std::vector<std::vector<point>> polygons;

  //line segumentの並びかえ
  //TODO x,yの最小を最初に選択するようにする?
  //line_datasがなくなるまでループする
  int iter = 0;
  while(true){
    std::cout << "number: " << iter << std::endl;
    //polygon内の要素を全て削除
    polygon.clear();
    //polygonの作成
    make_polygon(line_datas, polygon);
    //polygonsへ追加
    polygons.push_back(polygon);
    //line_datasのサイズを確認
    if(line_datas.size() == 0){
      break;
    }
    iter++;
  }


  for(int poly=0; poly < polygons.size(); poly++)
  {
    std::vector<double> x_row,y_row,z_row;
    //std::vector<double> x2_row,y2_row,z2_row;
    for(int idx=0; idx < polygons[poly].size(); idx++)
    {
      x_row.push_back(polygons[poly][idx].x);
      y_row.push_back(polygons[poly][idx].y);
    }
    x_row.push_back(polygons[poly][0].x);
    y_row.push_back(polygons[poly][0].y);
    plt::plot(x_row,y_row);
  }



  plt::show();
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

void make_polygon(std::vector<line>&line_datas, std::vector<point>&polygon)
{
  //とりあえず先頭の点データを取得
  bool end_flag = false;
  point search_p = line_datas[0].p1;
  point goal_p = line_datas[0].p2;
  //先頭のlineデータを削除
  polygon.push_back(search_p);
  line_datas.erase(line_datas.begin());

  //goal_pに辿りつくまでループ
  while (!end_flag)
  {
    for(int idx=0; idx < line_datas.size(); idx++)
    {
      
      //線分の両端に対して距離を計算
      if(sqrt(pow(line_datas[idx].p1.x - search_p.x,2) + pow(line_datas[idx].p1.y - search_p.y,2) + pow(line_datas[idx].p1.z - search_p.z,2) ) < line_diff) //ユークリッド距離の計算(p1)
      {
        //次のsearch_pを定義
        search_p = line_datas[idx].p2;
        polygon.push_back(line_datas[idx].p1);
        polygon.push_back(line_datas[idx].p2);
        line_datas.erase(line_datas.begin() + idx);
        //search_pとgoal_pの計算(ほぼ同じなら終了する)
        if(sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) < line_diff)
        {
          polygon.push_back(goal_p);
          end_flag = true;
        }
        break;
      }else if(sqrt(pow(line_datas[idx].p2.x - search_p.x,2) + pow(line_datas[idx].p2.y - search_p.y,2) + pow(line_datas[idx].p2.z - search_p.z,2) ) < line_diff)//ユークリッド距離の計算(p2)
      {
        //次のsearch_pを定義
        search_p = line_datas[idx].p1;
        polygon.push_back(line_datas[idx].p2);
        polygon.push_back(line_datas[idx].p1);
        line_datas.erase(line_datas.begin() + idx);
        //search_pとgoal_pの計算(ほぼ同じなら終了する)
        if(sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) < line_diff)
        {
          polygon.push_back(goal_p);
          end_flag = true;
        }
        break;

      }
    }
  }
}