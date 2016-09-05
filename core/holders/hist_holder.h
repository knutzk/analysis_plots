/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef HISTHOLDER_H_
#define HISTHOLDER_H_

#include <TH1D.h>
#include "core/holders/tholder.h"

namespace plotting {
/**
 * A class that holds and manages a TH1D histogram object (via
 * unique pointers).
 */
class HistHolder : public THolder<TH1D> {
 public:
  //! Inherit constructors from the THolder template class.
  using THolder<TH1D>::THolder;

  /**
   * Construct a new HistHolder object from an existing one. This
   * constructor simply makes an exact copy of the old object.
   *
   * @param old The old HistHolder object
   */
  HistHolder(const HistHolder& old)
      : THolder::THolder{old},
        include_x_overflow_{old.include_x_overflow_},
        include_x_underflow_{old.include_x_underflow_},
        y1_{old.y1_},
        y2_{old.y2_} {}

  //! Return whether overflow is set to be included.
  inline bool getIncludeXOverflow() { return include_x_overflow_; }

  //! Return whether overflow is set to be include.
  inline bool getIncludeXUnderflow() { return include_x_underflow_; }

  //! Get the upper value of the Y range.
  inline double getYRangeHigh() const { return y2_; }

  //! Get the lower value of the Y range.
  inline double getYRangeLow() const { return y1_; }

  /**
   * Set whether overflow shall be included or not.
   *
   * @param b Boolean whether to include overflow
   */
  void setIncludeXOverflow(const bool& b = true);

  /**
   * Set whether underflow shall be included or not.
   *
   * @param b Boolean whether to include underflow
   */
  void setIncludeXUnderflow(const bool& b = true);

  /**
   * Set the upper range of the Y range.
   *
   * @param high The upper value of the Y range
   */
  inline void setYRangeHigh(const double& high) { y2_ = high; }

  /**
   * Set the lower range of the Y range.
   *
   * @param low The lower value of the Y range
   */
  inline void setYRangeLow(const double& low) { y1_ = low; }

  //! Draw the histogram hold by this class.
  inline void draw() const override {
    if (y1_ != y2_) hist_->GetYaxis()->SetRangeUser(y1_, y2_);
    THolder::draw();
  }

 private:
  double y1_{0};
  double y2_{0};
  bool include_x_overflow_{false};
  bool include_x_underflow_{false};
  double overflow_content_{0.};
  double underflow_content_{0.};
};
}  // namespace plotting

#endif  // HISTHOLDER_H_
