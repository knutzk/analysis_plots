/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_TEMPLATE_H_
#define STUDIES_TEMPLATE_H_

#include "FileContainer.h"

namespace plotting {
namespace studies {
class Template {
 public:
  Template() {}
  virtual ~Template() {}

  virtual void loadFiles(char* input_list) {
    file_container_.readFileList(input_list);
  }
  virtual void execute() = 0;

 protected:
  FileContainer file_container_{};
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_TEMPLATE_H_
