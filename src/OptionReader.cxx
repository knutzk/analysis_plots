#include "OptionReader.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

namespace plotting {
void OptionReader::addFlag(const std::string& names, const std::string& description) {
  // First register the flag as a normal option, then search for it
  // again and make sure that it does not take any arguments.
  addOption(names, description);
  auto short_name = names;
  while (short_name.find(" ") != std::string::npos) {
    const auto& pos = short_name.find(" ");
    if (short_name.substr(0, pos).size() > 0) {
      short_name = short_name.substr(0, pos);
      break;
    } else {
      short_name = short_name.substr(pos + 1, short_name.size() - pos);
    }
  }
  for (auto& candidate : all_options_) {
    if (short_name == candidate->getName()) {
      candidate->setNeedsArguments(false);
      break;
    }
  }
}

void OptionReader::addOption(const std::string& names, const std::string& desription, const std::string& def_argument) {
  // It is possible to provide multiple names within the string
  // 'names' (i.e. aliases). In a first step, they have to be
  // disentangled. They are separately stored in a vector.
  auto tmp_string = names;
  std::vector<std::string> strings;
  while (tmp_string.find(" ") != std::string::npos) {
    const auto& pos = tmp_string.find(" ");
    if (tmp_string.substr(0, pos).size() > 0) {
      strings.push_back(tmp_string.substr(0, pos));
    }
    tmp_string = tmp_string.substr(pos + 1, tmp_string.size() - pos);
  }
  if (tmp_string.size() > 0) {
    strings.push_back(tmp_string);
  }

  // The first string found within 'names' will now be the main name
  // of the option, all others will be saved as aliases. The strings
  // containing the description and a possible default argument will
  // be saved in the Option object as well. At the end, everything is
  // pushed into the all_options container.
  std::unique_ptr<Option> option{new Option{strings.at(0)}};
  for (const auto& alias : strings) {
    if (alias == strings.front()) continue;  /* skip the first */
    option->addAlias(alias);
  }
  option->setDescription(desription);
  option->setArgument(def_argument);
  option->setDefaultArgument(def_argument);
  all_options_.push_back(std::move(option));
}

std::string OptionReader::getMainArgument(unsigned int i) const {
  if (i > 0 && i <= main_args_.size()) {
    return main_args_.at(i-1);
  } else {
    return 0;
  }
}

std::string OptionReader::getOption(const std::string& name) const {
  for (const auto& option : all_options_) {
    if (name == option->getName()) {
      return option->getArgument();
    }
  }
  return "";
}

void OptionReader::printOptions() const {
  std::cout << "Going to use the following options: " << std::endl;
  for (const auto& option : all_options_) {
    if (option->getNeedsArguments()) {
      std::cout << "  --" << option->getName() << " " << option->getArgument();
      if (!option->getIsMandatory()) {
        std::cout << " (default: " << option->getDefaultArgument() << ")";
      }
      std::cout << std::endl;
    } else {
      if (option->getIsSetByUser()) {
        std::cout << "  --" << option->getName() << std::endl;
      }
    }
  }
}

void OptionReader::setMandatory(const std::string& name) {
  // Before the option can be set to be mandatory, it has to be
  // checked whether this option is registered at all.
  bool does_exist{false};
  for (auto& candidate : all_options_) {
    if (name == candidate->getName()) {
      does_exist = true;
      candidate->setIsMandatory(true);
      break;
    }
  }
  if (!does_exist) {
    std::cout << "Tried to register option \"" << name << "\" as "
              << "mandatory option, but it could not be found."
              << std::endl;
  }
}

bool OptionReader::readCommandLineArguments(int n_args, char *args[]) {
  // First build a proper container, instead of using the crappy
  // C-style arrays that are painful to use.
  std::vector<std::string> bare_strings;
  for (int i = 1; i < n_args; ++i) bare_strings.push_back(args[i]);

  bool is_fine{true};
  // Save the user input from the command line as candidates in a
  // multimap (option type vs. option argument) in order to check them
  // against the registered options afterwards.
  std::multimap<std::string, std::string> candidates;
  for (auto itr = bare_strings.begin(); itr != bare_strings.end(); ++itr) {
    std::string option_type{""};
    std::string option_arg{""};

    if (itr->substr(0,2) == "--") {
      option_type = itr->substr(2, itr->size() - 2);
      if (option_type.size() < 2) is_fine = false;
      const auto& next = std::next(itr);  /* check possible arguments */
      if (next != bare_strings.end() && next->substr(0, 1) != "-") {
        option_arg = *next;
        ++itr;
      }
    } else if (itr->substr(0,1) == "-") {
      option_type = itr->substr(1, itr->size() - 1);
      if (option_type.size() != 1) is_fine = false;
      const auto& next = std::next(itr);  /* check possible arguments */
      if (next != bare_strings.end() && next->substr(0, 1) != "-") {
        option_arg = *next;
        ++itr;
      }
    } else {
      option_type = "main_arg";
      option_arg = *itr;
    }

    if (!is_fine) {
      std::cout << "Something went wrong when trying to read"
                << " the command line input. Please check if" << "\n"
                << "you have accidentally used double-dashed"
                << " instead of single-dashed flags (or vice" << "\n"
                << "versa) and try again."
                << std::endl;
      return false;
    }
    candidates.insert(std::pair<std::string, std::string>(option_type, option_arg));
  }

  // Now check all candidates against the registered options (also
  // against their aliases). If option exists, change the arguments.
  for (const auto& candidate : candidates) {
    bool is_known{false};
    for (auto& known : all_options_) {
      if (known->getName() == candidate.first) is_known = true;
      for (const auto& alias : known->getAliases()) {
        if (alias == candidate.first) is_known = true;
        if (is_known) break;
      }
      if (is_known) {
        if (known->getIsSetByUser()) {  /* avoid double-setting */
          std::cout << "Option \"" << candidate.first << "\" was "
                    << "provided multiple times." << std::endl;
          return false;
        }
        if (candidate.second != "") {  /* don't set empty args */
          known->setArgument(candidate.second);
          known->setIsSetByUser(true);
        }
        if (!known->getNeedsArguments()) {  /* for flags w/o args */
          known->setIsSetByUser(true);
        }
        break;
      }
    }  // for (registered options)

    if (candidate.first == "main_arg") {
      is_known = true;
      main_args_.push_back(candidate.second);
    }

    if (!is_known) {
      std::cout << "Option \"" << candidate.first << "\" is not known within th"
                << "is context." << std::endl;
      return false;
    }
  }  // for (candidates)

  // Check for mandatory arguments.
  for (const auto& known : all_options_) {
    if (known->getIsMandatory() && (known->getArgument() == "")) {
      std::cout << "Option \"" << known->getName() << "\" is declared mandatory"
                << ", so please provide an argument." << std::endl;
      return false;
    }
  }

  // Check for options that don't take arguments.
  for (const auto& known : all_options_) {
    if (!known->getNeedsArguments() && (known->getArgument() != "")) {
      std::cout << "Option \"" << known->getName() << "\" does not take any "
                << "arguments, so please remove it." << std::endl;
      return false;
    }
  }

  // Check for main arguments.
  if (main_args_.size() != n_main_args_requested_) {
    std::cout << "Expected " << n_main_args_requested_ << " main argument";
    if (n_main_args_requested_ > 1) std::cout << "s" << std::endl;
    std::cout << ", but " << main_args_.size() << " were provided."
              << std::endl;
    return false;
  }
  return true;
}
}  // namespace plotting
