// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include <TStyle.h>
#include <string>
#include <vector>
#include "core/holders/hist_holder_container.h"
#include "core/holders/matrix_holder_container.h"
#include "core/plotters/matrix_plotter.h"
#include "core/plotters/ratio_plotter.h"
#include "studies/match_efficiencies.h"

// Expected order of the files:
//  1) ttz - kDedicated,  kWP
//  2) ttz - kAmongThree, kWP
//  3) ttz - kAmongThree, kNT
//  4) ttz - kLeading,    kNT
//  5) ttbar -            kWP
//  6) ttbar -            kNT

namespace plotting {
namespace studies {
void MatchEfficiencies::execute() {
  if (file_container_.empty()) return;

  HistPlotter plotter;
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchEfficiencies/");
  plotter.getAtlasLabel()->setChannel("(3)#mu+jets");
  plotter.initCanvas(800, 600);
  plotter.initLegend(0.57, 0.70, 0.91, 0.92);

  HistHolderContainer ttz_container;
  ttz_container.pullHistograms(file_container_, "h_andreacomp");

  HistHolderContainer ttbar_container;
  ttbar_container.push_back(std::move(ttz_container.at(4)));
  ttbar_container.push_back(std::move(ttz_container.at(5)));
  ttz_container.erase(ttz_container.end() - 2, ttz_container.end());

  ttz_container.at(0)->setDrawOptions("HIST BAR1");
  ttz_container.at(0)->setLegendTitle("t#bar{t}Z, kDedicated, kWP");
  ttz_container.at(0)->getHist()->SetFillColor(97);
  ttz_container.at(1)->setDrawOptions("HIST BAR1 SAME");
  ttz_container.at(1)->setLegendTitle("t#bar{t}Z, kAmongThree, kWP");
  ttz_container.at(1)->getHist()->SetFillColor(92);
  ttz_container.at(2)->setDrawOptions("HIST BAR1 SAME");
  ttz_container.at(2)->setLegendTitle("t#bar{t}Z, kAmongThree, kNT");
  ttz_container.at(2)->getHist()->SetFillColor(5);
  ttz_container.at(3)->setDrawOptions("HIST BAR1 SAME");
  ttz_container.at(3)->setLegendTitle("t#bar{t}Z, kLeading, kNT");
  ttz_container.at(3)->getHist()->SetFillColor(95);
  for (auto& holder : ttz_container) {
    holder->setLegendOptions("F");
    holder->getHist()->SetBarWidth(0.8);
    holder->getHist()->SetBarOffset(0.1);
    holder->getHist()->SetFillStyle(1001);
    holder->getHist()->GetXaxis()->SetLabelSize(16);
  }

  ttbar_container.at(0)->setLegendTitle("t#bar{t}, kWP");
  ttbar_container.at(0)->getHist()->SetMarkerStyle(23);
  ttbar_container.at(1)->setLegendTitle("t#bar{t}, kNT");
  ttbar_container.at(1)->getHist()->SetMarkerStyle(22);
  for (auto& holder : ttbar_container) {
    holder->setDrawOptions("P E1 SAME");
    holder->setLegendOptions("P");
    holder->getHist()->SetMarkerSize(1.5);
    holder->getHist()->SetLineColor(kBlack);
    holder->getHist()->GetXaxis()->SetLabelSize(16);
  }
  const auto& error_band = new HistHolder(*ttz_container.at(0));
  error_band->setDrawOptions("E2 SAME");
  error_band->getHist()->SetMarkerStyle(0);
  error_band->getHist()->SetFillStyle(3354);
  gStyle->SetHatchesSpacing(0.5);

  ttz_container.setOptimalMax();
  ttz_container.draw();
  ttbar_container.draw();
  // error_band->draw();
  plotter.addToLegend(ttz_container);
  plotter.addToLegend(ttbar_container);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("h_incl_ttbar");

  // =======================================================

  plotter.initCanvas(800, 600);
  plotter.initLegend(0.57, 0.74, 0.91, 0.92);
  std::vector<HistHolder*> incl_ttbar_no_leading;
  incl_ttbar_no_leading.push_back(ttz_container.at(0).get());
  incl_ttbar_no_leading.push_back(ttz_container.at(1).get());
  incl_ttbar_no_leading.push_back(ttz_container.at(2).get());
  incl_ttbar_no_leading.push_back(ttbar_container.at(0).get());
  incl_ttbar_no_leading.push_back(ttbar_container.at(1).get());
  for (const auto& holder : incl_ttbar_no_leading) {
    holder->draw();
    plotter.addToLegend(*holder);
  }
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("h_incl_ttbar_no_leading");

  // =======================================================

  plotter.initCanvas(800, 600);
  plotter.initLegend(0.57, 0.74, 0.91, 0.92);
  std::vector<HistHolder*> wp_only;
  wp_only.push_back(ttz_container.at(0).get());
  wp_only.push_back(ttz_container.at(1).get());
  wp_only.push_back(ttbar_container.at(0).get());
  for (const auto& holder : wp_only) {
    holder->draw();
    plotter.addToLegend(*holder);
  }
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("h_wp_only");

  // =======================================================

  plotter.initCanvas(800, 600);
  plotter.initLegend(0.57, 0.74, 0.91, 0.92);
  for (const auto& holder : ttz_container) {
    holder->draw();
    plotter.addToLegend(*holder);
  }
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("h_ttz_all");

  // =======================================================

  plotter.initCanvas(800, 600);
  plotter.initLegend(0.57, 0.74, 0.91, 0.92);
  for (const auto& holder : ttz_container) {
    if (holder == ttz_container.back()) continue;
    holder->draw();
    plotter.addToLegend(*holder);
  }
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("h_ttz_no_leading");

  plotter.resetCanvas();
  plotter.resetLegend();

  // =======================================================
  // =======================================================

  MatrixPlotter matrix_plotter;
  matrix_plotter.initCanvas(600, 600);
  matrix_plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchEfficiencies/");
  matrix_plotter.setCustomColorPalette();

  MatrixHolderContainer matrix_container;
  matrix_container.pullHistograms(file_container_, "h_matchingMatrix");

  for (auto& matrix : matrix_container) {
    matrix->getHist()->GetXaxis()->SetTitleOffset(1.6);
    matrix->getHist()->GetYaxis()->SetTitleOffset(1.6);
    matrix->getHist()->GetZaxis()->SetRangeUser(0, 0.8);
    matrix->getHist()->GetZaxis()->SetTitleOffset(1.6);
    matrix->getHist()->SetMarkerSize(900);
    matrix->roundMatrix(3);
    matrix->setDrawOptions("COLZ TEXT ERR");

    matrix->draw();
    matrix_plotter.plotAtlasLabel();
    matrix_plotter.saveToFile(matrix->getFileName());
  }
}
}  // namespace studies
}  // namespace plotting
