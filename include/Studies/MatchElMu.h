// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
// Copyright 2016 <Alexander Johnsen> <ajohnsen@cern.ch>
#ifndef STUDIES_MATCHELMU_H_
#define STUDIES_MATCHELMU_H_

#include <iostream>
#include "Studies/Template.h"

namespace plotting {
namespace studies {
class MatchElMu : public plotting::studies::Template {
 public:
  void execute() override;

  void loadFiles(const std::string& input_list) override;

 protected:
  FileContainer file_container_2_;
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHELMU_H_
