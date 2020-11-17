#include "lexer.hh"
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <utility>

namespace compiler {

auto str2kw_lut = std::unordered_map<std::string, kw>{
  { "begin", kw::kw_begin },
  { "end", kw::kw_end },
  { "label", kw::kw_label },
  { "integer", kw::kw_integer },
  { "goto", kw::kw_goto },
  { "if", kw::kw_if },
  { "then", kw::kw_then },
  { "else", kw::kw_else },
  { "fi", kw::kw_fi },
  { "output", kw::kw_output },
  { "input", kw::kw_input },
};

auto lexer::tokenize(std::string_view sv) -> std::vector<token> {
  auto it = sv.begin();
  auto end = sv.end();
  auto tokens = std::vector<token>{};

  while (it != end) {
    auto chr = *it;
    auto ss = std::stringstream{};
    if (std::isspace(chr)) {
      ++it;
    } else if (std::isalpha(chr) || chr == '_') {
      ss << chr;
      ++it;
      while (it != end && (std::isalnum(*it) || chr == '_')) {
        ss << *it;
        ++it;
      }
      if (auto found = str2kw_lut.find(ss.str()); found != str2kw_lut.end()) {
        tokens.emplace_back(found->second);
      } else {
        tokens.emplace_back(token{std::in_place_index<0>, ss.str()});
      }
    } else if (std::isdigit(chr)) {
      ss << chr;
      ++it;
      while (it != end && std::isdigit(*it)) {
        ss << *it;
        ++it;
      }
      tokens.push_back(token{std::in_place_index<1>, ss.str()});
    } else if (chr == '<') {
      tokens.emplace_back(op::op_less);
      ++it;
    } else if (chr == '>') {
      tokens.emplace_back(op::op_greater);
      ++it;
    } else if (chr == '=') {
      ++it;
      if (it != end && *it == '>') {
        tokens.emplace_back(delim::delim_assign);
        ++it;
      } else {
        tokens.emplace_back(op::op_equal);
      }
    } else if (chr == '+') {
      tokens.emplace_back(op::op_plus);
      ++it;
    } else if (chr == '-') {
      tokens.emplace_back(op::op_minus);
      ++it;
    } else if (chr == '*') {
      tokens.emplace_back(op::op_asterisk);
      ++it;
    } else if (chr == '/') {
      tokens.emplace_back(op::op_slash);
      ++it;
    } else if (chr == ',') {
      tokens.emplace_back(delim::delim_comma);
      ++it;
    } else if (chr == '.') {
      tokens.emplace_back(delim::delim_period);
      ++it;
    } else if (chr == ';') {
      tokens.emplace_back(delim::delim_semicolon);
      ++it;
    } else if (chr == ':') {
      tokens.emplace_back(delim::delim_colon);
      ++it;
    } else if (chr == '(') {
      tokens.emplace_back(delim::delim_open_paren);
      ++it;
    } else if (chr == ')') {
      tokens.emplace_back(delim::delim_close_paren);
      ++it;
    } else {
      std::cerr << "error\"" << chr;
      ++it;
      while (it != end && !std::isspace(*it) && !std::isalnum(*it) &&
          std::string{"_<>=+-*/,.;:()"}.find(*it) == std::string::npos) {
        std::cerr << *it;
        ++it;
      }
      std::cerr << '"' << std::endl;
    }
  }
  return tokens;
}

}
