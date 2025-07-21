
#ifndef COMMON_H
#define COMMON_H

#include "mangashu.h"
#include "utils.h"
#include <dirent.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>

class Common {

public:
  inline static void get_dirs(std::vector<std::string> &pages,
                              const std::string &path);
  inline static void get_files(std::vector<std::string> &pages,
                               const std::string &path,
                               const std::string &main_path);
};

inline void Common::get_dirs(std::vector<std::string> &pages,
                             const std::string &path) {

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
      spdlog::info("Traversing {}", dir->d_name);
      get_files(pages, dir->d_name, path);

      continue;
    };
  }
  closedir(dp);
};

inline void Common::get_files(std::vector<std::string> &pages,
                              const std::string &path,
                              const std::string &main_path) {
  struct dirent *dir;
  std::string ss = main_path + "/" + path;
  DIR *dp = opendir(ss.c_str());

  if (!dp) {
    spdlog::error("{} does not exist or cannot be opened", ss.c_str());
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
  Utils::sort_files(pages);
  MangaShu::mangashu_chapter(ss, pages);
  closedir(dp);
};

#endif
