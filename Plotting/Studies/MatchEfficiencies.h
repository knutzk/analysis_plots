// -*- mode: c++; -*-
#ifndef PLOTTING_STUDIES_MATCHEFFICIENCIES_H_
#define PLOTTING_STUDIES_MATCHEFFICIENCIES_H_

#include "Plotting/Studies/Template.h"

namespace plotting {
namespace studies {
class MatchEfficiencies : public plotting::studies::Template {
 public:
  virtual void execute();
};
}  // namespace studies
}  // namespace plotting

#endif  // PLOTTING_STUDIES_MATCHEFFICIENCIES_H_
