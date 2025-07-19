#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <dirent.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>

class Utils {

public:
  inline void sort_files(std::vector<std::string> &pages);
  inline void get_files(std::vector<std::string> &pages, std::string path);
  inline int extract_num(const std::string &fname);
};

int Utils::extract_num(const std::string &fname) {

  int num;
  size_t hyphen_pos = fname.find('-');
  if (hyphen_pos == std::string::npos)
    return 0;
  try {
    num = std::stoi(fname.substr(0, hyphen_pos));
  } catch (std::exception error_) {
    spdlog::error("{}", error_.what());
    return -1;
  }
  return num;
};

void Utils::get_files(std::vector<std::string> &pages, std::string path) {
  struct dirent *dir;
  DIR *dp = opendir(path.c_str());

  if (!dp) {
    spdlog::error("{} does not exist or cannot be opened", path.c_str());
    return;
  }

  while ((dir = readdir(dp)) != nullptr) {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
      continue;

    if (dir->d_type == DT_DIR) {
      continue;
    };
    std::string final_path = path + "/" + dir->d_name;
    if (!final_path.empty()) {
      pages.push_back(dir->d_name);
    }
  }
  sort_files(pages);
  closedir(dp);
};

void Utils::sort_files(std::vector<std::string> &pages) {

  std::sort(pages.begin(), pages.end(),
            [](const std::string &lpage, const std::string &rpage) {
              int ln = extract_num(lpage);
              int rn = extract_num(rpage);
              return ln < rn;
            });
};
#endif
