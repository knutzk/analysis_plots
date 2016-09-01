// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "RatioPlotter.h"

#include <TArrow.h>
#include <iostream>
#include "HistHolder.h"
#include "HistHolderContainer.h"

namespace plotting {
RatioPlotter::RatioPlotter() {
  canvas_.reset();
  initCanvas();
  getAtlasLabel()->setLabelX(0.20);
}

RatioPlotter::RatioPlotter(const double& ratio) : ratio_{ratio} {
  canvas_.reset();
  initCanvas();
  getAtlasLabel()->setLabelX(0.20);
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

void RatioPlotter::drawRatio(HistHolderContainer* ratio_container) {
  // Adjust the markers of the histograms that are meant to be plotted
  // with this RatioPlotter. Make a copy of the first histogram
  // because for the plotting we need one histogram for the shaded
  // errors and one for the black reference line.
  // NOTE: It will be emplaced to the very front of the container,
  // i.e. at(0) will be the error, at(1) the reference line.

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

  // Check the fraction of data points outside the chosen range and
  // adjust it if necessary (desired: less than 25%).
  double y_ratio_min{0.5};
  double y_ratio_max{1.5};
  while (true) {
    int n_datapoints{0};
    for (const auto& hist : *ratio_container) {
      n_datapoints += hist->getHist()->GetNbinsX();
    }

    double fraction_out_of_range{0.};
    for (const auto& hist : *ratio_container) {
      const auto& n_bins = hist->getHist()->GetNbinsX();
      for (int bin = 0; bin < n_bins; ++bin) {
        const auto& bin_content = hist->getHist()->GetBinContent(bin);
        if (bin_content > y_ratio_max) {
          fraction_out_of_range += bin_content / n_datapoints;
        }
      }
    }
    if (fraction_out_of_range > 0.25) {
      y_ratio_max += 0.5;
    } else {
      break;
    }
  }

  // Now make sure that we don't have ranges such as 0.5 -- 2.0 which
  // would cause the y axis to have weird labels. Adjust the lower
  // value accordingly.
  if (fmod(y_ratio_max - y_ratio_min, 1) != 0) {
    y_ratio_min -= 0.5;
  }

  for (auto& hist : *ratio_container) {
    hist->getHist()->GetYaxis()->SetRangeUser(y_ratio_min, y_ratio_max);
    hist->getHist()->GetYaxis()->SetNdivisions(503, true);
    hist->draw();

    // If the bin is out of range, draw an arrow to indicate this
    // (this part of the code has been 'borrowed' from TtHFitter).
    const auto n_bins = hist->getHist()->GetNbinsX();
    for (int i = 1; i < n_bins + 1; ++i) {
      // Ignore empty bins.
      if (hist->getHist()->GetBinContent(i) == 0) continue;

      int is_out_of_range{0};
      if (hist->getHist()->GetBinContent(i) > y_ratio_max) {
        is_out_of_range = 1;
      } else if (hist->getHist()->GetBinContent(i) < y_ratio_min) {
        is_out_of_range = -1;
      }

      if (is_out_of_range != 0) {
        TArrow* arrow;
        if (is_out_of_range == 1) {
          arrow = new TArrow(hist->getHist()->GetXaxis()->GetBinCenter(i),
                             y_ratio_max - 0.05 * (y_ratio_max - y_ratio_min),
                             hist->getHist()->GetXaxis()->GetBinCenter(i),
                             y_ratio_max, 0.022, "|>");
        } else {
          arrow = new TArrow(hist->getHist()->GetXaxis()->GetBinCenter(i),
                             y_ratio_min + 0.05 * (y_ratio_max - y_ratio_min),
                             hist->getHist()->GetXaxis()->GetBinCenter(i),
                             y_ratio_min, 0.022, "|>");
        }
        arrow->SetFillColor(10);
        arrow->SetFillStyle(1001);
        arrow->SetLineColor(hist->getHist()->GetLineColor());
        arrow->SetLineWidth(2);
        arrow->SetAngle(40);
        arrow->Draw();
      }
    }
  }
}

void RatioPlotter::initCanvas(const int& width, const int& height) {
  resetCanvas();
  HistPlotter::initCanvas(width, height);
  // canvas_width_ = width;
  // canvas_height_ = height;
  // canvas_.reset(new TCanvas{"rcanvas", "rcanvas", width, height});
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
