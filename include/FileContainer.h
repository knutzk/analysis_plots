/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef FILECONTAINER_H_
#define FILECONTAINER_H_

#include <TFile.h>
#include <string>
#include <vector>

namespace plotting {
class FileContainer : public std::vector<TFile*> {
 public:
  /*
   * Default constructor
   */
  FileContainer() : std::vector<TFile*>{} {}

  /*
   * Constructor opening files from a string container
   * @param Vector of file names
   */
  explicit FileContainer(const std::vector<std::string>& name_container);

  /*
   * Destructor (close all files for memory clean-up)
   */
  ~FileContainer();

  /*
   * Read a list of files from a text file
   * @param Name of the text file containing the file names
   */
  void readFileList(const std::string& file_list);
};
}  // namespace plotting

#endif  // FILECONTAINER_H_
