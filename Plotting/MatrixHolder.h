/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef PLOTTING_MATRIXHOLDER_H_
#define PLOTTING_MATRIXHOLDER_H_

#include "Plotting/THolder.h"
#include <TH2D.h>

/*
 * Class to hold matrix objects (TH2D). This class also manages
 * ownership of the TH2D object via unique pointer.
 */
namespace plotting {
class MatrixHolder : public THolder<TH2D> {
 public:
  /*
   * Default constructor calling the base class constructor.
   */
  MatrixHolder() : THolder::THolder() {}

  /*
   * Construct a MatrixHolder from an existing TH2D object.
   * WARNING: This takes over ownership of the corresponding memory!
   * @param Pointer to the TH2D object.
   */
  explicit MatrixHolder(TH2D* matrix) : THolder::THolder{matrix} {}

  /*
   * Construct a MatrixHolder from an existing TH2D that is already
   * managed by a unique pointer.
   * WARNING: This transfers ownership to the MatrixHolder class.
   * @param Unique pointer to the TH2D object.
   */
  explicit MatrixHolder(std::unique_ptr<TH2D> matrix)
      : THolder::THolder{std::move(matrix)} {}

  /*
   * Construct a new MatrixHolder from an existing one.
   * @param The old MatrixHolder object.
   */
  MatrixHolder(const MatrixHolder& old) : THolder::THolder{old} {}

  /*
   * Round the matrix object managed by this class.
   * @param Number of desired decimal places.
   */
  void roundMatrix(const int& n_places);
};
// using MatrixHolder = THolder<TH2D>;
}  // namespace plotting

#endif  // PLOTTING_MATRIXHOLDER_H_
