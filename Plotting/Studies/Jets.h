// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef PLOTTING_STUDIES_JETS_H_
#define PLOTTING_STUDIES_JETS_H_

#include "Plotting/Studies/Template.h"

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

#endif  // PLOTTING_STUDIES_JETS_H_
