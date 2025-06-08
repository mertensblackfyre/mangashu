#include <algorithm>
#include <cstddef>
#include <cstring>
#include <dirent.h>
#include <vector>

#include <iostream>

int extract_num(const std::string &filename);
void sort_files(std::vector<std::vector<std::string>> &chapters);
void get_files(std::vector<std::vector<std::string>> &chapters,
               std::string path);

int main() {
  std::vector<std::vector<std::string>> chapters;

  get_files(chapters, "tmp");
  sort_files(chapters);

  /*
  for (auto pages : chapters) {
    for (auto s : pages) {
      std::cout << s << std::endl;
    }
    std::cout << "---------" << std::endl;
  };
*/
  return 0;
}

int extract_num(const std::string &filename) {
  size_t hyphen_pos = filename.find('-');

  if (hyphen_pos == std::string::npos)
    return 0;

  return std::stoi(filename.substr(0, hyphen_pos));
}

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
        pages.push_back(s);
      };
    }
  }
  chapters.emplace_back(pages);
  closedir(dp);
}

void sort_files(std::vector<std::vector<std::string>> &chapters) {
  for (auto pages : chapters) {
 for (auto s : pages) {
      std::cout << s << std::endl;
    }
    std::sort(pages.begin(), pages.end(),
              [](const std::string &a, const std::string &b) {
                return extract_num(a) < extract_num(b);
              });
  }
}
