#ifndef MANGASHU_H
#define MANGASHU_H

#include "utils.h"
#include <algorithm>
#include <hpdf.h>
#include <iostream>
#include <podofo/podofo.h>
#include <spdlog/spdlog.h>
#include <string>
#include <unistd.h>
#include <vector>

class MangaShu {

public:
  inline static void mangashu_merge_chapters(const std::string &path);
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

    std::cout << ppp << std::endl;
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

inline void MangaShu::mangashu_merge_chapters(const std::string &path) {

  std::vector<std::string> pdfs;
  struct dirent *dir;
  DIR *dp = opendir(path.c_str());

  if (!dp) {
    spdlog::error("{} does not exist or cannot be opened", path.c_str());
    return;
  }

  while ((dir = readdir(dp)) != nullptr) {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
      continue;

    if (dir->d_type == DT_DIR)
      continue;

    std::string s = dir->d_name;
    pdfs.emplace_back(s);
  }

  std::sort(pdfs.begin(), pdfs.end(),
            [](const std::string &lpage, const std::string &rpage) {
              int ln, rn;
              try {
                ln = std::stoi(lpage.substr(lpage.size() - 7, 3));
                rn = std::stoi(rpage.substr(rpage.size() - 7, 3));
              } catch (std::exception error_) {
                spdlog::error("{}", error_.what());
              }
              return ln < rn;
            });

  const char *outputFile = "vol12";

  try {
    PoDoFo::PdfMemDocument outDoc;

    for (int i = 0; i < pdfs.size(); ++i) {
      PoDoFo::PdfMemDocument inDoc(pdfs[i]);
      outDoc.append(inDoc,true);
    }
    outDoc.WriteToFile(outputFile);
    printf("Merged PDF saved to: %s\n", outputFile);
  } catch (const PoDoFo::PdfError &err) {
    spdlog::warn("Error: {}", err.what());
  }
  closedir(dp);
  return;
};

#endif
