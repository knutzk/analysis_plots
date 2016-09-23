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

  // Move the last two files to the other container.
  for (int i : {4, 5}) {
    file_container_2_.push_back(file_container_.at(i));
  }
  file_container_.erase(file_container_.end() - 3, file_container_.end());
}

void MatchOnOff::execute() {
  HistPlotter plotter;
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchOnOff/");

  // h_andreacomp histograms
  HistHolderContainer hists_on{file_container_, "h_andreacomp_onshell"};
  HistHolderContainer hists_off{file_container_, "h_andreacomp_offshell"};
  HistHolderContainer hists_all{file_container_, "h_andreacomp"};

  std::map<HistHolderContainer*, std::string> andreacomp_dictionary;
  andreacomp_dictionary.emplace(&hists_on, "On-shell events only");
  andreacomp_dictionary.emplace(&hists_off, "Off-shell events only");
  andreacomp_dictionary.emplace(&hists_all, "All events");

  for (auto& element : andreacomp_dictionary) {
    plotter.initCanvas(800, 600);
    plotter.initLegend();
    plotter.getAtlasLabel()->setAdditionalInfo(element.second);
    auto& container = element.first;
    auto short_name = container->at(0)->getName();
    short_name.replace(0, 12, "comp_on-off");

    container->at(0)->setLegendTitle("Combined LL, 0.869");
    container->at(0)->setDrawOptions("HIST BAR1");
    container->at(0)->setLegendOptions("F");
    container->at(0)->getHist()->SetFillColor(kGray);
    container->at(0)->getHist()->SetBarWidth(0.8);
    container->at(0)->getHist()->SetBarOffset(0.1);
    container->at(0)->getHist()->SetFillStyle(1001);

    container->at(1)->setLegendTitle("On-shell LL");
    container->at(1)->getHist()->SetLineColor(kBlue);
    container->at(1)->getHist()->SetMarkerColor(kBlue);
    container->at(2)->setLegendTitle("Off-shell LL");
    container->at(2)->getHist()->SetLineColor(kRed);
    container->at(2)->getHist()->SetMarkerColor(kRed);

    container->setOptimalMax();
    for (auto& hist_holder : *container) {
      if (hist_holder != container->at(0)) {
        hist_holder->setDrawOptions("P E1 SAME");
        hist_holder->setLegendOptions("PL");
        hist_holder->getHist()->GetXaxis()->SetLabelSize(16);
      }
      hist_holder->draw();

      // If we're at the first element, draw the shaded errors as well.
      if (hist_holder == container->at(0)) {
        auto shaded_errors = new HistHolder{*container->at(0)};
        shaded_errors->getHist()->SetMarkerSize(0);
        shaded_errors->getHist()->SetFillColor(kBlack);
        shaded_errors->getHist()->SetFillStyle(3245);
        shaded_errors->setDrawOptions("e2 same");
        shaded_errors->draw();
      }
    }
    plotter.addToLegend(*container);
    plotter.plotAtlasLabel();
    plotter.plotLegend();
    plotter.saveToFile(short_name);
    plotter.resetCanvas();
    plotter.resetLegend();
  }

  // =================================================================

  RatioPlotter ratio_plotter{0.3};
  ratio_plotter.setRatioTitle("LL/Onshell");
  ratio_plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchOnOff/");
  ratio_plotter.getAtlasLabel()->setChannel("(3)#mu+jets");

  HistHolderContainer like_on{file_container_2_, "h_likelihood_onshell"};
  HistHolderContainer like_off{file_container_2_, "h_likelihood_offshell"};
  HistHolderContainer like_all{file_container_2_, "h_likelihood"};

  std::map<HistHolderContainer*, std::string> likelihood_dictionary;
  likelihood_dictionary.emplace(&like_on, "On-shell events only");
  likelihood_dictionary.emplace(&like_off, "Off-shell events only");
  likelihood_dictionary.emplace(&like_all, "All events");

  for (auto& element : likelihood_dictionary) {
    ratio_plotter.initCanvas();
    ratio_plotter.initLegend();
    ratio_plotter.getAtlasLabel()->setAdditionalInfo(element.second);

    auto& container = element.first;
    auto short_name = container->at(0)->getName();
    short_name.replace(0, 12, "comp_on-off-LL");

    for (auto& hist : *container) {
      hist->setIncludeXOverflow();
      hist->setIncludeXUnderflow();
    }
    container->at(0)->setDrawOptions("P E1");
    container->at(0)->setLegendTitle("On-shell LL");
    container->at(0)->setLegendOptions("F");
    container->at(0)->getHist()->SetLineColor(1);
    container->at(0)->getHist()->SetMarkerColor(1);
    container->at(0)->getHist()->SetFillColor(kGray);
    container->at(0)->setDrawOptions("hist");

    container->at(1)->setDrawOptions("P E1 SAME");
    container->at(1)->setLegendTitle("Off-shell LL");
    container->at(1)->getHist()->SetLineColor(2);
    container->at(1)->getHist()->SetMarkerColor(2);

    // container->at(2)->setDrawOptions("P E1 SAME");
    // container->at(2)->setLegendTitle("Comb. LL, 0.869");
    // container->at(2)->getHist()->SetLineColor(4);
    // container->at(2)->getHist()->SetMarkerColor(4);

    auto ratio_container = new HistHolderContainer{*container};
    ratio_container->divideHistograms(*container->at(0));

    ratio_plotter.adjustLabels(container, ratio_container);
    ratio_plotter.addToLegend(*container);

    ratio_plotter.switchToHistPad();
    container->setOptimalMax();
    container->draw();
    ratio_plotter.switchToRatioPad();
    ratio_plotter.drawRatio(ratio_container);
    ratio_plotter.switchToMainPad();
    ratio_plotter.plotAtlasLabel();
    ratio_plotter.plotLegend();
    ratio_plotter.saveToFile(short_name);
    ratio_plotter.resetCanvas();
    ratio_plotter.resetLegend();
  }

  // =================================================================

  // Probability plots with ratios
  HistHolderContainer event_prob_on{file_container_2_, "h_eventProb_onshell"};
  HistHolderContainer event_prob_off{file_container_2_, "h_eventProb_offshell"};
  HistHolderContainer event_prob_all{file_container_2_, "h_eventProb"};

  std::map<HistHolderContainer*, std::string> event_prob_dictionary;
  event_prob_dictionary.emplace(&event_prob_on, "On-shell events only");
  event_prob_dictionary.emplace(&event_prob_off, "Off-shell events only");
  event_prob_dictionary.emplace(&event_prob_all, "All events");

  for (auto& element : event_prob_dictionary) {
    ratio_plotter.initCanvas();
    ratio_plotter.initLegend();
    ratio_plotter.getAtlasLabel()->setAdditionalInfo(element.second);

    auto& container = element.first;
    auto short_name = container->at(0)->getName();
    short_name.replace(0, 11, "comp_on-off-evtprob");

    for (auto& hist : *container) {
      hist->setIncludeXOverflow();
      hist->setIncludeXUnderflow();
    }
    container->at(0)->setDrawOptions("P E1");
    container->at(0)->setLegendTitle("On-shell LL");
    container->at(0)->setLegendOptions("F");
    container->at(0)->getHist()->SetLineColor(1);
    container->at(0)->getHist()->SetMarkerColor(1);
    container->at(0)->getHist()->SetFillColor(kGray);
    container->at(0)->setDrawOptions("hist");

    container->at(1)->setDrawOptions("P E1 SAME");
    container->at(1)->setLegendTitle("Off-shell LL");
    container->at(1)->getHist()->SetLineColor(2);
    container->at(1)->getHist()->SetMarkerColor(2);

    // container->at(2)->setDrawOptions("P E1 SAME");
    // container->at(2)->setLegendTitle("Comb. LL, 0.869");
    // container->at(2)->getHist()->SetLineColor(4);
    // container->at(2)->getHist()->SetMarkerColor(4);

    auto ratio_container = new HistHolderContainer{*container};
    ratio_container->divideHistograms(*container->at(0));

    ratio_plotter.adjustLabels(container, ratio_container);
    ratio_plotter.addToLegend(*container);

    ratio_plotter.switchToHistPad();
    container->setOptimalMax();
    container->draw();
    ratio_plotter.switchToRatioPad();
    ratio_plotter.drawRatio(ratio_container);
    ratio_plotter.switchToMainPad();
    ratio_plotter.plotAtlasLabel();
    ratio_plotter.plotLegend();
    ratio_plotter.saveToFile(short_name);

    ratio_plotter.initCanvas();
    ratio_plotter.initLegend();
  }
}
}  // namespace studies
}  // namespace plotting
