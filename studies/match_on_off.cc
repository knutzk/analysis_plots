// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include <TColor.h>
#include <TROOT.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "core/holders/hist_holder_container.h"
#include "core/holders/matrix_holder_container.h"
#include "core/plotters/hist_plotter.h"
#include "core/plotters/matrix_plotter.h"
#include "core/plotters/ratio_plotter.h"
#include "studies/match_on_off.h"

namespace plotting {
namespace studies {
void MatchOnOff::loadFiles(const std::string& input_list) {
  file_container_.readFileList(input_list);
  if (file_container_.size() != 6) {
    std::cout << "\nERROR: expected six files in the input list. "
              << "Aborting ... " << std::endl;
    throw;
  }

  // Move the last three files to the other container.
  for (int i : {3, 4}) {
    file_container_2_.push_back(file_container_.at(i));
  }
  file_container_.erase(file_container_.end() - 3, file_container_.end());
}

void MatchOnOff::execute() {
  plotting::HistPlotter plotter;
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchOnOff/");

  // h_andreacomp histograms
  plotting::HistHolderContainer hists_on{file_container_, "h_andreacomp_onshell"};
  plotting::HistHolderContainer hists_off{file_container_, "h_andreacomp_offshell"};
  plotting::HistHolderContainer hists_all{file_container_, "h_andreacomp"};

  std::map<HistHolderContainer*, std::string> hist_container_dictionary;
  hist_container_dictionary.emplace(&hists_on, "On-shell events only");
  hist_container_dictionary.emplace(&hists_off, "Off-shell events only");
  hist_container_dictionary.emplace(&hists_all, "All events");

  for (auto& element : hist_container_dictionary) {
    plotter.initCanvas(800, 600);
    plotter.initLegend();
    plotter.getAtlasLabel()->setAdditionalInfo(element.second);
    auto& container = element.first;

    container->at(0)->setLegendTitle("On-shell LL");
    container->at(0)->getHist()->SetLineColor(kBlue);
    container->at(0)->getHist()->SetMarkerColor(kBlue);
    container->at(1)->setLegendTitle("Off-shell LL");
    container->at(1)->getHist()->SetLineColor(kRed);
    container->at(1)->getHist()->SetMarkerColor(kRed);
    container->at(2)->setLegendTitle("Combined LL, 0.869");
    container->at(2)->getHist()->SetLineColor(kGreen + 2);
    container->at(2)->getHist()->SetMarkerColor(kGreen + 2);

    for (auto& hist_holder : *container) {
      hist_holder->setDrawOptions("P E1 SAME");
      hist_holder->setLegendOptions("PL");
      hist_holder->getHist()->GetXaxis()->SetLabelSize(16);
    }
    container->setOptimalMax();
    container->draw();
    plotter.addToLegend(*container);
    plotter.plotAtlasLabel();
    plotter.plotLegend();
    plotter.saveToFile(container->at(0)->getName());
    plotter.resetCanvas();
    plotter.resetLegend();
  }

  // Likelihood plots with ratios
  plotting::RatioPlotter ratio_plotter{0.3};
  ratio_plotter.setRatioTitle("LL/Onshell");
  ratio_plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchOnOff/");
  ratio_plotter.getAtlasLabel()->setChannel("(3)#mu+jets");

  std::vector<std::string> hist_names;
  hist_names.push_back("h_likelihood_onshell");
  hist_names.push_back("h_likelihood_offshell");
  hist_names.push_back("h_likelihood");

  for (const auto& name : hist_names) {
    plotting::HistHolderContainer likelihood_hists{file_container_2_, name.c_str()};
    for (auto& hist : likelihood_hists) {
      hist->setIncludeXOverflow();
      hist->setIncludeXUnderflow();
    }
    likelihood_hists.at(0)->setDrawOptions("P E1");
    likelihood_hists.at(0)->setLegendTitle("On-shell LL");
    likelihood_hists.at(0)->setLegendOptions("F");
    likelihood_hists.at(0)->getHist()->SetLineColor(1);
    likelihood_hists.at(0)->getHist()->SetMarkerColor(1);
    likelihood_hists.at(0)->getHist()->SetFillColor(kGray);
    likelihood_hists.at(0)->setDrawOptions("hist");

    likelihood_hists.at(1)->setDrawOptions("P E1 SAME");
    likelihood_hists.at(1)->setLegendTitle("Off-shell LL");
    likelihood_hists.at(1)->getHist()->SetLineColor(2);
    likelihood_hists.at(1)->getHist()->SetMarkerColor(2);

    // likelihood_hists.at(2)->setDrawOptions("P E1 SAME");
    // likelihood_hists.at(2)->setLegendTitle("Comb. LL, 0.869");
    // likelihood_hists.at(2)->getHist()->SetLineColor(4);
    // likelihood_hists.at(2)->getHist()->SetMarkerColor(4);

    auto likelihood_ratios = likelihood_hists;
    likelihood_ratios.divideHistograms(*likelihood_hists.at(0));

    ratio_plotter.adjustLabels(&likelihood_hists, &likelihood_ratios);
    ratio_plotter.addToLegend(likelihood_hists);

    ratio_plotter.switchToHistPad();
    likelihood_hists.setOptimalMax();
    likelihood_hists.draw();
    ratio_plotter.switchToRatioPad();
    ratio_plotter.drawRatio(&likelihood_ratios);
    ratio_plotter.switchToMainPad();
    ratio_plotter.plotAtlasLabel();
    ratio_plotter.plotLegend();
    ratio_plotter.saveToFile(name.c_str());

    ratio_plotter.initCanvas();
    ratio_plotter.initLegend();
  }

  // Probability plots with ratios
  std::vector<std::string> hist_names2;
  hist_names2.push_back("h_eventProb_onshell");
  hist_names2.push_back("h_eventProb_offshell");
  hist_names2.push_back("h_eventProb");

  for (const auto& name : hist_names2) {
    plotting::HistHolderContainer probability_hists{file_container_2_, name.c_str()};
    for (auto& hist : probability_hists) {
      hist->setIncludeXOverflow();
      hist->setIncludeXUnderflow();
    }
    probability_hists.at(0)->setDrawOptions("P E1");
    probability_hists.at(0)->setLegendTitle("On-shell LL");
    probability_hists.at(0)->setLegendOptions("F");
    probability_hists.at(0)->getHist()->SetLineColor(1);
    probability_hists.at(0)->getHist()->SetMarkerColor(1);
    probability_hists.at(0)->getHist()->SetFillColor(kGray);
    probability_hists.at(0)->setDrawOptions("hist");

    probability_hists.at(1)->setDrawOptions("P E1 SAME");
    probability_hists.at(1)->setLegendTitle("Off-shell LL");
    probability_hists.at(1)->getHist()->SetLineColor(2);
    probability_hists.at(1)->getHist()->SetMarkerColor(2);

    // probability_hists.at(2)->setDrawOptions("P E1 SAME");
    // probability_hists.at(2)->setLegendTitle("Comb. LL, 0.869");
    // probability_hists.at(2)->getHist()->SetLineColor(4);
    // probability_hists.at(2)->getHist()->SetMarkerColor(4);

    auto probability_ratios = probability_hists;
    probability_ratios.divideHistograms(*probability_hists.at(0));

    ratio_plotter.adjustLabels(&probability_hists, &probability_ratios);
    ratio_plotter.addToLegend(probability_hists);

    ratio_plotter.switchToHistPad();
    probability_hists.setOptimalMax();
    probability_hists.draw();
    ratio_plotter.switchToRatioPad();
    ratio_plotter.drawRatio(&probability_ratios);
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
