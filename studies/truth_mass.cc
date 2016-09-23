// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include <THStack.h>
#include <iostream>
#include <string>
#include "core/holders/hist_holder_container.h"
#include "core/plotters/hist_plotter.h"
#include "studies/truth_mass.h"

namespace plotting {
namespace studies {
void TruthMass::execute() {
  HistPlotter plotter;
  plotter.initCanvas();
  plotter.getCanvas()->SetLogy();
  plotter.getAtlasLabel()->setIsThesis();
  plotter.getAtlasLabel()->setAdditionalInfo("All events");
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/");

  auto& file = file_container_.at(0);
  HistHolder mass_on{file, "mass_on"};
  HistHolder mass_off{file, "mass_off"};

  mass_on.getHist()->SetFillColor(kGray);
  mass_on.getHist()->SetFillStyle(1001);
  mass_off.getHist()->SetFillColor(kWhite);
  mass_off.getHist()->SetFillStyle(1001);
  mass_on.setLegendTitle("On-shell events");
  mass_off.setLegendTitle("Off-shell events");
  mass_on.setLegendOptions("F");
  mass_off.setLegendOptions("F");

  mass_on.getHist()->GetYaxis()->SetRangeUser(1e-4, 10.);
  mass_on.getHist()->Draw("hist");

  THStack stack{};
  stack.Add(mass_off.getHist());
  stack.Add(mass_on.getHist());
  stack.Draw("hist same");

  plotter.addToLegend(mass_on);
  plotter.addToLegend(mass_off);
  plotter.plotLegend();
  plotter.plotAtlasLabel();

  plotter.saveToFile("mass_dist");

  // =================================================================

  plotter.initCanvas();
  plotter.initLegend();
  plotter.getCanvas()->SetLogy();
  plotter.getAtlasLabel()->setAdditionalInfo("Lepton cuts imposed");

  HistHolder mass_on_20{file, "mass_on_20"};
  HistHolder mass_off_20{file, "mass_off_20"};

  mass_on_20.getHist()->SetFillColor(kGray);
  mass_on_20.getHist()->SetFillStyle(1001);
  mass_off_20.getHist()->SetFillColor(kWhite);
  mass_off_20.getHist()->SetFillStyle(1001);
  mass_on_20.setLegendTitle("On-shell events");
  mass_off_20.setLegendTitle("Off-shell events");
  mass_on_20.setLegendOptions("F");
  mass_off_20.setLegendOptions("F");

  mass_on_20.getHist()->GetYaxis()->SetRangeUser(1e-4, 10.);
  mass_on_20.getHist()->Draw("hist");

  THStack stack2{};
  stack2.Add(mass_off_20.getHist());
  stack2.Add(mass_on_20.getHist());
  stack2.Draw("hist same");

  plotter.addToLegend(mass_on_20);
  plotter.addToLegend(mass_off_20);
  plotter.plotLegend();
  plotter.plotAtlasLabel();

  plotter.saveToFile("mass_dist_20");
}
}  // namespace studies
}  // namespace plotting
