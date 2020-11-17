#include <iostream>
#include <string>
#include <string_view>
#include <cctype>
#include <unordered_set>
#include <sstream>

using std::string_literals::operator""s;
auto keyword_table = std::unordered_set{
  "begin"s, "end"s,
  "label"s, "integer"s,
  "goto"s,
  "if"s, "then"s, "else"s,"fi"s,
  "output"s, "input"s,
};

auto tokenize(std::string_view input) -> void;

auto main() -> int {
  auto input = std::string{};

  for (;;) {
    std::cout << ">> " << std::flush;
    std::getline(std::cin, input);
    if (std::cin.eof() || std::cin.fail()) {
      break;
    }
    tokenize(input);
  }
}

auto tokenize(std::string_view input) -> void {
  auto it = input.begin();
  auto end = input.end();

  while (it != end) {
    auto chr = *it;
    if (std::isspace(chr)) {
      ++it;
    } else if (std::isalpha(chr) || chr == '_') {
      auto ss = std::stringstream{};
      ss << chr;
      ++it;
      while (it != end && (std::isalnum(*it) || chr == '_')) {
        ss << *it;
        ++it;
      }
      if (keyword_table.find(ss.str()) == keyword_table.end()) {
        std::cout << "id\"" << ss.str() << '"' << std::endl;
      } else {
        std::cout << "keyword\"" << ss.str() << '"' << std::endl;
      }
    } else if (std::isdigit(chr)) {
      std::cout << "number\"" << chr;
      ++it;
      while (it != end && std::isdigit(*it)) {
        std::cout << *it;
        ++it;
      }
      std::cout << '"' << std::endl;
    } else if (chr == '<') {
      std::cout << "operator\"<\"" << std::endl;
      ++it;
    } else if (chr == '>') {
      std::cout << "operator\">\"" << std::endl;
      ++it;
    } else if (chr == '=') {
      ++it;
      if (it != end && *it == '>') {
        std::cout << "delimiter\"=>\"" << std::endl;
        ++it;
      } else {
        std::cout << "operator\"=\"" << std::endl;
      }
    } else if (chr == '+') {
      std::cout << "operator\"+\"" << std::endl;
      ++it;
    } else if (chr == '-') {
      std::cout << "operator\"-\"" << std::endl;
      ++it;
    } else if (chr == '*') {
      std::cout << "operator\"*\"" << std::endl;
      ++it;
    } else if (chr == '/') {
      std::cout << "operator\"/\"" << std::endl;
      ++it;
    } else if (chr == ',') {
      std::cout << "delimiter\",\"" << std::endl;
      ++it;
    } else if (chr == '.') {
      std::cout << "delimiter\".\"" << std::endl;
      ++it;
    } else if (chr == ';') {
      std::cout << "delimiter\";\"" << std::endl;
      ++it;
    } else if (chr == ':') {
      std::cout << "delimiter\":\"" << std::endl;
      ++it;
    } else if (chr == '(') {
      std::cout << "delimiter\"(\"" << std::endl;
      ++it;
    } else if (chr == ')') {
      std::cout << "delimiter\")\"" << std::endl;
      ++it;
    } else {
      std::cout << "error\"" << chr;
      ++it;
      while (it != end && !std::isspace(*it) && !std::isalnum(*it) &&
          std::string{"_<>=+-*/,.;:()"}.find(*it) == std::string::npos) {
        std::cout << *it;
        ++it;
      }
      std::cout << '"' << std::endl;
    }
  }
}
