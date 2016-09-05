// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
// Copyright 2016 <Alexander Johnsen> <ajohnsen@cern.ch>
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
#include "studies/match_el_mu.h"

namespace plotting {
namespace studies {
void MatchElMu::loadFiles(const std::string& input_list) {
  file_container_.readFileList(input_list);
  if (file_container_.size() != 2) {
    std::cout << "\nERROR: expected two files in the input list. "
              << "Aborting ... " << std::endl;
    throw;
  }
}

void MatchElMu::execute() {
  plotting::HistPlotter plotter;
  plotter.initCanvas(800, 600);
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchElMu/");

  // ======================================================

  plotting::HistHolderContainer hists{file_container_, "h_andreacomp"};

  hists.at(0)->setDrawOptions("P E1 SAME");
  hists.at(0)->setLegendTitle("t#bar{t}Z -> ejets, NLO");
  hists.at(0)->setLegendOptions("PL");
  hists.at(0)->getHist()->SetMarkerColor(4);
  hists.at(0)->getHist()->SetLineColor(4);

  hists.at(1)->setDrawOptions("P E1 SAME");
  hists.at(1)->setLegendTitle("t#bar{t}Z -> mujets, NLO");
  hists.at(1)->setLegendOptions("PL");
  hists.at(1)->getHist()->SetMarkerColor(2);
  hists.at(1)->getHist()->SetLineColor(2);

  for (auto& hist : hists) {
    hist->getHist()->GetXaxis()->SetLabelSize(16);
  }

  hists.setOptimalMax();
  hists.draw();
  plotter.addToLegend(hists);
  plotter.getAtlasLabel()->setChannel("");
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("h_comparison");
  plotter.resetCanvas();
  plotter.resetLegend();

  // =======================================================

  plotting::MatrixHolderContainer matrices{file_container_, "h_matchingMatrix"};

  plotting::MatrixPlotter matrixplotter;
  matrixplotter.initCanvas(600, 600);
  matrixplotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchElMu/");
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
    if (matrix == matrices.front()) {
      matrixplotter.getAtlasLabel()->setChannel("3e+jets");
    } else {
      matrixplotter.getAtlasLabel()->setChannel("3#mu+jets");
    }
    matrixplotter.plotAtlasLabel();
    matrixplotter.saveToFile(matrix->getFileName().c_str());
  }
  matrixplotter.resetCanvas();
  matrixplotter.resetLegend();
}
}  // namespace studies
}  // namespace plotting
