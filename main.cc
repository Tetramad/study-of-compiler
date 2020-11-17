#include <iostream>

#include "lexer.hh"

auto source_code = std::string{R"(
begin
  integer N, min, max, now, idx;
  label getInput;

  input => N;
  0 => idx;
  0 => max;
  2147483647 => min;

getInput:
  input => now;
  idx + 1 => idx;

  if now > max then
    now => max
  fi;

  if now < min then
    now => min
  fi;

  if idx < N then
    goto getInput
  fi;

  output(min, max)
end.
)"};

auto main() -> int {
  using compiler::tokenize;

  auto tokens = tokenize(source_code.begin(), source_code.end());

  for (auto const &token : tokens) {
    switch (token.type) {
      using namespace compiler;
      case token_identifier:
        std::cout << "identifier  ";
        break;
      case token_keyword:
        std::cout << "keyword     ";
        break;
      case token_number:
        std::cout << "number      ";
        break;
      case token_operator:
        std::cout << "operator    ";
        break;
      case token_delimiter:
        std::cout << "delimiter   ";
        break;
      defualt:
        std::cout << "error       ";
    }
    std::cout << token.text << '\n';
  }
}
