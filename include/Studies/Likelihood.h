/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_LIKELIHOOD_H_
#define STUDIES_LIKELIHOOD_H_

#include "Studies/Template.h"

namespace plotting {
namespace studies {
class Likelihood : public plotting::studies::Template {
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_LIKELIHOOD_H_
