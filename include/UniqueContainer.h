/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef UNIQUECONTAINER_H_
#define UNIQUECONTAINER_H_

#include <memory>
#include <vector>

namespace plotting {
/**
 * A template class that corresponds to a vector of unique pointer
 * objects. This is basically just a normal vector, but it takes care
 * of making *deep* copies in order to ensure uniqueness of the memory
 * managed by the unique pointers.
 */
template <typename T>
class UniqueContainer : public std::vector<std::unique_ptr<T>> {
 public:
  //! The default constructor
  UniqueContainer() : std::vector<std::unique_ptr<T>>{} {}

  /**
   * Construct a new UniqueContainer using an existing one. This makes
   * *deep* copies of the objects the unique pointers manage. This
   * ensures their uniqueness and does not caus any problems at
   * deletion time.
   *
   * @param cont The existing container
   */
  UniqueContainer(const UniqueContainer& cont);

  /**
   * Assignment operator to assign a UniqueContainer to another one.
   * This makes *deep* copies of the objects the unique pointers
   * manage. This ensures their uniqueness and does not caus any
   * problems at deletion time.
   *
   * @param cont UniqueContainer to be assigned.
   */
  UniqueContainer& operator=(const UniqueContainer<T>& cont);
};

template <typename T>
UniqueContainer<T>::UniqueContainer(const UniqueContainer<T>& cont) {
  for (const auto& element : cont) {
    this->emplace_back(new T{*element});
  }
}

template <typename T>
UniqueContainer<T>& UniqueContainer<T>::operator=(
    const UniqueContainer<T>& cont) {
  for (const auto& element : cont) {
    this->emplace_back(new T{*element});
  }
}
}  // namespace plotting

#endif  // UNIQUECONTAINER_H_
