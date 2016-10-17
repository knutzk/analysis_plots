/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_LIKELIHOOD_H_
#define STUDIES_LIKELIHOOD_H_

#include "studies/template.h"

namespace plotting {
namespace studies {
/**
 * Make comparison plots of the KLFitter likelihood output. This class
 * expects three files: the likelihood output for diboson, ttbar and
 * ttz samples. Comparison between dibson and ttbar with ttz will be
 * produced.
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
