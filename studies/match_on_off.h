// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHONOFF_H_
#define STUDIES_MATCHONOFF_H_

#include <iostream>
#include "studies/template.h"

namespace plotting {
namespace studies {
/**
 * Check the performance of different KLFitter likelihoods for
 * on-shell, off-shell and all events. This class currently expects
 * three files: ttZ processed with the combined likelihood, with the
 * on-shell likelihood and with the off-shell likelihood.
 */
class MatchOnOff : public plotting::studies::Template {
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
   * cross check if the given numbers equals '3'.
  */
  void loadFiles(const std::string& input_list) override;

 protected:
  //! Second file container for the StudyJets files
  FileContainer file_container_2_;
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHONOFF_H_
