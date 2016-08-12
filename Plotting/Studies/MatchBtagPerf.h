// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHBTAGPERF_H_
#define STUDIES_MATCHBTAGPERF_H_

#include "Studies/Template.h"

namespace plotting {
namespace studies {
class MatchBtagPerf : public plotting::studies::Template {
 public:
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHBTAGPERF_H_
