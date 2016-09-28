// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include <sstream>
#include <string>
#include <vector>
#include "core/holders/hist_holder_container.h"
#include "core/plotters/ratio_plotter.h"
#include "studies/likelihood.h"

namespace plotting {
namespace studies {
void Likelihood::execute() {
  if (file_container_.empty()) return;

  plotting::RatioPlotter ratio_plotter{0.3};
  ratio_plotter.setOutputDir("$HOME/AnalysisPlots/plots/Likelihood/");
  ratio_plotter.getAtlasLabel()->setIsThesis();
  ratio_plotter.getAtlasLabel()->setIsWorkInProgress(false);

  plotting::HistHolderContainer hist_container;
  hist_container.pullHistograms(file_container_, "h_likelihood");

  HistHolderContainer hist_container_ttdil;
  hist_container_ttdil.emplace(hist_container_ttdil.end(), new HistHolder{*hist_container.at(1)});
  hist_container_ttdil.emplace(hist_container_ttdil.end(), new HistHolder{*hist_container.at(2)});

  hist_container.erase(hist_container.end() - 2, hist_container.end() - 1);

  hist_container.at(0)->setDrawOptions("P E1");
  hist_container.at(0)->setLegendTitle("diboson");
  hist_container.at(0)->getHist()->SetLineColor(1);
  hist_container.at(0)->getHist()->SetMarkerColor(1);
  hist_container.at(1)->setDrawOptions("P E1 SAME");
  hist_container.at(1)->setLegendTitle("t#bar{t}Z");
  hist_container.at(1)->getHist()->SetLineColor(2);
  hist_container.at(1)->getHist()->SetMarkerColor(2);

  const auto& separation = ratio_plotter.getSeparation(hist_container.at(0).get(),
                                                       hist_container.at(1).get());
  std::ostringstream os;
  os << "Separation: " << separation << "%";
  ratio_plotter.getAtlasLabel()->setAdditionalInfo(os.str());

  auto ratio_container = hist_container;
  ratio_container.divideHistograms(*hist_container.at(0));

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
  ratio_plotter.saveToFile("separation_diboson");

  // =================================================================

  ratio_plotter.getAtlasLabel()->setAdditionalInfo("");
  ratio_plotter.initCanvas();
  ratio_plotter.initLegend();

  hist_container_ttdil.at(0)->setDrawOptions("P E1");
  hist_container_ttdil.at(0)->setLegendTitle("t#bar{t} + fake");
  hist_container_ttdil.at(0)->getHist()->SetLineColor(1);
  hist_container_ttdil.at(0)->getHist()->SetMarkerColor(1);
  hist_container_ttdil.at(1)->setDrawOptions("P E1 SAME");
  hist_container_ttdil.at(1)->setLegendTitle("t#bar{t}Z");
  hist_container_ttdil.at(1)->getHist()->SetLineColor(2);
  hist_container_ttdil.at(1)->getHist()->SetMarkerColor(2);

  auto ratio_container_ttdil = hist_container_ttdil;
  ratio_container_ttdil.divideHistograms(*hist_container_ttdil.at(0));

  ratio_plotter.adjustLabels(&hist_container_ttdil, &ratio_container_ttdil);
  ratio_plotter.addToLegend(hist_container_ttdil);

  ratio_plotter.switchToHistPad();
  hist_container_ttdil.setOptimalMax();
  hist_container_ttdil.draw();
  ratio_plotter.switchToRatioPad();
  ratio_plotter.drawRatio(&ratio_container_ttdil);
  ratio_plotter.switchToMainPad();
  ratio_plotter.plotAtlasLabel();
  ratio_plotter.plotLegend();
  ratio_plotter.saveToFile("separation_ttdil");
}
}  // namespace studies
}  // namespace plotting
