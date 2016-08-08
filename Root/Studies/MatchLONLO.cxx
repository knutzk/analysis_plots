// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "Plotting/Studies/MatchLONLO.h"

#include <TColor.h>
#include <TROOT.h>
#include <string>
#include <vector>
#include <iostream>
#include "Plotting/MatrixHolderContainer.h"
#include "Plotting/HistHolderContainer.h"
#include "Plotting/HistPlotter.h"
#include "Plotting/MatrixPlotter.h"
#include "Plotting/RatioPlotter.h"

namespace {
void setDrawing(plotting::HistHolderContainer* container) {
  container->at(0)->setDrawOptions("P E1");
  container->at(0)->setLegendTitle("t#bar{t}");
  container->at(0)->getHist()->SetLineColor(1);
  container->at(0)->getHist()->SetMarkerColor(1);

  container->at(1)->setDrawOptions("P E1 SAME");
  container->at(1)->setLegendTitle("t#bar{t}Z, LO");
  container->at(1)->getHist()->SetLineColor(2);
  container->at(1)->getHist()->SetMarkerColor(2);

  container->at(2)->setDrawOptions("P E1 SAME");
  container->at(2)->setLegendTitle("t#bar{t}Z, NLO");
  container->at(2)->getHist()->SetLineColor(4);
  container->at(2)->getHist()->SetMarkerColor(4);
}
}  // namespace

namespace plotting {
namespace studies {
void MatchLONLO::execute() {
  std::cout << "Ignoring user input file ... " << std::endl;
  file_container_.clear();
  file_container_.readFileList(
      "/home/knut.zoch/AnalysisFiles/Matcher/files-MatchLONLO.txt");
  file_container_2_.readFileList(
      "/home/knut.zoch/AnalysisFiles/Reader/files-jets-LONLO.txt");

  plotting::HistPlotter plotter;
  plotter.initCanvas(800, 600);
  plotter.setOutputDir("$HOME/AnalysisPlots/Output/MatchLONLO/");

  plotting::HistHolderContainer hists;
  hists.pullHistograms(file_container_, "h_andreacomp");

  hists.at(0)->setDrawOptions("HIST BAR1");
  hists.at(0)->setLegendTitle("t#bar{t}");
  hists.at(0)->setLegendOptions("F");
  hists.at(0)->getHist()->SetBarWidth(0.8);
  hists.at(0)->getHist()->SetBarOffset(0.1);
  hists.at(0)->getHist()->SetFillColor(kGray);
  hists.at(0)->getHist()->SetFillStyle(1001);

  hists.at(1)->setDrawOptions("P E1 SAME");
  hists.at(1)->setLegendTitle("kDedicated, LO");
  hists.at(1)->setLegendOptions("PL");
  hists.at(1)->getHist()->SetMarkerColor(4);
  hists.at(1)->getHist()->SetLineColor(4);

  hists.at(2)->setDrawOptions("P E1 SAME");
  hists.at(2)->setLegendTitle("kDedicated, NLO");
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
  plotter.saveToFile("h_comparison");
  plotter.resetCanvas();
  plotter.resetLegend();

  // =======================================================
  plotting::MatrixHolderContainer matrices;
  matrices.pullHistograms(file_container_, "h_matchingMatrix");

  plotting::MatrixPlotter matrixplotter;
  matrixplotter.initCanvas(600, 600);
  matrixplotter.setOutputDir("$HOME/AnalysisPlots/Output/MatchLONLO/");
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
    matrixplotter.saveToFile(matrix->getName().c_str());
  }

  // =======================================================

  plotting::RatioPlotter ratio_plotter{0.3};
  ratio_plotter.setRatioTitle("t#bar{t}Z / t#bar{t}");
  ratio_plotter.setOutputDir("$HOME/AnalysisPlots/Output/MatchLONLO/");
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
    plotting::HistHolderContainer jet_hists;
    jet_hists.pullHistograms(file_container_2_, name.c_str());
    setDrawing(&jet_hists);
    auto jet_ratios = jet_hists;
    jet_ratios.divideHistograms(*jet_hists.at(0));

    ratio_plotter.adjustLabels(&jet_hists, &jet_ratios);
    ratio_plotter.adjustMarkers(&jet_ratios);
    ratio_plotter.addToLegend(jet_hists);

    ratio_plotter.switchToHistPad();
    jet_hists.setOptimalMax();
    jet_hists.at(0)->setDrawOptions("hist");
    jet_hists.at(0)->getHist()->SetFillColor(kGray);
    jet_hists.draw();
    ratio_plotter.switchToRatioPad();
    jet_ratios.setOptimalRatioRange();
    jet_ratios.draw();
    ratio_plotter.switchToMainPad();
    ratio_plotter.plotAtlasLabel();
    ratio_plotter.plotLegend();
    ratio_plotter.saveToFile(name.c_str());

    ratio_plotter.initCanvas();
    ratio_plotter.initLegend();
  }
}
}  // namespace studies
}  // namespace plotting
