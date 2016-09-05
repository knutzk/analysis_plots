// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "core/utils/file_container.h"

namespace plotting {
FileContainer::FileContainer(const std::vector<std::string>& name_container) {
  for (const auto& name : name_container) {
    push_back(TFile::Open(name.c_str()));
  }
}

FileContainer::~FileContainer() {
  for (auto& file : *this) {
    file->Close();
  }
}

void FileContainer::readFileList(const std::string& file_list) {
  std::ifstream file_input;
  file_input.open(file_list);

  if (!file_input.is_open()) {
    std::cout << "File \"" << file_list << "\" not found." << std::endl;
    throw false;
    return;
  }

  std::string name{""};
  while (!file_input.eof()) {
    name = "";
    file_input >> name;
    if (name.size() == 0) break;
    push_back(TFile::Open(name.c_str()));
  }
  file_input.close();
  return;
}
}  // namespace plotting
