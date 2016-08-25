/* -*- mode: c++; -*- */
#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>

/**
 * @brief A class holding information about a specific Option, i.e. possible
 * aliases, default arguments, whether it is mandatory etc.
 */
namespace plotting {
class Option {
 public:
  inline explicit Option(const std::string& name) : name_{name} {}

  inline void addAlias(const std::string& synonym) {
    aliases_.insert(synonym);
  }

  inline std::string getArgument() const { return argument_; }
  inline std::string getDefaultArgument() const { return default_arg_; }
  inline std::string getDescription() const { return description_; }
  inline bool getIsMandatory() const { return is_mandatory_; }
  inline bool getIsSetByUser() const { return is_set_by_user_; }
  inline std::string getName() const { return name_; }
  inline bool getNeedsArguments() const { return needs_arguments_; }
  inline std::set<std::string> getAliases() const { return aliases_; }

  inline void setArgument(std::string s) { argument_ = s; }
  inline void setDefaultArgument(std::string s) { default_arg_ = s; }
  inline void setDescription(std::string s) { description_ = s; }
  inline void setIsMandatory(bool b) { is_mandatory_ = b; }
  inline void setIsSetByUser(bool b) { is_set_by_user_ = b; }
  inline void setName(std::string s) { name_ = s; }
  inline void setNeedsArguments(bool b) { needs_arguments_ = b; }
  inline void setAliases(std::set<std::string> set) { aliases_ = set; }

 protected:
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
 * @brief A class to hold a set of options, read the command line input given
 * by the user, check it with the registered options and take appropriate
 * actions.
 */
class OptionReader {
 public:
  /**
   * @brief Add a flag to the list.
   * @param name Main name plus optional aliases (separated with spaces).
   * @param description A short description of what the flag does.
   */
  void addFlag(const std::string& names, const std::string& description);

  /**
   * @brief Add an option to the list.
   * @param name Main name plus optional aliases (separated with spaces).
   * @param description A short description of what the option does.
   * @param def_argument (Optional) The default argument of the option.
   */
  void addOption(const std::string& names, const std::string& description,
                 const std::string& def_argument = "");

  /**
   * @brief Return the main argument i
   * @param int The number of the main argument to be return
   * @param string The main argument
   */
  std::string getMainArgument(unsigned int i) const;

  /**
   * @brief Get the argument saved for a specific option.
   * @param name Name of the option
   * @return string String containing the argument (either set by default
   * or overwritten by the user).
   */
  std::string getOption(const std::string& name) const;

  /**
   * @brief Print all the registered options to the output.
   */
  void printOptions() const;

  /**
   * @brief Set an option to be mandatory, i.e. is has to be provided by the
   * user including an argument.
   * @param name Name of the option
   */
  void setMandatory(const std::string& name);

  /**
   * @brief Set the number of main arguments requested as input.
   * @param unsigned int Number of requested arguments
   */
  inline void setNumberOfMainArguments(unsigned const int& number) {
    n_main_args_requested_ = number;
  }

  /**
   * @brief Read the command line input of the user and check it.
   * @param int The number of command line arguments
   * @param Pointer to the char* array containing the arguments
   */
  bool readCommandLineArguments(int n_args, char* args[]);

 protected:
  /* The list of options that is currently registered */
  std::list<std::unique_ptr<Option>> all_options_;

  /* The list of main arguments that was given by the user */
  std::vector<std::string> main_args_;

  /* The number of main arguments requested by the program */
  unsigned int n_main_args_requested_{0};
};
}  // namespace plotting
