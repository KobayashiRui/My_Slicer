#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "polyclipping/clipper.hpp"
#include <iostream>
 
using namespace ClipperLib;

static GLFWwindow*  aWindow;
static int          aWidth = 640;
static int          aHeight = 480;
static std::string  aTitle = "Line";
bool flag=true;

void DrowPolygon(Paths);

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
    //PolyTree solution;
    Paths solution;
    Paths solutions;
    
    Path p;
    //addPoint(100,100, &p);
    //addPoint(500,100, &p);
    //addPoint(500,500, &p);
    //addPoint(100,500, &p);
    addPoint(100,0, &p);
    addPoint(0,0, &p);
    addPoint(0,100, &p);
    addPoint(100,100, &p);
    subj.push_back(p);
    
    ClipperOffset co;
    co.AddPaths(subj, jtRound, etClosedPolygon);
    int offset_num = 0;
    while(true)
    {
        co.Execute(solution, offset_num);
        if(solution.size()== 0){
            break;
        }
        for(int i=0; i < solution.size(); i++){
            std::cout << solution << std::endl;
            solutions.push_back(solution[i]);
        }
        offset_num -=5;
    }
    std::cout << solutions << std::endl;

    
    //printf("solution size = %d\n",(int)solution.ChildCount());
    //if(solution.ChildCount() > 0){
    //    std::cout << solution.Childs[0]->IsHole() << std::endl;;
    //    std::cout << solution.Childs[0]->Contour.size() << std::endl;
    //    std::cout << solution.Childs[0]->Contour << std::endl;
    //}
    //std::cout << "X:" <<  solution.Childs[0]->Contour[0].X << ", Y:" << solution.Childs[0]->Contour[0].Y <<std::endl;

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
    //double cam_x,cam_y,cam_z;
    //cam_x = cam_length * sin((cam_deg2*M_PI)/180)*cos((cam_deg1*M_PI)/180);
    //cam_y = cam_length * sin((cam_deg2*M_PI)/180)*sin((cam_deg1*M_PI)/180);
    //cam_z = cam_length * cos((cam_deg2*M_PI)/180);
    //gluLookAt( cam_x, cam_y, cam_z,  0.0, 0.0, 0.0,  0.0, 0.0, 1.0 );
    gluLookAt(0, 1, 500, 0,0,0,0,0,1);
    DrowPolygon(solutions);


    /* ダブルバッファのスワップとイベントのポーリング */
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
        if(flag){
            std::cout << Area(paths[i]) << std::endl;
        }
    }
    flag=false;

}