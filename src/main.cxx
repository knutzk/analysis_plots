// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>

#include <TDirectory.h>
#include <TH1.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "OptionReader.h"
#include "Studies/Jets.h"
#include "Studies/Likelihood.h"
#include "Studies/MatchBtagPerf.h"
#include "Studies/MatchEfficiencies.h"
#include "Studies/MatchLONLO.h"
#include "Studies/MatchElMu.h"
#include "Studies/MatchOnOff.h"

using ProgMap = std::map<unsigned int, std::string>;

void printOptions(const ProgMap& programs);

int main(int argc, char* argv[]) {
  TH1::AddDirectory(kFALSE);

  ProgMap programs;
  programs[1] = "Jets: produce jet kinematics ratio plots";
  programs[2] = "Likelihood: produce LL ratio plots";
  programs[3] = "MatchEfficiencies: produce ttz/tt matching plots";
  programs[5] = "MatchBtagPerf: evaluate b-tagging performances";
  programs[6] = "MatchLONLO: evaluate LO and NLO samples";
  programs[7] = "MatchElMu: evaluate ejets and mujets samples";
  programs[8] = "MatchOnOff: compare the matching of on, off and all events for on, off and combined LL";

  plotting::OptionReader option_reader;
  option_reader.addOption("mode m", "The running mode of the program");
  option_reader.setMandatory("mode");
  option_reader.setNumberOfMainArguments(1);
  if (!option_reader.readCommandLineArguments(argc, argv)) {
    printOptions(programs);
    return -1;
  }

  const auto& input_file = option_reader.getMainArgument(1);
  const auto& mode_string = option_reader.getOption("mode");
  unsigned int mode{0};
  try {
    mode = std::stoi(mode_string);
  } catch (std::invalid_argument t) {
    std::cout << "The running mode of the program has to be given as a positive integer. Please\n"
              << "try again and choose from the options below."
              << std::endl;
    printOptions(programs);
    return -1;
  }
  
  std::unique_ptr<plotting::studies::Template> study{nullptr};
  switch (mode) {
    case 1:
      study.reset(new plotting::studies::Jets());
      break;
    case 2:
      study.reset(new plotting::studies::Likelihood());
      break;
    case 3:
      study.reset(new plotting::studies::MatchEfficiencies());
      break;
    case 5:
      study.reset(new plotting::studies::MatchBtagPerf());
      break;
    case 6:
      study.reset(new plotting::studies::MatchLONLO());
      break;
    case 7:
      study.reset(new plotting::studies::MatchElMu());
    case 8:
      study.reset(new plotting::studies::MatchOnOff());
      break;
    default:
      std::cout << "Option " << mode
                << " is not known. Please choose from the options below."
                << std::endl;
      printOptions(programs);
      return -1;
  }

  study->loadFiles(input_file);
  study->execute();
  return 0;
}

void printOptions(const ProgMap& programs) {
  std::cout << std::endl;
  std::cout << "Possible plotting options:" << std::endl;
  for (const auto& entry : programs) {
    std::cout << "  (" << entry.first;
    std::cout << ") " << entry.second << std::endl;
  }
}
