// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "HistPlotter.h"

#include <TLegend.h>
#include <TH1D.h>
#include <iostream>
#include <sstream>
#include <string>
#include "HistHolder.h"
#include "HistHolderContainer.h"

namespace plotting {
void HistPlotter::addToLegend(const HistHolder& hist) {
  if (!legend_) {
    std::cout << "HistPlotter WARNING: Tried to add legend entry,";
    std::cout << "but legend is not initialised:" << std::endl;
    return;
  }
  legend_->AddEntry(hist.getHist(), hist.getLegendTitle().c_str(),
                    hist.getLegendOptions().c_str());
}

void HistPlotter::addToLegend(const HistHolderContainer& hist_container) {
  for (const auto& hist : hist_container) {
    addToLegend(*hist);
  }
}

void HistPlotter::initCanvas(unsigned const int& width,
                             unsigned const int& height) {
  resetCanvas();
  canvas_width_ = width;
  canvas_height_ = height;
  canvas_.reset(new TCanvas("canvas", "canvas", width, height));
  canvas_->SetLeftMargin(0.12);
  canvas_->SetRightMargin(0.05);
  canvas_->SetTopMargin(0.05);
  canvas_->SetBottomMargin(0.18);
}

void HistPlotter::initLegend(const double& x1, const double& y1,
                             const double& x2, const double& y2) {
  resetLegend();
  legend_x1_ = x1;
  legend_y1_ = y1;
  legend_x2_ = x2;
  legend_y2_ = y2;
  legend_.reset(new TLegend(x1, y1, x2, y2));
  legend_->SetTextSize(20);
  legend_->SetTextFont(63);
}

void HistPlotter::resetCanvas() {
  if (canvas_) {
    if (do_verbose_) {
      std::cout << " -- Releasing canvas and let ";
      std::cout << "ROOT free the memory" << std::endl;
    }
    canvas_.release()->Close();
  }
}

void HistPlotter::resetLegend() {
  if (legend_) {
    if (do_verbose_) {
      std::cout << " -- Releasing legend and let ";
      std::cout << "ROOT free the memory" << std::endl;
    }
  }
  legend_.release();
}

void HistPlotter::saveToFile(const std::string& title) {
  if (!canvas_) {
    std::cout << "WARNING: Tried to save to file, but ";
    std::cout << "canvas was not initialised." << std::endl;
    return;
  }

  // Make sure the axes are drawn on top of histograms etc.
  canvas_->RedrawAxis();

  std::ostringstream ostring;
  if (export_to_eps_) {
    ostring << output_dir_.c_str() << title << ".eps";
    canvas_->SaveAs(ostring.str().c_str());
    std::cout << "Saving to file " << ostring.str() << std::endl;
    ostring.str("");
  }
  if (export_to_pdf_) {
    ostring << output_dir_.c_str() << title << ".pdf";
    canvas_->SaveAs(ostring.str().c_str());
    std::cout << "Saving to file " << ostring.str() << std::endl;
    ostring.str("");
  }
  if (export_to_png_) {
    ostring << output_dir_.c_str() << title << ".png";
    canvas_->SaveAs(ostring.str().c_str());
    std::cout << "Saving to file " << ostring.str() << std::endl;
    ostring.str("");
  }
}
}  // namespace plotting
