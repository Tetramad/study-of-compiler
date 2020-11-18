#pragma once

#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

enum token_type {
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

struct spl_automata {
  using token_type = token;
  using InputIt = std::istream_iterator<char>;
  using OutputIt = std::back_insert_iterator<std::vector<token>>;

  static std::unordered_set<std::string> keywords;

  auto operator()(InputIt first, InputIt last, OutputIt d_first) -> InputIt;
};
