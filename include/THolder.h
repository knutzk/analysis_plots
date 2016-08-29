// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef THOLDER_H_
#define THOLDER_H_

#include <TFile.h>
#include <memory>
#include <string>

namespace plotting {
/**
 * Template class to hold (and manage) different sorts of histogram
 * objects. The main class member is a unique pointer that holds an
 * object of type T and manages its memory.
 */
template <typename T>
class THolder {
 public:
  //! Default constructor
  inline THolder() {}

  /**
   * Construct a THolder using an existing T object. This will first
   * create a unique pointer taking care of the memory that T points
   * to. Then the THolder will be wrapped around it to manage this
   * histogram object entirely. WARNING: This constructor takes over
   * ownership of the corresponding memory.
   *
   * @param hist Pointer to the T object.
   */
  inline explicit THolder(T* hist) : hist_{hist}, name_{hist->GetName()} {}

  /**
   * Construct a THolder from a T object that is already managed by a
   * unique pointer. It is expected that the unique pointer properly
   * takes care of the requested memory already (and did *not* let
   * ROOT take care of it). WARNING: This constructor transfers
   * ownership of the memory to the THolder class.
   *
   * @param hist Unique pointer of the T object
   */
  inline explicit THolder(std::unique_ptr<T> hist) : hist_{std::move(hist)} {}

  /**
   * Construct a THolder object from an existing one. This copy
   * constructor will create an identical copy of the existing THolder
   * object an instantiate a new one.
   *
   * @param old Reference of the existing THolder
   */
  explicit THolder(const THolder& old);

  /**
   * Construct a THolder object by pulling a T object from a given
   * TFile. This constructor uses the Get() function of the TFile
   * class and receives a pointer to a TObject. This pointer is then
   * casted to be of type T. WARNING: This does not make any sanity
   * checks whether this cast is actually valid!
   *
   * @param file The TFile object
   * @param name The name of the T object in the file
   */
  THolder(TFile* file, const std::string& name);

  /**
   * Assignment operator to assign a THolder to another one.
   *
   * @param holder THolder to be assigned
   */
  THolder& operator=(const THolder& holder);

  //! Call the draw function of the T object and use the given
  //! plotting options.
  inline virtual void draw() const { hist_->Draw(draw_options_.c_str()); }

  //! Get a pointer to the histogram managed by this holder class.
  inline T* const getHist() { return hist_.get(); }

  //! Get a pointer to the histogram managed by this holder class.
  inline const T* const getHist() const { return hist_.get(); }

  // =================================================================

  //! Get the draw options set for the histogram object.
  inline std::string getDrawOptions() const { return draw_options_; }

  //! Get the name of the file where the histgram originates from.
  inline std::string getFileName() const { return file_name_; }

  //! Get the legend options set for the histogram object.
  inline std::string getLegendOptions() const { return legend_options_; }

  //! Get the legend title set for the histogram object.
  inline std::string getLegendTitle() const { return legend_title_; }

  //! Get the name set for the histogram object.
  inline std::string getName() const { return name_; }

  //! Set the draw options for the histogram object.
  inline void setDrawOptions(const std::string& options) {
    draw_options_ = options;
  }

  //! Set the file name where the histogram originates from.
  inline void setFileName(const std::string& name) { file_name_ = name; }

  //! Set the legend options for the histogram object.
  inline void setLegendOptions(const std::string& options) {
    legend_options_ = options;
  }

  //! Set the legend title for the histogram object.
  inline void setLegendTitle(const std::string& title) {
    legend_title_ = title;
  }

  //! Set the name for the histogram object.
  inline void setName(const std::string& name) { name_ = name; }

 protected:
  //! The unique pointer managing the T object.
  std::unique_ptr<T> hist_{nullptr};

 private:
  std::string draw_options_{"P1 ERR"};
  std::string file_name_{""};
  std::string legend_options_{"pel"};
  std::string legend_title_{"Legend title not set"};
  std::string name_{""};
};

template <typename T>
THolder<T>::THolder(const THolder& old)
    : hist_{std::unique_ptr<T>{old.hist_ ? new T{*old.hist_} : nullptr}},
      draw_options_{old.draw_options_},
      file_name_{old.file_name_},
      legend_title_{old.legend_title_},
      legend_options_{old.legend_options_},
      name_{old.name_} {}

template <typename T>
THolder<T>::THolder(TFile* file, const std::string& name)
    : hist_{new T{*static_cast<T*>(file->Get(name.c_str()))}} {
  std::string file_name = file->GetName();
  file_name =
      file_name.substr(file_name.find_last_of("/") + 1, file_name.size());
  file_name = file_name.substr(0, file_name.find_last_of("."));
  setFileName(file_name.c_str());
  setName(name.c_str());
}

template <typename T>
THolder<T>& THolder<T>::operator=(const THolder<T>& H) {
  hist_ = std::unique_ptr<T>{H.hist_ ? new T{*H.hist_} : nullptr};
}
}  // namespace plotting

#endif  // THOLDER_H_
