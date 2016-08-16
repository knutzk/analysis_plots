/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef MATRIXPLOTTER_H_
#define MATRIXPLOTTER_H_

#include "HistPlotter.h"
#include <TLegend.h>

/*
 * Class to plot matrix object (TH2D)
 */
namespace plotting {
class MatrixPlotter : public HistPlotter {
 public:
  /*
   * Default constructor
   */
  MatrixPlotter();

  /*
   * Initialise the canvas (this function is inherited from the
   * base class, but has some modifications).
   * @param Width of the canvas
   * @param Height of the canvas
   */
  void initCanvas(const int& width, const int& height) override;

  /*
   * Set a custom colour scheme for the ZCOL plotting option.
   */
  void setCustomColorPalette();
};
}  // namespace plotting

#endif  // MATRIXPLOTTER_H_
