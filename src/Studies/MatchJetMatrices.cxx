// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "Studies/MatchJetMatrices.h"

#include <string>
#include <vector>
#include "MatrixHolderContainer.h"
#include "MatrixPlotter.h"

namespace plotting {
namespace studies {
void MatchJetMatrices::execute() {
  if (file_container_.empty()) return;

  plotting::MatrixHolderContainer matrix_container;
  plotting::MatrixHolderContainer matrix_container_onshell;
  plotting::MatrixHolderContainer matrix_container_offshell;
  matrix_container.pullHistograms(file_container_, "h_matchingMatrix");
  matrix_container_onshell.pullHistograms(file_container_,
                                          "h_matchingMatrix_onshell");
  matrix_container_offshell.pullHistograms(file_container_,
                                           "h_matchingMatrix_offshell");

  plotting::MatrixPlotter plotter;
  plotter.initCanvas(600, 600);
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchJetMatrices/");
  plotter.setCustomColorPalette();

  for (auto& matrix : matrix_container) {
    auto&& obj = matrix->getHist();
    obj->GetXaxis()->SetLabelSize(0.045);
    obj->GetXaxis()->SetTitleOffset(1.6);
    obj->GetYaxis()->SetLabelSize(0.045);
    obj->GetYaxis()->SetTitleOffset(1.6);
    obj->GetZaxis()->SetRangeUser(0, 0.65);
    obj->GetZaxis()->SetTitleOffset(1.6);
    obj->SetMarkerSize(1.5);
    matrix->roundMatrix(3);
    matrix->setDrawOptions("COLZ TEXT ERR");

    matrix->draw();
    plotter.plotAtlasLabel();
    plotter.saveToFile(matrix->getFileName());
  }

  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchJetMatrices/onshell/");

  for (auto& matrix : matrix_container_onshell) {
    auto&& obj = matrix->getHist();
    obj->GetXaxis()->SetLabelSize(0.045);
    obj->GetXaxis()->SetTitleOffset(1.6);
    obj->GetYaxis()->SetLabelSize(0.045);
    obj->GetYaxis()->SetTitleOffset(1.6);
    obj->GetZaxis()->SetRangeUser(0, 0.65);
    obj->GetZaxis()->SetTitleOffset(1.6);
    obj->SetMarkerSize(1.5);
    matrix->roundMatrix(3);
    matrix->setDrawOptions("COLZ TEXT ERR");

    matrix->draw();
    plotter.plotAtlasLabel();
    plotter.saveToFile(matrix->getFileName());
  }

  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchJetMatrices/offshell/");

  for (auto& matrix : matrix_container_offshell) {
    auto&& obj = matrix->getHist();
    obj->GetXaxis()->SetLabelSize(0.045);
    obj->GetXaxis()->SetTitleOffset(1.6);
    obj->GetYaxis()->SetLabelSize(0.045);
    obj->GetYaxis()->SetTitleOffset(1.6);
    obj->GetZaxis()->SetRangeUser(0, 0.65);
    obj->GetZaxis()->SetTitleOffset(1.6);
    obj->SetMarkerSize(1.5);
    matrix->roundMatrix(3);
    matrix->setDrawOptions("COLZ TEXT ERR");

    matrix->draw();
    plotter.plotAtlasLabel();
    plotter.saveToFile(matrix->getFileName());
  }
}
}  // namespace studies
}  // namespace plotting
