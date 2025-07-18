#include <algorithm>
#include <dirent.h>
#include <hpdf.h>
#include <iostream>
#include <spdlog/spdlog.h>

void pdf_append(std::string image_name);
void sort_files(std::vector<std::string> &pages);
void get_files(std::vector<std::string> &pages, std::string path);
int extract_num(const std::string &fname);

int main() {
  std::vector<std::string> pages;
  get_files(pages, "ss");

  for(auto h : pages)
    std::cout << h << std::endl;
  return 0;
}

void pdf_append(std::string image_name) {

  HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
  if (!pdf) {
    spdlog::error("Failed to create PDF object.");
    return;
  }
  // Load image file (e.g., "image.jpg")
  HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf, "0.jpg");

  HPDF_Page page = HPDF_AddPage(pdf);
  HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

  HPDF_REAL page_width = HPDF_Page_GetWidth(page);
  HPDF_REAL page_height = HPDF_Page_GetHeight(page);

  HPDF_REAL img_width = HPDF_Image_GetWidth(image);
  HPDF_REAL img_height = HPDF_Image_GetHeight(image);

  // Calculate scale to fit image within page (preserve aspect ratio)
  HPDF_REAL scale = std::min(page_width / img_width, page_height / img_height);

  HPDF_REAL draw_width = img_width * scale;
  HPDF_REAL draw_height = img_height * scale;

  // Center the image on the page
  HPDF_REAL x = (page_width - draw_width) / 2;
  HPDF_REAL y = (page_height - draw_height) / 2;

  HPDF_Page_DrawImage(page, image, x, y, draw_width, draw_height);

  HPDF_SaveToFile(pdf, "output.pdf");
  HPDF_Free(pdf);
  spdlog::info("PDF created as output.pdf");
};

void get_files(std::vector<std::string> &pages, std::string path) {
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

void sort_files(std::vector<std::string> &pages) {

  std::sort(pages.begin(), pages.end(),
            [](const std::string &lpage, const std::string &rpage) {
                    int ln = extract_num(lpage);
                    int rn = extract_num(rpage);
                    return ln < rn;
            });
};

int extract_num(const std::string &fname) {

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
