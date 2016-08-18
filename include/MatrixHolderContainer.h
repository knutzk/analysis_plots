/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef MATRIXHOLDERCONTAINER_H_
#define MATRIXHOLDERCONTAINER_H_

#include <string>
#include "FileContainer.h"
#include "MatrixHolder.h"
#include "UniqueContainer.h"

/*
 * Definition of the MatrixHolderContainer class. This class represents
 * a vector of unique pointers to MatrixHolder objects. The MatrixHolder
 * objects themselves own TH2D objects.
 */
namespace plotting {
class MatrixHolderContainer : public UniqueContainer<MatrixHolder> {
 public:
  /*
   * The standard constructor
   */
  MatrixHolderContainer() : UniqueContainer<MatrixHolder>{} {}

  /*
   * A custom constructor that pulls histograms called 'name' from a
   * file container.
   * @param The file container (vector with TFile objects)
   * @param The name of the histograms in these files
   */
  MatrixHolderContainer(const FileContainer& file_container,
                        const std::string& name);

  /*
   * A function to pull histograms called 'name' from a file container.
   * @param The file container (vector with TFile objects)
   * @param The name of the histograms in these files
   */
  void pullHistograms(const FileContainer& file_container,
                      const std::string& name);

  /* Call the draw() function for all entries of this container.
   */
  void draw() const;
};
}  // namespace plotting

#endif  // MATRIXHOLDERCONTAINER_H_
