/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHJETMATRICES_H_
#define STUDIES_MATCHJETMATRICES_H_

#include "Studies/Template.h"

namespace plotting {
namespace studies {
class MatchJetMatrices : public plotting::studies::Template {
 public:
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHJETMATRICES_H_
