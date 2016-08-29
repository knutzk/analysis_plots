/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef MATRIXHOLDERCONTAINER_H_
#define MATRIXHOLDERCONTAINER_H_

#include <string>
#include "MatrixHolder.h"
#include "THolderContainer.h"

namespace plotting {
/**
 * A class representing a vector of unique pointers to MatrixHolder
 * objects. The MatrixHolder objects themselves own TH2D objects.
 */
class MatrixHolderContainer : public THolderContainer<MatrixHolder> {
  //! Inherit constructors from THolderContainer template class.
  using THolderContainer<MatrixHolder>::THolderContainer;
};
}  // namespace plotting

#endif  // MATRIXHOLDERCONTAINER_H_
