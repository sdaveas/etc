#include <regex>

class Regex {
public:
  Regex(std::string regex_str) : m_regex(regex_str) {}

  std::string const replace(const std::string &buffer, std::string format) {
    return std::regex_replace(buffer, m_regex, format);
  }

  std::regex &regex() { return m_regex; }

private:
  std::regex m_regex;
};
