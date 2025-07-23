#ifndef MANGASHU_H
#define MANGASHU_H

#include "utils.h"
#include <hpdf.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>
#include <podofo/podofo.h>

class MangaShu {

public:
  inline void mangashu_merge_chapters(std::string &path);
  inline static void mangashu_chapter(std::string &path,
                                      std::vector<std::string> &pages);
};

inline void MangaShu::mangashu_chapter(std::string &path,
                                        std::vector<std::string> &pages) {

  if (pages.empty()) {
    spdlog::warn("No images provided.");
    return;
  };

  HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
  if (!pdf) {
    spdlog::error("Failed to create PDF object.");
    return;
  }

  for (const auto &file_name : pages) {
    std::string ppp = path + "/" + file_name;
    HPDF_Image image;
    std::string ext = Utils::utils_get_extension(file_name);

    if (ext == ".jpg") {
      image = HPDF_LoadJpegImageFromFile(pdf, ppp.c_str());
    } else if (ext == ".png") {
      image = HPDF_LoadPngImageFromFile(pdf, ppp.c_str());
    } else {
      spdlog::error("Unknown extension: {}", ext);
      return;
    };

    if (!image) {
      spdlog::error("Failed to load image: {}", file_name);
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
    spdlog::info("Appended {} to the pdf", file_name);
  }

  std::string output = path + ".pdf";
  HPDF_STATUS result = HPDF_SaveToFile(pdf, output.c_str());

  if (result != HPDF_OK) {
    spdlog::error("Failed to save {}", output);
  } else {
    spdlog::info("PDF successfully saved to {}", output);
  }
  pages.clear();
  return;
};


inline void mangashu_merge_chapters(){

};

#endif
