/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef ATLASLABEL_H_
#define ATLASLABEL_H_

#include <string>

namespace plotting {
/**
 * A class managing an ATLAS label to be printed on plots. This class
 * is usually owned by a Plotter class and should not be used by the
 * user directly. It allows changes of the displayed information,
 * e.g. energy, channel, 'work in progress' etc.
 */
class AtlasLabel {
 public:
  //! Get the ATLAS label string, e.g. "simulation".
  inline std::string getLabel() const { return string_label_; }

  //! Get the energy string, e.g. "13 TeV".
  inline std::string getEnergy() const { return string_energy_; }

  //! Get the channel string, e.g. "3mu + jets".
  inline std::string getChannel() const { return string_channel_; }

  //! Get the additional information string, e.g. "On-shell events only".
  inline std::string getAdditionalInfo() const {
    return string_additional_info_;
  }

  //! Get information whether this plot is intended for a thesis.
  inline bool getIsThesis() const { return is_thesis_; }

  //! Get information whether "Work In Progress" is used.
  inline bool getIsWorkInProgress() const { return is_in_progress_; }

  //! Get the x position of the ATLAS label.
  inline double getLabelX() const { return label_pos_x_; }

  //! Get the y position of the ATLAS label.
  inline double getLabelY() const { return label_pos_y_; }

  //! Get the x position of the channel label.
  inline double getChannelX() const { return channel_pos_x_; }

  //! Get the x position of the channel label.
  inline double getChannelY() const { return channel_pos_y_; }

  //! Get the label scaling factor.
  inline double getTextScale() const { return text_scale_; }

  //! Set the ATLAS label, e.g. "Simulation"
  inline void setLabel(const std::string& text) { string_label_ = text; }

  //! Set the energy label, e.g. "13 TeV"
  inline void setEnergy(const std::string& text) { string_energy_ = text; }

  //! Set the channel label, e.g. "3mu + jets"
  inline void setChannel(const std::string& text) { string_channel_ = text; }

  //! Set the additional information, e.g. "On-shell events only"
  inline void setAdditionalInfo(const std::string& text) {
    string_additional_info_ = text;
  }

  //! Set whether the plot is for a thesis. This will remove 'ATLAS'.
  inline void setIsThesis(const bool& t = true) { is_thesis_ = t; }

  //! Set whether the plot should have a tag "Work In Progress"
  inline void setIsWorkInProgress(const bool& t = true) { is_in_progress_ = t; }

  //! Set the x position of the ATLAS label.
  inline void setLabelX(const double& x) { label_pos_x_ = x; }

  //! Set the y position of the ATLAS label.
  inline void setLabelY(const double& y) { label_pos_y_ = y; }

  //! Set both the x and y position of the ATLAS label.
  inline void setLabelPosition(const double& x, const double& y) {
    label_pos_x_ = x;
    label_pos_y_ = y;
  }

  //! Set the x position of the channel label.
  inline void setChannelX(const double& x) {
    channel_pos_x_ = x;
    channel_pos_is_custom_ = true;
  }

  //! Set the y position of the channel label.
  inline void setChannelY(const double& y) {
    channel_pos_y_ = y;
    channel_pos_is_custom_ = true;
  }

  //! Set both the x and y position of the channel label.
  inline void setChannelPosition(const double& x, const double& y) {
    channel_pos_x_ = x;
    channel_pos_y_ = y;
    channel_pos_is_custom_ = true;
  }

  //! Set the text scaling factor
  inline void setTextScale(const double& scale) { text_scale_ = scale; }

  //! Plot the ATLAS label with all settings.
  void plot();

 private:
  bool channel_pos_is_custom_{false};
  bool is_thesis_{false};
  bool is_in_progress_{true};
  double channel_pos_x_{0};
  double channel_pos_y_{0};
  double label_pos_x_{0.16};
  double label_pos_y_{0.88};
  double text_scale_{1};
  std::string string_channel_{"3#mu+jets"};
  std::string string_energy_{"13 TeV"};
  std::string string_label_{"Simulation"};
  std::string string_additional_info_{""};
};
}  // namespace plotting

#endif  // ATLASLABEL_H_
