// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_MATCHLONLO_H_
#define STUDIES_MATCHLONLO_H_

#include <iostream>
#include "Studies/Template.h"

namespace plotting {
namespace studies {
class MatchLONLO : public plotting::studies::Template {
 public:
  void execute() override;

  void loadFiles(const std::string& input_list) override;

 protected:
  FileContainer file_container_2_;
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_MATCHLONLO_H_
