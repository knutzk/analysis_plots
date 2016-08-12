// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "Studies/Jets.h"

#include <TH1D.h>
#include <string>
#include <vector>
#include "RatioPlotter.h"
#include "HistHolder.h"
#include "HistHolderContainer.h"

namespace plotting {
namespace studies {
void Jets::execute() {
  if (file_container_.empty()) return;

  plotting::HistHolderContainer hist_container, ratio_container;
  plotting::RatioPlotter ratio_plotter{0.3};
  ratio_plotter.setRatioTitle("t#bar{t}Z / t#bar{t}");
  ratio_plotter.setOutputDir("$HOME/AnalysisPlots/plots/Jets/");

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
    hist_container.pullHistograms(file_container_, name.c_str());
    setDrawing(&hist_container);
    ratio_container = hist_container;
    ratio_container.divideHistograms(*hist_container.at(0));

    ratio_plotter.adjustLabels(&hist_container, &ratio_container);
    ratio_plotter.adjustMarkers(&ratio_container);
    ratio_plotter.addToLegend(hist_container);

    ratio_plotter.switchToHistPad();
    hist_container.setOptimalMax();
    hist_container.draw();
    ratio_plotter.switchToRatioPad();
    ratio_container.setOptimalRatioRange();
    ratio_container.draw();
    ratio_plotter.switchToMainPad();
    ratio_plotter.plotAtlasLabel();
    ratio_plotter.plotLegend();
    ratio_plotter.saveToFile(name.c_str());

    hist_container.clear();
    ratio_container.clear();
    ratio_plotter.initCanvas();
    ratio_plotter.initLegend();
  }
}

void Jets::setDrawing(plotting::HistHolderContainer* hist_container) {
  hist_container->at(0)->setDrawOptions("P E1");
  hist_container->at(0)->setLegendTitle("t#bar{t}, kWP");
  hist_container->at(0)->getHist()->SetLineColor(1);
  hist_container->at(0)->getHist()->SetMarkerColor(1);

  hist_container->at(1)->setDrawOptions("P E1 SAME");
  hist_container->at(1)->setLegendTitle("t#bar{t}Z, kWP");
  hist_container->at(1)->getHist()->SetLineColor(2);
  hist_container->at(1)->getHist()->SetMarkerColor(2);
}
}  // namespace studies
}  // namespace plotting
