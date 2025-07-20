#include "includes/mangashu.h"
#include "includes/utils.h"
#include <iostream>
#include <vector>

int main() {
  std::vector<std::string> pages;

  Utils utils;
  MangaShu main;
  std::string d_name = "ss";

  utils.get_files(pages, d_name);
  main.mangashu_chapter(d_name, pages);

  //  for(auto h : pages){
  //    std::cout << h << std::endl;
  //   }
  return 0;
}
