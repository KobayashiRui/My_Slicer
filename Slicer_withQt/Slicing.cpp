/*
 * スライサーの処理部分
*/
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

#include "slice_data.h"
#include "Slicing.h"

Slicing::Slicing(){
    ACCURACY = 1e6;
    M2MM = 1e3;
    LINE_DIFF = 1e-6;
    WALL_THICKNESS =3;
    INFILL = true;
    NOZZULE = 0.4;
    LAYER = 0.5;
    FILAMENT = 1.75;
}

//スライスを行う
void Slicing::SliceData()
{
    std::cout << "start slicing !!" << std::endl;

  std::vector<std::vector<std::vector<point>>> layer_polygons; //各レイヤのごとにポリゴンデータ格納す
  std::vector<line> line_datas; //三角形をスライスした結果の線分データを保存する

  layer_polygons.clear();
  for(int i=0; ; i++)
  {
        line_datas.clear();

        //平面データの定義
        point origin = point(0, 0, (i+0 )* LAYER);
        point plane_normal = point(0, 0, 1);
        plane slice_plane = plane(origin, plane_normal);

        //線分を求める
        //std::cout << "get line" << std::endl;
        for(int j = 0; j < mesh_triangles.triangles.size(); j++){
            makeLine(line_datas,slice_plane, mesh_triangles.triangles[j]);
        }

        if(line_datas.size() == 0){
            break;
        }

        //一周分のポリゴンを作成する
        //std::cout << "make polygon" << std::endl;
        std::vector<point> polygon_buf;
        std::vector<std::vector<point>> polygons_buf;
        while(true){
            polygon_buf.clear();
            makePolygon(line_datas,polygon_buf);

            if(polygon_buf.size()>=3){
                polygons_buf.push_back(polygon_buf);
            }

            if(line_datas.size() < 3){
                break;
            }
        }
        layer_polygons.push_back(polygons_buf);
  }

  //std::vector<std::vector<std::vector<point>>> layer_polygons_end; //各レイヤのごとにポリゴンデータ縮小処理済み

  //オフセットを作成
  layer_polygons_end.clear();
  std::vector<std::vector<point>> polygons_buf2;
  for(int i = 0; i < layer_polygons.size(); i++){
     polygons_buf2.clear(); 
     makeOffset(layer_polygons[i], polygons_buf2);
     layer_polygons_end.push_back(polygons_buf2);
  }
  std::cout << "End Slicing" << std::endl;
}

