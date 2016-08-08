/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef PLOTTING_STUDIES_LIKELIHOOD_H_
#define PLOTTING_STUDIES_LIKELIHOOD_H_

#include "Plotting/Studies/Template.h"

namespace plotting {
namespace studies {
class Likelihood : public plotting::studies::Template {
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // PLOTTING_STUDIES_LIKELIHOOD_H_
