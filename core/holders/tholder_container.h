/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef THOLDERCONTAINER_H_
#define THOLDERCONTAINER_H_

#include <string>
#include "core/holders/tholder.h"
#include "core/utils/file_container.h"
#include "core/utils/unique_container.h"

class string;

namespace plotting {
/**
 * Definition of the THolderContainer class. This class represents a
 * vector of unique pointers that manage THolder objects.
 */
template <typename THolder>
class THolderContainer : public UniqueContainer<THolder> {
 public:
  //! The default constructor
  THolderContainer() : UniqueContainer<THolder>() {}

  /**
   * A custom constructor that pulls histograms from a file container.
   * This constructor uses the Get() function of the TFile class.
   * WARNING: This does not make any sanity checks whether a cast to
   * type T is actually valid!
   *
   * @param file_container The container (vector with TFile objects)
   * @param name The name of the histograms in these files
   */
  THolderContainer(const FileContainer& file_container,
                   const std::string& name);

  /**
   * A function to pull histograms called 'name' from a file
   * container. The histograms are appended to this container. This
   * constructor uses the Get() function of the TFile class. WARNING:
   * This does not make any sanity checks whether a cast to type T is
   * actually valid!
   *
   * @param file_container The container (vector with TFile objects)
   * @param name The name of the histograms in these files
   */
  void pullHistograms(const FileContainer& file_container,
                      const std::string& name);

  //! Call the draw() function for all entries of this container.
  inline virtual void draw() const {
    for (const auto& holder : *this) {
      holder->draw();
    }
  }
};

template <typename THolder>
THolderContainer<THolder>::THolderContainer(const FileContainer& file_container,
                                            const std::string& name) {
  for (const auto& file : file_container) {
    this->emplace_back(new THolder{file, name});
  }
}

template <typename THolder>
void THolderContainer<THolder>::pullHistograms(
    const FileContainer& file_container, const std::string& name) {
  for (const auto& file : file_container) {
    this->emplace_back(new THolder{file, name});
  }
}
}  // namespace plotting

#endif  // THOLDERCONTAINER_H_
