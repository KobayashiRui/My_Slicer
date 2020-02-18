#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "polyclipping/clipper.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

#include <Eigen/Dense>

#include "stl_read.h"
#include "slice_data.h"


#define accuracy 1e6
#define m2mm 1e3
#define line_diff 1e-6

static GLFWwindow*  aWindow;
static int          aWidth = 640;
static int          aHeight = 480;
static std::string  aTitle = "Line";
static int          camera_move_dead = 1;
static int          camera_move_sens = 3;
static int          cam_deg2_min = 1;
static int          cam_deg2_max = 160;

//プリンタの設定
static float nozzule = 0.4;
static float layer = 0.2;
static float filament = 1.75;



void make_line(std::vector<line>&,plane, triangle);
bool check_line(std::vector<line>&, line);
void make_polygon(std::vector<line>&, std::vector<point>&);
void make_polygon2(std::vector<line>&, std::vector<point>&);
void drawLine(std::vector<std::vector<point>>);
void make_offset(std::vector<std::vector<point>>&, std::vector<std::vector<point>>&); //ポリゴンデータの配列, オフセット生成後のデータ
void make_gcode(std::vector<std::vector<point>>&, std::ofstream&); 
void addPoint(int , int , ClipperLib::Path *);
point float2int(point);
float round_n(float, float);

