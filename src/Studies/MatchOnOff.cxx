// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#include "Studies/MatchOnOff.h"

#include <TColor.h>
#include <TROOT.h>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include "MatrixHolderContainer.h"
#include "HistHolderContainer.h"
#include "HistPlotter.h"
#include "MatrixPlotter.h"
#include "RatioPlotter.h"

namespace plotting {
namespace studies {
void MatchOnOff::loadFiles(const std::string& input_list) {
  file_container_.readFileList(input_list);
  if (file_container_.size() != 3) {
    std::cout << "\nERROR: expected three files in the input list. "
              << "Aborting ... " << std::endl;
    throw;
  }
}

void MatchOnOff::execute() {
  plotting::HistPlotter plotter;
  plotter.setOutputDir("$HOME/AnalysisPlots/plots/MatchOnOff/");

  plotting::HistHolderContainer hists_on{file_container_, "h_andreacomp_onshell"};
  plotting::HistHolderContainer hists_off{file_container_, "h_andreacomp_offshell"};
  plotting::HistHolderContainer hists_all{file_container_, "h_andreacomp"};

  std::list<HistHolderContainer> hist_container_list = {hists_on, hists_off, hists_all}; 

  for (auto& container : hist_container_list) {
    plotter.initCanvas(800, 600);
    plotter.initLegend();

    if (container.at(0)->getName() == "h_andreacomp_onshell") {
      plotter.getAtlasLabel()->setAdditionalInfo("On-shell events only");
    } else if (container.at(0)->getName() == "h_andreacomp_offshell") {
      plotter.getAtlasLabel()->setAdditionalInfo("Off-shell events only");
    } else if (container.at(0)->getName() == "h_andreacomp") {
      plotter.getAtlasLabel()->setAdditionalInfo("All events");
    }

    for (int i = 0; i < 3; ++i) {
      if (i == 0) {
        container.at(i)->setLegendTitle("On-shell LL");
        container.at(i)->getHist()->SetLineColor(kBlue);
        container.at(i)->getHist()->SetMarkerColor(kBlue);
      } else if (i == 1) {
        container.at(i)->setLegendTitle("Off-shell LL");
        container.at(i)->getHist()->SetLineColor(kRed);
        container.at(i)->getHist()->SetMarkerColor(kRed);
      } else if (i == 2) {
        container.at(i)->setLegendTitle("Combined LL, 0.882");
        container.at(i)->getHist()->SetLineColor(kGreen + 2);
        container.at(i)->getHist()->SetMarkerColor(kGreen + 2);
      }
      container.at(i)->setDrawOptions("P E1 SAME");
      container.at(i)->setLegendOptions("PL");
      container.at(i)->getHist()->GetXaxis()->SetLabelSize(16);
    }
    container.setOptimalMax();
    container.draw();
    plotter.addToLegend(container);
    plotter.plotAtlasLabel();
    plotter.plotLegend();
    plotter.saveToFile(container.at(0)->getName());
    plotter.resetCanvas();
    plotter.resetLegend();
  }
}
}  // namespace studies
}  // namespace plotting
