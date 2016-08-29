/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef MATRIXHOLDER_H_
#define MATRIXHOLDER_H_

#include "THolder.h"
#include <TH2D.h>

namespace plotting {
/**
 * Class to hold matrix objects (TH2D). This class also manages
 * ownership of the TH2D object via a unique pointer.
 */
class MatrixHolder : public THolder<TH2D> {
 public:
  //! Inherit constructors from the THolder template class.
  using THolder<TH2D>::THolder;

  /**
   * Round the matrix object managed by this class. This rounds both
   * values and errors saved in the different entries within the TH2D
   * object.
   *
   * @param n_places Number of desired decimal places.
   */
  void roundMatrix(const int& n_places);
};
}  // namespace plotting

#endif  // MATRIXHOLDER_H_