//OpenGL用
double cam_deg1 = 45, cam_deg2 = 1;
double cam_length = 100;
double mousex, mousey, old_mousex, old_mousey;
bool flag = false;

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



  std::vector<std::vector<std::vector<point>>> layer_polygons; //各レイヤのごとにポリゴンデータ格納す
  std::vector<std::vector<std::vector<point>>> layer_polygons_2; //各レイヤのごとにポリゴンデータ縮小処理済み

  //TODO STLのサイズに合わせてルプ数を決定する
  std::vector<line> line_datas;
  for(int i = 0; i < 1; i++){
  //for(int i = 0; i < 1; i++){

    std::cout << "Count: " << i << std::endl;
    //線分データをクリア
    line_datas.clear();

    //平面の定義
    point origin = point(0, 0, (i+1 )* layer);
    point plane_normal = point(0, 0, 1);
    plane slice_plane = plane(origin, plane_normal);

    //line segumentの作成
    //交点の計算(線分を求める)
    int count_make_line = 0;
    for (auto t : info.triangles) {
      make_line(line_datas,slice_plane, t); //slice_planeにてスライスした結果の線分がline_datasに格納される
      count_make_line ++;
    }
    //std::cout << "END line" << std::endl;

    std::vector<point> polygon;
    std::vector<std::vector<point>> polygons;

    //line segumentの並びかえ
    //TODO x,yの最小を最初に選択するようにする?
    //line_datasがなくなるまでループする
    while(true){
      //polygon内の要素を全て削除
      //std::cout << "line_size " << line_datas.size() << std::endl;
      polygon.clear();
      //polygonの作成
      //std::cout << "Make Polygon" << std::endl;
      make_polygon2(line_datas, polygon);
      //std::cout << "END Polygon:" << polygon.size() << std::endl;
      //polygonsへ追加
      if(polygon.size() >= 3){
        polygons.push_back(polygon);
      }
      //line_datasのサイズを確認
      if(line_datas.size() < 3){
        break;
      }
    }
    //std::cout << "Poygon num:" << polygons.size() << std::endl;

    //layerデータを保存
    layer_polygons.push_back(polygons);
  }
  std::cout << "END slice!!" <<std::endl;

  //ポリゴンの縮小
  std::vector<std::vector<point>> polygons;
  for(int i=0; i < layer_polygons.size(); i++){
    std::cout << "layer num: " << i << std::endl;
    polygons.clear();
    make_offset(layer_polygons[i], polygons);
    layer_polygons_2.push_back(polygons);
  }

  //Gコードの生成
  //最初のGコード
  //プリント用のGコード
  //レイヤーごとの処理
  std::ofstream gcode_file;
  std::string filename = "test.gcode";
  gcode_file.open(filename, std::ios::trunc);
  for(int i=0; i < layer_polygons_2.size(); i++){
    make_gcode(layer_polygons_2[i], gcode_file);
  }
  //最後のGコード

  gcode_file.close();

  std::cout << "Make Gcode" << std::endl;



  //openglにて表示

  /* GLFW3の初期化 */
  if(! glfwInit() )
  {
      std::cerr << "glfwInit failed." << std::endl;
      exit( EXIT_FAILURE );
  }

  //windowの作成
  aWindow = glfwCreateWindow( aWidth, aHeight, aTitle.c_str(), nullptr, nullptr );
  if(! aWindow )
  {
      std::cerr << "glfwCreateWindow failed." << std::endl;
      glfwTerminate();
      exit( EXIT_FAILURE );
  }

  glfwMakeContextCurrent( aWindow );

  // メインループ。
  while(! glfwWindowShouldClose( aWindow ))
  {
    //マウス操作(視点の回転)
    if( glfwGetMouseButton(aWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ) {
        glfwGetCursorPos(aWindow, &mousex, &mousey);
        if(old_mousex == -1 || old_mousey==-1){
            old_mousex = mousex;
            old_mousey = mousey;
        }
        if(mousex - old_mousex >= camera_move_dead){
            cam_deg1 -= camera_move_sens;
        }else if(mousex - old_mousex <= -1*camera_move_dead){
            cam_deg1 += camera_move_sens;
        }

        if(mousey -old_mousey >= camera_move_dead && cam_deg2 >= (camera_move_sens + cam_deg2_min) ){
            cam_deg2 -= camera_move_sens;
        }else if(mousey - old_mousey <= -1*camera_move_dead && cam_deg2 <= cam_deg2_max){
            cam_deg2 += camera_move_sens;
        }

        old_mousex = mousex;
        old_mousey = mousey;

    }else{
        mousex=-1;
        mousey=-1;
        old_mousex=-1;
        old_mousey=-1;
    }

    /* 初期化 */

    // 画面をクリア。
    glClear(GL_COLOR_BUFFER_BIT);
    // 変換行列の初期化。ここで初期化しないと延々と同じ行列に積算される。
    glLoadIdentity();
    /* 更新 */
    // 現在のウィンドウの大きさを取得。
    int width, height;
    glfwGetFramebufferSize( aWindow, &width, &height );
    // ビューポートの更新。
    glViewport( 0, 0, width, height );
    // 透視投影。 //これないと表示されない
    gluPerspective( 30.0, (double)width / (double)height, 1.0, 500.0 );
    
    //カメラ
    double cam_x,cam_y,cam_z;
    cam_x = cam_length * sin((cam_deg2*M_PI)/180)*cos((cam_deg1*M_PI)/180);
    cam_y = cam_length * sin((cam_deg2*M_PI)/180)*sin((cam_deg1*M_PI)/180);
    cam_z = cam_length * cos((cam_deg2*M_PI)/180);
    gluLookAt( cam_x, cam_y, cam_z,  0.0, 0.0, 0.0,  0.0, 0.0, 1.0 );


    for (int i =0; i < layer_polygons_2.size(); i++){
      drawLine(layer_polygons_2[i]);
    }
    //for (int i =0; i < layer_polygons.size(); i++){
    //  drawLine(layer_polygons[i]);
    //}

    /* ダブルバッファのスワップとイベントのポーリング */
    glfwSwapBuffers( aWindow );
    glfwPollEvents();
  }

  // GLFW3 の終了。
  glfwTerminate();
  return EXIT_SUCCESS;
}


