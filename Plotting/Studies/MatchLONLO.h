// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef PLOTTING_STUDIES_MATCHLONLO_H_
#define PLOTTING_STUDIES_MATCHLONLO_H_

#include <iostream>
#include "Plotting/Studies/Template.h"

namespace plotting {
namespace studies {
class MatchLONLO : public plotting::studies::Template {
 public:
  void execute() override;

  void loadFiles(char* input_list) override;

 protected:
  FileContainer file_container_2_;
};
}  // namespace studies
}  // namespace plotting

#endif  // PLOTTING_STUDIES_MATCHLONLO_H_
