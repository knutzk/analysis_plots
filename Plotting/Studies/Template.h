/* -*- mode: c++; -*- */
#ifndef PLOTTING_STUDIES_TEMPLATE_H_
#define PLOTTING_STUDIES_TEMPLATE_H_

#include "Plotting/FileContainer.h"

namespace plotting {
namespace studies {
class Template {
 public:
  Template() {}
  virtual ~Template() {}

  inline void loadFiles(char* input_list) {
    file_container_.readFileList(input_list);
  }
  virtual void execute() = 0;

 protected:
  FileContainer file_container_{};
};
}  // namespace studies
}  // namespace plotting

#endif
