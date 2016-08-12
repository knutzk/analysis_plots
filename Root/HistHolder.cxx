// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "HistHolder.h"

namespace plotting {
void HistHolder::setIncludeXOverflow(const bool& b) {
  // Do nothing if set to the same value as before.
  if (b == include_x_overflow_) return;

  include_x_overflow_ = b;

  // If changed to true, add overflow.
  if (include_x_overflow_) {
    const auto& n_bins = hist_->GetNbinsX();
    overflow_content_ = hist_->GetBinContent(n_bins + 1);
    if (overflow_content_ > 0) {
      const auto& old = hist_->GetBinContent(n_bins);
      hist_->SetBinContent(n_bins, old + overflow_content_);
      hist_->SetBinContent(n_bins + 1, 0);
    }
  }

  // If changed to false, remove overflow again.
  if (!include_x_overflow_) {
    const auto& n_bins = hist_->GetNbinsX();
    const auto& old = hist_->GetBinContent(n_bins);
    hist_->SetBinContent(n_bins, old - overflow_content_);
    hist_->SetBinContent(n_bins + 1, overflow_content_);
    overflow_content_ = 0.;
  }
}

void HistHolder::setIncludeXUnderflow(const bool& b) {
  // Do nothing if set to the same value as before.
  if (b == include_x_underflow_) return;

  include_x_underflow_ = b;

  // If changed to true, add underflow.
  if (include_x_underflow_) {
    underflow_content_ = hist_->GetBinContent(0);
    if (underflow_content_ > 0) {
      const auto& old = hist_->GetBinContent(1);
      hist_->SetBinContent(1, old + underflow_content_);
      hist_->SetBinContent(0, 0);
    }
  }

  // If changed to false, remove underflow again.
  if (!include_x_underflow_) {
    const auto& old = hist_->GetBinContent(1);
    hist_->SetBinContent(1, old - underflow_content_);
    hist_->SetBinContent(0, underflow_content_);
    underflow_content_ = 0;
  }
}
}  // namespace plotting
