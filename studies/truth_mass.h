// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_TRUTHMASS_H_
#define STUDIES_TRUTHMASS_H_

#include <iostream>
#include "studies/template.h"

namespace plotting {
namespace studies {
/**
 * Class to create a truth-level Z mass distribution plot. The class
 * divides on-shell and off-shell contributions and stacks them on top
 * of each other.
 */
class TruthMass : public plotting::studies::Template {
 public:
  /**
   * Reimplementation of the execute() function from the Template
   * class. This function contains the main code to be processed
   * within this class.
   */
  void execute() override;
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_TRUTHMASS_H_
