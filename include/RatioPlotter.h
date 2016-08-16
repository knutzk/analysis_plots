/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef RATIOPLOTTER_H_
#define RATIOPLOTTER_H_

#include "HistPlotter.h"
#include <string>
#include <TPad.h>

/*
 * Class to produce ratio plots of histograms
 */
namespace plotting {
class RatioPlotter : public HistPlotter {
 public:
  /*
   * Default constructor
   */
  RatioPlotter();

  /*
   * Construct a ratio plotter with a certain ratio value
   * @param Ratio value, i.e. ratio between the two pads used for
   * the histograms and the ratio plot).
   */
  explicit RatioPlotter(const double& ratio);

  /*
   * Construct a ratio plotter form an existing one.
   * @param Reference to the old RatioPlotter object.
   */
  inline RatioPlotter(const RatioPlotter& R) {}

  /*
   * Set the ratio between the two pads handled by the class.
   * @param Ratio value
   */
  inline void setRatio(const double& ratio) { ratio_ = ratio; }

  /*
   * Get the current value of the ratio between the two pads.
   * @return Ratio value
   */
  inline double getRatio() { return ratio_; }

  /*
   * Set the title of the ratio plot (displayed on the left).
   * @param String of the ratio title
   */
  inline void setRatioTitle(const std::string& title) { ratio_title_ = title; }

  /*
   * Get the current ratio title.
   * @return String with the current title
   */
  inline std::string getRatioTitle() { return ratio_title_; }

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
  void adjustLabels(HistHolderContainer* hist_container,
                    HistHolderContainer* ratio_container);

  /*
   * Adjust the markes (i.e. plotting style) of the histograms that
   * are meant to be plotted with this RatioPlotter.  Make a copy of
   * the first histogram because for the plotting we need one
   * histogram for the shaded errors and one for the black reference
   * line.
   * NOTE: It will be emplaced to the very front of the container,
   * i.e. at(0) will be the error, at(1) the reference line.
   * @param HistHolderContainer containing the HistHolder objects
   *        to be used for the ratio pad.
   */
  void adjustMarkers(HistHolderContainer* ratio_container);

  /*
   * Initialise a new canvas (this function is inherited from the
   * base class, but makes some adjustments).
   * @param Width of the canvas
   * @param Height of the canvas
   */
  void initCanvas(const int& width = 600, const int& height = 600) override;

  /*
   * Reset the canvas managed by this class.
   */
  void resetCanvas() override;

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

#endif  // RATIOPLOTTER_H_
