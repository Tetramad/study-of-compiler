#pragma once

#include <iterator>
#include <vector>

namespace compiler {

template <typename InputIt, typename Automata>
auto tokenize(InputIt first, InputIt last, Automata automata) -> std::vector<typename Automata::token_type> {
  auto tokens = std::vector<typename Automata::token_type>{};
  while (first != last) {
    first = automata(first, last, std::back_inserter(tokens));
  }
  return tokens;
}

} // compiler
