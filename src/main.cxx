// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>

#include <TDirectory.h>
#include <TH1.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "OptionReader.h"
#include "Studies/Likelihood.h"
#include "Studies/MatchBtagPerf.h"
#include "Studies/MatchEfficiencies.h"
#include "Studies/MatchLONLO.h"
#include "Studies/MatchElMu.h"
#include "Studies/MatchOnOff.h"

using ProgMap = std::map<unsigned int, std::string>;

void printOptions(const ProgMap& programs);
void printWelcomeMessage();

int main(int argc, char* argv[]) {
  TH1::AddDirectory(kFALSE);

  ProgMap programs;
  programs[1] = "MatchEfficiencies: evaluate different ttZ+ttbar running modes (matching -- 6 files)";
  programs[2] = "MatchLONLO: evaluate ttbar, ttZ LO, ttZ NLO samples (matching, matrices, kinematics -- 6 files)";
  programs[3] = "MatchElMu: evaluate performance of ejets and mujets samples (matching, matrices -- 2 files)";
  programs[4] = "MatchOnOff: evaluate performance for on, off and combined LL (matching -- 3 files)";
  programs[11] = "MatchBtagPerf (temporary): evaluate performances for fixed and kinematic-dep. b-tagging (2 files)";
  programs[12] = "Likelihood (to be decided)";

  printWelcomeMessage();

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
      study.reset(new plotting::studies::MatchEfficiencies());
      break;
    case 2:
      study.reset(new plotting::studies::MatchLONLO());
      break;
    case 3:
      study.reset(new plotting::studies::MatchElMu());
      break;
    case 4:
      study.reset(new plotting::studies::MatchOnOff());
      break;
    case 11:
      study.reset(new plotting::studies::MatchBtagPerf());
      break;
    case 12:
      study.reset(new plotting::studies::Likelihood());
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

void printWelcomeMessage() {
  std::cout
      << "#                                          _.--\"\"\"--,                       #\n"
      << "#                                        .'          `\\                     #\n"
      << "#      .-\"\"\"\"\"\"-.                      .'              |                    #\n"
      << "#     /          '.                   /            .-._/                    #\n"
      << "#    |             `.                |             |                        #\n"
      << "#     \\              \\          .-._ |          _   \\                       #\n"
      << "#      `\"\"'-.         \\_.-.     \\   `          ( \\__/                       #\n"
      << "#            |             )     '=.       .,   \\                           #\n"
      << "#           /             (         \\     /  \\  /                           #\n"
      << "#         /`               `\\        |   /    `'                            #\n"
      << "#         '..-`\\        _.-. `\\ _.__/   .=.                                 #\n"
      << "#              |  _    / \\  '.-`    `-.'  /                                 #\n"
      << "#              \\_/ |  |   './ _     _  \\.'         W E L C O M E            #\n"
      << "#                   '-'    | /       \\ |                                    #\n"
      << "#                          |  .-. .-.  |              to  the               #\n"
      << "#                          \\ / o| |o \\ /                                    #\n"
      << "#                           |   / \\   |     A N A L Y S I S   P L O T S     #\n"
      << "#                          / `\"`   `\"` \\           p a c k a g e            #\n"
      << "#                         /             \\                                   #\n"
      << "#                        | '._.'         \\                                  #\n"
      << "#                        |  /             |                                 #\n"
      << "#                         \\ |             |                                 #\n"
      << "#      (c) 2016            ||    _    _   /                                 #\n"
      << "#      Knut Zoch           /|\\  (_\\  /_) /                                  #\n"
      << "#   <kzoch@cern.ch>        \\ \\'._  ` '_.'                                   #\n"
      << "#                           `\"\"` `\"\"\"`                                      #\n"
      << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
      << std::endl;
}
