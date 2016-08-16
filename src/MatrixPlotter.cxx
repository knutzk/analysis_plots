// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "MatrixPlotter.h"

#include <TColor.h>
#include <TStyle.h>

namespace plotting {
MatrixPlotter::MatrixPlotter() : HistPlotter::HistPlotter{} {
  const auto& ypos = atlas_label_->getLabelY();
  atlas_label_->setChannelPosition(0.50, ypos);
  atlas_label_->setTextScale(0.95);
}

void MatrixPlotter::initCanvas(const int& width, const int& height) {
  HistPlotter::initCanvas(width, height);
  canvas_->SetRightMargin(0.18);
}

void MatrixPlotter::setCustomColorPalette() {
  const int NRGBs(3);
  const int NCont(255);
  gStyle->SetNumberContours(NCont);
  double stops[NRGBs] = {0.00, 0.20, 1.00};
  double red[NRGBs] = {1.00, 0.77, 0.10};
  double green[NRGBs] = {1.00, 0.84, 0.38};
  double blue[NRGBs] = {1.00, 0.94, 0.76};
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
}
}  // namespace plotting
