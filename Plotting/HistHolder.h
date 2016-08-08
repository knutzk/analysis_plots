/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef PLOTTING_HISTHOLDER_H_
#define PLOTTING_HISTHOLDER_H_

#include "Plotting/THolder.h"
#include <TH1D.h>

/*
 * Definition of the HistHolder class that holds and manages a TH1D
 * histogram object (via unique_ptr).
 */
namespace plotting {
class HistHolder : public THolder<TH1D> {
 public:
  /*
   * Default constructor calling the base class' default constructor.
   */
  HistHolder() : THolder::THolder() {
    setIncludeXOverflow(true);
    setIncludeXUnderflow(true);
  }

  /*
   * Contruct a HistHolder object from an existing TH1D object.
   * WARNING: This class takes ownership of the TH1D!
   * @param Pointer to the TH1D histogram.
   */
  explicit HistHolder(TH1D* hist) : THolder::THolder{hist} {
    setIncludeXOverflow(true);
    setIncludeXUnderflow(true);
  }

  /*
   * Construct a HistHolder object from an existing TH1D object which
   * is already managed by a unique pointer.
   * WARNING: This constructor moves ownership to the HistHolder object.
   * @param Unique pointer managing a TH1D histogram.
   */
  explicit HistHolder(std::unique_ptr<TH1D> hist)
      : THolder::THolder{std::move(hist)} {
    setIncludeXOverflow(true);
    setIncludeXUnderflow(true);
  }

  /*
   * Construct a new HistHolder object from an existing one.
   * @param Old HistHolder object.
   */
  HistHolder(const HistHolder& old)
      : THolder::THolder{old},
        include_x_overflow_{old.include_x_overflow_},
        include_x_underflow_{old.include_x_underflow_} {
    // do nothing
  }

  /*
   * Return whether overflow is set to be included.
   * @return True if it is set to included.
   */
  bool getIncludeXOverflow() { return include_x_overflow_; }

  /*
   * Set whether overflow shall be included or not.
   * @param Boolean
   */
  void setIncludeXOverflow(const bool& b);

  /*
   * Return whether underflow is set to be included.
   * @return True if it is set to included.
   */
  bool getIncludeXUnderflow() { return include_x_underflow_; }

  /*
   * Set whether underflow shall be included or not.
   * @param Boolean
   */
  void setIncludeXUnderflow(const bool& b);

 private:
  bool include_x_overflow_{false};
  bool include_x_underflow_{false};
  double overflow_content_{0.};
  double underflow_content_{0.};
};
}  // namespace plotting

#endif  // PLOTTING_HISTHOLDER_H_
