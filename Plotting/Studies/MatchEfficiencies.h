// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHEFFICIENCIES_H_
#define STUDIES_MATCHEFFICIENCIES_H_

#include "Studies/Template.h"

namespace plotting {
namespace studies {
class MatchEfficiencies : public plotting::studies::Template {
 public:
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHEFFICIENCIES_H_
