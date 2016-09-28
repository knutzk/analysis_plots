// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include <TColor.h>
#include <TROOT.h>
#include <iostream>
#include <string>
#include <vector>
#include "core/holders/hist_holder_container.h"
#include "core/holders/matrix_holder_container.h"
#include "core/plotters/hist_plotter.h"
#include "core/plotters/matrix_plotter.h"
#include "core/plotters/ratio_plotter.h"
#include "studies/match_lo_nlo.h"

namespace plotting {
namespace studies {
void MatchLONLO::loadFiles(const std::string& input_list) {
  file_container_.readFileList(input_list);
  if (file_container_.size() != 6) {
    std::cout << "\nERROR: expected six files in the input list. "
              << "Aborting ... " << std::endl;
    throw;
  }

  // Move the last three files to the other container.
  for (int i : {3, 4, 5}) {
    file_container_2_.push_back(file_container_.at(i));
  }
  file_container_.erase(file_container_.end() - 3, file_container_.end());
}

void MatchLONLO::execute() {
  plotting::HistPlotter plotter;
  plotter.initCanvas(800, 600);
  plotter.getAtlasLabel()->setIsThesis();
  plotter.getAtlasLabel()->setIsWorkInProgress(false);
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchLONLO/");

  plotting::HistHolderContainer hists{file_container_, "h_andreacomp"};

  hists.at(0)->setDrawOptions("HIST BAR1");
  hists.at(0)->setLegendTitle("t#bar{t}, NLO");
  hists.at(0)->setLegendOptions("F");
  hists.at(0)->getHist()->SetBarWidth(0.8);
  hists.at(0)->getHist()->SetBarOffset(0.1);
  hists.at(0)->getHist()->SetFillColor(kGray);
  hists.at(0)->getHist()->SetFillStyle(1001);

  hists.at(1)->setDrawOptions("P E1 SAME");
  hists.at(1)->setLegendTitle("t#bar{t}Z, LO");
  hists.at(1)->setLegendOptions("PL");
  hists.at(1)->getHist()->SetMarkerColor(4);
  hists.at(1)->getHist()->SetLineColor(4);

  hists.at(2)->setDrawOptions("P E1 SAME");
  hists.at(2)->setLegendTitle("t#bar{t}Z, NLO");
  hists.at(2)->setLegendOptions("PL");
  hists.at(2)->getHist()->SetMarkerColor(2);
  hists.at(2)->getHist()->SetLineColor(2);

  for (auto& hist : hists) {
    hist->getHist()->GetXaxis()->SetLabelSize(16);
  }

  hists.setOptimalMax();
  hists.draw();
  plotter.addToLegend(hists);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("comp_lo-nlo-ttbar");
  plotter.resetCanvas();
  plotter.resetLegend();

  // =======================================================

  plotting::MatrixHolderContainer matrices{file_container_, "h_matchingMatrix"};

  plotting::MatrixPlotter matrixplotter;
  matrixplotter.initCanvas(600, 600);
  matrixplotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchLONLO/");
  matrixplotter.getAtlasLabel()->setIsThesis();
  matrixplotter.getAtlasLabel()->setIsWorkInProgress(false);
  matrixplotter.setCustomColorPalette();

  for (auto& matrix : matrices) {
    matrix->getHist()->GetXaxis()->SetTitleOffset(1.6);
    matrix->getHist()->GetYaxis()->SetTitleOffset(1.6);
    matrix->getHist()->GetZaxis()->SetRangeUser(0, 0.8);
    matrix->getHist()->GetZaxis()->SetTitleOffset(1.6);
    matrix->getHist()->SetMarkerSize(900);
    matrix->roundMatrix(3);
    matrix->setDrawOptions("COLZ TEXT ERR");
    matrix->draw();
    matrixplotter.plotAtlasLabel();
    matrixplotter.saveToFile("matrix_" + matrix->getFileName());
  }
  matrixplotter.resetCanvas();
  matrixplotter.resetLegend();

  // =======================================================

  plotting::RatioPlotter ratio_plotter{0.3};
  ratio_plotter.setRatioTitle("t#bar{t}Z / t#bar{t}");
  ratio_plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchLONLO/");
  ratio_plotter.getAtlasLabel()->setIsThesis();
  ratio_plotter.getAtlasLabel()->setIsWorkInProgress(false);
  ratio_plotter.getAtlasLabel()->setChannel("(3)#mu+jets");

  std::vector<std::string> hist_names;
  hist_names.push_back("h_jetPt1");
  hist_names.push_back("h_jetPt2");
  hist_names.push_back("h_jetPt3");
  hist_names.push_back("h_jetPt4");
  hist_names.push_back("h_jetPt5");
  hist_names.push_back("h_jetPtRatio45Log10");
  hist_names.push_back("h_jetPtRatio45LogE");
  hist_names.push_back("h_Njets");

  for (const auto& name : hist_names) {
    plotting::HistHolderContainer jet_hists{file_container_2_, name};
    auto short_name = name.substr(2, name.size() - 2);

    for (auto& hist : jet_hists) {
      hist->setIncludeXOverflow();
    }
    jet_hists.at(0)->setDrawOptions("P E1");
    jet_hists.at(0)->setLegendTitle("t#bar{t}, NLO");
    jet_hists.at(0)->setLegendOptions("F");
    jet_hists.at(0)->getHist()->SetLineColor(1);
    jet_hists.at(0)->getHist()->SetMarkerColor(1);
    jet_hists.at(0)->getHist()->SetFillColor(kGray);
    jet_hists.at(0)->setDrawOptions("hist");

    jet_hists.at(1)->setDrawOptions("P E1 SAME");
    jet_hists.at(1)->setLegendTitle("t#bar{t}Z, LO");
    jet_hists.at(1)->getHist()->SetLineColor(2);
    jet_hists.at(1)->getHist()->SetMarkerColor(2);

    jet_hists.at(2)->setDrawOptions("P E1 SAME");
    jet_hists.at(2)->setLegendTitle("t#bar{t}Z, NLO");
    jet_hists.at(2)->getHist()->SetLineColor(4);
    jet_hists.at(2)->getHist()->SetMarkerColor(4);

    auto jet_ratios = jet_hists;
    jet_ratios.divideHistograms(*jet_hists.at(0));

    ratio_plotter.adjustLabels(&jet_hists, &jet_ratios);
    ratio_plotter.addToLegend(jet_hists);

    ratio_plotter.switchToHistPad();
    jet_hists.setOptimalMax();
    jet_hists.draw();
    ratio_plotter.switchToRatioPad();
    ratio_plotter.drawRatio(&jet_ratios);
    ratio_plotter.switchToMainPad();
    ratio_plotter.plotAtlasLabel();
    ratio_plotter.plotLegend();
    ratio_plotter.saveToFile("kin_" + short_name);

    ratio_plotter.initCanvas();
    ratio_plotter.initLegend();
  }
}
}  // namespace studies
}  // namespace plotting
