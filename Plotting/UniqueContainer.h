/* -*- mode: c++; -*- */
#ifndef PLOTTING_UNIQUE_CONTAINER_H_
#define PLOTTING_UNIQUE_CONTAINER_H_

#include <memory>
#include <vector>

/*
 * A template class called 'UniqueContainer' that corresponds
 * to a vector of unique pointer objects.
 */
namespace plotting {
template <typename T>
class UniqueContainer : public std::vector<std::unique_ptr<T>> {
public:
  /*
   * Default constructor
   */
  UniqueContainer() : std::vector<std::unique_ptr<T>>() {}

  /*
   * Construct a new UniqueContainer using an existing one.
   */
  UniqueContainer(const UniqueContainer& cont);

  /*
   * Assignment operator to assign a UniqueContainer to another one.
   * @param UniqueContainer to be assigned.
   */
  UniqueContainer& operator=(const UniqueContainer<T>& cont);
};

template <typename T>
UniqueContainer<T>::UniqueContainer(const UniqueContainer<T>& cont) {
  for (const auto& element : cont) {
    this->emplace_back(new T(*element));
  }
}

template <typename T>
UniqueContainer<T>& UniqueContainer<T>::operator=(const UniqueContainer<T>& cont) {
  for (const auto& element : cont) {
    this->emplace_back(new T(*element));
  }
}
}  // namespace plotting

#endif  // PLOTTING_UNIQUE_CONTAINER_H_
