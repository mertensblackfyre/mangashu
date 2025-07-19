#include <algorithm>
#include <dirent.h>
#include <hpdf.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>

void mangahu_chapter(std::string path,const std::vector<std::string> &pages);
int main() {
  std::vector<std::string> pages;
 // get_files(pages, "ss");

  mangahu_chapter("ss",pages);
  // for(auto h : pages){
  //   std::cout << h << std::endl;
  //  }
  return 0;
}

void mangashu_chapter(std::string path,const std::vector<std::string> &pages) {

  if (pages.empty()) {
    spdlog::warn("No images provided.");
    return;
  };

  HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
  if (!pdf) {
    spdlog::error("Failed to create PDF object.");
    return;
  }

  for (const auto &path : pages) {
    // Load image file (e.g., "image.jpg")
    std::string ppp = "ss/" + path;
    HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf, ppp.c_str());
    if (!image) {
      spdlog::error("Failed to load image: {}", path);
      continue;
    };

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    HPDF_REAL page_width = HPDF_Page_GetWidth(page);
    HPDF_REAL page_height = HPDF_Page_GetHeight(page);

    HPDF_REAL img_width = HPDF_Image_GetWidth(image);
    HPDF_REAL img_height = HPDF_Image_GetHeight(image);

    HPDF_REAL scale =
        std::min(page_width / img_width, page_height / img_height);

    HPDF_REAL draw_width = img_width * scale;
    HPDF_REAL draw_height = img_height * scale;

    // Center the image on the page
    HPDF_REAL x = (page_width - draw_width) / 2;
    HPDF_REAL y = (page_height - draw_height) / 2;

    HPDF_Page_DrawImage(page, image, x, y, draw_width, draw_height);
  }

  HPDF_STATUS result = HPDF_SaveToFile(pdf, "output.pdf");
  if (result != HPDF_OK) {
    spdlog::error("Failed to save output.pdf");
  } else {
    spdlog::info("PDF successfully saved to output.pdf");
  }
  return;
};
