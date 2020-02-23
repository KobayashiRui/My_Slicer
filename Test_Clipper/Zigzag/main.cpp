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
    Paths subj, _subj;
    Paths zigzag;
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
    _subj.push_back(p);
    p.clear();
    addPoint(100,50, &p);
    addPoint(50,100, &p);
    addPoint(100,150, &p);
    addPoint(150,100, &p);
    _subj.push_back(p);


    Clipper c,zigzag_clip;
    ClipperOffset co;
    SimplifyPolygons(_subj,subj);
    co.AddPaths(subj, jtRound, etClosedPolygon);
    co.Execute(offset_solution, -2.5);
    std::cout << "offset " << std::endl;
    std::cout << offset_solution[0] << std::endl;
    std::cout << offset_solution[1] << std::endl;
    c.AddPaths(offset_solution, ptSubject, true);
    zigzag_clip.AddPaths(offset_solution, ptClip, true);
    IntRect rect =  c.GetBounds();

    std::cout << "top:" << rect.top << ", left:" << rect.left <<", right:" << rect.right << ", bottom:" << rect.bottom  << std::endl;
    int xmin = rect.left;
    int xmax = rect.right;
    int ymin = rect.top;
    int ymax = rect.bottom;
    int k_offset = 5;
    int k = 0;
    float rad = 45*3.1415/180;

    int counter =0;
    while(true) {
        counter += 1;
        k += k_offset;
        std::cout << "counter:" << counter << std::endl;

        float xk = k * cos(rad) + xmin;
        float yk = k * sin(rad) + ymin;
        //std::cout << "xk:" << xk << ",yk:" << yk << std::endl;
        //p1の処理
        p.clear();
        int y_p1 = y_callback(rad,xmin,xk,yk);
        std::cout << "y:p1:" << y_p1 << std::endl;
        if(y_p1 < ymax){
          addPoint(xmin, y_p1, &p);
        }else{
            int x_p1 =x_callback(rad,ymax,xk,yk); 
            std::cout << "x:p1:" << x_p1 << std::endl;
            if(x_p1 > xmax){
               break;
            } 
            addPoint(x_p1, ymax, &p);
        }
        //p2の処理
        int x_p2 = x_callback(rad,ymin,xk,yk);
        if(x_p2 < xmax){
            addPoint(x_p2, ymin, &p);
        }else{
            int y_p2 = y_callback(rad,xmax,xk,yk);
            if(y_p2 > ymax){
                break;
            }
            addPoint(xmax, y_p2, &p);
        }
        zigzag.push_back(p);
    }
    std::cout << "zigzag" << std::endl;
    std::cout << zigzag << std::endl;
    zigzag_clip.AddPaths(zigzag, ptSubject, false);
    zigzag_clip.Execute(ctIntersection, solutions);


    //polytreeをpathsに変換
    std::cout << solutions.ChildCount() << std::endl;
    for(int i =0; i< solutions.ChildCount(); i++)
    {
        solution.push_back(solutions.Childs[i]->Contour);
      //for(int j=0; j< solutions.Childs[i]->Contour.size(); j++)
    }


    

    
    //printf("solution size = %d\n",(int)solution.ChildCount());
    //if(solution.ChildCount() > 0){
    //    std::cout << solution.Childs[0]->IsHole() << std::endl;;
    //    std::cout << solution.Childs[0]->Contour.size() << std::endl;
    //    std::cout << solution.Childs[0]->Contour << std::endl;
    //}
    //std::cout << "X:" <<  solution.Childs[0]->Contour[0].X << ", Y:" << solution.Childs[0]->Contour[0].Y <<std::endl;

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
    DrowPolygon(solution);
    //DrowPolygon_polytree(solutions);
    //DrowPolygon(offset_solution);
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

int y_callback(float rad,int x, float xk, float yk)
{
    //std::cout << tan(rad+1.57)*(x-xk) << std::endl;
    float result =tan(rad+1.57)*(x-xk) + yk + 0.5; 
    return (int) result;
}

int x_callback(float rad,int y, float xk, float yk)
{
    //std::cout << ((y-yk)/tan(rad+1.57)) << std::endl;
    float result = ((y-yk)/tan(rad+1.57)) + xk + 0.5;
    return (int) result;
}