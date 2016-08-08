#include "Plotting/RatioPlotter.h"

#include "Plotting/HistHolder.h"
#include "Plotting/HistHolderContainer.h"
#include <TH1D.h>
#include <iostream>

namespace plotting {
void RatioPlotter::adjustLabels(HistHolderContainer& hist_container,
                                HistHolderContainer& ratio_container) {
  double size_old;
  double title_offset{1.7};

  double hist_scaling{1. / (1 - ratio_)};
  double hist_width_wo_margins{1 - 0.21 * hist_scaling};
  double hist_height_wo_margins{1 - 0.07 * hist_scaling};

  double ratio_scaling{1. / ratio_};
  double ratio_width_wo_margins{1 - 0.21 * ratio_scaling};
  double ratio_height_wo_margins{1 - 0.16 * ratio_scaling};

  for (auto& hist : hist_container) {
    auto&& xaxis = hist->getHist()->GetXaxis();
    auto&& yaxis = hist->getHist()->GetYaxis();

    xaxis->SetTitleOffset(50.00);
    xaxis->SetLabelOffset(50.00);
    size_old = xaxis->GetTickLength();
    xaxis->SetTickLength(size_old / hist_width_wo_margins);

    // size_old = yaxis->GetTitleSize();
    // yaxis->SetTitleSize(size_old * hist_scaling);
    yaxis->SetTitleOffset(title_offset);
    // size_old = yaxis->GetLabelSize();
    // yaxis->SetLabelSize(size_old * hist_scaling);
    size_old = yaxis->GetTickLength();
    yaxis->SetTickLength(size_old / hist_height_wo_margins / 1.2);
  }

  for (auto& hist : ratio_container) {
    auto&& xaxis = hist->getHist()->GetXaxis();
    auto&& yaxis = hist->getHist()->GetYaxis();

    yaxis->SetTitle(ratio_title_.c_str());

    // size_old = xaxis->GetLabelSize();
    // xaxis->SetLabelSize(size_old * ratio_scaling);
    // xaxis->SetTitleSize(size_old * ratio_scaling);
    xaxis->SetTitleOffset(5);
    size_old = xaxis->GetTickLength();
    xaxis->SetTickLength(size_old / ratio_width_wo_margins);

    // size_old = yaxis->GetTitleSize();
    // yaxis->SetLabelSize(size_old * ratio_scaling);
    // yaxis->SetTitleSize(size_old * ratio_scaling);
    yaxis->SetTitleOffset(title_offset);
    yaxis->SetNdivisions(502);
    size_old = yaxis->GetTickLength();
    yaxis->SetTickLength(size_old / ratio_height_wo_margins / 1.2);
  }
}

void RatioPlotter::adjustMarkers(HistHolderContainer& ratio_container) {
  // Make a copy of the first histogram because for the plotting we
  // need one histogram for the shaded errors and one for the black
  // reference line.
  ratio_container.emplace_back(new HistHolder(*ratio_container.at(0)));

  auto& error_area = ratio_container.front();
  error_area->getHist()->SetMarkerSize(0);
  error_area->getHist()->SetFillColor(kBlue);
  error_area->getHist()->SetFillStyle(3245);
  error_area->setDrawOptions("e2");

  auto& hist = ratio_container.back();
  hist->setDrawOptions("hist same");
  for (int bin = 0; bin < hist->getHist()->GetNbinsX() + 1; ++bin) {
    if (hist->getHist()->GetBinContent(bin) == 0) {
      hist->getHist()->SetBinContent(bin, 1);
    }
  }
}

void RatioPlotter::initCanvas(unsigned const int& width,
                              unsigned const int& height) {
  resetCanvas();
  canvas_width_ = width;
  canvas_height_ = height;
  canvas_.reset(new TCanvas("rcanvas", "rcanvas", width, height));
  if (do_verbose_) {
    std::cout << "Created ratio-specific canvas with name 'rcanvas'"
              << std::endl;
  }

  double histPad_scaling{1. / (1 - ratio_)};
  double ratioPad_scaling{1. / ratio_};

  pad_hist_.reset(new TPad("histPad", "histPad", 0, ratio_, 1, 1));
  pad_hist_->SetNumber(1);
  pad_hist_->SetLeftMargin(0.16);
  pad_hist_->SetRightMargin(0.05);
  pad_hist_->SetTopMargin(0.05 * histPad_scaling);
  pad_hist_->SetBottomMargin(0.02 * histPad_scaling);
  pad_hist_->SetFrameFillStyle(4000);
  pad_hist_->Draw();
  if (do_verbose_) {
    std::cout << "Created histogram pad with name 'histPad'" << std::endl;
  }

  pad_ratio_.reset(new TPad("ratioPad", "ratioPad", 0, 0, 1, ratio_));
  pad_ratio_->SetNumber(2);
  pad_ratio_->SetLeftMargin(0.16);
  pad_ratio_->SetRightMargin(0.05);
  pad_ratio_->SetTopMargin(0.02 * ratioPad_scaling);
  pad_ratio_->SetBottomMargin(0.14 * ratioPad_scaling);
  pad_ratio_->SetFrameFillStyle(4000);
  pad_ratio_->Draw();
  if (do_verbose_) {
    std::cout << "Created ratio pad with name 'ratioPad'" << std::endl;
  }
}

void RatioPlotter::resetCanvas() {
  if (canvas_) {
    if (pad_hist_) pad_hist_.release()->Close();
    if (pad_ratio_) pad_ratio_.release()->Close();
    if (do_verbose_) {
      std::cout << " -- Releasing canvas and let ";
      std::cout << "ROOT free the memory" << std::endl;
    }
    canvas_.release()->Close();
  }
}

void RatioPlotter::switchToHistPad() const {
  if (!canvas_ || !pad_hist_) {
    std::cout << "Tried to switch pads, but pad or canvas ";
    std::cout << "is not initialised." << std::endl;
    return;
  }
  canvas_->cd(1);
}

void RatioPlotter::switchToRatioPad() const {
  if (!canvas_ || !pad_ratio_) {
    std::cout << "Tried to switch pads, but pad or canvas ";
    std::cout << "is not initialised." << std::endl;
    return;
  }
  canvas_->cd(2);
}

void RatioPlotter::switchToMainPad() const {
  if (!canvas_) {
    std::cout << "Tried to switch pads, but canvas ";
    std::cout << "is not initialised." << std::endl;
    return;
  }
  canvas_->cd();
}
}  // namespace plotting
