#include <sstream>

#include "spl_automata.hh"

auto spl_automata::operator()(InputIt first, InputIt last, OutputIt d_first) -> InputIt {
  auto text = std::stringstream{};

  if (std::isspace(*first)) {
    while (first != last && std::isspace(*first)) {
      ++first;
    }
    return first;
  }

  if (std::isalpha(*first) || *first == '_') {
    while (first != last && (std::isalnum(*first) || *first == '_')) {
      text << *first;
      ++first;
    }
    if (keywords.find(text.str()) != keywords.end()) {
      *d_first = token{token_keyword, text.str()};
      return first;
    } else {
      *d_first = token{token_identifier, text.str()};
      return first;
    }
  }

  if (std::isdigit(*first)) {
    while (first != last && std::isdigit(*first)) {
      text << *first;
      ++first;
    }
    *d_first = token{token_number, text.str()};
    return first;
  }

  if (*first == '<') {
    text << *first;
    ++first;
    *d_first = token{token_operator, text.str()};
    return first;
  }

  if (*first == '>') {
    text << *first;
    ++first;
    *d_first = token{token_operator, text.str()};
    return first;
  }

  if (*first == '=') {
    text << *first;
    ++first;
    if (first != last && *first == '>') {
      text << *first;
      ++first;
      *d_first = token{token_delimiter, text.str()};
      return first;
    } else {
      *d_first = token{token_operator, text.str()};
      return first;
    }
  }

  if (*first == '+') {
    text << *first;
    ++first;
    *d_first = token{token_operator, text.str()};
    return first;
  }

  if (*first == '-') {
    text << *first;
    ++first;
    *d_first = token{token_operator, text.str()};
    return first;
  }

  if (*first == '*') {
    text << *first;
    ++first;
    *d_first = token{token_operator, text.str()};
    return first;
  }

  if (*first == '/') {
    text << *first;
    ++first;
    *d_first = token{token_operator, text.str()};
    return first;
  }

  if (*first == ',') {
    text << *first;
    ++first;
    *d_first = token{token_delimiter, text.str()};
    return first;
  }

  if (*first == '.') {
    text << *first;
    ++first;
    *d_first = token{token_delimiter, text.str()};
    return first;
  }

  if (*first == ';') {
    text << *first;
    ++first;
    *d_first = token{token_delimiter, text.str()};
    return first;
  }

  if (*first == ':') {
    text << *first;
    ++first;
    *d_first = token{token_delimiter, text.str()};
    return first;
  }

  if (*first == '(') {
    text << *first;
    ++first;
    *d_first = token{token_delimiter, text.str()};
    return first;
  }

  if (*first == ')') {
    text << *first;
    ++first;
    *d_first = token{token_delimiter, text.str()};
    return first;
  }

  text << *first;
  ++first;
  while (first != last && !std::isspace(*first) && !std::isalnum(*first) &&
      std::string{"_<>=+-*/,.;:()"}.find(*first) == std::string::npos) {
    text << *first;
    ++first;
  }
  *d_first = token{token_error, text.str()};
  return first;
}

std::unordered_set<std::string> spl_automata::keywords = {
  "begin", "end", "label", "integer", "goto",
  "if", "then", "else", "fi",
  "output", "input",
};
