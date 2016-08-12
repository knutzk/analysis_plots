// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_JETS_H_
#define STUDIES_JETS_H_

#include "Studies/Template.h"

namespace plotting {
class HistHolderContainer;
}

namespace plotting {
namespace studies {
class Jets : public plotting::studies::Template {
 public:
  virtual void execute();
  virtual void setDrawing(plotting::HistHolderContainer* hist_container);
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_JETS_H_
