#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <vector>
#include <ImageMagick-7/Magick++.h>
#include <ImageMagick-7/Magick++/Image.h>
#include <ImageMagick-7/Magick++/Include.h>
#include <ImageMagick-7/Magick++/STL.h>

#include <iostream>

int extract_num(const std::string &filename);

void get_files(std::vector<std::string> &img_files);

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);
  Magick::Image image;
  std::vector<Magick::Image> images;
  std::vector<std::string> img_files;
  get_files(img_files);

  try {
    for (const auto &file : img_files) {
      std::cout << file << std::endl;
      std::string f = "1/" + file;
      images.emplace_back(f);
    };
    Magick::writeImages(images.begin(), images.end(), "out.pdf");

  } catch (std::exception &error_) {
    std::cerr << "Magick++ error: " << error_.what() << std::endl;
    return 1;
  }

  return 0;
}


int extract_num(const std::string &filename) {
  size_t dot_pos = filename.find('.');
  if (dot_pos == std::string::npos)
    return 0;
  return std::stoi(filename.substr(0, dot_pos));
}

void get_files(std::vector<std::string> &img_files) {
  struct dirent *dir;
  DIR *dp = opendir("1");
  if (dp) {
    while ((dir = readdir(dp)) != NULL) {
      if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
        continue;

      std::string s(dir->d_name);
      img_files.push_back(s);
    }
  }

  closedir(dp);

  // Sort using custom comparator
  std::sort(img_files.begin(), img_files.end(),
            [](const std::string &a, const std::string &b) {
              return extract_num(a) < extract_num(b);
            });
}