/*///////////////////////////////// 
 *  ここから関数定義
*/////////////////////////////////

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
  //std::cout << "points" << "::A:" << A << ", B:" << B << ", C:" << C << std::endl;

  //各頂点が平面上にある = 終了
  if( abs(A) <= 0.00001 && abs(B) <= 0.00001 && abs(C) <= 0.00001){
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
    check_line_result = check_line(line_datas,line(line_points[0], line_points[1]) );
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
      check_line_result = check_line(line_datas,line(line_points[0], line_points[1]) );
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
      check_line_result = check_line(line_datas,line(line_points[0], line_points[1]) );
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
      check_line_result = check_line(line_datas,line(line_points[0], line_points[1]) );
      if(check_line_result){
        std::cout << "!!!!重複!!!!" << std::endl;
      }else{
        line_datas.push_back(line(line_points[0], line_points[1]));
      }
      return ;
    }
  }

  //if(line_points.size() == 1){
  //  line_datas.push_back(line(line_points[0], line_points[0]));
  //}

  
}

point float2int(point p)
{
  return point(p.x*accuracy, p.y*accuracy, p.z*accuracy);

}

bool check_line(std::vector<line>& line_datas, line line_data)
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


void make_polygon(std::vector<line>&line_datas, std::vector<point>&polygon)
{
  //とりあえず先頭の点データを取得
  bool end_flag = false;
  point search_p = line_datas[0].p1;
  point goal_p = line_datas[0].p2;
  //先頭のlineデータを削除
  polygon.push_back(search_p);
  line_datas.erase(line_datas.begin());
  int old_line_num = line_datas.size();

  double line_diff_p1, line_diff_p2;
  //goal_pに辿りつくまでループ
  double diff_acc = 1;
  while (!end_flag && line_datas.size()!=0 )
  {
    for(int idx=0; idx < line_datas.size(); idx++)
    {
      //線分の両端に対して距離を計算
      //std::cout << "length_p1: " << sqrt(pow(line_datas[idx].p1.x - search_p.x,2) + pow(line_datas[idx].p1.y - search_p.y,2) + pow(line_datas[idx].p1.z - search_p.z,2) ) << std::endl;
      //std::cout << "length_p2: " << sqrt(pow(line_datas[idx].p2.x - search_p.x,2) + pow(line_datas[idx].p2.y - search_p.y,2) + pow(line_datas[idx].p2.z - search_p.z,2) ) << std::endl;

      //p1とp2のline_diffを算出!
      line_diff_p1 = sqrt(pow(line_datas[idx].p1.x - search_p.x,2) + pow(line_datas[idx].p1.y - search_p.y,2) + pow(line_datas[idx].p1.z - search_p.z,2) );
      line_diff_p2 = sqrt(pow(line_datas[idx].p2.x - search_p.x,2) + pow(line_datas[idx].p2.y - search_p.y,2) + pow(line_datas[idx].p2.z - search_p.z,2) );
      //std::cout << "l1: " << line_diff_p1 << ", l2: " << line_diff_p2 << std::endl;
      

      if (line_diff_p1 <= (line_diff * diff_acc) || line_diff_p2 <= (line_diff* diff_acc) )
      {
        //std::cout <<  "line diff" << std::endl;
        diff_acc = 1;
        if(line_diff_p1 <= line_diff_p2 ) //ユークリッド距離の計算(p1)
        {
          //次のsearch_pを定義
          //std::cout << "ok p1" << std::endl;
          search_p = line_datas[idx].p2;
          polygon.push_back(line_datas[idx].p1);
          polygon.push_back(line_datas[idx].p2);
          line_datas.erase(line_datas.begin() + idx);
          //search_pとgoal_pの計算(ほぼ同じなら終了する)
          //std::cout << "goal diff : " << sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) << std::endl;
          if(sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) <= line_diff)
          {
            polygon.push_back(goal_p);
            end_flag = true;
          }
          break;
        }else {
          //次のsearch_pを定義
          //std::cout << "ok p2" << std::endl;
          search_p = line_datas[idx].p1;
          polygon.push_back(line_datas[idx].p2);
          polygon.push_back(line_datas[idx].p1);
          line_datas.erase(line_datas.begin() + idx);
          //search_pとgoal_pの計算(ほぼ同じなら終了する)
          //std::cout << "goal diff : " << sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) << std::endl;
          if(sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) <= line_diff)
          {
            polygon.push_back(goal_p);
            end_flag = true;
          }
          break;
        }

        //if(sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) == 0){
        //  std::cout << "END??" << std::endl;
        //    polygon.push_back(goal_p);
        //    end_flag = true;
        //    break;
        //}
      
      }

      
    }

    if(line_datas.size()- old_line_num == 0){
      //std::cout << "force " << std::endl;

      //std::cout << "line num" << line_datas.size() << std::endl;
      if(diff_acc > 100000){
        polygon.clear();
        break;
      }
      diff_acc *= 10;
      //break;

    }else{
      old_line_num = line_datas.size();
    }
  }
}

