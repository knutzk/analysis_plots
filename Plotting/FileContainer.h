/* -*- mode: c++; -*- */
#ifndef PLOTTING_FILECONTAINER_H_
#define PLOTTING_FILECONTAINER_H_

#include <TFile.h>
#include <string>
#include <vector>

namespace plotting {
class FileContainer : public std::vector<TFile*> {
 public:
  /*
   * Default constructor
   */
  FileContainer() : std::vector<TFile*>() {}

  /*
   * Constructor opening files from a string container
   * @param Vector of file names
   */
  explicit FileContainer(const std::vector<std::string>& name_container) {
    for (const auto& name : name_container) {
      push_back(TFile::Open(name.c_str()));
    }
  }

  /*
   * Destructor (close all files for memory clean-up)
   */
  ~FileContainer() {
    for (auto& file : *this) {
      file->Close();
    }
  }

  /*
   * Read a list of files from a text file
   * @param Name of the text file containing the file names
   */
  void readFileList(const std::string& file_list);
};
}  // namespace plotting

#endif  // PLOTTING_FILECONTAINER_H_
