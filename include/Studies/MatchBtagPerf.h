// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHBTAGPERF_H_
#define STUDIES_MATCHBTAGPERF_H_

#include "Studies/Template.h"

namespace plotting {
namespace studies {
/**
 * Check the b-tagging performance of different KLFitter runs. This
 * class was designed to check whether the jet matching performance
 * for fixed b-tagging efficiencies or kinematic-dependent
 * efficiencies is better.
 */
class MatchBtagPerf : public plotting::studies::Template {
 public:
  /**
   * Reimplementation of the execute() function from the Template
   * class. This function contains the main code to be processed
   * within this class.
   */
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHBTAGPERF_H_
