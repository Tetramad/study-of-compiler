#include <iostream>
#include <fstream>

#include "lexer.hh"
#include "spl_automata.hh"

auto main(int argc, char *argv[]) -> int {
  if (argc != 2) {
    std::cerr << "run with exactly one source file path." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto source_fs = std::ifstream(argv[1]);
  if (!source_fs.is_open()) {
    std::cerr << "failed to open file \"" << argv[1] << "\"." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  source_fs.unsetf(source_fs.skipws);

  auto tokens = compiler::tokenize(
      std::istream_iterator<char>(source_fs),
      std::istream_iterator<char>(),
      spl_automata{});

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
