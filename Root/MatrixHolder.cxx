#include "Plotting/MatrixHolder.h"

namespace plotting {
void MatrixHolder::roundMatrix(const int& n_places) {
  const int n_rows = hist_->GetNbinsY();
  const int n_columns = hist_->GetNbinsX();
  double value, error;
  for (int column = 1; column < n_columns + 1; ++column) {
    for (int row = 1; row < n_rows + 1; ++row) {
      value = hist_->GetBinContent(column, row);
      error = hist_->GetBinError(column, row);
      for (int place = 0; place < n_places; ++place) {
        value *= 10.;
        error *= 10.;
      }
      value = round(value);
      error = round(error + .49);
      for (int place = 0; place < n_places; ++place) {
        value /= 10.;
        error /= 10.;
      }
      hist_->SetBinContent(column, row, value);
      hist_->SetBinError(column, row, error);
    }
  }
}
}  // namespace plotting

