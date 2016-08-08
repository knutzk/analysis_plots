/* -*- mode: c++; -*- */
#ifndef PLOTTING_HISTHOLDERCONTAINER_H_
#define PLOTTING_HISTHOLDERCONTAINER_H_

#include <string>
#include "Plotting/FileContainer.h"
#include "Plotting/HistHolder.h"
#include "Plotting/UniqueContainer.h"

class string;

/*
 * Definition of the HistHolderContainer class. This class represents
 * a vector of unique pointers to HistHolder objects. The HistHolder
 * objects themselves own TH1D objects.
 */
namespace plotting {
class HistHolderContainer : public UniqueContainer<HistHolder> {
 public:
  /*
   * The standard constructor
   */
  HistHolderContainer() : UniqueContainer<HistHolder>() {}

  /*
   * A custom constructor that pulls histograms called 'name' from a
   * file container.
   * @param The file container (vector with TFile objects)
   * @param The name of the histograms in these files
   */
  HistHolderContainer(const FileContainer& file_container,
                      const std::string& name);

  /*
   * A function to pull histograms called 'name' from a file container.
   * The histograms are appended to this container.
   * @param The file container (vector with TFile objects)
   * @param The name of the histograms in these files
   */
  void pullHistograms(const FileContainer& file_container,
                      const std::string& name);

  /*
   * Calculate the optimal maximal y value for the histograms and set
   * the y range to this custom value.
   */
  void setOptimalMax();

  /*
   * Calculate the optimal y values for a ratio plot.
   */
  void setOptimalRatioRange();

  /*
   * Call the draw() function for all entries of this container.
   */
  void draw() const;

  /*
   * A function to divide all histograms of the container by another
   * histogram.
   * @param The histogram used as denominator.
   */
  void divideHistograms(const HistHolder& denom);
};
}  // namespace plotting

#endif  // PLOTTING_HISTHOLDERCONTAINER_H_