void make_polygon2(std::vector<line>&line_datas, std::vector<point>&polygon)
{
  //とりあえず先頭の点データを取得
  bool end_flag = false;
  point search_p = line_datas[0].p1;
  point goal_p = line_datas[0].p2;
  //先頭のlineデータを削除
  polygon.push_back(search_p);
  line_datas.erase(line_datas.begin());
  int old_line_num = line_datas.size();

  double line_diff_p1, line_diff_p2;
  //goal_pに辿りつくまでループ
  double diff_acc = 1;
  while (!end_flag && line_datas.size()!=0 )
  {
    double most_small = -1;
    double most_small_idx = -1;
    bool reverse = false;

    for(int idx=0; idx < line_datas.size(); idx++)
    {
      //線分の両端に対して距離を計算
      //std::cout << "length_p1: " << sqrt(pow(line_datas[idx].p1.x - search_p.x,2) + pow(line_datas[idx].p1.y - search_p.y,2) + pow(line_datas[idx].p1.z - search_p.z,2) ) << std::endl;
      //std::cout << "length_p2: " << sqrt(pow(line_datas[idx].p2.x - search_p.x,2) + pow(line_datas[idx].p2.y - search_p.y,2) + pow(line_datas[idx].p2.z - search_p.z,2) ) << std::endl;

      //p1とp2のline_diffを算出!
      line_diff_p1 = sqrt(pow(line_datas[idx].p1.x - search_p.x,2) + pow(line_datas[idx].p1.y - search_p.y,2) + pow(line_datas[idx].p1.z - search_p.z,2) );
      line_diff_p2 = sqrt(pow(line_datas[idx].p2.x - search_p.x,2) + pow(line_datas[idx].p2.y - search_p.y,2) + pow(line_datas[idx].p2.z - search_p.z,2) );
      //std::cout << "l1: " << line_diff_p1 << ", l2: " << line_diff_p2 << std::endl;
      //初期値を代入
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

      if(most_small == 0){
        break;
      }
      //std::cout << "most small" << most_small << std::endl;
      
    }

      
    if(most_small <= 0.00001*accuracy)
    {
      //std::cout << "goal small" << most_small << std::endl;
      if(!reverse) 
      {
        search_p = line_datas[most_small_idx].p2;
        //std::cout << "p1:" << line_datas[most_small_idx].p1.x <<  std::endl;
        //std::cout << "p2:" << line_datas[most_small_idx].p2 << std::endl;
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
     //std::cout << "dff : " << (sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ))<< std::endl;

      if(sqrt(pow(goal_p.x - search_p.x,2) + pow(goal_p.y - search_p.y,2) + pow(goal_p.z - search_p.z,2) ) <= line_diff* accuracy)
      {
        polygon.push_back(goal_p);
        end_flag = true;
        break;
      }

    }
    

    if(line_datas.size()- old_line_num == 0){
      //std::cout << "force " << std::endl;

      polygon.clear();
      //std::cout << "line num" << line_datas.size() << std::endl;
        break;

    }else{
      old_line_num = line_datas.size();
    }
  }
}


void drawLine(std::vector<std::vector<point>> polygons)
{
  for(int i =0; i < polygons.size(); i++){
  //for(int i =0; i < 3; i++){
    //一つのポリゴンを取得 polygons[i]
    glColor3f(1.0, 0.5*i, 0.1*i/2);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    //glBegin(GL_LINE_STRIP);

    //glPointSize(5);
    //glBegin(GL_POINTS);
    
    for(int j =0; j < polygons[i].size(); j++){
      //1つのポイントを取得 polygons[i][j]
      glVertex3d(polygons[i][j].x/accuracy, polygons[i][j].y/accuracy, polygons[i][j].z/accuracy);
    }
    glEnd();
  }
}

void addPoint(int x, int y, ClipperLib::Path *path)
{
    ClipperLib::IntPoint ip;
    ip.X = x;
    ip.Y = y;
    path->push_back(ip);
}
void make_offset(std::vector<std::vector<point>>& polygons_data, std::vector<std::vector<point>>& result_polygons_data)
{
  ClipperLib::Paths subj,solution;
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
    //co.AddPath(p, ClipperLib::jtSquare, ClipperLib::etClosedPolygon);
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
    //std::cout << "面積: " << ClipperLib::Area(subj[i]) << std::endl;
  }

  co.AddPaths(subj, ClipperLib::jtRound, ClipperLib::etClosedPolygon);
  //co.AddPaths(subj, ClipperLib::jtSquare, ClipperLib::etClosedPolygon);
  int offset_num = 0;
  int count = 0;
  while(true)
  {
    //std::cout << "Count :" << count << std::endl;
      co.Execute(solution, offset_num);
      //std::cout << "solution size: " << solution.size() << std::endl;
      if(solution.size()== 0){
          break;
      }
      for(int i=0; i < solution.size(); i++){
        polygon.clear();
        for(int j=0; j< solution[i].size(); j++)
        {
          polygon.push_back(point((float)solution[i][j].X, (float)solution[i][j].Y, (float)z_data));
        }
        result_polygons_data.push_back(polygon);
      }
      offset_num -=0.4*accuracy;
      count +=1;
      //break;
  }
}


