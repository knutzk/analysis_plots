// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHLONLO_H_
#define STUDIES_MATCHLONLO_H_

#include <iostream>
#include "studies/template.h"

namespace plotting {
namespace studies {
/**
 * Check the performance of KLFitter for LO and NLO samples compared
 * to ttbar. This class expects six input files: The Matcher output
 * for ttz NLO, ttz LO and ttbar; and the StudyJets output for those
 * samples.
 */
class MatchLONLO : public plotting::studies::Template {
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
   * cross check if the given numbers equals '6'. Afterwards, the
   * second half of the files is transferred to
   * file_container_2_. This procedure is necessary, because first and
   * second half of the files are not of the same type (Matcher and
   * StudyJets output).
  */
  void loadFiles(const std::string& input_list) override;

 protected:
  //! Second file container for the StudyJets files
  FileContainer file_container_2_;
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHLONLO_H_
