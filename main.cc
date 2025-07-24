#include "includes/common.h"
#include "includes/mangashu.h"
#include <spdlog/spdlog.h>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> pages;

  if (argc > 3) {
    spdlog::error("Usage:./Mangashu directory output-file-name ");
    return -1;
  }

  std::string d_name = argv[1];
  std::string output = argv[2];
  Common::get_dirs(pages, d_name);
  MangaShu::mangashu_merge_chapters(d_name,output);
  return 0;
}
