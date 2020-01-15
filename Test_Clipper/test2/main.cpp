#include "polyclipping/clipper.hpp"
#include <iostream>
 
using namespace ClipperLib;


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
    Paths clip;
    PolyTree solution;
    
    Path p;
    addPoint(100,100, &p);
    addPoint(100,500, &p);
    addPoint(500,500, &p);
    addPoint(500,100, &p);
    subj.push_back(p);
    
    Path p2;
    addPoint(150,150, &p2);
    addPoint(175,150, &p2);
    addPoint(175,175, &p2);
    addPoint(150,175, &p2);
    subj.push_back(p2);

    Path p3;
    addPoint(110,110, &p3);
    addPoint(130,110, &p3);
    addPoint(130,130, &p3);
    addPoint(110,130, &p3);
    subj.push_back(p3);
    
    Clipper c;
    
    c.AddPaths(subj, ptSubject, true);
    //c.AddPath(p, ptSubject, true);
    //c.AddPath(p2, ptSubject, true);
    //c.AddPaths(clip, ptClip, true);
    //c.Execute(ctIntersection, solution, pftNonZero, pftNonZero);
    c.Execute(ctUnion, solution);
    //c.Execute(ctXor, solution, pftNonZero, pftNonZero);
    
    printf("solution size = %d\n",(int)solution.ChildCount());
    printf("solution2 size = %d\n",(int)solution.Childs[0]->ChildCount());
    std::cout << "Child Holl: " << solution.Childs[0]->IsHole() << std::endl;
    //for (unsigned i=0; i<solution.size(); i++)
    //{
    //    Path p3 = solution.at(i);
    //    
    //    for (unsigned j=0; j<p3.size(); j++)
    //    {
    //        IntPoint ip = p3.at(j);
    //        printf("%d = %lld, %lld\n",j, ip.X,ip.Y);
    //    }
    //    
    //}
    
    return 0;
}