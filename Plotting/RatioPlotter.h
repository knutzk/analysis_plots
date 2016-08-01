/* -*- mode: c++; -*- */
#ifndef PLOTTING_RATIOPLOTTER_H_
#define PLOTTING_RATIOPLOTTER_H_

#include "Plotting/HistPlotter.h"
#include <string>

/*
 * Class to produce ratio plots of histograms
 */
namespace plotting {
class RatioPlotter : public HistPlotter {
 public:
  /*
   * Default constructor
   */
  RatioPlotter() {
    canvas_.reset(nullptr);
    initCanvas();
    atlas_label_.setLabelX(0.20);
  }

  /*
   * Construct a ratio plotter with a certain ratio value
   * @param Ratio value, i.e. ratio between the two pads used for
   * the histograms and the ratio plot).
   */
  RatioPlotter(double ratio) : ratio_{ratio} {
    canvas_.reset(nullptr);
    initCanvas();
    atlas_label_.setLabelX(0.20);
  }

  /*
   * Construct a ratio plotter form an existing one.
   * @param Reference to the old RatioPlotter object.
   */
  RatioPlotter(const RatioPlotter& R) {}

  /*
   * Destructor
   */
  virtual ~RatioPlotter() {}

  /*
   * Set the ratio between the two pads handled by the class.
   * @param Ratio value
   */
  void setRatio(const double& ratio) { ratio_ = ratio; }

  /*
   * Get the current value of the ratio between the two pads.
   * @return Ratio value
   */
  double getRatio() { return ratio_; }

  /*
   * Set the title of the ratio plot (displayed on the left).
   * @param String of the ratio title
   */
  void setRatioTitle(const std::string& title) { ratio_title_ = title; }

  /*
   * Get the current ratio title.
   * @return String with the current title
   */
  std::string getRatioTitle() { return ratio_title_; }

  /*
   * Adjust the label sizes of the histograms that are meant to
   * be plotted with this RatioPlotter. This step is necessary
   * because ROOT automatically adjusts label sizes according to
   * the size of the current pad.
   * @param HistHolderContainer containing the HistHolder objects
   *        to be used for the histogram pad.
   * @param HistHolderContainer containing the HistHolder objects
   *        to be used for the ratio pad.
   */
  void adjustLabels(HistHolderContainer& hist_container,
                    HistHolderContainer& ratio_container);

  /*
   * Adjust the markes (i.e. plotting style) of the histograms
   * that are meant to be plotted with this RatioPlotter.
   * @param HistHolderContainer containing the HistHolder objects
   *        to be used for the ratio pad.
   */
  void adjustMarkers(HistHolderContainer& ratio_container);

  /*
   * Initialise a new canvas (this function is inherited from the
   * base class, but makes some adjustments).
   * @param Width of the canvas
   * @param Height of the canvas
   */
  void initCanvas(const unsigned int& width = 600,
                  const unsigned int& height = 600);

  /*
   * Reset the canvas managed by this class.
   */
  void resetCanvas();

  /*
   * Switch to the histogram pad of this class.
   */
  void switchToHistPad() const;

  /*
   * Switch to the ratio pad of this class.
   */
  void switchToRatioPad() const;

  /*
   * Switch to the main pad of this class.
   */
  void switchToMainPad() const;

 private:
  double ratio_{0.3};
  std::string ratio_title_{"Signal / BG"};
  std::unique_ptr<TPad> pad_hist_{nullptr};
  std::unique_ptr<TPad> pad_ratio_{nullptr};
};
}  // namespace plotting

#endif  // PLOTTING_RATIOPLOTTER_H_

/* // Set specific draw option and some more cosmetics. */
/* for (auto itr = 0; itr < ratioHist->GetNbinsX() + 1; ++itr) { */
/*   if (ratioHist->GetBinContent(itr) == 0) { */
/*     ratioHist->SetBinContent(itr, 1.); */
/*   } */
/* } */

/* // Now initialise the pads. */
/* TPad* ratioPad = new TPad("ratioPad", "ratioPad", 0, 0, 1, 0.32); */
/* ratioPad->SetNumber(1); */
/* ratioPad->SetTopMargin(0.1); */
/* ratioPad->SetBottomMargin(0.45); */
/* ratioPad->SetFrameFillStyle(4000); */
/* ratioPad->Draw(); */
/* TPad* histPad = new TPad("histPad", "histPad", 0, 0.3, 1, 1); */
/* histPad->SetNumber(2); */
/* histPad->SetBottomMargin(0.03); */
/* histPad->SetFrameFillStyle(4000); */
/* histPad->Draw(); */

/* canvas_->cd(1); */
/* ratioHist->GetYaxis()->SetRangeUser(ratioMin, ratioMax); */
/* ratioHist->SetMarkerSize(0); */
/* ratioHist->DrawCopy("hist"); */
/* ratioHist->SetFillColor(kBlue); */
/* ratioHist->SetFillStyle(3245); */
/* ratioHist->Draw("e2 same"); */
/* for (auto itr : *ratios) { */
/*   if (itr != ratios->front()) { */
/*     itr->Draw(); */
/*   } */
/* } */
