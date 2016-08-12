// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "HistHolderContainer.h"

#include <TH1D.h>
#include <algorithm>
#include <string>
#include <iostream>
#include "FileContainer.h"
#include "HistHolder.h"

namespace plotting {
HistHolderContainer::HistHolderContainer(const FileContainer& file_container,
                                         const std::string& name) {
  for (const auto& file : file_container) {
    auto raw = static_cast<TH1D*>(file->Get(name.c_str()));
    std::unique_ptr<HistHolder> unique{new HistHolder(raw)};
    this->push_back(std::move(unique));
  }
}

void HistHolderContainer::pullHistograms(const FileContainer& file_container,
                                         const std::string& name) {
  for (const auto& file : file_container) {
    auto raw = static_cast<TH1D*>(file->Get(name.c_str()));
    std::unique_ptr<HistHolder> unique{new HistHolder(raw)};
    std::string name = file->GetName();
    name = name.substr(name.find_last_of("/") + 1, name.size());
    name = name.substr(0, name.find_last_of("."));
    unique->setName(name.c_str());
    this->push_back(std::move(unique));
  }
}

void HistHolderContainer::setOptimalMax() {
  double max(0);
  for (const auto& hist : *this) {
    if (hist->getHist()->GetMaximum() > max) {
      max = hist->getHist()->GetMaximum();
    }
  }
  for (auto& hist : *this) {
    hist->setYRangeHigh(max * 1.5);
  }
}

void HistHolderContainer::setOptimalRatioRange() {
  double min(1.5);
  double max(0.5);
  for (const auto& hist : *this) {
    if (hist->getHist()->GetMaximum() > max) {
      max = hist->getHist()->GetMaximum();
    }
    if (hist->getHist()->GetMinimum() < min) {
      min = hist->getHist()->GetMinimum();
    }
  }
  min = round(10 * min - 1) / 10.;
  max = round(10 * max + 1) / 10.;
  if (min < 0) min = 0;
  for (auto& hist : *this) {
    hist->setYRangeLow(min);
    hist->setYRangeHigh(max);
  }
}

void HistHolderContainer::draw() const {
  for (const auto& hist : *this) {
    hist->draw();
  }
}

void HistHolderContainer::divideHistograms(const HistHolder& denom) {
  for (auto& hist : *this) {
    hist->getHist()->Divide(denom.getHist());
  }
}
}  // namespace plotting
