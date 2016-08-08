/* -*- mode: c++; -*- */
#ifndef PLOTTING_MATRIXPLOTTER_H_
#define PLOTTING_MATRIXPLOTTER_H_

#include "Plotting/HistPlotter.h"

/*
 * Class to plot matrix object (TH2D)
 */
namespace plotting {
class MatrixPlotter : public HistPlotter {
 public:
  /*
   * Default constructor
   */
  MatrixPlotter() : HistPlotter::HistPlotter{} {
    const auto& ypos = atlas_label_.getLabelY();
    atlas_label_.setChannelPosition(0.50, ypos);
    atlas_label_.setTextScale(0.95);
  }

  /*
   * Set a custom colour scheme for the ZCOL plotting option.
   */
  void setCustomColorPalette();

  /*
   * Initialise the canvas (this function is inherited from the
   * base class, but has some modifications).
   * @param Width of the canvas
   * @param Height of the canvas
   */
  void initCanvas(unsigned const int& width, unsigned const int& height) {
    HistPlotter::initCanvas(width, height);
    canvas_->SetRightMargin(0.18);
  }
};
}  // namespace plotting

#endif  // PLOTTING_MATRIXPLOTTER_H_
