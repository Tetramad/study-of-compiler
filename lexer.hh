#pragma once

#include <sstream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace compiler {

enum token_type : int;
struct token;

template <typename InputIt>
auto tokenize(InputIt first, InputIt last) -> std::vector<token>;
template <typename InputIt>
auto lexer(InputIt first, InputIt last) -> std::tuple<InputIt, token>;

enum token_type : int {
  token_error,
  token_identifier,
  token_keyword,
  token_number,
  token_operator,
  token_delimiter,
};

struct token {
  token_type type;
  std::string text;
};

template <typename InputIt>
auto tokenize(InputIt first, InputIt last) -> std::vector<token> {
  auto tokens = std::vector<token>{};

  while (first != last && std::isspace(*first)) {
    ++first;
  };
  while (first != last) {
    auto [stop_point, token] = lexer(first, last);
    first = stop_point;
    tokens.push_back(token);
    while (first != last && std::isspace(*first)) {
      ++first;
    };
  }

  return tokens;
}

template <typename InputIt>
auto lexer(InputIt first, InputIt last) -> std::tuple<InputIt, token> {
  static auto keywords = std::unordered_set<std::string>{
    "begin", "end", "label", "integer", "goto",
    "if", "then", "else", "fi",
    "output", "input",
  };
  auto text = std::stringstream{};

  if (std::isalpha(*first) || *first == '_') {
    while (first != last && (std::isalnum(*first) || *first == '_')) {
      text << *first;
      ++first;
    }
    if (keywords.find(text.str()) != keywords.end()) {
      return {first, token{token_keyword, text.str()}};
    } else {
      return {first, token{token_identifier, text.str()}};
    }
  }

  if (std::isdigit(*first)) {
    while (first != last && std::isdigit(*first)) {
      text << *first;
      ++first;
    }
    return {first, token{token_number, text.str()}};
  }

  if (*first == '<') {
    text << *first;
    ++first;
    return {first, token{token_operator, text.str()}};
  }

  if (*first == '>') {
    text << *first;
    ++first;
    return {first, token{token_operator, text.str()}};
  }

  if (*first == '=') {
    text << *first;
    ++first;
    if (first != last && *first == '>') {
      text << *first;
      ++first;
      return {first, token{token_delimiter, text.str()}};
    } else {
      return {first, token{token_operator, text.str()}};
    }
  }

  if (*first == '+') {
    text << *first;
    ++first;
    return {first, token{token_operator, text.str()}};
  }

  if (*first == '-') {
    text << *first;
    ++first;
    return {first, token{token_operator, text.str()}};
  }

  if (*first == '*') {
    text << *first;
    ++first;
    return {first, token{token_operator, text.str()}};
  }

  if (*first == '/') {
    text << *first;
    ++first;
    return {first, token{token_operator, text.str()}};
  }

  if (*first == ',') {
    text << *first;
    ++first;
    return {first, token{token_delimiter, text.str()}};
  }

  if (*first == '.') {
    text << *first;
    ++first;
    return {first, token{token_delimiter, text.str()}};
  }

  if (*first == ';') {
    text << *first;
    ++first;
    return {first, token{token_delimiter, text.str()}};
  }

  if (*first == ':') {
    text << *first;
    ++first;
    return {first, token{token_delimiter, text.str()}};
  }

  if (*first == '(') {
    text << *first;
    ++first;
    return {first, token{token_delimiter, text.str()}};
  }

  if (*first == ')') {
    text << *first;
    ++first;
    return {first, token{token_delimiter, text.str()}};
  }

  text << *first;
  ++first;
  while (first != last && !std::isspace(*first) && !std::isalnum(*first) &&
      std::string{"_<>=+-*/,.;:()"}.find(*first) == std::string::npos) {
    text << *first;
    ++first;
  }
  return {first, token{token_error, text.str()}};
}

} // compiler
