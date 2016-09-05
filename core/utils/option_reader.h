/* -*- mode: c++; -*- */
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>

#ifndef OPTIONREADER_H_
#define OPTIONREADER_H_

#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace plotting {
/**
 * A class managing a single option for the OptionReader class. This
 * includes settings such as default arguments, whether the option is
 * mandatory, whether it is set by the user etc.
 */
class Option {
 public:
  /**
   * Construct an option with a certain name. This name may also
   * include different aliases for this option (separated by
   * whitespaces).
   *
   * @param name The name of the option (including aliases)
   */
  inline explicit Option(const std::string& name) : name_{name} {}

  /**
   * Add an alias to the option managed by this class.
   *
   * @param synonym String containing the alias
   */
  inline void addAlias(const std::string& synonym) { aliases_.insert(synonym); }

  //! Get the argument saved for this option.
  inline std::string getArgument() const { return argument_; }
  //! Get the default argument for this option.
  inline std::string getDefaultArgument() const { return default_arg_; }
  //! Get the description of the option.
  inline std::string getDescription() const { return description_; }
  //! Get boolean whether this option is set to be mandatory.
  inline bool getIsMandatory() const { return is_mandatory_; }
  //! Get boolean whether the option has been set by the user.
  inline bool getIsSetByUser() const { return is_set_by_user_; }
  //! Get the name of the option.
  inline std::string getName() const { return name_; }
  //! Get boolean whether this option needs arguments.
  inline bool getNeedsArguments() const { return needs_arguments_; }
  //! Get the set of strings containing all aliases.
  inline std::set<std::string> getAliases() const { return aliases_; }

  //! Set the argument.
  inline void setArgument(std::string s) { argument_ = s; }
  //! Set the default argument.
  inline void setDefaultArgument(std::string s) { default_arg_ = s; }
  //! Set the description.
  inline void setDescription(std::string s) { description_ = s; }
  //! Set whether this option is mandatory.
  inline void setIsMandatory(bool b) { is_mandatory_ = b; }
  //! Set whether it has been set by the user.
  inline void setIsSetByUser(bool b) { is_set_by_user_ = b; }
  //! Set the name.
  inline void setName(std::string s) { name_ = s; }
  //! Set whether the option needs arguments.
  inline void setNeedsArguments(bool b) { needs_arguments_ = b; }
  //! Set the aliases of the option.
  inline void setAliases(std::set<std::string> set) { aliases_ = set; }

 private:
  bool is_mandatory_{false};
  bool is_set_by_user_{false};
  bool needs_arguments_{true};
  std::string argument_{""};
  std::string default_arg_{""};
  std::string description_{""};
  std::string name_{""};
  std::set<std::string> aliases_;
};

/**
 * Class to hold a set of options and read the command line input
 * given by the user. The command line input will be checked with the
 * registered options and the option reader then takes appropriate
 * actions. Options are easily accessible by the user from outside,
 * without having to deal with the Option class.
 */
class OptionReader {
 public:
  /**
   * Add a flag to the list of options.
   *
   * @param names Main name plus optional aliases (separated with spaces)
   * @param description A short description of what the flag does.
   */
  void addFlag(const std::string& names, const std::string& description);

  /**
   * Add an option to the list.
   *
   * @param names Main name plus optional aliases (separated with spaces)
   * @param description A short description of what the option does
   * @param def_argument (Optional) The default argument of the option
   */
  void addOption(const std::string& names, const std::string& description,
                 const std::string& def_argument = "");

  //! Get the main argument i read from the command line.
  std::string getMainArgument(unsigned int i) const;

  //! Get the argument that has been set for a specific option.
  std::string getOption(const std::string& name) const;

  //! Print all registered options to the output.
  void printOptions() const;

  /**
   * Set an option to be mandatory. This means that the option has to
   * be provided by the user including an argument. Otherwise, the
   * readCommandLineArguments() function will fail.
   *
   * @param name The name of the option
   */
  void setMandatory(const std::string& name);

  /**
   * Set the number of main arguments requested as input. This will
   * also be requested within the readCommandLineArguments() function
   * which fails if the number does not fit the requested number.
   *
   * @param number The number of requested arguments
   */
  inline void setNumberOfMainArguments(unsigned const int& number) {
    n_main_args_requested_ = number;
  }

  /**
   * Read the command line input of the user and check it. This will
   * check all options given by the user in terms of ambiguity,
   * missing options, missing arguments, wrong syntax etc. If any of
   * the checks fails, the function will return FALSE.
   *
   * @param n_args The number of command line arguments
   * @param args Pointer to the char* array containing the arguments
   */
  bool readCommandLineArguments(int n_args, char* args[]);

 private:
  std::list<std::unique_ptr<Option>> all_options_;
  std::vector<std::string> main_args_;
  unsigned int n_main_args_requested_{0};
};
}  // namespace plotting

#endif  // OPTIONREADER_H_
