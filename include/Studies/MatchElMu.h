// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
// Copyright 2016 <Alexander Johnsen> <ajohnsen@cern.ch>
#ifndef STUDIES_MATCHELMU_H_
#define STUDIES_MATCHELMU_H_

#include <iostream>
#include "Studies/Template.h"

namespace plotting {
namespace studies {
/**
 * Compare KLFitter performance in the electron and muon
 * channels. This class expects two input files: the Matcher output
 * for the electron and the muon channel.
 */
class MatchElMu : public plotting::studies::Template {
 public:
  /**
   * Reimplementation of the execute() function from the Template
   * class. This function contains the main code to be processed
   * within this class.
   */
  void execute() override;

  /**
   * Reimplementation of the loadFiles() function from the Template
   * class. This function now reads all input files and then makes a
   * cross check if the given numbers equals '2'.
  */
  void loadFiles(const std::string& input_list) override;
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHELMU_H_
