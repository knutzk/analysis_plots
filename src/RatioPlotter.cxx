// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "RatioPlotter.h"

#include <iostream>
#include "HistHolder.h"
#include "HistHolderContainer.h"

namespace plotting {
RatioPlotter::RatioPlotter() {
  canvas_.reset();
  initCanvas();
  atlas_label_->setLabelX(0.20);
}

RatioPlotter::RatioPlotter(const double& ratio) : ratio_{ratio} {
  canvas_.reset();
  initCanvas();
  atlas_label_->setLabelX(0.20);
}

void RatioPlotter::adjustLabels(HistHolderContainer* hist_container,
                                HistHolderContainer* ratio_container) {
  double size_old;
  const double title_offset{1.7};

  const double hist_scaling{1. / (1 - ratio_)};
  const double hist_width_wo_margins{1 - 0.21 * hist_scaling};
  const double hist_height_wo_margins{1 - 0.07 * hist_scaling};

  const double ratio_scaling{1. / ratio_};
  const double ratio_width_wo_margins{1 - 0.21 * ratio_scaling};
  const double ratio_height_wo_margins{1 - 0.16 * ratio_scaling};

  for (auto& hist : *hist_container) {
    hist->getHist()->GetXaxis()->SetTitleOffset(50.00);
    hist->getHist()->GetXaxis()->SetLabelOffset(50.00);
    hist->getHist()->GetYaxis()->SetTitleOffset(title_offset);

    size_old = hist->getHist()->GetXaxis()->GetTickLength();
    hist->getHist()->GetXaxis()->SetTickLength(size_old /
                                               hist_width_wo_margins);
    size_old = hist->getHist()->GetYaxis()->GetTickLength();
    hist->getHist()->GetYaxis()->SetTickLength(size_old /
                                               hist_height_wo_margins / 1.2);
  }

  for (auto& hist : *ratio_container) {
    hist->getHist()->GetXaxis()->SetTitleOffset(5);
    hist->getHist()->GetYaxis()->SetTitleOffset(title_offset);
    hist->getHist()->GetYaxis()->SetNdivisions(502);
    hist->getHist()->GetYaxis()->SetTitle(ratio_title_.c_str());

    size_old = hist->getHist()->GetXaxis()->GetTickLength();
    hist->getHist()->GetXaxis()->SetTickLength(size_old /
                                               ratio_width_wo_margins);
    size_old = hist->getHist()->GetYaxis()->GetTickLength();
    hist->getHist()->GetYaxis()->SetTickLength(size_old /
                                               ratio_height_wo_margins / 1.2);
  }
}

void RatioPlotter::adjustMarkers(HistHolderContainer* ratio_container) {
  ratio_container->emplace(ratio_container->begin(),
                           new HistHolder{*ratio_container->at(0)});

  ratio_container->at(0)->getHist()->SetMarkerSize(0);
  ratio_container->at(0)->getHist()->SetFillColor(kBlue);
  ratio_container->at(0)->getHist()->SetFillStyle(3245);
  ratio_container->at(0)->setDrawOptions("e2");

  ratio_container->at(1)->getHist()->SetFillStyle(0);
  ratio_container->at(1)->setDrawOptions("hist same");
  for (int bin = 0; bin < ratio_container->at(1)->getHist()->GetNbinsX() + 1;
       ++bin) {
    if (ratio_container->at(1)->getHist()->GetBinContent(bin) == 0) {
      ratio_container->at(1)->getHist()->SetBinContent(bin, 1);
    }
  }
}

void RatioPlotter::initCanvas(const int& width, const int& height) {
  resetCanvas();
  canvas_width_ = width;
  canvas_height_ = height;
  canvas_.reset(new TCanvas{"rcanvas", "rcanvas", width, height});
  if (do_verbose_) {
    std::cout << "Created ratio-specific canvas with name 'rcanvas'"
              << std::endl;
  }

  const double histPad_scaling{1. / (1 - ratio_)};
  const double ratioPad_scaling{1. / ratio_};

  pad_hist_.reset(new TPad{"histPad", "histPad", 0, ratio_, 1, 1});
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

  pad_ratio_.reset(new TPad{"ratioPad", "ratioPad", 0, 0, 1, ratio_});
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
  pad_hist_.reset();
  pad_ratio_.reset();
  HistPlotter::resetCanvas();
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
