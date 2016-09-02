/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_LIKELIHOOD_H_
#define STUDIES_LIKELIHOOD_H_

#include "Studies/Template.h"

namespace plotting {
namespace studies {
/**
 * Make comparison plots of the KLFitter likelihood output (WIP).
 */
class Likelihood : public plotting::studies::Template {
  /**
   * Reimplementation of the execute() function from the Template
   * class. This function contains the main code to be processed
   * within this class.
   */
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_LIKELIHOOD_H_
