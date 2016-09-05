/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef MATRIXPLOTTER_H_
#define MATRIXPLOTTER_H_

#include <TLegend.h>
#include "core/plotters/hist_plotter.h"

namespace plotting {
/**
 * Class to plot matrix objects (TH2D).
 */
class MatrixPlotter : public HistPlotter {
 public:
  //! Default constructor
  MatrixPlotter();

  /**
   * Initialise the canvas for matrix plots. This function is
   * inherited from the base class, but has some modifications in it.
   *
   * @param width Desired width of the canvas
   * @param height Desired height of the canvas
   */
  void initCanvas(const int& width, const int& height) override;

  //! Set a custom colour scheme for the ZCOL plotting option.
  void setCustomColorPalette();
};
}  // namespace plotting

#endif  // MATRIXPLOTTER_H_
