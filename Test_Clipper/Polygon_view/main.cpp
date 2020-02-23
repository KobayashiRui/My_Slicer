#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "polyclipping/clipper.hpp"
#include <iostream>
#include <cmath>
 
using namespace ClipperLib;

static GLFWwindow*  aWindow;
static int          aWidth = 640;
static int          aHeight = 480;
static std::string  aTitle = "Line";
bool flag=true;

void DrowPolygon(Paths);
void DrowPolygon_polytree(PolyTree);
int y_callback(float,int,float,float);
int x_callback(float,int,float,float);

void addPoint(int x, int y, Path *path)
{
    IntPoint ip;
    ip.X = x;
    ip.Y = y;
    path->push_back(ip);
}

int main()
{
    Paths subj;
    PolyTree solutions;
    Paths solution;
    Paths offset_solution;
    //Paths solutions;
    
    Path p;
    p.clear();
    addPoint(0,0, &p);
    addPoint(0,200, &p);
    addPoint(200,200, &p);
    addPoint(200,0, &p);
    subj.push_back(p);
    p.clear();
    addPoint(100,50, &p);
    addPoint(50,100, &p);
    addPoint(100,150, &p);
    addPoint(150,100, &p);
    subj.push_back(p);


    
  //openglにて表示
  // GLFW3の初期化 
  
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
    
    // 初期化 

    // 画面をクリア。
    glClear(GL_COLOR_BUFFER_BIT);
    // 変換行列の初期化。ここで初期化しないと延々と同じ行列に積算される。
    glLoadIdentity();
    // 更新 
    // 現在のウィンドウの大きさを取得。
    int width, height;
    glfwGetFramebufferSize( aWindow, &width, &height );
    // ビューポートの更新。
    glViewport( 0, 0, width, height );
    // 透視投影。 //これないと表示されない
    gluPerspective( 30.0, (double)width / (double)height, 1.0, 1000.0 );
    
    //カメラ
    //double cam_x,cam_y,cam_z;
    //cam_x = cam_length * sin((cam_deg2*M_PI)/180)*cos((cam_deg1*M_PI)/180);
    //cam_y = cam_length * sin((cam_deg2*M_PI)/180)*sin((cam_deg1*M_PI)/180);
    //cam_z = cam_length * cos((cam_deg2*M_PI)/180);
    //gluLookAt( cam_x, cam_y, cam_z,  0.0, 0.0, 0.0,  0.0, 0.0, 1.0 );
    gluLookAt(0, -0.00001, 800, 0,0,0, 0,0,1);
    DrowPolygon(subj);


    // ダブルバッファのスワップとイベントのポーリング 
    glfwSwapBuffers( aWindow );
    glfwPollEvents();
  }

  // GLFW3 の終了。
  glfwTerminate();
  return EXIT_SUCCESS;
  

}

void DrowPolygon(Paths paths){
    for(int i=0; i < paths.size(); i++)
    {
        glColor3f(1.0, 0.1*i, 0);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
        for(int j=0; j < paths[i].size(); j++ )
        {
            //std::cout << paths[i][j] << std::endl;
            glVertex3d((double)paths[i][j].X, (double)paths[i][j].Y, 0);
        }
        glEnd();
        //if(flag){
        //    std::cout << Area(paths[i]) << std::endl;
        //}
    }
    flag=false;

}

void DrowPolygon_polytree(PolyTree polytree){
    //PolyNode* polynode = polytree.GetFirst();
    //while (polynode)
    //{
    //  //do stuff with polynode here
    //  glColor3f(1.0, 0.1, 0);
    //  glLineWidth(5);
    //  glBegin(GL_LINE_LOOP);
    //  Path path_data = polynode->Contour;
    //  for(int i=0; i< path_data.size(); i++)
    //  {
    //    glVertex3d((double)path_data[i].X, (double)path_data[i].Y, 0);

    //  }
    //  glEnd();
    
    //  polynode = polynode->GetNext();
    //}
    for(int i =0; i< polytree.ChildCount(); i++)
    {
      glColor3f(1.0, 0.1, 0);
      glLineWidth(5);
      glBegin(GL_LINES);
      for(int j=0; j< polytree.Childs[i]->Contour.size(); j++)
      {

        std::cout << polytree.Childs[i]->Contour[j] << std::endl;
        glVertex3d((double)polytree.Childs[i]->Contour[j].X, (double)polytree.Childs[i]->Contour[j].Y, 0);

      }
      glEnd();
    }

}
