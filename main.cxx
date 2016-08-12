// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>

#include <TDirectory.h>
#include <TH1.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "Studies/Jets.h"
#include "Studies/Likelihood.h"
#include "Studies/MatchBtagPerf.h"
#include "Studies/MatchEfficiencies.h"
#include "Studies/MatchJetMatrices.h"
#include "Studies/MatchLONLO.h"

using ProgMap = std::map<unsigned int, std::string>;

bool checkArguments(const int& number);
void printOptions(const ProgMap& programs);

int main(int argc, char* argv[]) {
  TH1::AddDirectory(kFALSE);
  if (!checkArguments(argc)) return -1;

  ProgMap programs;
  programs[1] = "Jets: produce jet kinematics ratio plots";
  programs[2] = "Likelihood: produce LL ratio plots";
  programs[3] = "MatchEfficiencies: produce ttz/tt matching plots";
  programs[4] = "MatchJetMatrices: produce ttz/tt jet matching matrices";
  programs[5] = "MatchBtagPerf: evaluate b-tagging performances";
  programs[6] = "MatchLONLO: evaluate LO and NLO samples";
  printOptions(programs);

  int chosen{0};
  std::cout << "Please choose: ";
  std::cin >> chosen;

  std::unique_ptr<plotting::studies::Template> study{nullptr};
  switch (chosen) {
    case 1:
      study.reset(new plotting::studies::Jets());
      break;
    case 2:
      study.reset(new plotting::studies::Likelihood());
      break;
    case 3:
      study.reset(new plotting::studies::MatchEfficiencies());
      break;
    case 4:
      study.reset(new plotting::studies::MatchJetMatrices());
      break;
    case 5:
      study.reset(new plotting::studies::MatchBtagPerf());
      break;
    case 6:
      study.reset(new plotting::studies::MatchLONLO());
      break;
    default:
      return -1;
  }

  study->loadFiles(argv[1]);
  study->execute();
  return 0;
}

bool checkArguments(const int& number) {
  if (number < 2) {
    std::cout << "Don't know which input file to use. Exiting" << std::endl;
    std::cout << "Usage: plot [input-list]" << std::endl;
  } else if (number > 2) {
    std::cout << "Too many arguments. Exiting" << std::endl;
    std::cout << "Usage: plot [input-list]" << std::endl;
  } else {
    return true;
  }
}

void printOptions(const ProgMap& programs) {
  std::cout << "Possible plotting options:" << std::endl;
  for (const auto& entry : programs) {
    std::cout << "  (" << entry.first;
    std::cout << ") " << entry.second << std::endl;
  }
}