void make_gcode(std::vector<std::vector<point>>& polygons, std::ofstream& gcode_file)
{
  //一つのポリゴンを取得
  for(int i=0; i < polygons.size(); i++)
  {
    //スタート点を設定
    point start_point = polygons[i][0];
    float marume = 4;

    //スタート点への移動 押し出しなし
    gcode_file << "G0" << " X" << round_n(start_point.x/accuracy, marume) << " Y" << round_n(start_point.y/accuracy, marume) << " Z" << round_n(start_point.z/accuracy, marume) << std::endl;
    //ポリゴン内の点を取得
    for(int j=1; j < polygons[i].size()+1; j++)
    {
      //距離の計算
      if(j < polygons[i].size()){
        float L = sqrt(pow((polygons[i][j].x - polygons[i][j-1].x)/accuracy,2) + pow((polygons[i][j].y - polygons[i][j-1].y)/accuracy ,2) + pow((polygons[i][j].z - polygons[i][j-1].z)/accuracy ,2) );
        float E = nozzule * layer * L / pow(filament,2) ;
        gcode_file << "G1" << " X" << round_n(polygons[i][j].x/accuracy, marume) << " Y" << round_n(polygons[i][j].y/accuracy, marume) << " Z" << round_n(polygons[i][j].z/accuracy, marume) << " E" << round_n(E, marume) << std::endl;
      }else{
        float L = sqrt(pow((polygons[i][j-1].x - start_point.x)/accuracy,2) + pow((polygons[i][j-1].y - start_point.y)/accuracy ,2) + pow((polygons[i][j-1].z - start_point.z)/accuracy ,2) );
        float E = nozzule * layer * L / pow(filament,2) ;
        gcode_file << "G1" << " X" << round_n(start_point.x/accuracy, marume) << " Y" << round_n(start_point.y/accuracy, marume) << " Z" << round_n(start_point.z/accuracy, marume) << " E" << round_n(E, marume) << std::endl;
      }

    }
  }
}


float round_n(float number, float n)
{
    number = number * pow(10,n-1); //四捨五入したい値を10の(n-1)乗倍する。
    number = round(number); //小数点以下を四捨五入する。
    number /= pow(10, n-1); //10の(n-1)乗で割る。
    return number;
}