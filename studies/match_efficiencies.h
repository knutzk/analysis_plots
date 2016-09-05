// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHEFFICIENCIES_H_
#define STUDIES_MATCHEFFICIENCIES_H_

#include "studies/template.h"

namespace plotting {
namespace studies {
/**
 * Compare efficiencies of different KLFitter modes. This expects six
 * different running mdoes in total: four ttZ modes (kDedicated,
 * kAmongThree with kWP, kAmongThree with kNT, kLeading with kNT), two
 * ttbar modes (kWP and kNT).
 */
class MatchEfficiencies : public plotting::studies::Template {
 public:
  /**
   * Reimplementation of the execute() function from the Template
   * class. This function contains the main code to be processed
   * within this class.
   */
  virtual void execute() override;
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHEFFICIENCIES_H_
