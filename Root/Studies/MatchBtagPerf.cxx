// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "Studies/MatchBtagPerf.h"

#include <TColor.h>
#include <TROOT.h>
#include <iostream>
#include <string>
#include <vector>
#include "MatrixHolderContainer.h"
#include "HistHolderContainer.h"
#include "HistPlotter.h"
#include "MatrixPlotter.h"

namespace plotting {
namespace studies {
void MatchBtagPerf::execute() {
  if (file_container_.empty()) return;

  plotting::HistPlotter plotter;
  plotter.initCanvas(800, 600);
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchBtagPerf/");

  plotting::HistHolderContainer hist_container;
  hist_container.pullHistograms(file_container_, "h_andreacomp");

  hist_container.at(0)->setDrawOptions("HIST BAR2");
  hist_container.at(0)->setLegendTitle("t#bar{t}Z, kAmongThree, kWP");
  hist_container.at(0)->setLegendOptions("F");
  auto&& hist = hist_container.at(0)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(92);
  hist->SetFillStyle(1001);

  hist_container.at(1)->setDrawOptions("P E1 SAME");
  hist_container.at(1)->setLegendTitle("t#bar{t}Z, kAmongThree, kWP, fixed");
  hist_container.at(1)->setLegendOptions("P");
  hist = hist_container.at(1)->getHist();
  hist->SetMarkerStyle(23);
  hist->SetMarkerSize(1.5);
  hist->SetLineColor(kBlack);

  hist_container.setOptimalMax();
  hist_container.draw();
  plotter.addToLegend(hist_container);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("h_btagPerf");
  plotter.resetCanvas();
  plotter.resetLegend();

  // =======================================================
  plotting::MatrixHolderContainer matrix_container;
  matrix_container.pullHistograms(file_container_, "h_matchingMatrix_norm");

  plotting::MatrixPlotter matrixplotter;
  matrixplotter.initCanvas(600, 600);
  matrixplotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchBtagPerf/");
  matrixplotter.setCustomColorPalette();

  // Calculate the differences of the two histograms.
  auto&& diff_hist = new MatrixHolder(*matrix_container.at(0));
  for (auto row = 1; row < diff_hist->getHist()->GetNbinsY(); ++row) {
    for (auto column = 1; column < diff_hist->getHist()->GetNbinsX() + 1;
         ++column) {
      const auto old = diff_hist->getHist()->GetBinContent(column, row);
      const auto diff =
          old - matrix_container.at(1)->getHist()->GetBinContent(column, row);
      diff_hist->getHist()->SetBinContent(column, row, diff * 100.);
    }
  }
  diff_hist->getHist()->GetZaxis()->SetTitle("Matching difference [%]");
  diff_hist->getHist()->GetZaxis()->SetRangeUser(-1., 1.);
  diff_hist->getHist()->GetXaxis()->SetLabelSize(0.045);
  diff_hist->getHist()->GetXaxis()->SetTitleOffset(1.6);
  diff_hist->getHist()->GetYaxis()->SetLabelSize(0.045);
  diff_hist->getHist()->GetYaxis()->SetTitleOffset(1.6);
  diff_hist->getHist()->GetZaxis()->SetTitleOffset(1.6);
  diff_hist->getHist()->SetMarkerSize(1.5);
  diff_hist->roundMatrix(2);

  for (auto& matrix : matrix_container) {
    auto&& obj = matrix->getHist();
    obj->GetXaxis()->SetLabelSize(0.045);
    obj->GetXaxis()->SetTitleOffset(1.6);
    obj->GetYaxis()->SetLabelSize(0.045);
    obj->GetYaxis()->SetTitleOffset(1.6);
    obj->GetZaxis()->SetRangeUser(0, 0.8);
    obj->GetZaxis()->SetTitleOffset(1.6);
    obj->SetMarkerSize(1.5);
    matrix->roundMatrix(3);
    matrix->setDrawOptions("COLZ TEXT ERR");
  }

  matrix_container.at(0)->draw();
  matrixplotter.plotAtlasLabel();
  matrixplotter.saveToFile("matrix_dependent");

  matrix_container.at(1)->draw();
  matrixplotter.plotAtlasLabel();
  matrixplotter.saveToFile("matrix_static");

  // Make custom color palette for the difference matrix.
  const int NRGBs(3);
  const int NCont(255);
  gStyle->SetNumberContours(NCont);
  double stops[NRGBs] = {0.10, 0.50, 0.90};
  double red[NRGBs] = {0.80, 1.00, 0.10};
  double green[NRGBs] = {0.30, 1.00, 0.38};
  double blue[NRGBs] = {0.30, 1.00, 0.76};
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

  diff_hist->setDrawOptions("COLZ0 TEXT");
  diff_hist->draw();
  matrixplotter.plotAtlasLabel();
  matrixplotter.saveToFile("matrix_diff");
}
}  // namespace studies
}  // namespace plotting
