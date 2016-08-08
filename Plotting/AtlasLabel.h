/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef PLOTTING_ATLASLABEL_H_
#define PLOTTING_ATLASLABEL_H_

#include <string>

namespace plotting {
class AtlasLabel {
 public:
  /*
   * Get the ATLAS label string, e.g. "simulation".
   * @return string
   */
  std::string getLabel() const { return string_label_; }

  /*
   * Get the energy string, e.g. "13 TeV"
   * @return string
   */
  std::string getEnergy() const { return string_energy_; }

  /*
   * Get the channel string, e.g. "3mu + jets"
   * @return string
   */
  std::string getChannel() const { return string_channel_; }

  /*
   * Get information whether "Work In Progress" is used
   * @return bool
   */
  bool getIsWorkInProgress() const { return is_in_progress_; }

  /*
   * Get the x position of the ATLAS label
   * @return int position
   */
  double getLabelX() const { return label_pos_x_; }

  /*
   * Get the y position of the ATLAS label
   * @return int position
   */
  double getLabelY() const { return label_pos_y_; }

  /*
   * Get the x position of the channel label
   * @return int position
   */
  double getChannelX() const { return channel_pos_x_; }

  /*
   * Get the x position of the channel label
   * @return int position
   */
  double getChannelY() const { return channel_pos_y_; }

  /*
   * Get the label scaling factor
   * @return double scaling factor
   */
  double getTextScale() const { return text_scale_; }

  /*
   * Set the ATLAS label, e.g. "Simulation"
   * @param string
   */
  inline void setLabel(const std::string& text) { string_label_ = text; }

  /*
   * Set the energy label, e.g. "13 TeV"
   * @param string
   */
  inline void setEnergy(const std::string& text) { string_energy_ = text; }

  /*
   * Set the channel label, e.g. "3mu + jets"
   * @param string
   */
  inline void setChannel(const std::string& text) { string_channel_ = text; }

  /*
   * Set whether the plot should have a tag "Work In Progress"
   * @param bool
   */
  inline void setIsWorkInProgress(const bool& t = true) { is_in_progress_ = t; }

  /*
   * Set the x position of the ATLAS label.
   * @param int
   */
  inline void setLabelX(const double& x) { label_pos_x_ = x; }

  /*
   * Set the y position of the ATLAS label.
   * @param int
   */
  inline void setLabelY(const double& y) { label_pos_y_ = y; }

  /*
   * Set both the x and y position of the ATLAS label.
   * @param int
   */
  inline void setLabelPosition(const double& x, const double& y) {
    label_pos_x_ = x;
    label_pos_y_ = y;
  }

  /*
   * Set the x position of the channel label.
   * @param int
   */
  inline void setChannelX(const double& x) {
    channel_pos_x_ = x;
    channel_pos_is_custom_ = true;
  }

  /*
   * Set the y position of the channel label.
   * @param int
   */
  inline void setChannelY(const double& y) {
    channel_pos_y_ = y;
    channel_pos_is_custom_ = true;
  }

  /*
   * Set both the x and y position of the channel label.
   * @param int
   */
  inline void setChannelPosition(const double& x, const double& y) {
    channel_pos_x_ = x;
    channel_pos_y_ = y;
    channel_pos_is_custom_ = true;
  }

  /*
   * Set the text scaling factor
   * @param double scale
   */
  void setTextScale(const double& scale) { text_scale_ = scale; }

  /*
   * Plot the ATLAS label with all settings.
   */
  void plot();

 private:
  bool channel_pos_is_custom_{false};
  bool is_in_progress_{true};
  double channel_pos_x_{0};
  double channel_pos_y_{0};
  double label_pos_x_{0.16};
  double label_pos_y_{0.88};
  double text_scale_{1};
  std::string string_channel_{"3#mu+jets"};
  std::string string_energy_{"13 TeV"};
  std::string string_label_{"Simulation"};
};
}  // namespace plotting

#endif  // PLOTTING_ATLASLABEL_H_
