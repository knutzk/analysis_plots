// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "AtlasLabel.h"

#include <TLatex.h>
#include <TPad.h>
#include <sstream>

namespace plotting {
void AtlasLabel::plot() {
  if (string_label_.empty()) return;

  TLatex label;
  label.SetNDC();
  label.SetTextFont(73);
  label.SetTextSize(20);
  label.DrawLatex(label_pos_x_, label_pos_y_, "ATLAS");

  double delx = 0.145 * gPad->GetWh() / gPad->GetWw();
  double dely = 0.05;

  if (!channel_pos_is_custom_) {
    channel_pos_x_ = label_pos_x_;
    channel_pos_y_ = label_pos_y_ - dely;
    if (is_in_progress_) {
      channel_pos_y_ -= dely;
    }
  }

  TLatex other_info;
  other_info.SetNDC();
  other_info.SetTextFont(43);
  other_info.SetTextSize(20);

  // 1) Draw the label, e.g. "Simulation"
  other_info.DrawLatex(label_pos_x_ + delx, label_pos_y_,
                       string_label_.c_str());

  // 2) Draw "Work In Progress"
  if (is_in_progress_) {
    other_info.DrawLatex(label_pos_x_, label_pos_y_ - dely, "Work In Progress");
  }

  // 3) Draw channel and energy (if given)
  std::ostringstream ostring;
  if (!string_channel_.empty() && !string_energy_.empty()) {
    ostring << string_channel_ << ",  #sqrt{s} = " << string_energy_;
  } else if (!string_energy_.empty()) {
    ostring << "#sqrt{s} = " << string_energy_;
  } else if (!string_channel_.empty()) {
    ostring << string_channel_;
  }
  other_info.DrawLatex(channel_pos_x_, channel_pos_y_, ostring.str().c_str());

  // 4) Add additional info e.g. specific cuts applied
  if (!string_additional_info_.empty()) {
    other_info.DrawLatex(channel_pos_x_, channel_pos_y_ - dely,
                         string_additional_info_.c_str());
  }
}
}  // namespace plotting
