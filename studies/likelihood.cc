// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include <string>
#include <vector>
#include "core/holders/hist_holder_container.h"
#include "core/plotters/ratio_plotter.h"
#include "studies/likelihood.h"

namespace plotting {
namespace studies {
void Likelihood::execute() {
  if (file_container_.empty()) return;

  plotting::HistHolderContainer hist_container;
  hist_container.pullHistograms(file_container_, "h_likelihood");

  hist_container.at(0)->setDrawOptions("P E1");
  hist_container.at(0)->setLegendTitle("diboson");
  hist_container.at(0)->getHist()->SetLineColor(1);
  hist_container.at(0)->getHist()->SetMarkerColor(1);
  hist_container.at(1)->setDrawOptions("P E1 SAME");
  hist_container.at(1)->setLegendTitle("t#bar{t}Z");
  hist_container.at(1)->getHist()->SetLineColor(2);
  hist_container.at(1)->getHist()->SetMarkerColor(2);

  auto ratio_container = hist_container;
  ratio_container.divideHistograms(*hist_container.at(0));

  plotting::RatioPlotter ratio_plotter{0.3};
  ratio_plotter.setOutputDir("$HOME/AnalysisPlots/plots/Likelihood/");
  ratio_plotter.adjustLabels(&hist_container, &ratio_container);
  ratio_plotter.addToLegend(hist_container);

  ratio_plotter.switchToHistPad();
  hist_container.setOptimalMax();
  hist_container.draw();
  ratio_plotter.switchToRatioPad();
  ratio_plotter.drawRatio(&ratio_container);
  ratio_plotter.switchToMainPad();
  ratio_plotter.plotAtlasLabel();
  ratio_plotter.plotLegend();
  ratio_plotter.saveToFile("likelihood");
}
}  // namespace studies
}  // namespace plotting
