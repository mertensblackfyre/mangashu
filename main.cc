#include <algorithm>
#include <cstddef>
#include <cstring>
#include <dirent.h>
#include <vector>

#include <iostream>

void pdf_convert();

void extract_name(const std::string &path)
int extract_num(const std::string &path);
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

int extract_num(const std::string &path) {

    size_t slow = path.find('/');
    size_t fast = -1;
    while ((fast = path.find('/', slow + 1)) !=
            std::string::npos){

   std::cout << path.substr(res);

            };
 // size_t hyphen_pos = path.find('-');

  //if (hyphen_pos == std::string::npos)
   // return 0;

   return 1;
 // return std::stoi(path.substr(0, hyphen_pos));
}
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
  std::sort(pages.begin(), pages.end(),
            [](const std::string &a, const std::string &b) {
              return extract_num(a) < extract_num(b);
            });
};
