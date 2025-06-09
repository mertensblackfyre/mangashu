#include <algorithm>
#include <cstddef>
#include <cstring>
#include <dirent.h>
#include <tuple>
#include <vector>

#include <iostream>

void pdf_convert();

std::tuple<std::string, std::string> extract_name(const std::string &path);
int extract_num(const std::string &filename);
void sort_files(std::vector<std::string> &pages);
void get_files(std::vector<std::vector<std::string>> &chapters,
               std::string path);

int main() {
  std::vector<std::vector<std::string>> chapters;

  get_files(chapters, "tmp");
  // for (auto pages : chapters) {
  //   for (auto s : pages) {
  //     std::cout << s << std::endl;
  //   }
  //   std::cout << "---------" << std::endl;
  // };
  return 0;
}

std::tuple<std::string, std::string> extract_name(const std::string &path){

    size_t first = path.find('/');
    size_t second = path.find('/', first + 1);

    std::string dir_name = path.substr(first, second-3);
    std::string file_name = path.substr(second+1,path.size());

   return {dir_name, file_name};
};

int extract_num(const std::string &filename) {
    size_t hyphen_pos = filename.find('-');
    if (hyphen_pos == std::string::npos)
      return 0;
    return std::stoi(filename.substr(0, hyphen_pos));
};
/*

void pdf_convert(char **argv,std::string path ,std::vector<std::vector<std::string>> &chapters) {
  Magick::InitializeMagick(*argv);
  Magick::Image image;
  std::vector<Magick::Image> images;

  std::vector<std::vector<Magick::Image>> images;
  try {
    for (auto pages : chapters) {
        for (auto files: page) {
            std::string f = path + files;
            images.emplace_back(f);
        }
    };
    Magick::writeImages(images.begin(), images.end(), "out.pdf");

  } catch (std::exception &error_) {
    std::cerr << "Magick++ error: " << error_.what() << std::endl;
    return 1;
  }
}
*/
void get_files(std::vector<std::vector<std::string>> &chapters,
               std::string path) {
  struct dirent *dir;

  std::vector<std::string> pages;

  DIR *dp = opendir(path.c_str());
  if (dp) {
    while ((dir = readdir(dp)) != NULL) {
      if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
        continue;

      if (dir->d_type == DT_DIR) {
        std::string str_path = path + "/" + dir->d_name;
        get_files(chapters, str_path);
      } else {
        std::string s(dir->d_name);
        std::string final_path = path +"/" +dir->d_name;
        pages.push_back(final_path);
      };
    }
  }
  sort_files(pages);
  chapters.emplace_back(pages);
  closedir(dp);
}

void sort_files(std::vector<std::string> &pages) {
  // std::sort(pages.begin(), pages.end(),
  //           [](const std::string &a, const std::string &b) {
  //             return extract_num(a) < extract_num(b);
  //           });
  //
  if(!pages.empty())
    extract_num(pages[0]);
};
