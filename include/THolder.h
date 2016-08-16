// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef THOLDER_H_
#define THOLDER_H_

#include <memory>
#include <string>

/*
 * Template class to hold (and manage) some sort of histogram objects.
 */
namespace plotting {
template <typename T>
class THolder {
 public:
  /*
   * Default constructor
   */
  THolder() {}

  /*
   * Construct a THolder using an existing T object.
   * WARNING: This takes over ownership of the corresponding memory.
   * @param Pointer to the T object.
   */
  explicit THolder(T* hist) : hist_{hist}, name_{hist->GetName()} {}

  /*
   * Construct a THolder from a T object that is already
   * managed by a unique pointer.
   * WARNING: This transfers ownership to the THolder class.
   * @param Unique pointer of the T object
   */
  explicit THolder(std::unique_ptr<T> hist) : hist_{std::move(hist)} {}

  /*
   * Construct a THolder object from an existing one.
   * @param Reference of the existing THolder
   */
  THolder(const THolder& old)
      : hist_{std::unique_ptr<T>(old.hist_ ? new T(*old.hist_) : nullptr)},
        draw_options_{old.draw_options_},
        file_name_{old.file_name_},
        legend_title_{old.legend_title_},
        legend_options_{old.legend_options_},
        name_{old.name_},
        y1_{old.y1_},
        y2_{old.y2_} {}

  /*
   * Assignment operator to assign a THolder to another one.
   * @param THolder to be assigned
   */
  THolder& operator=(const THolder& H) {
    hist_(std::unique_ptr<T>(H.hist_ ? new T(*H.hist_) : nullptr));
  }

  /*
   * Destructor
   */
  virtual ~THolder() {}

  /*
   * Call the draw function of the T object using the given
   * plotting options etc.
   */
  void draw();

  T* const getHist() { return hist_.get(); }
  T const* const getHist() const { return hist_.get(); }

  double getYRangeHigh() const { return y2_; }
  double getYRangeLow() const { return y1_; }
  std::string getDrawOptions() const { return draw_options_; }
  std::string getFileName() const { return file_name_; }
  std::string getLegendOptions() const { return legend_options_; }
  std::string getLegendTitle() const { return legend_title_; }
  std::string getName() const { return name_; }

  void setDrawOptions(const std::string& options) { draw_options_ = options; }
  void setFileName(const std::string& name) { file_name_ = name; }
  void setLegendOptions(const std::string& options) {
    legend_options_ = options;
  }
  void setLegendTitle(const std::string& title) { legend_title_ = title; }
  void setName(const std::string& name) { name_ = name; }
  void setYRangeHigh(const double& high) { y2_ = high; }
  void setYRangeLow(const double& low) { y1_ = low; }

 protected:
  double y1_{0};
  double y2_{0};
  std::string draw_options_{"P1 ERR"};
  std::string file_name_{""};
  std::string legend_options_{"pel"};
  std::string legend_title_{"Legend title not set"};
  std::string name_{""};
  std::unique_ptr<T> hist_{nullptr};
};

template <typename T>
void THolder<T>::draw() {
  if (y1_ != y2_) {
    hist_->GetYaxis()->SetRangeUser(y1_, y2_);
  }
  // hist_->SetFillColor(fill_color_);
  // hist_->SetFillStyle(fill_style_);
  // hist_->SetLineColor(line_color_);
  // hist_->SetMarkerColor(marker_color_);
  // hist_->SetMarkerSize(marker_size_);
  // hist_->SetMarkerStyle(marker_style_);
  hist_->Draw(draw_options_.c_str());
}
}  // namespace plotting

#endif  // THOLDER_H_
