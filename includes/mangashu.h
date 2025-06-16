#ifndef MANGASHU_H
#define MANGASHU_H

/*
#include <ImageMagick - 7 / Magick++.h>
#include <ImageMagick-7/Magick++/Image.h>
#include <ImageMagick-7/Magick++/Include.h>
#include <ImageMagick-7/Magick++/STL.h>
*/
#include "spdlog/spdlog.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <dirent.h>
#include <exception>
#include <filesystem>
#include <functional>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <tuple>
#include <unistd.h>
#include <vector>

class Mangashu {
public:
  inline void pdf_convert();

private:
  std::vector<std::vector<std::string>> chapters;
  inline void mangashu_create_dir(const std::string &dir);
  inline void mangashu_move_files(std::string &dir_name, std::string &extension,
                                  std::string &new_path);
  inline void mangashu_traverse_dir(const std::string &dir, std::string f);
};

void Mangashu::pdf_convert() {

  //  Magick::Image image;
  // std::vector<Magick::Image> images;
  int n = 1;
  try {
    for (auto pages : chapters) {
      for (auto files : pages)
        images.emplace_back(files);

      if (pages.empty()) {
        spdlog::error("Pages vector is empty");
        break;
      }
      auto [dir_name, file_name] = extract_name(pages[0]);
      std::string nn = std::to_string(n);
      std::string pdf_name = nn + ".pdf";
      //   Magick::writeImages(images.begin(), images.end(), pdf_name);
      spdlog::info(" Converted {} to pdf", dir_name.substr(1, dir_name.size()));
      images.clear();
      n++;
    };
  } catch (std::exception &error_) {
    spdlog::error("Magick++ error {}", error_.what());
  }

  mangashu_traverse_dir("output","m");
}
void Mangashu::mangashu_create_dir(const std::string &dir) {
  if (mkdir(dir.c_str(), 0777) == -1) {
    spdlog::error("{}", strerror(errno));
  } else {
    spdlog::info("output directory created");
  };
};

void Mangashu::mangashu_move_files(std::string &dir_name,
                                   std::string &extension,
                                   std::string &new_path) {
  std::string s(dir_name);
  size_t dot_pos = s.find(".");
  std::string curr_extension = s.substr(dot_pos + 1, s.size());

  if (std::strcmp(curr_extension.c_str(), extension.c_str()) == 0) {
    try {
      std::string curr_path = std::filesystem::current_path().c_str();
      std::string new_name = curr_path + new_path + s;
      std::filesystem::rename(s, new_name);
      spdlog::info("{} move successfully", s);
    } catch (const std::filesystem::filesystem_error &e) {
      spdlog::error("Error moving {} {}", s, e.what());
      std::cerr << "Error moving file: " << e.what() << std::endl;
    }
  }
};
void Mangashu::mangashu_traverse_dir(const std::string &dir_name,
                                     std::string f) {
  struct dirent *dir;
  DIR *dp = opendir(dir_name.c_str());
  if (dp) {
    while ((dir = readdir(dp)) != NULL) {
      if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
        continue;

      std::string s(dir->d_name);
      std::string exe = "pdf";
      std::string exe1 = "/tmp/";
      if (f == "m")
        mangashu_move_files(s, exe, exe);
    }
  } else {
    spdlog::error("File does not exist");
    closedir(dp);
    return;
  }
}
#endif
