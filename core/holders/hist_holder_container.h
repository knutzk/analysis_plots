/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef HISTHOLDERCONTAINER_H_
#define HISTHOLDERCONTAINER_H_

#include "core/holders/hist_holder.h"
#include "core/holders/tholder_container.h"

namespace plotting {
/**
 * This class represents a vector of unique pointers to HistHolder
 * objects (which themselves own TH1D objects).
 */
class HistHolderContainer : public THolderContainer<HistHolder> {
 public:
  //! Inherits constructors from THolderContainer.
  using THolderContainer<HistHolder>::THolderContainer;

  //! Calculate and set the optimal maximal Y value.
  void setOptimalMax();

  /**
   * Divide all histograms of the container by another histogram.
   *
   * @param denom The histogram used as denominator.
   */
  void divideHistograms(const HistHolder& denom);

 protected:
  //! Second file container for the StudyJets files
  FileContainer file_container_2_;
};
}  // namespace plotting

#endif  // HISTHOLDERCONTAINER_H_
