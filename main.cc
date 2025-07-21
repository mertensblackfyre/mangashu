#include "includes/common.h"
#include <spdlog/spdlog.h>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> pages;

  if (argc > 2) {
    spdlog::error("[Usage]:./Mangashu directory");
    return -1;
  }

  std::string d_name = argv[1];

  Common::get_dirs(pages,d_name);
  // utils.get_files(pages, d_name);
  // main.mangashu_chapter(d_name, pages);
  return 0;
}