void Slicing::makeLine(std::vector<line>&line_datas ,plane _plane, triangle _triangle)
{
  //垂線距離を求める
  Eigen::Vector3f p_normal, ap, bp, cp; //平面の法線, 頂点1, 頂点2, 頂点3
  p_normal << _plane.normal.x, _plane.normal.y, _plane.normal.z;
  ap << _triangle.v1.x - _plane.p.x,  _triangle.v1.y - _plane.p.y, _triangle.v1.z - _plane.p.z;
  bp << _triangle.v2.x - _plane.p.x,  _triangle.v2.y - _plane.p.y, _triangle.v2.z - _plane.p.z;
  cp << _triangle.v3.x - _plane.p.x,  _triangle.v3.y - _plane.p.y, _triangle.v3.z - _plane.p.z;


  //TODO　最適化
  float A = (std::round(p_normal.dot(ap)*ACCURACY))/ACCURACY;
  float B = (std::round(p_normal.dot(bp)*ACCURACY))/ACCURACY;
  float C = (std::round(p_normal.dot(cp)*ACCURACY))/ACCURACY;

  //各頂点が平面上にある = 終了
  if( abs(A) <= 0.00001 && abs(B) <= 0.00001 && abs(C) <= 0.00001)
  {
    return ;
  }

  bool check_line_result;


  std::vector<point> line_points;
  
  //平面上にある頂点を取得
  if( abs(A) <= 0.00001){
    line_points.push_back( float2int(_triangle.v1) );
  }
  if( abs(B) <= 0.00001){
    line_points.push_back( float2int(_triangle.v2) );
  }
  if( abs(C) <= 0.00001){
    line_points.push_back( float2int(_triangle.v3) );
  }

  //2頂点による線が決まればこれで終了
  if( line_points.size() == 2){
    //重複判定
    check_line_result = checkLine(line_datas,line(line_points[0], line_points[1]) );
      if(check_line_result){
        std::cout << "!!!!重複!!!!" << std::endl;
      }else{
        line_datas.push_back(line(line_points[0], line_points[1]));
      }
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
    line_points.push_back( float2int(point(ab(0)+_triangle.v1.x,ab(1)+_triangle.v1.y,ab(2)+_triangle.v1.z)) );
    //2頂点による線が決まればこれで終了
    if( line_points.size() == 2){
      //チェック
      check_line_result = checkLine(line_datas,line(line_points[0], line_points[1]) );
      if(check_line_result){
        std::cout << "!!!!重複!!!!" << std::endl;
      }else{
        line_datas.push_back( line(line_points[0], line_points[1]));
      }
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
    line_points.push_back( float2int(point(bc(0)+_triangle.v2.x,bc(1)+_triangle.v2.y,bc(2)+_triangle.v2.z)));
    //2頂点による線が決まればこれで終了
    if( line_points.size() == 2){
      //重複判定
      check_line_result = checkLine(line_datas,line(line_points[0], line_points[1]) );
      if(check_line_result){
        std::cout << "!!!!重複!!!!" << std::endl;
      }else{
        line_datas.push_back(line(line_points[0], line_points[1]));
      }
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
    line_points.push_back( float2int(point(ac(0)+_triangle.v1.x,ac(1)+_triangle.v1.y,ac(2)+_triangle.v1.z)));
    //2頂点による線が決まればこれで終了
    if( line_points.size() == 2){
      //重複判定
      check_line_result = checkLine(line_datas,line(line_points[0], line_points[1]) );
      if(check_line_result){
        std::cout << "!!!!重複!!!!" << std::endl;
      }else{
        line_datas.push_back(line(line_points[0], line_points[1]));
      }
      return ;
    }
  }
  
}



bool Slicing::checkLine(std::vector<line>& line_datas, line line_data)
{
  //重複を検索
  point line_p1 = line_data.p1;
  point line_p2 = line_data.p2;

  for(int i =0 ; i < line_datas.size(); i++)
  {
    //p1とlineのp1が同じ
    if(line_datas[i].p1.x == line_p1.x && line_datas[i].p1.y == line_p1.y && line_datas[i].p1.z == line_p1.z)
    {
      //p2とline_p2が同じ
      if(line_datas[i].p2.x == line_p2.x && line_datas[i].p2.y == line_p2.y && line_datas[i].p2.z == line_p2.z)
      {
        //重複判定
        return true;
      }
    //p2とlineのp1が同じ
    }else if(line_datas[i].p2.x == line_p1.x && line_datas[i].p2.y == line_p1.y && line_datas[i].p2.z == line_p1.z)
    {
      //p1とline_p2が同じ
      if(line_datas[i].p1.x == line_p2.x && line_datas[i].p1.y == line_p2.y && line_datas[i].p1.z == line_p2.z)
      {
        //重複判定
        return true;
      }
    }
  } 
  //非重複
  return false;

}


void Slicing::makePolygon(std::vector<line>&line_datas, std::vector<point>&polygon)
{
  //先頭の点データを取得
  bool end_flag = false;
  point search_p = line_datas[0].p1;
  point goal_p = line_datas[0].p2;

  //先頭のlineデータを削除
  polygon.push_back(search_p);
  line_datas.erase(line_datas.begin());
  int old_line_num = line_datas.size();

  double line_diff_p1, line_diff_p2;
  //goal_pに辿りつくまでループ
  while (!end_flag && line_datas.size()!=0 )
  {
    double most_small = -1;
    double most_small_idx = -1;
    bool reverse = false;

    for(int idx=0; idx < line_datas.size(); idx++)
    {
      //p1とp2のline_diffを算出!
      line_diff_p1 = sqrt(pow(line_datas[idx].p1.x - search_p.x,2) + pow(line_datas[idx].p1.y - search_p.y,2) + pow(line_datas[idx].p1.z - search_p.z,2) );
      line_diff_p2 = sqrt(pow(line_datas[idx].p2.x - search_p.x,2) + pow(line_datas[idx].p2.y - search_p.y,2) + pow(line_datas[idx].p2.z - search_p.z,2) );

      //-1の場合 初期値を代入
      if(most_small == -1){
        if(line_diff_p1 <= line_diff_p2){
          most_small = line_diff_p1;
          most_small_idx = idx;
          reverse = false;
        }else{
          most_small = line_diff_p2;
          most_small_idx = idx;
          reverse = true;
        }
      }

      //最小か比較
      if(line_diff_p1 < most_small ){
          most_small = line_diff_p1;
          most_small_idx = idx;
          reverse = false;
      }

      if(line_diff_p2 < most_small){
        most_small = line_diff_p2;
        most_small_idx = idx;
        reverse = true;
      }

      //最小値が0なら即終了
      if(most_small == 0){
        break;
      }
      
    }

      
    if(most_small <= 0.00001*ACCURACY)
    {
      if(!reverse) 
      {
        search_p = line_datas[most_small_idx].p2;
        polygon.push_back(line_datas[most_small_idx].p1);
        polygon.push_back(line_datas[most_small_idx].p2);
        line_datas.erase(line_datas.begin() + most_small_idx);
      }else
      {
        search_p = line_datas[most_small_idx].p1;
        polygon.push_back(line_datas[most_small_idx].p2);
        polygon.push_back(line_datas[most_small_idx].p1);
        line_datas.erase(line_datas.begin() + most_small_idx);
      }

      if(sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) <= LINE_DIFF * ACCURACY)
      {
        polygon.push_back(goal_p);
        end_flag = true;
        break;
      }

    }
    

    if(line_datas.size()- old_line_num == 0){
        polygon.clear();
        break;

    }else{
        old_line_num = line_datas.size();
    }
  }
}

void Slicing::makeOffset(std::vector<std::vector<point>>& polygons_data, std::vector<std::vector<point>>& result_polygons_data)
{
  ClipperLib::Paths subj,solution,solution_opt;
  ClipperLib::Path p;
  std::vector<point> polygon;
  ClipperLib::ClipperOffset co;
  
  int z_data = polygons_data[0][0].z;
  
  for(int i=0; i < polygons_data.size(); i++)
  {
    p.clear();
    for(int j=0; j < polygons_data[i].size(); j++)
    {
      addPoint((int)polygons_data[i][j].x, (int)polygons_data[i][j].y, &p);
    }
    subj.push_back(p);

  }

  //ポリゴンをきれいにする
  ClipperLib::SimplifyPolygons(subj);

  //面積が小さいものは削除する
  for(int i=0; i < subj.size(); i++)
  {
    double area = ClipperLib::Area(subj[i]);
    if(area >= 0  && area <= 1e11){
      subj.erase(subj.begin()+ i);
    }
  }

  co.AddPaths(subj, ClipperLib::jtMiter, ClipperLib::etClosedPolygon);
  int offset_num = 0;
  int count = 0;
  int start_point[] = {0,0}; //開始地点
  ClipperLib::Path solution_buf;
  for(int i=0; i < WALL_THICKNESS; i++)
  {
    //std::cout << "Count :" << count << std::endl;
      co.Execute(solution, offset_num);
      solution_opt.clear();
      //std::cout << "solution size: " << solution.size() << std::endl;
      if(solution.size()== 0){
          break;
      }

      //#########経路の最適化###########################
      //start_posに一番近い地点を求める
      for(int i=0; i < solution.size(); i++){
        int polygon_start_index = 0;
        //std::cout << "start_point :: " << start_point[0] << ", " << start_point[1] << std::endl;
        searchStartPoint(solution[i], start_point, polygon_start_index);
        //std::cout << "polygon start index :: " << polygon_start_index << std::endl;
        //順番を入れ替える
        solution_buf.clear();
        sortPolygon(solution[i], solution_buf, polygon_start_index, start_point);
        solution_opt.push_back(solution_buf);
      }

      solution = solution_opt;
      //solution_opt.reserve(solution.size()); //solutionのサイズ分メモリを確保


      for(int i=0; i < solution.size(); i++){
        polygon.clear();
        for(int j=0; j< solution[i].size(); j++)
        {
          polygon.push_back(point((float)solution[i][j].X, (float)solution[i][j].Y, (float)z_data));
        }
        polygon.push_back(point((float)solution[i][0].X, (float)solution[i][0].Y, (float)z_data));
        result_polygons_data.push_back(polygon);
      }
      offset_num -=0.4 * ACCURACY;
      count +=1;
      //インフィルがいらない場合
      if(!INFILL){ 
        break;
      }
  }
}

void Slicing::addPoint(int x, int y, ClipperLib::Path *path)
{
    ClipperLib::IntPoint ip;
    ip.X = x;
    ip.Y = y;
    path->push_back(ip);
}

void Slicing::searchStartPoint(ClipperLib::Path &path, int * start_point, int &polygon_start_index){
  int most_small = sqrt(pow(path[0].X - start_point[0],2) + pow(path[0].Y - start_point[1],2) );;
  for(int i=0; i < path.size(); i++){
    float result = sqrt(pow(path[i].X - start_point[0],2) + pow(path[i].Y - start_point[1],2));
    if(most_small > result ) {
      most_small = result;
      polygon_start_index = i;
    }
  }
}


void Slicing::sortPolygon(ClipperLib::Path &solution_path, ClipperLib::Path &sorted_path, int &start_index, int *start_point){
  for(int i = start_index; i < solution_path.size(); i++){
    sorted_path.push_back(solution_path[i]);
  }
  for(int i =0; i < start_index; i++){
    sorted_path.push_back(solution_path[i]);
  }
  start_point[0] = solution_path[start_index].X;
  start_point[1] = solution_path[start_index].Y;
}


point Slicing::float2int(point p)
{
  return point(p.x * ACCURACY, p.y * ACCURACY, p.z * ACCURACY);

}

float Slicing::round_n(float number, float n)
{
    number = number * pow(10,n-1) + 0.5; //四捨五入したい値を10の(n-1)乗倍する。
    number = round(number); //小数点以下を四捨五入する。
    number /= pow(10, n-1); //10の(n-1)乗で割る。
    return number;
}