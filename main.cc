#include <cstddef>
#include <ImageMagick-7/Magick++.h>
#include <ImageMagick-7/Magick++/Image.h>
#include <ImageMagick-7/Magick++/Include.h>
#include <ImageMagick-7/Magick++/STL.h>
#include <cstring>
#include <dirent.h>
#include <exception>
#include <tuple>
#include <vector>
#include <algorithm>

#include <iostream>


void pdf_convert(std::vector<std::vector<std::string>> &chapters);
std::tuple<std::string, std::string> extract_name(const std::string &path);
int extract_num(std::string &filename);
void sort_files(std::vector<std::string> &pages);
void get_files(std::vector<std::vector<std::string>> &chapters,
               std::string path);

int main(int argc, char **argv) {
  std::vector<std::vector<std::string>> chapters;

  Magick::InitializeMagick(*argv);
  get_files(chapters, "tmp");
  pdf_convert(chapters);


  return 0;
};

std::tuple<std::string, std::string> extract_name(const std::string &path){

    size_t first = path.find('/');
    size_t second = path.find('/', first + 1);

    std::string dir_name = path.substr(first, second - 3);
    std::string file_name = path.substr(second+1,path.size());

   return {dir_name, file_name};
};

int extract_num( std::string &filename) {

    auto [dir_name ,file_name] = extract_name(filename);
    size_t hyphen_pos = file_name.find('-');
    if (hyphen_pos == std::string::npos)
        return 0;

    int num;
        try {
             num =  std::stoi(file_name.substr(0, hyphen_pos));
        } catch (std::exception error_) {
            std::cerr <<"Error: " << error_.what() << std::endl;
        }

    return num;
};

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
};

void sort_files(std::vector<std::string> &pages) {
  std::sort(pages.begin(), pages.end(),
            []( std::string &a, std::string &b) {
              return extract_num(a) < extract_num(b);
            });
};


void pdf_convert(std::vector<std::vector<std::string>> &chapters) {
  Magick::Image image;
  std::vector<Magick::Image> images;

  try {
    for (auto pages : chapters) {
        for (auto files: pages)
            images.emplace_back(files);

        if(pages.empty())
            break;
        auto [dir_name, file_name] = extract_name(pages[0]);
        std::string pdf_name = dir_name.substr(1,dir_name.size()) + ".pdf";
        Magick::writeImages(images.begin(), images.end(),pdf_name);
        images.clear();
    };

  } catch (std::exception &error_) {
    std::cerr << "Magick++ error: " << error_.what() << std::endl;
  }
}
