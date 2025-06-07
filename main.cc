#include <ImageMagick-7/Magick++.h>
#include <ImageMagick-7/Magick++/Image.h>
#include <ImageMagick-7/Magick++/Include.h>
#include <ImageMagick-7/Magick++/STL.h>
#include <algorithm>
#include <cstring>
#include <exception>
#include <iostream>

#include <dirent.h>


// Custom sorting function for natural numeric order (e.g., "1.png" < "10.png")
bool naturalSort(const std::string &a, const std::string &b) {
    return a < b; // Replace with a proper natural sort if needed (see notes below)
}

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);
  Magick::Image image;
  std::vector<Magick::Image> images;
  std::vector<std::string> img_files;

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
  // Sort files naturally (1.png, 2.png, ..., 10.png)
       std::sort(img_files.begin(), img_files.end(), naturalSort);

  try {

    for (const auto &file : img_files) {
        std::cout << file << std::endl;
      std::string f = "1/" + file;
      images.emplace_back(f);
    };
    // Magick::writeImages(images.begin(),images.end(),"out.pdf");

  } catch (std::exception &error_) {
    std::cerr << "Magick++ error: " << error_.what() << std::endl;
    return 1;
  }
  return 0;
}

// The QuickSort function implementation
void quickSort(std::vector<std::string> &arr) {

}
