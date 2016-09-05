/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef MATRIXHOLDERCONTAINER_H_
#define MATRIXHOLDERCONTAINER_H_

#include <string>
#include "core/holders/matrix_holder.h"
#include "core/holders/tholder_container.h"

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
