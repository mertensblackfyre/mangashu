#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <dirent.h>
#include <exception>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>

class Utils {

public:
  inline static std::string utils_get_extension(const std::string &f_name);
  inline static void sort_files(std::vector<std::string> &pages);
  inline static int extract_num(const std::string &fname);
};

inline void Utils::sort_files(std::vector<std::string> &pages) {

  std::sort(pages.begin(), pages.end(),
            [](const std::string &lpage, const std::string &rpage) {
              int ln = extract_num(lpage);
              int rn = extract_num(rpage);
              return ln < rn;
            });
};

inline int Utils::extract_num(const std::string &fname) {

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

inline std::string Utils::utils_get_extension(const std::string &f_name) {
  size_t dot_pos = f_name.find('.');
  if (dot_pos == std::string::npos)
    return "";
  std::string ext = "";
  try {
    ext = f_name.substr(dot_pos, f_name.size() - 1);
  } catch (std::exception error_) {
    spdlog::error("{}", error_.what());
    return ext;
  }
  return ext;
};
#endif
