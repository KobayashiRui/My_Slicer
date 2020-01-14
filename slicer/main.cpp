#include <iostream>
#include <cassert>
#include <vector>

#include "stl_read.h"

int main(int argc, char *argv[])
{
  std::string stl_file_name = "../Box1x1x1.stl";

  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  }

  auto info = stl::parse_stl(stl_file_name);

  std::vector<stl::triangle> triangles = info.triangles;
  std::cout << "STL HEADER = " << info.name << std::endl;
  std::cout << "# triangles = " << triangles.size() << std::endl;
  for (auto t : info.triangles) {
    std::cout << t << std::endl;
  }
}