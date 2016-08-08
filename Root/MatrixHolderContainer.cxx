// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "Plotting/MatrixHolderContainer.h"

#include <string>

namespace plotting {
MatrixHolderContainer::MatrixHolderContainer(
    const FileContainer& file_container, const std::string& name) {
  for (const auto& file : file_container) {
    auto raw = static_cast<TH2D*>(file->Get(name.c_str()));
    std::unique_ptr<MatrixHolder> unique{new MatrixHolder(raw)};
    this->push_back(std::move(unique));
  }
}

void MatrixHolderContainer::pullHistograms(const FileContainer& file_container,
                                           const std::string& name) {
  for (const auto& file : file_container) {
    auto raw = static_cast<TH2D*>(file->Get(name.c_str()));
    std::unique_ptr<MatrixHolder> unique{new MatrixHolder(raw)};
    std::string name = file->GetName();
    name = name.substr(name.find_last_of("/") + 1, name.size());
    name = name.substr(0, name.find_last_of("."));
    unique->setName(name.c_str());
    this->push_back(std::move(unique));
  }
}

void MatrixHolderContainer::draw() const {
  for (const auto& matrix : *this) {
    matrix->draw();
  }
}
}  // namespace plotting
