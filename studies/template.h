/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef STUDIES_TEMPLATE_H_
#define STUDIES_TEMPLATE_H_

#include "core/utils/file_container.h"

namespace plotting {
namespace studies {
/**
 * A purely virtual class that serves as a template for various
 * studies. This class provides common functions that are re-used
 * within all those studies.
 */
class Template {
 public:
  /**
   * Open a given list of files and store these files in a
   * FileContainer. This utilises functionality of the FileContainer
   * class to read a list of files, open TFile objects and store
   * pointer to these File objects in a container.
   *
   * @param input_list The name of the file containing the input list
   */
  inline virtual void loadFiles(const std::string& input_list) {
    file_container_.readFileList(input_list);
  }

  /**
   * Purely virtual function that contains the main code to be
   * executed for individual studies.
   */
  virtual void execute() = 0;

 protected:
  //! Container with pointers to TFile objects
  FileContainer file_container_{};
};
}  // namespace studies
}  // namespace plotting

#endif  // STUDIES_TEMPLATE_H_
