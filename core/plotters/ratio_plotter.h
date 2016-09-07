/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef RATIOPLOTTER_H_
#define RATIOPLOTTER_H_

#include <TPad.h>
#include <string>
#include "core/plotters/hist_plotter.h"

namespace plotting {
/**
 * Class specifically designed to produce ratio plots of
 * histograms. This inherits functionality from the HistPlotter class,
 * but adds special features for ratio optimisation.
 */
class RatioPlotter : public HistPlotter {
 public:
  //! Default constructor
  RatioPlotter();

  /**
   * Construct a ratio plotter with a certain ratio value.
   *
   * @param ratio Value of the ratio between the two pads used for the
   * histograms and the ratio plot
   */
  explicit RatioPlotter(const double& ratio);

  /**
   * Construct a ratio plotter from an existing one.
   *
   * @param old Reference to the old RatioPlotter object
   */
  inline RatioPlotter(const RatioPlotter& old) {}

  /**
   * Set the ratio between the two pads handled by the class.
   *
   * @param ratio value of the pad ratio
   */
  inline void setRatio(const double& ratio) { ratio_ = ratio; }

  /**
   * Set the title of the ratio plot (displayed on the left).
   * @param title String of the ratio title
   */
  inline void setRatioTitle(const std::string& title) { ratio_title_ = title; }

  //! Get the value of the pad ratio.
  inline double getRatio() { return ratio_; }

  //! Get the title that is set for the ratio plot.
  inline std::string getRatioTitle() { return ratio_title_; }

  /**
   * Adjust the label sizes of the histograms that are meant to
   * be plotted with this RatioPlotter. This step is necessary
   * because ROOT automatically adjusts label sizes according to
   * the size of the current pad.
   *
   * @param hist_container Container with the HistHolder objects to be
   *        used for the histogram pad.
   * @param ratio_container Container with the HistHolder objects to
   *        be used for the ratio pad.
   */
  void adjustLabels(HistHolderContainer* hist_container,
                    HistHolderContainer* ratio_container);

  /**
   * Calculate the separation of two histograms. This makes use of the
   * separation calculation formula used within the TtHFitter
   * programme, so no warranty!
   *
   * @param first_hist Reference of the first histogram that should be
   * considered for the calculation
   * @param second_hist Reference to the second histogram
   */
  double getSeparation(const HistHolder* first_hist,
                       const HistHolder* second_hist);

  /**
   * Draw the ratio container as a ratio plot. This will place an
   * object to the front of the ratio container in order to allow
   * plotting of the shaded uncertainties as well as the black
   * reference line. The optimal range of the ratio will be
   * determined. If data points are out of range, an arrow indicates
   * this.
   *
   * @param ratio_container The container with the ratio histograms
   */
  void drawRatio(HistHolderContainer* ratio_container);

  /**
   * Initialise a new canvas for plotting. This function is inherited
   * from the base class, but makes some adjustments.
   *
   * @param width Desired width of the canvas
   * @param height Desired height of the canvas
   */
  void initCanvas(const int& width = 600, const int& height = 600) override;

  //! Reset the canvas managed by this class.
  void resetCanvas() override;

  //! Switch to the histogram pad (the upper pad).
  void switchToHistPad() const;

  //! Switch to the ratio pad (the lower pad).
  void switchToRatioPad() const;

  //! Switch to the main pad, i.e. the canvas.
  void switchToMainPad() const;

 private:
  double ratio_{0.3};
  std::string ratio_title_{"Signal / BG"};
  std::unique_ptr<TPad> pad_hist_{nullptr};
  std::unique_ptr<TPad> pad_ratio_{nullptr};
};
}  // namespace plotting

#endif  // RATIOPLOTTER_H_
