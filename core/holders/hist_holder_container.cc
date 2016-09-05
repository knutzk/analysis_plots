// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "core/holders/hist_holder.h"
#include "core/holders/hist_holder_container.h"

namespace plotting {
void HistHolderContainer::setOptimalMax() {
  double maximum{0};
  for (const auto& hist : *this) {
    if (hist->getHist()->GetMaximum() > maximum) {
      maximum = hist->getHist()->GetMaximum();
    }
  }
  for (auto& hist : *this) {
    hist->setYRangeHigh(maximum * 1.5);
  }
}

void HistHolderContainer::divideHistograms(const HistHolder& denom) {
  for (auto& hist : *this) {
    hist->getHist()->Divide(denom.getHist());
  }
}
}  // namespace plotting
