/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef FILECONTAINER_H_
#define FILECONTAINER_H_

#include <TFile.h>
#include <string>
#include <vector>

namespace plotting {
/**
 * Class managing a vector of TFile pointers. It includes some
 * specific functionality, for example creating this vector of TFile
 * pointers from a given list of file names.
 */
class FileContainer : public std::vector<TFile*> {
 public:
  //! Default constructor
  FileContainer() : std::vector<TFile*>{} {};

  /**
   * Construct a FileContainer from a list of file names. This will
   * automatically read the list of file names (given as string
   * obects), open the corresponding TFile objects and append their
   * pointers to the vector managed by this class.
   *
   * @param name_container Vector of file names (given as strings)
   */
  explicit FileContainer(const std::vector<std::string>& name_container);

  //! Destructor (close all files for memory clean-up)
  ~FileContainer();

  /**
   * Read a list of files from a text file. This will automatically
   * open the file, read the list of file names within it, open the
   * corresponding TFile objects and append their pointers to the
   * vector managed by this class.
   *
   * @param file_list Name of the text file containing the file names
   */
  void readFileList(const std::string& file_list);
};
}  // namespace plotting

#endif  // FILECONTAINER_H_
