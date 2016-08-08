#include "Plotting/Studies/MatchEfficiencies.h"

#include "Plotting/HistHolderContainer.h"
#include "Plotting/RatioPlotter.h"
#include <string>
#include <vector>

namespace plotting {
namespace studies {
void MatchEfficiencies::execute() {
  if (file_container_.empty()) return;

  plotting::HistPlotter plotter;
  plotter.initCanvas(800, 600);
  plotter.setOutputDir("$HOME/AnalysisPlots/Output/MatchEfficiencies/");

  plotting::HistHolderContainer hist_container_onshell;
  hist_container_onshell.pullHistograms(file_container_,
                                        "h_andreacomp_onshell");
  hist_container_onshell.erase(hist_container_onshell.end() - 3,
                               hist_container_onshell.end());

  plotting::HistHolderContainer hist_container;
  hist_container.pullHistograms(file_container_, "h_andreacomp");

  hist_container.at(0)->setDrawOptions("HIST BAR1");
  hist_container.at(0)->setLegendTitle("t#bar{t}Z, kDedicated, kWP");
  hist_container.at(0)->setLegendOptions("F");
  auto&& hist = hist_container.at(0)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(97);
  hist->SetFillStyle(1001);

  hist_container.at(1)->setDrawOptions("HIST BAR1 SAME");
  hist_container.at(1)->setLegendTitle("t#bar{t}Z, kAmongThree, kWP");
  hist_container.at(1)->setLegendOptions("F");
  hist = hist_container.at(1)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(92);
  hist->SetFillStyle(1001);

  hist_container.at(2)->setDrawOptions("HIST BAR1 SAME");
  hist_container.at(2)->setLegendTitle("t#bar{t}Z, kAmongThree, kNT");
  hist_container.at(2)->setLegendOptions("F");
  hist = hist_container.at(2)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(5);
  hist->SetFillStyle(1001);

  hist_container.at(3)->setDrawOptions("HIST BAR1 SAME");
  hist_container.at(3)->setLegendTitle("t#bar{t}Z, kLeading, kNT");
  hist_container.at(3)->setLegendOptions("F");
  hist = hist_container.at(3)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(95);
  hist->SetFillStyle(1001);

  hist_container.at(4)->setDrawOptions("P E1 SAME");
  hist_container.at(4)->setLegendTitle("t#bar{t}, kWP");
  hist_container.at(4)->setLegendOptions("P");
  hist = hist_container.at(4)->getHist();
  hist->SetMarkerStyle(23);
  hist->SetMarkerSize(1.5);
  hist->SetLineColor(kBlack);

  hist_container.at(5)->setDrawOptions("P E1 SAME");
  hist_container.at(5)->setLegendTitle("t#bar{t}, kNT");
  hist_container.at(5)->setLegendOptions("P");
  hist = hist_container.at(5)->getHist();
  hist->SetMarkerStyle(22);
  hist->SetMarkerSize(1.5);
  hist->SetLineColor(kBlack);

  const auto& error_band = new HistHolder(*hist_container.at(0));
  error_band->setDrawOptions("E2 SAME");
  hist = error_band->getHist();
  hist->SetMarkerStyle(0);
  hist->SetFillStyle(3354);
  gStyle->SetHatchesSpacing(0.5);

  hist_container.setOptimalMax();
  hist_container.draw();
  // error_band->draw();
  plotter.initLegend(0.57, 0.70, 0.91, 0.92);
  plotter.addToLegend(hist_container);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("incl_ttbar");

  plotting::HistHolderContainer hist_wo_leading;
  hist_wo_leading.emplace_back(new HistHolder(*hist_container.at(0)));
  hist_wo_leading.emplace_back(new HistHolder(*hist_container.at(1)));
  hist_wo_leading.emplace_back(new HistHolder(*hist_container.at(2)));
  hist_wo_leading.emplace_back(new HistHolder(*hist_container.at(4)));
  hist_wo_leading.emplace_back(new HistHolder(*hist_container.at(5)));
  plotter.initCanvas(800, 600);
  plotter.initLegend(0.57, 0.74, 0.91, 0.92);
  hist_wo_leading.draw();
  plotter.addToLegend(hist_wo_leading);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("incl_ttbar_no_leading");

  plotting::HistHolderContainer hist_wp_only;
  hist_wp_only.emplace_back(new HistHolder(*hist_container.at(0)));
  hist_wp_only.emplace_back(new HistHolder(*hist_container.at(4)));
  plotter.initCanvas(800, 600);
  plotter.initLegend();
  hist_wp_only.draw();
  plotter.addToLegend(hist_wp_only);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("incl_ttbar_wp_only");

  plotting::HistHolderContainer hist_ttz;
  hist_ttz.emplace_back(new HistHolder(*hist_container.at(0)));
  hist_ttz.emplace_back(new HistHolder(*hist_container.at(1)));
  hist_ttz.emplace_back(new HistHolder(*hist_container.at(2)));
  hist_ttz.emplace_back(new HistHolder(*hist_container.at(3)));
  plotter.initCanvas(800, 600);
  plotter.initLegend();
  hist_ttz.draw();
  plotter.addToLegend(hist_ttz);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("ttz_all");

  plotting::HistHolderContainer hist_ttz_wo_leading;
  hist_ttz_wo_leading.emplace_back(new HistHolder(*hist_container.at(0)));
  hist_ttz_wo_leading.emplace_back(new HistHolder(*hist_container.at(1)));
  hist_ttz_wo_leading.emplace_back(new HistHolder(*hist_container.at(2)));
  plotter.initCanvas(800, 600);
  plotter.initLegend();
  hist_ttz_wo_leading.draw();
  plotter.addToLegend(hist_ttz_wo_leading);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("ttz_no_leading");

  // =======================================================
  hist_container_onshell.at(0)->setDrawOptions("HIST BAR1");
  hist_container_onshell.at(0)->setLegendTitle("t#bar{t}Z, kDedicated, kWP");
  hist_container_onshell.at(0)->setLegendOptions("F");
  hist = hist_container_onshell.at(0)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(97);
  hist->SetFillStyle(1001);

  hist_container_onshell.at(1)->setDrawOptions("HIST BAR1 SAME");
  hist_container_onshell.at(1)->setLegendTitle("t#bar{t}Z, kAmongThree, kWP");
  hist_container_onshell.at(1)->setLegendOptions("F");
  hist = hist_container_onshell.at(1)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(92);
  hist->SetFillStyle(1001);

  hist_container_onshell.at(2)->setDrawOptions("HIST BAR1 SAME");
  hist_container_onshell.at(2)->setLegendTitle("t#bar{t}Z, kAmongThree, kNT");
  hist_container_onshell.at(2)->setLegendOptions("F");
  hist = hist_container_onshell.at(2)->getHist();
  hist->SetBarWidth(0.8);
  hist->SetBarOffset(0.1);
  hist->SetFillColor(5);
  hist->SetFillStyle(1001);

  // hist_container_onshell.at(3)->setDrawOptions("HIST BAR1 SAME");
  // hist_container_onshell.at(3)->setLegendTitle("t#bar{t}Z, kLeading, kNT");
  // hist_container_onshell.at(3)->setLegendOptions("F");
  // hist = hist_container_onshell.at(3)->getHist();
  // hist->SetBarWidth(0.8);
  // hist->SetBarOffset(0.1);
  // hist->SetFillColor(95);
  // hist->SetFillStyle(1001);

  // plotter.initCanvas(800, 600);
  plotter.initLegend();
  hist_container_onshell.setOptimalMax();
  hist_container_onshell.draw();
  plotter.addToLegend(hist_container_onshell);
  plotter.plotAtlasLabel();
  plotter.plotLegend();
  plotter.saveToFile("ttz_onshell");
}
}  // namespace studies
}  // namespace plotting
